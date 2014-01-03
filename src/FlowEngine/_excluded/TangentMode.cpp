// -----------------------------------------------------------------------------
//  File        TangentMode.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.27 $
// -----------------------------------------------------------------------------

#include "FlowEngine/TangentMode.h"
#include "FlowCore/Archive.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FTangentMode
// -----------------------------------------------------------------------------

const char* FTangentMode::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(DirectionCoupled);
		F_ENUM_NAME(AngleCoupled);
		F_ENUM_NAME(Independent);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FTangentMode);

// -----------------------------------------------------------------------------


