// -----------------------------------------------------------------------------
//  File        AttributeRole.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2014/02/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_ATTRIBUTEROLE_H
#define FLOWGRAPHICS_ATTRIBUTEROLE_H

#include "FlowGraphics/Library.h"

class FArchive;

// -----------------------------------------------------------------------------
//  Class FAttributeRole
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FAttributeRole
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Undefined,
		Position,
		Normal,
		Tangent,
		Bitangent,
		TexCoords,
		Color,
		Weight,
		Custom
	};

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FAttributeRole, Undefined);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_ATTRIBUTEROLE_H