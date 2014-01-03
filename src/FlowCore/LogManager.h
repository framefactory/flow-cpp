// -----------------------------------------------------------------------------
//  File        LogManager.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_LOGMANAGER_H
#define FLOWCORE_LOGMANAGER_H

#include "FlowCore/Library.h"

#include "FlowCore/SingletonT.h"
#include "FlowCore/CriticalSection.h"
#include "FlowCore/LogMessage.h"

#include <QString>
#include <vector>

// -----------------------------------------------------------------------------
//  Interface FLogListener 
// -----------------------------------------------------------------------------

class FLogListener
{
public:
	virtual ~FLogListener() { }
	virtual void logMessage(const FLogMessage& message) = 0;
};

// -----------------------------------------------------------------------------
//  Class FLogManager
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FLogManager : public FSingletonAutoT<FLogManager>
{
	friend class FSingletonAutoT<FLogManager>;

	//  Constructors and destructor ----------------------------------

protected:
	/// Default constructor.
	FLogManager();
	/// Virtual destructor.
	virtual ~FLogManager();

	//  Public commands ----------------------------------------------

public:
	/// Writes an entry to the log system.
	void addMessage(const FLogMessage& message);

	void addListener(FLogListener* pListener);
	void removeListener(FLogListener* pListener);

	/// Sets the file name used to write the log entries to a file.
	void setLogFileName(const QString& fileName);
	
	/// Enables or disables logging to a file.
	void enableLogFile(bool state);

	//  Public queries -----------------------------------------------

	/// Returns a list with all log entries of the given type.
	std::vector<const FLogMessage> getMessages(FLogType type = FLogType::All) const;

	/// Returns the name of the log file.
	const QString& logFileName() const { return m_logFileName; }
	
	/// Returns true if logging to a file is enabled.
	bool logFileEnabled() const { return m_logFileEnabled; }

	//  Internal functions -------------------------------------------

private:
	void _writeLogFileMessage(const FLogMessage& message);
	void _writeLogFileSessionStart();
	void _writeLogFileSessionEnd();

	//  Internal data members ----------------------------------------

private:
	mutable FCriticalSection m_objectLock;
	QString m_logFileName;
	bool m_logFileEnabled;

	typedef std::vector<const FLogMessage> messageVec_t;
	messageVec_t m_messages;

	typedef QList<FLogListener*> listenerList_t;
	listenerList_t m_listeners;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_LOGMANAGER_H
