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

/// Holds the current state of the FreeType API.
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
	// initialize and obtain a FreeType library instance
	FT_Library library;
	int err = FT_Init_FreeType(&library);

	// initialize the internal library state object
	if (err == 0) {
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
		// release the current font face if one is loaded
		if (m_pImpl->face) {
			FT_Done_Face(m_pImpl->face);
		}

		// release the FreeType library instance
		FT_Done_FreeType(m_pImpl->library);
		delete m_pImpl;
		m_pImpl = NULL;
	}
}

// Public commands -------------------------------------------------------------

bool FTypeFactory::loadFont(
	const QString& filePath, uint32_t faceIndex /* = 0 */)
{
	// release previously loaded font face
	if (m_pImpl->face) {
		FT_Done_Face(m_pImpl->face);
		m_pImpl->glyph = NULL;
	}

	// load face from font file path
	int err = FT_New_Face(
		m_pImpl->library, filePath.toLatin1(), faceIndex, &m_pImpl->face);

	// check for errors
	if (err != 0) {
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

	// release previously loaded font face
	if (m_pImpl->face) {
		FT_Done_Face(m_pImpl->face);
		m_pImpl->glyph = NULL;
	}

	// load font face from memory
	int err = FT_New_Memory_Face(
		m_pImpl->library, pData, numBytes, faceIndex, &m_pImpl->face);

	// check for errors
	if (err != 0) {
		m_pImpl->face = NULL;
		return false;
	}

	return true;
}

void FTypeFactory::setGlyphBitmapMaxHeight(uint32_t height)
{
	if (!m_pImpl || !m_pImpl->face) {
		return;
	}

	FT_Set_Pixel_Sizes(m_pImpl->face, 0, height);
}

bool FTypeFactory::loadGlyph(uint32_t charCode)
{
	// make sure a font face is loaded
	if (!m_pImpl || !m_pImpl->face) {
		return false;
	}

	// get the internal glyph index from the unicode character code
	uint32_t glyphIndex = FT_Get_Char_Index(m_pImpl->face, charCode);
	if (glyphIndex == 0) {
		return false;
	}

	// load the glyph, note that the glyph is not rendered yet
	int err = FT_Load_Glyph(m_pImpl->face, glyphIndex, FT_LOAD_DEFAULT);
	if (err != 0) {
		return false;
	}

	m_pImpl->glyph = m_pImpl->face->glyph;
	m_pImpl->charCode = charCode;
	m_pImpl->glyphIndex = glyphIndex;

	return true;
}

bool FTypeFactory::renderGlyphBitmap()
{
	// ensure a glyph has been loaded
	if (!m_pImpl || !m_pImpl->glyph) {
		return false;
	}

	// render a bitmap of the glyph
	int err = FT_Render_Glyph(m_pImpl->glyph, FT_RENDER_MODE_NORMAL);
	return (err == 0);
}

// Public queries --------------------------------------------------------------

bool FTypeFactory::getGlyphInfo(glyphBitmapInfo_t* pGlyphInfo) const
{
	// ensure a glyph has been loaded
	if (!m_pImpl || !m_pImpl->glyph || !pGlyphInfo) {
		return false;
	}

	// copy glyph metrics to the given glyphBitmapInfo_t
	FT_GlyphSlot glyph = m_pImpl->glyph;
	pGlyphInfo->charCode = m_pImpl->charCode;

	// pitch and pData are 0 if no bitmap has been rendered for the glyph
	pGlyphInfo->pitch = glyph->bitmap.pitch;
	pGlyphInfo->pData = glyph->bitmap.buffer;

	pGlyphInfo->size.set(glyph->bitmap.width, glyph->bitmap.rows);
	pGlyphInfo->origin.set(glyph->bitmap_left, glyph->bitmap_top);
	pGlyphInfo->advance.set(glyph->advance.x / 64.0f, glyph->advance.y / 64.0f);

	return true;
}

// -----------------------------------------------------------------------------