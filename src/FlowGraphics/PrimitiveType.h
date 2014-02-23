// -----------------------------------------------------------------------------
//  File        PrimitiveType.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_PRIMITIVETYPE_H
#define FLOWGRAPHICS_PRIMITIVETYPE_H

#include "FlowGraphics/Library.h"

class FArchive;

// -----------------------------------------------------------------------------
//  Class FPrimitiveType
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FPrimitiveType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Undefined,
		Points,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		TriangleFan,
		Patches,
		LinesAdjacency,
		LineStripAdjacency,
		TrianglesAdjacency,
		TriangleStripAdjacency,
	};

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FPrimitiveType, Triangles);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_PRIMITIVETYPE_H