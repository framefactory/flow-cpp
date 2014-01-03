// -----------------------------------------------------------------------------
//  File        Message.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MESSAGE_H
#define FLOWCORE_MESSAGE_H

#include "FlowCore/Library.h"
#include "FlowCore/Object.h"
#include "FlowCore/UniqueId.h"
#include "FlowCore/MessagePriority.h"

class FArchive;

// -----------------------------------------------------------------------------
//  Class FMessage
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FMessage : public FObject
{
	F_DECLARE_ABSTRACT_SERIALIZABLE(FMessage);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a message for the given receiver.
	FMessage(const FUniqueId& receiver);
	/// Creates a message with the given receiver and sender.
	FMessage(const FUniqueId& sender, const FUniqueId& receiver);
	/// Virtual destructor.
	virtual ~FMessage();

	//  Public commands ----------------------------------------------

public:
	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the receiver object for this message.
	const FUniqueId& receiver() const { return m_receiver; }
	/// Returns the sender of this message.
	const FUniqueId& sender() const { return m_sender; }
	
	/// Returns the priority of this message.
	/// Override to change the priority in derived classes.
	virtual FMessagePriority priority() const {
		return FMessagePriority::Normal;
	}

	/// Returns a text representation of the message.
	virtual wstring_t toString() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Internal data members ----------------------------------------

private:
	FUniqueId m_sender;
	FUniqueId m_receiver;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_MESSAGE_H