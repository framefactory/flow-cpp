// -----------------------------------------------------------------------------
//  File        ImageType.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_IMAGETYPE_H
#define FLOWGRAPHICS_IMAGETYPE_H

#include "FlowGraphics/Library.h"

class FArchive;

// -----------------------------------------------------------------------------
//  Class FImageType
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FImageType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Unknown					= 0,
		Bitmap					= 1,
		UInt16					= 2,
		Int16					= 3,
		UInt32					= 4,
		Int32					= 5,
		Float					= 6,
		Double					= 7,
		Complex					= 8,
		RGB_UInt16				= 9,
		RGBA_UInt16				= 10,
		RGB_Float				= 11,
		RGBA_Float				= 12,
		Indexed_1				= 13,
		Indexed_4				= 14,
		Indexed_8				= 15,
		Special_16				= 16,
		RGB						= 17,
		RGBA					= 18,
		RGB_UInt8				= RGB,
		RGBA_UInt8				= RGBA
	};

	int bitsPerPixel() const;

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FImageType, Unknown);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_IMAGETYPE_H