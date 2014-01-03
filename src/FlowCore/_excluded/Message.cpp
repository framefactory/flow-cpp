// -----------------------------------------------------------------------------
//  File        Message.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/Message.h"
#include "FlowCore/Archive.h"

#include <sstream>

// -----------------------------------------------------------------------------
//  Class FMessage
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FMessage, FObject);

// Constructors and destructor -------------------------------------------------

FMessage::FMessage(const FUniqueId& receiver)
: m_receiver(receiver)
{
}

FMessage::FMessage(const FUniqueId& sender, const FUniqueId& receiver)
: m_sender(sender),
  m_receiver(receiver)
{
}

FMessage::~FMessage()
{
}

// Public commands -------------------------------------------------------------

void FMessage::serialize(FArchive& ar)
{
	if (ar.isReading())
	{
		ar >> m_sender;
		ar >> m_receiver; 
	}
	else // isWriting
	{
		ar << m_sender;
		ar << m_receiver; 
	}
}

// Public queries --------------------------------------------------------------

wstring_t FMessage::toString() const
{
	std::wostringstream stream;
	stream << FObject::toString() << L"R: " << receiver() << L", P: " << priority();
	return stream.str();
}

#ifdef FLOW_DEBUG
void FMessage::dump(std::wostream& stream) const
{
	FObject::dump(stream);
	stream << "\n--- FMessage ---";
	stream << "\n     Sender: " << sender();
	stream << "\n     Receiver: " << receiver();
	stream << "\n     Priority: " << priority();
}
#endif

// -----------------------------------------------------------------------------