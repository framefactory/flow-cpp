// -----------------------------------------------------------------------------
//  File        BitmapFontFactory.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/BitmapFontFactory.h"
#include "FlowCore/UnicodeTraits.h"
#include "FlowCore/TreeMap2T.h"
#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QFile>

#include <algorithm>
#include <fstream>

// -----------------------------------------------------------------------------
//  Class FBitmapFontFactory
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FBitmapFontFactory::FBitmapFontFactory()
: m_pFontData(NULL),
  m_fontDataSize(0),
  m_faceIndex(0),
  m_fontHeight(128),
  m_bitmapSize(1024),
  m_glyphPadding(1)
{
	m_unicodeBlocks.push_back("Basic Latin");
	m_unicodeBlocks.push_back("Latin-1 Supplement");
}

FBitmapFontFactory::~FBitmapFontFactory()
{
}

// Public commands -------------------------------------------------------------

void FBitmapFontFactory::setFontName(const QString& name)
{
	m_fontName = name;
}

void FBitmapFontFactory::setFontFile(const QString& fontFile)
{
	m_fontFile = fontFile;
	m_pFontData = NULL;
	m_fontDataSize = 0;
}

void FBitmapFontFactory::setFontData(uint8_t* pData, uint32_t numBytes)
{
	m_pFontData = pData;
	m_fontDataSize = numBytes;
	m_fontFile.clear();
}

void FBitmapFontFactory::setFontFaceIndex(int32_t index)
{
	F_ASSERT(index >= 0);
	m_faceIndex = index;
}

void FBitmapFontFactory::setTargetFolder(const QString& path)
{
	F_ASSERT(!path.isEmpty());
	m_targetFolder = path;
}

void FBitmapFontFactory::setFontHeight(uint32_t pixels)
{
	F_ASSERT(pixels > 0);
	m_fontHeight = pixels;
}

void FBitmapFontFactory::setBitmapSize(uint32_t pixels)
{
	F_ASSERT(pixels > 0);
	m_bitmapSize = pixels;
}

void FBitmapFontFactory::setGlyphPadding(uint32_t pixels)
{
	m_glyphPadding = pixels;
}

void FBitmapFontFactory::addCodeBlock(const char* blockName)
{
	m_unicodeBlocks.push_back(blockName);
}

bool FBitmapFontFactory::createFont()
{
	if (!m_factory.isValid())
		return false;

	if (m_unicodeBlocks.empty())
		m_unicodeBlocks.push_back("Basic Latin");

	F_ASSERT(!m_fontFile.isEmpty() || m_pFontData);

	bool ok = false;
	if (m_pFontData)
		ok = m_factory.loadFont(m_pFontData, m_fontDataSize, m_faceIndex);
	else
		ok = m_factory.loadFont(m_fontFile, m_faceIndex);
	
	if (!ok)
		return false;

	_loadGlyphs();
	_calculateBitmapSize();
	_createFontBitmaps();
	_writeFontDesc();
	_writeFontBitmaps();

	return true;
}

// Internal functions ----------------------------------------------------------

void FBitmapFontFactory::_loadGlyphs()
{
	m_factory.setGlyphBitmapMaxHeight(m_fontHeight);

	for (size_t i = 0; i < m_unicodeBlocks.size(); ++i) {
		FUnicodeTraits::range_type blockRange
			= FUnicodeTraits::codeBlockRange(m_unicodeBlocks[i]);
		
		if (!blockRange.isEmpty()) {
			uint32_t rangeStart = blockRange.lowerBound();
			uint32_t rangeEnd = blockRange.upperBound();
			uint32_t numGlyphs = 0;

			for (uint32_t charCode = rangeStart; charCode <= rangeEnd; ++charCode) {
				if (!m_factory.loadGlyph(charCode)) {
					continue;
				}

				if (!m_factory.renderGlyphBitmap()) {
					continue;
				}

				glyph_t glyphEntry;
				if (!m_factory.getGlyphInfo(&glyphEntry.bitmap)) {
					continue;
				}

				if (glyphEntry.bitmap.pData) {
					uint32_t numBytes = glyphEntry.bitmap.pitch * glyphEntry.bitmap.size.y;
					uint8_t* pGlyphBitmap = new uint8_t[numBytes];
					memcpy(pGlyphBitmap, glyphEntry.bitmap.pData, numBytes);
					glyphEntry.bitmap.pData = pGlyphBitmap;
					m_glyphTable.push_back(glyphEntry);
					numGlyphs++;
				}
			}

			F_PRINT << m_unicodeBlocks[i] << ": " << numGlyphs << " glyphs loaded";
		}
	}

	F_PRINT;
}

size_t FBitmapFontFactory::_fillMap(const FVector2i& mapSize, size_t firstGlyph) const
{
	// amount of padding added to glyphs
	FVector2i glyphPadding(m_glyphPadding, m_glyphPadding);

	FTreeMap2i treeMap(mapSize);

	for (size_t i = firstGlyph; i < m_glyphTable.size(); ++i)
	{
		if (!m_glyphTable[i].bitmap.pData)
			continue;

		FVector2i glyphSize = m_glyphTable[i].bitmap.size + glyphPadding * 2;
		if (!treeMap.insert(glyphSize))
			return i;
	}

	return m_glyphTable.size();
}

void FBitmapFontFactory::_calculateBitmapSize()
{
	// sort glyphs by descending height
	std::sort(m_glyphTable.begin(), m_glyphTable.end(), glyphSorter_t());

	// amount of padding added to glyphs
	FVector2i glyphPadding(m_glyphPadding, m_glyphPadding);

	// add the area in pixels of all glyphs
	uint32_t requiredCapacity = 0;
	for (uint32_t i = 0; i < m_glyphTable.size(); ++i)
	{
		FVector2i glyphSize = m_glyphTable[i].bitmap.size + glyphPadding * 2;
		requiredCapacity += (uint32_t)(glyphSize.x * glyphSize.y);
	}

	// calculate smallest possible bitmap size given the font height
	uint32_t fp2 = 1;
	while (fp2 < m_fontHeight)
		fp2 <<= 1;

	uint32_t bitmapWidth = fp2;
	uint32_t bitmapHeight = fp2;
	uint32_t numBitmaps = 1;

	// fill glyphs in bitmap and adjust size
	size_t startGlyph = 0;
	size_t overflowGlyph = 0;

	while(true)
	{
		uint32_t bitmapCapacity = bitmapWidth * bitmapHeight;
		if (bitmapCapacity > requiredCapacity)
		{
			overflowGlyph = _fillMap(
				FVector2i(bitmapWidth, bitmapHeight), startGlyph); 

			if (overflowGlyph == m_glyphTable.size())
				break;
		}

		if (bitmapWidth == bitmapHeight)
			bitmapWidth <<= 1;
		else
			bitmapHeight <<= 1;

		if (bitmapWidth > m_bitmapSize)
		{
			overflowGlyph = _fillMap(
				FVector2i(m_bitmapSize, m_bitmapSize), startGlyph); 

			requiredCapacity = 0;
			for (size_t i = overflowGlyph; i < m_glyphTable.size(); ++i)
			{
				FVector2i glyphSize = m_glyphTable[i].bitmap.size + glyphPadding * 2;
				requiredCapacity += (uint32_t)(glyphSize.x * glyphSize.y);
			}

			startGlyph = overflowGlyph;
			bitmapWidth = fp2;
			bitmapHeight = fp2;
			numBitmaps++;
		}
	}

	F_PRINT << "Required bitmap count: " << numBitmaps;
	F_PRINT << "Standard bitmap size: " << m_bitmapSize;
	F_PRINT << "Last fitted bitmap size: " << bitmapWidth << " x " << bitmapHeight;

	m_bitmaps.clear();

	for (size_t i = 0; i < numBitmaps; ++i)
	{
		FImage bitmap;
		uint32_t w = (i == numBitmaps - 1) ? bitmapWidth : m_bitmapSize;
		uint32_t h = (i == numBitmaps - 1) ? bitmapHeight : m_bitmapSize;

		bitmap.create(w, h, FImageType::Indexed_8);
		m_bitmaps.push_back(bitmap);
	}
}

void FBitmapFontFactory::_createFontBitmaps()
{
	// amount of padding added to glyphs
	FVector2i glyphPadding(m_glyphPadding, m_glyphPadding);

	size_t bitmapIndex = 0;
	FImage currentBitmap = m_bitmaps[bitmapIndex];

	FTreeMap2i treeMap(currentBitmap.width(),
					   currentBitmap.height());

	for (uint32_t i = 0; i < m_glyphTable.size(); ++i)
	{
		glyph_t& currentGlyph = m_glyphTable[i];
		if (!currentGlyph.bitmap.pData)
		{
			currentGlyph.texturePosition.setZero();
			currentGlyph.textureIndex = 0;
			continue;
		}

		FVector2i paddedGlyphSize = currentGlyph.bitmap.size + glyphPadding * 2;
		int glyphWidth = currentGlyph.bitmap.size.x;
		int glyphHeight = currentGlyph.bitmap.size.y;
	
		const FTreeMap2i::rect_t* pRect	= treeMap.insert(paddedGlyphSize);
		
		if (!pRect)
		{
			F_PRINT << "Bitmap #" << bitmapIndex
				<< " Coverage: " << treeMap.coverage();

			bitmapIndex++;
			F_ASSERT(bitmapIndex < m_bitmaps.size());
			currentBitmap = m_bitmaps[bitmapIndex];
			treeMap.reset(currentBitmap.width(), currentBitmap.height());
			pRect = treeMap.insert(paddedGlyphSize);
			F_ASSERT(pRect);
		}

		// store the texture position in the glyph
		currentGlyph.texturePosition = pRect->pMin();
		currentGlyph.textureIndex = bitmapIndex;

		// copy the glyph bitmap to the texture
		int32_t bitmapWidth  = currentBitmap.width();
		int32_t bitmapHeight = currentBitmap.height();
		int32_t bitmapPitch = currentBitmap.pitch();
		int32_t bitmapBytes = bitmapPitch * bitmapHeight;

		uint8_t* pTexData = currentBitmap.data()
			+ bitmapBytes - bitmapPitch
			- (currentGlyph.texturePosition.y + m_glyphPadding) * bitmapPitch
			+ (currentGlyph.texturePosition.x + m_glyphPadding);

		int32_t glyphPitch = currentGlyph.bitmap.pitch;
		F_ASSERT(pTexData - (glyphHeight - 1) * bitmapPitch >= currentBitmap.data());

		for (int32_t y = 0; y < glyphHeight; ++y)
		{
			const uint8_t* pSrc = currentGlyph.bitmap.pData + y * glyphPitch;
			uint8_t* pDst = pTexData - y * bitmapPitch;
			for (int32_t x = 0; x < glyphWidth; ++x)
				pDst[x] = pSrc[x] / 2 + 128;
		}

		delete[] currentGlyph.bitmap.pData;
	}

	F_PRINT << "Bitmap #" << bitmapIndex
		<< " Coverage: " << treeMap.coverage();
	F_PRINT << "\nCreated " << m_glyphTable.size() << " glyphs in "
		<< m_bitmaps.size() << " bitmaps.\n";
}

void FBitmapFontFactory::_writeFontDesc()
{
	QString path = QString("%1\\%2%3_desc.txt").arg(m_targetFolder).arg(m_fontName).arg(m_fontHeight);

	QDir dir;
	dir.mkpath(m_targetFolder);

	QFile outFile(path);
	if (!outFile.open(QFile::WriteOnly)) {
		return;
	}

	QTextStream stream(&outFile);

	stream << "{\n";
	stream << "    \"name\": \"" << m_fontName << "\",\n";
	stream << "    \"size\": \"" << m_fontHeight << "\",\n";
	stream << "    \"bitmaps\": [\n";
	for (size_t i = 0; i < m_bitmaps.size(); ++i)
	{
		QString mapFile = QString("%1%2_map%3.png").arg(m_fontName).arg(m_fontHeight).arg(i);

		stream << "        { \"name\": \"" << mapFile << "\""
			<< ", \"width\": " << m_bitmaps[i].width()
			<< ", \"height\": " << m_bitmaps[i].height() << " }";
		stream << ((i < m_bitmaps.size() - 1) ? "," : "") << "\n";
	}
	stream << "    ],\n";

	stream << "    \"glyphs\": [\n";
	for (size_t i = 0; i < m_glyphTable.size(); ++i)
	{
		glyph_t& glyph = m_glyphTable[i];
		stream << "        { \"c\": " << glyph.bitmap.charCode;
		stream << ", \"i\": " << glyph.textureIndex;
		stream << ", \"x\": " << glyph.texturePosition.x;
		stream << ", \"y\": " << glyph.texturePosition.y;
		stream << ", \"w\": " << glyph.bitmap.size.x;
		stream << ", \"h\": " << glyph.bitmap.size.y;
		stream << ", \"ox\": " << glyph.bitmap.origin.x;
		stream << ", \"oy\": " << glyph.bitmap.origin.y;
		stream << ", \"ax\": " << glyph.bitmap.advance.x;
		stream << ", \"ay\": " << glyph.bitmap.advance.y << " }";
		stream << ((i < m_glyphTable.size() - 1) ? "," : "") << "\n";
	}
	stream << "    ]\n";
	stream << "}\n";

	stream.flush();
}

void FBitmapFontFactory::_writeFontBitmaps()
{
	for (size_t i = 0; i < m_bitmaps.size(); ++i) {
		QString filePath = QString("%1\\%2%3_map%4.png").arg(m_targetFolder).arg(m_fontName).arg(m_fontHeight).arg(i);
		m_bitmaps[i].save(filePath, FImageFileFormat::PNG);
	}
}

// -----------------------------------------------------------------------------