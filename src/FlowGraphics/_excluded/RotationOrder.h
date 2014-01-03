// -----------------------------------------------------------------------------
//  File        RotationOrder.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_ROTATIONORDER_H
#define FLOWGRAPHICS_ROTATIONORDER_H

#include "FlowGraphics/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FRotationOrder
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FRotationOrder
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		XYZ,
		XZY,
		YXZ,
		YZX,
		ZXY,
		ZYX
	};

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FRotationOrder, XYZ);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_ROTATIONORDER_H