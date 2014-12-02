// -----------------------------------------------------------------------------
//  File        LogMessage.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_LOGMESSAGE_H
#define FLOWCORE_LOGMESSAGE_H

#include "FlowCore/Library.h"
#include "FlowCore/LogType.h"

#include <QString>
#include <QDateTime>

// -----------------------------------------------------------------------------
//  Class FLogMessage
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FLogMessage
{
	//  Constructors and destructor ----------------------------------

public:
    /// Default constructor.
    FLogMessage();

	/// Create a log message with the given type and text.
	/// The current date and time is recorded with the message.
	FLogMessage(FLogType type, const QString& module, const QString& text);

	/// Create a log message with the given date, time, type and text.
	FLogMessage(const QDateTime& dateTime, FLogType type,
		        const QString& module, const QString& text);

	//  Public commands ----------------------------------------------

	//  Public queries -----------------------------------------------

	FLogType type() const { return m_type; }
	const QDateTime& dateTime() const { return m_dateTime; }
	const QString& module() const { return m_module; }
	const QString& text() const { return m_text; }

	QString toString() const;

	//  Internal data members ----------------------------------------

private:
	FLogType m_type;
	QDateTime m_dateTime;
	QString m_module;
	QString m_text;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_LOGMESSAGE_H
