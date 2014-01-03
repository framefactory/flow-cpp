// -----------------------------------------------------------------------------
//  File        ImageFileFormat.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_IMAGEFILEFORMAT_H
#define FLOWGRAPHICS_IMAGEFILEFORMAT_H

#include "FlowGraphics/Library.h"

class FArchive;

// -----------------------------------------------------------------------------
//  Class FImageFileFormat
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FImageFileFormat
{
	typedef int32_t value_type;

	enum enum_type : value_type
	{
		Unknown		= -1,
		BMP			=  0,
		ICO			=  1,
		JPEG		=  2,
		JNG			=  3,
		KOALA		=  4,
		LBM			=  5,
		IFF			=  LBM,
		MNG			=  6,
		PBM			=  7,
		PBMRAW		=  8,
		PCD			=  9,
		PCX			= 10,
		PGM			= 11,
		PGMRAW		= 12,
		PNG			= 13,
		PPM			= 14,
		PPMRAW		= 15,
		RAS			= 16,
		TARGA		= 17,
		TIFF		= 18,
		WBMP		= 19,
		PSD			= 20,
		CUT			= 21,
		XBM			= 22,
		XPM			= 23,
		DDS			= 24,
		GIF			= 25,
		HDR			= 26,
		FAXG3		= 27,
		SGI			= 28,
		EXR			= 29,
		J2K			= 30,
		JP2			= 31,
		PFM			= 32,
		PICT		= 33,
		RAW			= 34
	};

	const char* description() const;
	const char* extension() const;

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FImageFileFormat, Unknown);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_IMAGEFILEFORMAT_H