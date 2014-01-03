// -----------------------------------------------------------------------------
//  File        MessageDispatcher.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/MessageDispatcher.h"
#include "FlowCore/MessageTarget.h"
#include "FlowCore/ObjectRegistry.h"
#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

// -----------------------------------------------------------------------------
//  Class FMessageDispatcher
// -----------------------------------------------------------------------------

F_IMPLEMENT_TYPEINFO(FMessageDispatcher, FNamedObject);

// Constructors and destructor -------------------------------------------------

FMessageDispatcher::FMessageDispatcher()
{
	m_pQueueAccess = new boost::mutex();
}

FMessageDispatcher::FMessageDispatcher(const FUniqueId& systemId)
: FNamedObject(systemId)
{
	m_pQueueAccess = new boost::mutex();
}

FMessageDispatcher::~FMessageDispatcher()
{
	{
		boost::lock_guard<boost::mutex> lock(*m_pQueueAccess);

		while (!m_messageQueue.empty())
		{
			delete m_messageQueue.top();
			m_messageQueue.pop();
		}
	}

	F_SAFE_DELETE(m_pQueueAccess);
}

// Public commands -------------------------------------------------------------

void FMessageDispatcher::postMessage(FMessage* pMessage)
{
	F_ASSERT(pMessage);

	if (!onPostMessage(pMessage))
		_queueMessage(pMessage);
}

bool FMessageDispatcher::sendMessage(FMessage* pMessage)
{
	F_ASSERT(pMessage);

	if (!onSendMessage(pMessage))
	{
		delete pMessage;
		return false;
	}

	return true;
}

bool FMessageDispatcher::processMessages()
{
	if (messageCount() == 0)
		return false;

	while (FMessage* pMessage = _dequeueMessage())
	{
		onProcessMessage(pMessage);
		delete pMessage;
	}

	return true;
}

bool FMessageDispatcher::processMessages(size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		FMessage* pMessage = _dequeueMessage();
		if (!pMessage)
			return false;

		onProcessMessage(pMessage);
		delete pMessage;
	}

	return true;
}

// Public queries --------------------------------------------------------------

size_t FMessageDispatcher::messageCount() const
{
	boost::lock_guard<boost::mutex> lock(*m_pQueueAccess);
	return m_messageQueue.size();
}

FMessageTarget* FMessageDispatcher::findTarget(const FUniqueId& id) const
{
	FNamedObject* pObject = FObjectRegistry::instance()->find(id);
	if (pObject)
		return pObject->castTo<FMessageTarget>();
	
	return NULL;
}

bool FMessageDispatcher::hasTarget(const FMessageTarget* pTarget) const
{
	F_ASSERT(pTarget);
	return (findTarget(pTarget->id()) != NULL);
}

#ifdef FLOW_DEBUG
void FMessageDispatcher::dump(std::wostream& stream) const
{
	FNamedObject::dump(stream);
	stream << "\n--- FMessageDispatcher ---";
	stream << "\n     Pending messages:   " << messageCount();
}
#endif

// Overridables ----------------------------------------------------------------

bool FMessageDispatcher::onPostMessage(FMessage* pMessage)
{
	return true;
}

bool FMessageDispatcher::onSendMessage(FMessage* pMessage)
{
	return false;
}

bool FMessageDispatcher::onProcessMessage(FMessage* pMessage)
{
	FMessageTarget* pTarget = findTarget(pMessage->receiver());

	if (pTarget)
	{
		if (pTarget->processMessage(pMessage))
			return true;

		F_DEBUG("FMessageDispatcher")
			<< "Message not processed: " << pMessage->toString();
	}
	else
	{
		F_DEBUG("FMessageDispatcher")
			<< "Message target not found: " << pMessage->toString();
	}

	return false;
}

// Internal functions ----------------------------------------------------------

void FMessageDispatcher::_queueMessage(FMessage* pMessage)
{
	boost::lock_guard<boost::mutex> lock(*m_pQueueAccess);
	m_messageQueue.push(pMessage);
}

FMessage* FMessageDispatcher::_dequeueMessage()
{
	boost::lock_guard<boost::mutex> lock(*m_pQueueAccess);

	if (m_messageQueue.empty())
		return NULL;

	FMessage* pMessage = m_messageQueue.top();
	m_messageQueue.pop();
	return pMessage;
}

// -----------------------------------------------------------------------------