// -----------------------------------------------------------------------------
//  File        TrackType.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_TRACKTYPE_H
#define FLOWENGINE_TRACKTYPE_H

#include "FlowEngine/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FTrackType
// -----------------------------------------------------------------------------

struct FLOWENGINE_EXPORT FTrackType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Trigger,
		Interpolate,
		Boolean,
		Integer,
		Double,
		String
	};

	F_DECLARE_ENUM(FLOWENGINE_EXPORT, FTrackType, Trigger);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_TRACKTYPE_H