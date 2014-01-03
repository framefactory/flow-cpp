// -----------------------------------------------------------------------------
//  File        MessageTarget.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/MessageTarget.h"
#include "FlowCore/MessageDispatcher.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FMessageTarget
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FMessageTarget, FInstance);

// Constructors and destructor -------------------------------------------------

FMessageTarget::FMessageTarget(const FUniqueId& id,
	                           FMessageTarget* pMaster /* = NULL */)
: FInstance(id, pMaster),
  m_pMessageDispatcher(NULL)
{
}

FMessageTarget::FMessageTarget(const FUniqueId& id,
	                           const wstring_t& name,
							   FMessageTarget* pMaster /* = NULL */)
: FInstance(id, name, pMaster),
  m_pMessageDispatcher(NULL)
{
}

FMessageTarget::~FMessageTarget()
{
}

// Public commands -------------------------------------------------------------

bool FMessageTarget::sendMessage(FMessage* pMessage)
{
	F_ASSERT(pMessage);

	if (!m_pMessageDispatcher)
	{
		delete pMessage;
		return false;
	}

	return m_pMessageDispatcher->sendMessage(pMessage);
}

void FMessageTarget::serialize(FArchive& ar)
{
	FInstance::serialize(ar);

	if (ar.isReading())
		m_pMessageDispatcher = NULL;
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FMessageTarget::dump(std::wostream& stream) const
{
	FInstance::dump(stream);
	stream << "\n--- FMessageTarget ---";
}
#endif

// -----------------------------------------------------------------------------