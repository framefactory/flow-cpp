// -----------------------------------------------------------------------------
//  File        BitmapFont.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_BITMAPFONT_H
#define FLOWGRAPHICS_BITMAPFONT_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/Font.h"

#include "FlowCore/Vector2T.h"

#include <unordered_map>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FBitmapFont
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FBitmapFont : public FFont
{
	F_DECLARE_SERIALIZABLE(FBitmapFont);
	friend class FBitmapFontFactory;

	//  Constructors and destructor ----------------------------------

public:
	/// Virtual destructor.
	virtual ~FBitmapFont();

	//  Public commands ----------------------------------------------

public:
	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual QString dump() const;
#endif

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	struct bitmap_t
	{
		size_t width;
		uint8_t* m_pData;
	};

	typedef std::vector<bitmap_t> bitmapVec_t;
	bitmapVec_t m_bitmaps;

	struct glyph_t
	{
		FVector2i size;
		FVector2i origin;
		uint32_t charCode;
		uint32_t bitmapIndex;
		float advance;
	};

	typedef std::unordered_map<uint32_t, glyph_t> glyphMap_t;
	glyphMap_t m_glyphMap;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_BITMAPFONT_H