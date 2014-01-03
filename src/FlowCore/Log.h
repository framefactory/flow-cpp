// -----------------------------------------------------------------------------
//  File        Log.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/19 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_LOG_H
#define FLOWCORE_LOG_H

#include "FlowCore/Library.h"
#include "FlowCore/LogType.h"

#include <QString>
#include <QTextStream>

// -----------------------------------------------------------------------------
//  Class FLogStream
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FLogStream
{
	//  Constructors and destructor ----------------------------------

public:
	FLogStream();
	FLogStream(FLogType type, const QString& module);

	~FLogStream();

	//  Public queries -----------------------------------------------

	QTextStream& stream() { return m_stream; }

	//  Internal data members ----------------------------------------

private:
	FLogType m_type;
	QString m_module;
	QString m_message;
	QTextStream m_stream;
};

// Macros ----------------------------------------------------------------------

#ifdef FLOW_DEBUG
#  define F_TRACE FLogStream().stream()
#  define F_DEBUG(module) FLogStream(FLogType::Debug, module).stream()
#else
#  define F_TRACE if(0) FLogStream().stream()
#  define F_DEBUG(module) if(0) FLogStream(FLogType::Debug, module).stream()
#endif

#define F_PRINT FLogStream().stream()

#define F_INFO(module)     FLogStream(FLogType::Info, module).stream()
#define F_WARNING(module)  FLogStream(FLogType::Warning, module).stream()
#define F_CRITICAL(module) FLogStream(FLogType::Critical, module).stream()
#define F_FATAL(module)    FLogStream(FLogType::Fatal, module).stream()

// -----------------------------------------------------------------------------

#endif // FLOWCORE_LOG_H