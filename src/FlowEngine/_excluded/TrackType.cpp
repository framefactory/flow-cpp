// -----------------------------------------------------------------------------
//  File        TrackType.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#include "FlowEngine/TrackType.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FTrackType
// -----------------------------------------------------------------------------

const char* FTrackType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Trigger);
		F_ENUM_NAME(Interpolate);
		F_ENUM_NAME(Boolean);
		F_ENUM_NAME(Integer);
		F_ENUM_NAME(Double);
		F_ENUM_NAME(String);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FTrackType);

// -----------------------------------------------------------------------------