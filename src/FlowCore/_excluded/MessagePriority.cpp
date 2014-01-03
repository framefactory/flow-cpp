// -----------------------------------------------------------------------------
//  File        MessagePriority.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/MessagePriority.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FMessagePriority
// -----------------------------------------------------------------------------

const char* FMessagePriority::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Low);
		F_ENUM_NAME(Normal);
		F_ENUM_NAME(High);
		F_ENUM_NAME(Critical);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FMessagePriority);

// -----------------------------------------------------------------------------