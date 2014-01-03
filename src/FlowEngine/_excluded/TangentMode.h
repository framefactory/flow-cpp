// -----------------------------------------------------------------------------
//  File        TangentMode.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.27 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_TANGENTMODE_H
#define FLOWENGINE_TANGENTMODE_H

#include "FlowEngine/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FTangentMode
// -----------------------------------------------------------------------------

struct FLOWENGINE_EXPORT FTangentMode
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		DirectionCoupled,
		AngleCoupled,
		Independent
	};

	F_DECLARE_ENUM(FLOWENGINE_EXPORT, FTangentMode, DirectionCoupled);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_TANGENTMODE_H