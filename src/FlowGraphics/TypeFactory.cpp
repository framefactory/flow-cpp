// -----------------------------------------------------------------------------
//  File        TypeFactory.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/TypeFactory.h"
#include "FlowCore/MemoryTracer.h"

#include <ft2build.h>
#include <freetype/freetype.h>

// -----------------------------------------------------------------------------
//  Class FTypeFactory
// -----------------------------------------------------------------------------

// Implementation --------------------------------------------------------------

struct _typeFactoryImpl_t
{
	FT_Library library;
	FT_Face face;
	FT_GlyphSlot glyph;
	uint32_t charCode;
	uint32_t glyphIndex;
};

// Constructors and destructor -------------------------------------------------

FTypeFactory::FTypeFactory()
: m_pImpl(NULL)
{
	FT_Library library;
	int err = FT_Init_FreeType(&library);

	if (err == 0)
	{
		m_pImpl = new _typeFactoryImpl_t();
		m_pImpl->library = library;
		m_pImpl->face = NULL;
		m_pImpl->glyph = NULL;
	}
}

FTypeFactory::~FTypeFactory()
{
	if (m_pImpl)
	{
		if (m_pImpl->face)
			FT_Done_Face(m_pImpl->face);

		FT_Done_FreeType(m_pImpl->library);
		delete m_pImpl;
		m_pImpl = NULL;
	}
}

// Public commands -------------------------------------------------------------

bool FTypeFactory::loadFont(
	const QString& filePath, uint32_t faceIndex /* = 0 */)
{
	// release font face, if already allocated
	if (m_pImpl->face)
	{
		FT_Done_Face(m_pImpl->face);
		m_pImpl->glyph = NULL;
	}

	// load face from font file path
	int err = FT_New_Face(
		m_pImpl->library, filePath.toLatin1(), faceIndex, &m_pImpl->face);

	if (err != 0)
	{
		m_pImpl->face = NULL;
		return false;
	}

	return true;
}

bool FTypeFactory::loadFont(uint8_t* pData, uint32_t numBytes,
	uint32_t faceIndex /* = 0 */)
{
	F_ASSERT(pData);
	F_ASSERT(numBytes > 0);

	if (m_pImpl->face)
	{
		FT_Done_Face(m_pImpl->face);
		m_pImpl->glyph = NULL;
	}

	int err = FT_New_Memory_Face(
		m_pImpl->library, pData, numBytes, faceIndex, &m_pImpl->face);

	if (err != 0)
	{
		m_pImpl->face = NULL;
		return false;
	}

	return true;
}

void FTypeFactory::setGlyphBitmapMaxHeight(uint32_t height)
{
	if (!m_pImpl || !m_pImpl->face)
		return;

	FT_Set_Pixel_Sizes(m_pImpl->face, 0, height);
}

bool FTypeFactory::loadGlyph(uint32_t charCode)
{
	if (!m_pImpl || !m_pImpl->face)
		return false;

	uint32_t glyphIndex = FT_Get_Char_Index(m_pImpl->face, charCode);
	if (glyphIndex == 0)
		return false;

	int err = FT_Load_Glyph(m_pImpl->face, glyphIndex, FT_LOAD_DEFAULT);
	if (err != 0)
		return false;

	m_pImpl->glyph = m_pImpl->face->glyph;
	m_pImpl->charCode = charCode;
	m_pImpl->glyphIndex = glyphIndex;

	return true;
}

bool FTypeFactory::renderGlyphBitmap()
{
	if (!m_pImpl || !m_pImpl->glyph)
		return false;

	int err = FT_Render_Glyph(m_pImpl->glyph, FT_RENDER_MODE_NORMAL);
	return (err == 0);
}

// Public queries --------------------------------------------------------------

bool FTypeFactory::getGlyphInfo(glyphBitmapInfo_t* pGlyphInfo) const
{
	if (!m_pImpl || !m_pImpl->glyph || !pGlyphInfo)
		return false;

	FT_GlyphSlot glyph = m_pImpl->glyph;
	pGlyphInfo->charCode = m_pImpl->charCode;
	pGlyphInfo->size.set(glyph->bitmap.width, glyph->bitmap.rows);
	pGlyphInfo->origin.set(glyph->bitmap_left, glyph->bitmap_top);
	pGlyphInfo->advance.set(glyph->advance.x / 64.0f, glyph->advance.y / 64.0f);
	pGlyphInfo->pitch = glyph->bitmap.pitch;
	pGlyphInfo->pData = glyph->bitmap.buffer;

	return true;
}

// -----------------------------------------------------------------------------