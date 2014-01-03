// -----------------------------------------------------------------------------
//  File        ImageFileFormat.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/ImageFileFormat.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FImageFileFormat
// -----------------------------------------------------------------------------

const char* FImageFileFormat::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Unknown);
		F_ENUM_NAME(BMP);
		F_ENUM_NAME(ICO);
		F_ENUM_NAME(JPEG);
		F_ENUM_NAME(JNG);
		F_ENUM_NAME(KOALA);
		F_ENUM_NAME(IFF);
		F_ENUM_NAME(MNG);
		F_ENUM_NAME(PBM);
		F_ENUM_NAME(PBMRAW);
		F_ENUM_NAME(PCD);
		F_ENUM_NAME(PCX);
		F_ENUM_NAME(PGM);
		F_ENUM_NAME(PGMRAW);
		F_ENUM_NAME(PNG);
		F_ENUM_NAME(PPM);
		F_ENUM_NAME(PPMRAW);
		F_ENUM_NAME(RAS);
		F_ENUM_NAME(TARGA);
		F_ENUM_NAME(TIFF);
		F_ENUM_NAME(WBMP);
		F_ENUM_NAME(PSD);
		F_ENUM_NAME(CUT);
		F_ENUM_NAME(XBM);
		F_ENUM_NAME(XPM);
		F_ENUM_NAME(DDS);
		F_ENUM_NAME(GIF);
		F_ENUM_NAME(HDR);
		F_ENUM_NAME(FAXG3);
		F_ENUM_NAME(SGI);
		F_ENUM_NAME(EXR);
		F_ENUM_NAME(J2K);
		F_ENUM_NAME(JP2);
		F_ENUM_NAME(PFM);
		F_ENUM_NAME(PICT);
		F_ENUM_NAME(RAW);

	default:
		return NULL;
	}
}

const char* FImageFileFormat::description() const
{
	switch (_state)
	{
		F_ENUM_CASE(Unknown,"Unknown format");
		F_ENUM_CASE(BMP,    "Windows or OS/2 Bitmap File");
		F_ENUM_CASE(ICO,    "Windows Icon");
		F_ENUM_CASE(JPEG,   "Independent JPEG Group");
		F_ENUM_CASE(JNG,    "JPEG Network Graphics");
		F_ENUM_CASE(KOALA,  "Commodore 64 Koala format");
		F_ENUM_CASE(IFF,    "Amiga IFF");
		F_ENUM_CASE(MNG,    "Multiple Network Graphics");
		F_ENUM_CASE(PBM,    "Portable Bitmap (ASCII)");
		F_ENUM_CASE(PBMRAW, "Portable Bitmap (BINARY)");
		F_ENUM_CASE(PCD,    "Kodak PhotoCD");
		F_ENUM_CASE(PCX,    "Zsoft Paintbrush PCX bitmap format");
		F_ENUM_CASE(PGM,    "Portable Graymap (ASCII)");
		F_ENUM_CASE(PGMRAW, "Portable Graymap (BINARY)");
		F_ENUM_CASE(PNG,    "Portable Network Graphics");
		F_ENUM_CASE(PPM,    "Portable Pixelmap (ASCII)");
		F_ENUM_CASE(PPMRAW, "Portable Pixelmap (BINARY)");
		F_ENUM_CASE(RAS,    "Sun Rasterfile");
		F_ENUM_CASE(TARGA,  "Truevision Targa files");
		F_ENUM_CASE(TIFF,   "Tagged Image File Format");
		F_ENUM_CASE(WBMP,   "Wireless Bitmap");
		F_ENUM_CASE(PSD,    "Adobe Photoshop");
		F_ENUM_CASE(CUT,    "Dr. Halo");
		F_ENUM_CASE(XBM,    "X11 Bitmap Format");
		F_ENUM_CASE(XPM,    "X11 Pixmap Format");
		F_ENUM_CASE(DDS,    "DirectDraw Surface");
		F_ENUM_CASE(GIF,    "Graphics Interchange Format");
		F_ENUM_CASE(HDR,    "High Dynamic Range");
		F_ENUM_CASE(FAXG3,  "Raw Fax format CCITT G3");
		F_ENUM_CASE(SGI,    "Silicon Graphics SGI image format");
		F_ENUM_CASE(EXR,    "ILM OpenEXR");
		F_ENUM_CASE(J2K,    "JPEG-2000 codestream");
		F_ENUM_CASE(JP2,    "JPEG-2000 File Format");
		F_ENUM_CASE(PFM,    "Portable Floatmap");
		F_ENUM_CASE(PICT,   "Macintosh PICT");
		F_ENUM_CASE(RAW,    "RAW camera image");

	default:
		return NULL;
	}
}

const char* FImageFileFormat::extension() const
{
	switch (_state)
	{
		F_ENUM_CASE(Unknown,"");
		F_ENUM_CASE(BMP,    "*.bmp");
		F_ENUM_CASE(ICO,    "*.ico");
		F_ENUM_CASE(JPEG,   "*.jpg, *.jpeg");
		F_ENUM_CASE(JNG,    "*.jng");
		F_ENUM_CASE(KOALA,  "*.koa");
		F_ENUM_CASE(IFF,    "*.iff, *.lbm");
		F_ENUM_CASE(MNG,    "*.mng");
		F_ENUM_CASE(PBM,    "*.pbm");
		F_ENUM_CASE(PBMRAW, "*.pbm");
		F_ENUM_CASE(PCD,    "*.pcd");
		F_ENUM_CASE(PCX,    "*.pcx");
		F_ENUM_CASE(PGM,    "*.pgm");
		F_ENUM_CASE(PGMRAW, "*.pgm");
		F_ENUM_CASE(PNG,    "*.png");
		F_ENUM_CASE(PPM,    "*.ppm");
		F_ENUM_CASE(PPMRAW, "*.ppm");
		F_ENUM_CASE(RAS,    "*.ras");
		F_ENUM_CASE(TARGA,  "*.tga, *.targa");
		F_ENUM_CASE(TIFF,   "*.tif, *.tiff");
		F_ENUM_CASE(WBMP,   "*.wbmp");
		F_ENUM_CASE(PSD,    "*.psd");
		F_ENUM_CASE(CUT,    "*.cut");
		F_ENUM_CASE(XBM,    "*.xbm");
		F_ENUM_CASE(XPM,    "*.xpm");
		F_ENUM_CASE(DDS,    "*.dds");
		F_ENUM_CASE(GIF,    "*.gif");
		F_ENUM_CASE(HDR,    "*.hdr");
		F_ENUM_CASE(FAXG3,  "*.G3");
		F_ENUM_CASE(SGI,    "*.sgi");
		F_ENUM_CASE(EXR,    "*.exr");
		F_ENUM_CASE(J2K,    "*.j2k, *.j2c");
		F_ENUM_CASE(JP2,    "*.jp2");
		F_ENUM_CASE(PFM,    "*.pfm");
		F_ENUM_CASE(PICT,   "*.pct, *.pict, *.pic");
		F_ENUM_CASE(RAW,    "*.raw");

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FImageFileFormat);

// -----------------------------------------------------------------------------