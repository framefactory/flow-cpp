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

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FPrimitiveType
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FPrimitiveType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Point,
		Line,
		Triangle,
		Quad
	};

	uint32_t vertexCount() const;

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FPrimitiveType, Triangle);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_PRIMITIVETYPE_H