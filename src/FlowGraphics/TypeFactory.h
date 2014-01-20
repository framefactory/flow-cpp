// -----------------------------------------------------------------------------
//  File        TypeFactory.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_TYPEFACTORY_H
#define FLOWGRAPHICS_TYPEFACTORY_H

#include "FlowGraphics/Library.h"
#include "FlowCore/Vector2T.h"

#include <QString>

struct _typeFactoryImpl_t;

// -----------------------------------------------------------------------------
//  Class FTypeFactory
// -----------------------------------------------------------------------------

/// The FTypeFactory class wraps the FreeType font library and provides convenient
/// methods to load a font, access its properties, load glyphs both rendered as
/// bitmaps and as path representations.
class FLOWGRAPHICS_EXPORT FTypeFactory
{
	//  Public types -------------------------------------------------
	
public:
	struct glyphBitmapInfo_t
	{
		int32_t charCode;
		FVector2i size;
		FVector2i origin;
		FVector2f advance;
		int32_t pitch;
		const uint8_t* pData;
	};

	//  Constructors and destructor ----------------------------------

	FTypeFactory();
	~FTypeFactory();

protected:
	FTypeFactory(const FTypeFactory& other);
	FTypeFactory& operator=(const FTypeFactory& other);

	//  Public commands ----------------------------------------------

public:
	bool loadFont(const QString& filePath, uint32_t faceIndex = 0);
	bool loadFont(uint8_t* pData, uint32_t numBytes, uint32_t faceIndex = 0);
	void setGlyphBitmapMaxHeight(uint32_t height);
	bool loadGlyph(uint32_t charCode);
	bool renderGlyphBitmap();

	//  Public queries -----------------------------------------------

	bool isValid() const { return m_pImpl != NULL; }

	bool getGlyphInfo(glyphBitmapInfo_t* pGlyphInfo) const;


	//  Internal data members ----------------------------------------

private:
	_typeFactoryImpl_t* m_pImpl;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_TYPEFACTORY_H