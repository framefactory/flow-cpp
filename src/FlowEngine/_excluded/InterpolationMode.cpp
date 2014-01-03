// -----------------------------------------------------------------------------
//  File        InterpolationMode.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.27 $
// -----------------------------------------------------------------------------

#include "FlowEngine/InterpolationMode.h"
#include "FlowCore/Archive.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FInterpolationMode
// -----------------------------------------------------------------------------

const char* FInterpolationMode::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Invalid);
		F_ENUM_NAME(Hold);
		F_ENUM_NAME(Linear);
		F_ENUM_NAME(Bezier);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FInterpolationMode);

// -----------------------------------------------------------------------------
