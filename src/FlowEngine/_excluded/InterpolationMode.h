// -----------------------------------------------------------------------------
//  File        InterpolationMode.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.27 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_INTERPOLATIONMODE_H
#define FLOWENGINE_INTERPOLATIONMODE_H

#include "FlowEngine/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FInterpolationMode
// -----------------------------------------------------------------------------

struct FLOWENGINE_EXPORT FInterpolationMode
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Invalid,
		Hold,
		Linear,
		Bezier
	};

	F_DECLARE_ENUM(FLOWENGINE_EXPORT, FInterpolationMode, Invalid);
};

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_INTERPOLATIONMODE_H