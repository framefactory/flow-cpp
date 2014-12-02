// -----------------------------------------------------------------------------
//  File        LogMessage.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#include "FlowCore/LogMessage.h"

// -----------------------------------------------------------------------------
//  Class FLogMessage
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FLogMessage::FLogMessage()
{
}

FLogMessage::FLogMessage(FLogType type,
                         const QString& module,
						 const QString& text)
: m_type(type),
  m_dateTime(QDateTime::currentDateTime()),
  m_module(module),
  m_text(text)
{
}

FLogMessage::FLogMessage(const QDateTime& dateTime,
                         FLogType type,
						 const QString& module,
						 const QString& text)
: m_type(type),
  m_dateTime(dateTime),
  m_module(module),
  m_text(text)
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

QString FLogMessage::toString() const
{
	return QString("%1 %2 - %3 %4 %5")
		.arg(m_dateTime.toString("dd.MM.yyyy hh:mm:ss"))
		.arg(m_type.name()).arg(m_module).arg(m_text);
}

