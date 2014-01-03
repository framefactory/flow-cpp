// -----------------------------------------------------------------------------
//  File        ChannelType.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_CHANNELTYPE_H
#define FLOWGRAPHICS_CHANNELTYPE_H

#include "FlowGraphics/Library.h"
#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FChannelType
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FChannelType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Position,
		Normal,
		Tangent,
		Bitangent,
		TexCoord,
		Color,
		Custom
	};

	static size_t count() { return (size_t)Custom + 1; }

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FChannelType, Position);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_CHANNELTYPE_H