// -----------------------------------------------------------------------------
//  File        BitmapFontFactory.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_BITMAPFONTFACTORY_H
#define FLOWGRAPHICS_BITMAPFONTFACTORY_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/TypeFactory.h"
#include "FlowGraphics/Image.h"

#include "FlowCore/Vector2T.h"
#include "FlowCore/Rect2T.h"

#include <QString>
#include <vector>


// -----------------------------------------------------------------------------
//  Class FBitmapFontFactory
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FBitmapFontFactory
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FBitmapFontFactory();
	/// Virtual destructor.
	virtual ~FBitmapFontFactory();

	//  Public commands ----------------------------------------------

public:
	void setFontName(const QString& name);
	void setFontFile(const QString& fontFileName);
	void setFontData(uint8_t* pData, uint32_t numBytes);
	void setFontFaceIndex(int32_t index);
	void setTargetFolder(const QString& path);
	void setFontHeight(uint32_t pixels);
	void setBitmapSize(uint32_t pixels);
	void setGlyphPadding(uint32_t pixels);
	void addCodeBlock(const char* blockName);

	bool createFont();

	//  Public queries -----------------------------------------------

	bool isValid() const { return m_factory.isValid(); }

	//  Internal functions -------------------------------------------

private:
	void _loadGlyphs();
	size_t _fillMap(const FVector2i& mapSize, size_t firstGlyph) const;
	void _calculateBitmapSize();
	void _createFontBitmaps();
	void _writeFontDesc();
	void _writeFontBitmaps();

	//  Internal data members ----------------------------------------

public: // testing
	struct glyph_t
	{
		FTypeFactory::glyphBitmapInfo_t bitmap;
		FVector2i texturePosition;
		size_t textureIndex;
	};

	struct glyphSorter_t
	{
		bool operator()(const glyph_t& g1, const glyph_t& g2) const {
			return g1.bitmap.size.y > g2.bitmap.size.y;
		}
	};

	QString m_fontFile;
	QString m_fontName;
	QString m_targetFolder;
	uint8_t* m_pFontData;
	uint32_t m_fontDataSize;
	int32_t m_faceIndex;
	uint32_t m_fontHeight;
	uint32_t m_bitmapSize;
	uint32_t m_glyphPadding;

	FTypeFactory m_factory;

	std::vector<const char*> m_unicodeBlocks;
	std::vector<glyph_t> m_glyphTable;
	std::vector<FImage> m_bitmaps;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_BITMAPFONTFACTORY_H