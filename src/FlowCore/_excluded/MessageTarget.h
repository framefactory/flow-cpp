// -----------------------------------------------------------------------------
//  File        MessageTarget.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MESSAGETARGET_H
#define FLOWCORE_MESSAGETARGET_H

#include "FlowCore/Library.h"
#include "FlowCore/Instance.h"

#include <iosfwd>

class FArchive;
class FMessage;
class FMessageDispatcher;

// -----------------------------------------------------------------------------
//  Class FMessageTarget
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FMessageTarget : public FInstance
{
	F_DECLARE_ABSTRACT_SERIALIZABLE(FMessageTarget);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a message target that references the given master.
	FMessageTarget(const FUniqueId& id, FMessageTarget* pMaster = NULL);
	/// Creates a named message target that references the given master.
	FMessageTarget(const FUniqueId& id, const wstring_t& name, FMessageTarget* pMaster = NULL);
	/// Virtual destructor.
	virtual ~FMessageTarget();

	//  Public commands ----------------------------------------------

	/// Delivers an incoming message to this object.
	bool processMessage(FMessage* pMessage);
	/// Sends an outgoing message to the registered dispatcher.
	bool sendMessage(FMessage* pMessage);
	/// Sets the dispatcher used to send outgoing messages.
	void setMessageDispatcher(FMessageDispatcher* pDispatcher);

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the dispatcher used to send outgoing messages.
	FMessageDispatcher* messageDispatcher() const { return m_pMessageDispatcher; }

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overridables -------------------------------------------------

	virtual bool onProcessMessage(FMessage* pMessage) = 0;

	//  Internal data members ----------------------------------------

private:
	FMessageDispatcher* m_pMessageDispatcher;
};

// Inline members --------------------------------------------------------------

inline bool FMessageTarget::processMessage(FMessage* pMessage)
{
	return onProcessMessage(pMessage);
}

inline void FMessageTarget::setMessageDispatcher(FMessageDispatcher* pDispatcher)
{
	m_pMessageDispatcher = pDispatcher;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_MESSAGETARGET_H