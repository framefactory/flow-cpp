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

// -----------------------------------------------------------------------------
//  Class FPrimitiveType
// -----------------------------------------------------------------------------

const char* FPrimitiveType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Undefined);
		F_ENUM_NAME(Points);
		F_ENUM_NAME(Lines);
		F_ENUM_NAME(LineStrip);
		F_ENUM_NAME(LineLoop);
		F_ENUM_NAME(Triangles);
		F_ENUM_NAME(TriangleStrip);
		F_ENUM_NAME(TriangleFan);
		F_ENUM_NAME(Patches);
		F_ENUM_NAME(LinesAdjacency);
		F_ENUM_NAME(LineStripAdjacency);
		F_ENUM_NAME(TrianglesAdjacency);
		F_ENUM_NAME(TriangleStripAdjacency);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FPrimitiveType);

// -----------------------------------------------------------------------------