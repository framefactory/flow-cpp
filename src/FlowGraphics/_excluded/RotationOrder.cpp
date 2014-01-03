// -----------------------------------------------------------------------------
//  File        RotationOrder.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/RotationOrder.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FRotationOrder
// -----------------------------------------------------------------------------

const char* FRotationOrder::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(XYZ);
		F_ENUM_NAME(XZY);
		F_ENUM_NAME(YXZ);
		F_ENUM_NAME(YZX);
		F_ENUM_NAME(ZXY);
		F_ENUM_NAME(ZYX);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FRotationOrder);

// -----------------------------------------------------------------------------