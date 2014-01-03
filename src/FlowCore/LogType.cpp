// -----------------------------------------------------------------------------
//  File        LogType.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// -----------------------------------------------------------------------------

#include "FlowCore/LogType.h"

// -----------------------------------------------------------------------------
//  Class FLogType
// -----------------------------------------------------------------------------

const char* FLogType::name() const
{
	switch (m_state)
	{
	case Trace:						return "Trace";
	case Debug:						return "Debug";
	case Info:						return "Info";
	case Warning:					return "Warning";
	case Critical:					return "Critical";
	case Fatal:						return "Fatal";
	case All:						return "All";
	default: F_ASSERT(false);	    return "UNKNOWN";
	}
}

// -----------------------------------------------------------------------------
