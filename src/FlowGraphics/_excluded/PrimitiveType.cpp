// -----------------------------------------------------------------------------
//  File        PrimitiveType.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/PrimitiveType.h"

#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FPrimitiveType
// -----------------------------------------------------------------------------

uint32_t FPrimitiveType::vertexCount() const
{
	switch(_state)
	{
	case Point: return 1;
	case Line: return 2;
	case Triangle: return 3;
	case Quad: return 4;

	default:
		return 0;
	}
}

const char* FPrimitiveType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Point);
		F_ENUM_NAME(Line);
		F_ENUM_NAME(Triangle);
		F_ENUM_NAME(Quad);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FPrimitiveType);

// -----------------------------------------------------------------------------