// -----------------------------------------------------------------------------
//  File        ComponentType.h
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/08/06 $
// -----------------------------------------------------------------------------

#ifndef TILATOR_COMPONENTTYPE_H
#define TILATOR_COMPONENTTYPE_H

#include "Tilator/Application.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FComponentType
// -----------------------------------------------------------------------------

struct  FComponentType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Diffuse,
		Zone,
		Normal,
		Occlusion,
		Depth,
		Alpha,
		DepthAlpha
	};

	const char* shortName() const;

	F_DECLARE_ENUM(, FComponentType, Diffuse);
};
	
// -----------------------------------------------------------------------------

#endif // TILATOR_COMPONENTTYPE_H