// -----------------------------------------------------------------------------
//  File        LogManager.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/18 $
// -----------------------------------------------------------------------------

#include "FlowCore/LogManager.h"
#include "FlowCore/Log.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// -----------------------------------------------------------------------------
//  Class FLogManager
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FLogManager::FLogManager()
: m_logFileName("log.txt")
{
#ifdef FLOW_DEBUG
	m_logFileEnabled = true;
#else
	m_logFileEnabled = false;
#endif

	if (m_logFileEnabled) {
		_writeLogFileSessionStart();
	}
}

FLogManager::~FLogManager()
{
	if (m_logFileEnabled) {
		_writeLogFileSessionEnd();
	}
}

// Public commands -------------------------------------------------------------

void FLogManager::addMessage(const FLogMessage& message)
{
	FSectionLock lock(&m_objectLock);

	if (m_logFileEnabled) {
		_writeLogFileMessage(message);
	}

	qDebug() << message.toString().toStdString().c_str();

	m_messages.push_back(message);
	
	for (size_t i = 0; i < m_listeners.size(); ++i)
		m_listeners[i]->logMessage(message);
}

void FLogManager::addListener(FLogListener* pListener)
{
	FSectionLock lock(&m_objectLock);

	F_ASSERT(pListener);
	m_listeners.push_back(pListener);
}

void FLogManager::removeListener(FLogListener* pListener)
{
	FSectionLock lock(&m_objectLock);

	F_ASSERT(pListener);
	m_listeners.removeOne(pListener);
}

void FLogManager::setLogFileName(const QString& fileName)
{
	FSectionLock lock(&m_objectLock);
	m_logFileName = fileName;
}

// Public queries --------------------------------------------------------------

std::vector<const FLogMessage> FLogManager::getMessages(FLogType type) const
{
	FSectionLock lock(&m_objectLock);
	std::vector<const FLogMessage> messages;

	for (messageVec_t::const_iterator it = m_messages.begin(); it != m_messages.end(); ++it) {
		if (type == FLogType::All || type == it->type()) {
			messages.push_back(*it);
		}
	}

	return messages;
}

// Internal functions ----------------------------------------------------------

void FLogManager::_writeLogFileMessage(const FLogMessage& message)
{
	QFile logFile(m_logFileName);
	if (logFile.open(QFile::WriteOnly | QFile::Append)) {
		QTextStream stream(&logFile);

		stream << message.toString() << "\n";
		stream.flush();
	}
}

void FLogManager::_writeLogFileSessionStart()
{
	QFile logFile(m_logFileName);
	if (logFile.open(QFile::WriteOnly | QFile::Append)) {
		QTextStream stream(&logFile);
#ifdef FLOW_DEBUG
		stream << "***** DEBUG SESSION STARTED: ";
#else
		stream << "***** RELEASE SESSION STARTED: ";
#endif
		stream << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
		stream << " *****\n\n";
		stream.flush();
	}
}

void FLogManager::_writeLogFileSessionEnd()
{
	QFile logFile(m_logFileName);
	if (logFile.open(QFile::WriteOnly | QFile::Append)) {
		QTextStream stream(&logFile);

		stream << "\n***** SESSION CLOSED: ";
		stream << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
		stream << " *****\n\n";
		stream.flush();
	}
}

// -----------------------------------------------------------------------------