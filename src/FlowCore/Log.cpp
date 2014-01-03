// -----------------------------------------------------------------------------
//  File        Log.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/19 $
// -----------------------------------------------------------------------------

#include "FlowCore/Log.h"
#include "FlowCore/LogManager.h"

#include <QDebug>

// -----------------------------------------------------------------------------
//  Class FLogStream
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FLogStream::FLogStream()
: m_type(FLogType::Trace),
  m_stream(&m_message)
{
}

FLogStream::FLogStream(FLogType type, const QString& module)
: m_type(type),
  m_module(module),
  m_stream(&m_message)
{
}

FLogStream::~FLogStream()
{
	if (m_type != FLogType::Trace) {
		FLogMessage message(m_type, m_module, m_message);
		FLogManager::instance()->addMessage(message);
	}
	else {
		qDebug() << m_message.toStdString().c_str();
	}
}

// -----------------------------------------------------------------------------