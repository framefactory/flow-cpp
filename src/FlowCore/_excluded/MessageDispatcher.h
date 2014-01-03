// -----------------------------------------------------------------------------
//  File        MessageDispatcher.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MESSAGEDISPATCHER_H
#define FLOWCORE_MESSAGEDISPATCHER_H

#include "FlowCore/Library.h"
#include "FlowCore/Message.h"
#include "FlowCore/NamedObject.h"
#include "FlowCore/UniqueId.h"

#include <iosfwd>
#include <queue>
#include <unordered_map>

class FArchive;
class FMessageTarget;

namespace boost { class mutex; }

// -----------------------------------------------------------------------------
//  Class FMessageDispatcher
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FMessageDispatcher : public FNamedObject
{
	F_DECLARE_TYPEINFO(FMessageDispatcher);

	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	FMessageDispatcher();
	/// Creates a message dispatcher with the given id.
	FMessageDispatcher(const FUniqueId& systemId);
	/// Virtual destructor.
	virtual ~FMessageDispatcher();

	//  Public commands ----------------------------------------------

	/// Adds the given message to the queue of the message system.
	/// The system takes ownership of the message object.
	void postMessage(FMessage* pMessage);

	/// Called by message targets of this system to send a message
	/// to a target in this or another system. The system takes
	/// ownership of the message object.
	bool sendMessage(FMessage* pMessage);

	/// Distributes all messages waiting in the queue.
	/// Returns true if any messages have been processed.
	bool processMessages();

	/// Distributes the given number of messages waiting in the queue.
	/// Returns true if more messages are waiting.
	bool processMessages(size_t count);

	//  Public queries -----------------------------------------------

	/// Returns the number of pending messages in the queue.
	size_t messageCount() const;

	/// Finds and returns the message target with the given id.
	FMessageTarget* findTarget(const FUniqueId& id) const;
	/// Returns true if the given target is registered.
	bool hasTarget(const FMessageTarget* pTarget) const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overridables -------------------------------------------------

protected:
	/// Called before a new message is added to the queue.
	/// Override to preprocess the message and return true to
	/// prevent the message from being added to the queue.
	virtual bool onPostMessage(FMessage* pMessage);

	/// Called if a message is sent from this system.
	/// Return true if the message has been delivered.
	/// If false is returned, the message is deleted immediately.
	virtual bool onSendMessage(FMessage* pMessage);

	/// Called to deliver a message from the queue. The default
	/// implementation delivers the message to its message target.
	/// Return true if the message has been processed successfully.
	virtual bool onProcessMessage(FMessage* pMessage);

	//  Internal functions -------------------------------------------

private:
	void _queueMessage(FMessage* pMessage);
	FMessage* _dequeueMessage();

	//  Internal data members ----------------------------------------

	struct messageComparer_t {
		bool operator() (const FMessage* pLeft, const FMessage* pRight) const {
			return (int)pLeft->priority() < (int)pRight->priority(); 
		}
	};

	typedef std::priority_queue<FMessage*,
		std::vector<FMessage*>, messageComparer_t> messageQueue_t;
	
	messageQueue_t m_messageQueue;
	boost::mutex* m_pQueueAccess;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_MESSAGEDISPATCHER_H