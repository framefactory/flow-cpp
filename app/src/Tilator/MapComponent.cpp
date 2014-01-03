// -----------------------------------------------------------------------------
//  File        MapComponent.cpp
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/02 $
// -----------------------------------------------------------------------------

#include "Tilator/MapComponent.h"

#include "FlowCore/Bit.h"
#include "FlowCore/String.h"
#include "FlowCore/MemoryTracer.h"

#include <FreeImage.h>

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>

using namespace boost::filesystem;

// -----------------------------------------------------------------------------
//  Class FMapComponent
// -----------------------------------------------------------------------------

static const uint16_t ALPHA_THRESHOLD = 1024;
static const uint16_t ALPHA_THRESHOLD2 = 64512;

// Constructors and destructor -------------------------------------------------

FMapComponent::FMapComponent(FComponentType componentType, FViewType viewType)
	: m_componentType(componentType),
	  m_viewType(viewType),
	  m_fileFormat(FImageFileFormat::PNG),
	  m_tileSize(512),
	  m_normalLayout("+x+y+z"),
	  m_autoContrast(true),
	  m_saveMaps(false),
	  m_saveTiles(true),
	  m_paddedMapSize(0),
	  m_levels(0),
	  m_createTileMap(false),
	  m_pTileMapSource(NULL),
	  m_pAlphaMap(NULL),
	  m_depthMin(0.0f),
	  m_depthMax(1.0f)
{
}

FMapComponent::~FMapComponent()
{
}

// Public commands -------------------------------------------------------------

void FMapComponent::setPrefix(const string_t& inputPrefix, const string_t& outputPrefix)
{
	m_inputPrefix = inputPrefix;
	m_outputPrefix = outputPrefix;
}

void FMapComponent::setTileSize(uint32_t tileSize)
{
	m_tileSize = tileSize;
}

void FMapComponent::setCreateTileMap(bool enable)
{
	m_createTileMap = enable;
}

void FMapComponent::setOptions(const string_t& normalLayout,
							   bool autoContrast,
							   bool saveMaps,
							   bool saveTiles)
{
	m_normalLayout = normalLayout;
	m_autoContrast = autoContrast;
	m_saveMaps = saveMaps;
	m_saveTiles = saveTiles;
}

void FMapComponent::setFileFormat(FImageFileFormat fileFormat)
{
	m_fileFormat = fileFormat;
}

void FMapComponent::setTileMapSource(FMapComponent* pComponent)
{
	F_ASSERT(pComponent);
	m_pTileMapSource = pComponent;
}

void FMapComponent::setAlphaMap(FMapComponent* pAlphaMap)
{
	F_ASSERT(pAlphaMap);
	m_pAlphaMap = pAlphaMap;
}

bool FMapComponent::process()
{
	std::cout << std::endl << "Processing component "
		<< m_componentType.name() << std::endl << std::endl;

	if (!loadSourceMap())
	{
		return false;
	}

	switch(m_componentType)
	{
	case FComponentType::Occlusion:
		if (m_autoContrast)
		{
			normalizeSourceChannel(FMapComponent::Red);
			normalizeSourceChannel(FMapComponent::Green);
			normalizeSourceChannel(FMapComponent::Blue);
		}
		break;

	case FComponentType::Depth:
		// we do not normalize the depth range anymore
		/*
		if (m_autoContrast)
		{
			FVector2f range = normalizeSourceChannel(FMapComponent::Red);
			m_depthMin = range.x;
			m_depthMax = range.y;
		}
		*/
		break;

	case FComponentType::Normal:
		swizzleNormals();
		break;
	}

	if (!createPyramid())
		return false;

	if (m_createTileMap && !createTileMap())
		return false;

	if (m_componentType == FComponentType::Depth)
	{
		convertTo8BitCombineDepthAlpha();
		m_componentType = FComponentType::DepthAlpha;
	}
	else if (m_componentType != FComponentType::Alpha)
	{
		convertTo8Bit();
	}

	if (m_componentType != FComponentType::Alpha)
	{
		if (m_saveMaps && !saveTargetMap())
			return false;

		if (m_saveTiles && !saveTiles())
			return false;
	}
	
	return true;
}

bool FMapComponent::saveAlphaOnly()
{
	std::cout << std::endl << "Processing component "
		<< m_componentType.name() << std::endl << std::endl;

	F_ASSERT(m_componentType == FComponentType::Alpha);

	if (m_sourceMap.isNull())
		return true;

	convertTo8BitAlphaOnly();

	if (m_saveMaps && !saveTargetMap())
		return false;

	if (m_saveTiles && !saveTiles())
		return false;
	
	return true;
}

bool FMapComponent::loadSourceMap()
{
	string_t baseFilePath = m_inputPrefix + "-" + m_componentType.name();
	string_t tifFilePath = baseFilePath + ".tif";
	string_t pngFilePath = baseFilePath + ".png";

	string_t filePath;
	FImageFileFormat fileFormat;

	if (exists(tifFilePath)) {
		filePath = tifFilePath;
		fileFormat = FImageFileFormat::TIFF;
	}
	else {
		filePath = pngFilePath;
		fileFormat = FImageFileFormat::PNG;
	}

	_logMessage(string_t("loading source map: ") + filePath);
	m_sourceMap.load(FString::toUtf(filePath), fileFormat);

	if (m_sourceMap.isNull())
		return _logError(string_t("Could not load map: ") + filePath);

	if (m_sourceMap.type() != FImageType::RGB_UInt16)
		return _logError(string_t("Map format must be 16-bit RGB: ") + filePath);

	return true;
}

FVector2f FMapComponent::normalizeSourceChannel(channel_t channel,
										   bool ignoreTransparentPixels /* = true */)
{
	ptrdiff_t offset = 0;
	FIRGB16 pixel;

	FImage& alphaMap = m_pAlphaMap->m_sourceMap;
	
	switch (channel)
	{
	case FMapComponent::Red: offset = (uint16_t*)&pixel.red - (uint16_t*)&pixel; break;
	case FMapComponent::Green: offset = (uint16_t*)&pixel.green - (uint16_t*)&pixel; break;
	case FMapComponent::Blue: offset = (uint16_t*)&pixel.blue - (uint16_t*)&pixel; break;
	}

	uint32_t width = m_sourceMap.width();
	uint32_t height = m_sourceMap.height();

	int minVal = 0xffff;
	int maxVal = 0x0000;

	for (uint32_t y = 0; y < height; ++y)
	{
		FIRGB16* pLine1 = (FIRGB16*)m_sourceMap.line(y);
		FIRGB16* pLine0 = y > 0 ? (FIRGB16*)m_sourceMap.line(y - 1) : pLine1;
		FIRGB16* pLine2 = y < height - 1 ? (FIRGB16*)m_sourceMap.line(y + 1) : pLine1;

		FIRGB16* pAlphaLine1 = (FIRGB16*)alphaMap.line(y);
		FIRGB16* pAlphaLine0 = y > 0 ? (FIRGB16*)alphaMap.line(y - 1) : pLine1;
		FIRGB16* pAlphaLine2 = y < height - 1 ? (FIRGB16*)alphaMap.line(y + 1) : pLine1;

		for (uint32_t x = 0; x < width; ++x)
		{
			FIRGB16* pPixel0 = pLine0 + x;
			FIRGB16* pPixel2 = pLine1 + x;
			FIRGB16* pPixel4 = pLine2 + x;

			FIRGB16* pPixel1 = x > 0 ? pLine1 + x - 1 : pPixel2;
			FIRGB16* pPixel3 = x < width - 1 ? pLine1 + x + 1 : pPixel2;

			FIRGB16* pAlphaPixel0 = pAlphaLine0 + x;
			FIRGB16* pAlphaPixel2 = pAlphaLine1 + x;
			FIRGB16* pAlphaPixel4 = pAlphaLine2 + x;

			FIRGB16* pAlphaPixel1 = x > 0 ? pAlphaLine1 + x - 1 : pAlphaPixel2;
			FIRGB16* pAlphaPixel3 = x < width - 1 ? pAlphaLine1 + x + 1 : pAlphaPixel2;

			if (pAlphaPixel0->red > ALPHA_THRESHOLD2
				&& pAlphaPixel1->red > ALPHA_THRESHOLD2
				&& pAlphaPixel2->red > ALPHA_THRESHOLD2
				&& pAlphaPixel3->red > ALPHA_THRESHOLD2
				&& pAlphaPixel4->red > ALPHA_THRESHOLD2)
			{
				int val0 = *((uint16_t*)pPixel0 + offset);
				int val1 = *((uint16_t*)pPixel1 + offset);
				int val2 = *((uint16_t*)pPixel2 + offset);
				int val3 = *((uint16_t*)pPixel3 + offset);
				int val4 = *((uint16_t*)pPixel4 + offset);

				int loVal = fMin(val0, fMin(val1, fMin(val2, fMin(val3, val4))));
				int hiVal = fMax(val0, fMax(val1, fMax(val2, fMax(val3, val4))));

				minVal = fMin(minVal, hiVal);
				maxVal = fMax(maxVal, loVal);
			}
		}
	}

	double scale = (double)(0xffff) / (double)(maxVal - minVal);

	std::ostringstream oss;
	oss << "channel normalization (" << (int)channel << "), min: "
		<< minVal << ", max: " << maxVal << ", scale factor: " << scale;
	_logMessage(oss.str());

	for (uint32_t y = 0; y < height; ++y)
	{
		FIRGB16* pLine = (FIRGB16*)m_sourceMap.line(y);

		for (uint32_t x = 0; x < width; ++x)
		{
			FIRGB16* pPixel = pLine + x;
			uint16_t* pComponent = (uint16_t*)pPixel + offset;
			int val = *pComponent;
			val = (int)((double)(val - minVal) * scale);
			*pComponent = (uint16_t)(fMax(0, fMin(0xffff, val)));
		}
	}

	// return normalized min and max channel values
	return FVector2f((float)minVal / 65536.0f, (float)maxVal / 65536.0f);
}

void FMapComponent::swizzleNormals()
{
	int swizzle[3] = { 0, 1, 2 };
	int flip[3] = { 0, 0, 0 };

	string_t layout = FString::toLower(m_normalLayout);
	int compIndex = 0;
	for (int i = 0; i < layout.size(); ++i)
	{
		char c = layout[i];
		if (c == 'x') {
			swizzle[compIndex] = 0;
			flip[compIndex] = (i > 0 && layout[i-1] == '-' ? 1 : 0);
			compIndex++;
		}
		else if (c == 'y') {
			swizzle[compIndex] = 1;
			flip[compIndex] = (i > 0 && layout[i-1] == '-' ? 1 : 0);
			compIndex++;
		}
		else if (c == 'z') {
			swizzle[compIndex] = 2;
			flip[compIndex] = (i > 0 && layout[i-1] == '-' ? 1 : 0);
			compIndex++;
		}

		if (compIndex > 2)
			break;
	}

	FIRGB16 pixel;
	ptrdiff_t offset[3];
	offset[0] = (uint16_t*)&pixel.red - (uint16_t*)&pixel;
	offset[1] = (uint16_t*)&pixel.green - (uint16_t*)&pixel; 
	offset[2] = (uint16_t*)&pixel.blue - (uint16_t*)&pixel;

	uint32_t width = m_sourceMap.width();
	uint32_t height = m_sourceMap.height();
	int o = 32768; // 0x8000

	for (uint32_t y = 0; y < height; ++y)
	{
		FIRGB16* pLine = (FIRGB16*)m_sourceMap.line(y);

		for (uint32_t x = 0; x < width; ++x)
		{
			FIRGB16* pPixel = pLine + x;
			uint16_t* pBase = (uint16_t*)pPixel;

			uint16_t nx = *(pBase + offset[swizzle[0]]);
			uint16_t ny = *(pBase + offset[swizzle[1]]);
			uint16_t nz = *(pBase + offset[swizzle[2]]);

			pPixel->red = flip[0] ? 0xffff - nx : nx;
			pPixel->green = flip[1] ? 0xffff - ny : ny;
			pPixel->blue = flip[2] ? 0xffff - nz : nz;
		}
	}
}

bool FMapComponent::createPyramid()
{
	m_pyramid.clear();
	uint32_t size = fMax(m_sourceMap.width(), m_sourceMap.height());
	m_paddedMapSize = FBit::ceilPow2(size);

	m_levels = 0;
	size = m_tileSize;
	while (size <= m_paddedMapSize)
	{
		size <<= 1;
		m_levels++;
	}

	std::ostringstream oss;
	oss << "creating pyramid with " << m_levels << " hierarchy levels";
	_logMessage(oss.str());

	if (m_levels < 1)
	{
		std::ostringstream oss;
		oss << "Tile size (" << m_tileSize << ") is larger than padded map size ("
			<< m_paddedMapSize << ")";
		return _logError(oss.str());
	}

	FImage paddedMap;
	paddedMap.create(m_paddedMapSize, m_paddedMapSize, FImageType::RGB_UInt16);
	uint32_t left = (m_paddedMapSize - m_sourceMap.width()) / 2;
	uint32_t top = (m_paddedMapSize - m_sourceMap.height()) / 2;
	paddedMap.paste(m_sourceMap, left, top);
	m_pyramid.push_back(paddedMap);

	uint32_t levelSize = m_paddedMapSize >> 1;
	for (uint32_t level = 1; level < m_levels; ++level)
	{
		FImage levelMap = m_pyramid[level - 1].resize(levelSize, levelSize);
		m_pyramid.push_back(levelMap);
		levelSize >>= 1;
	}

	return true;
}

bool FMapComponent::createTileMap()
{
	_logMessage("create tile map");
	m_tileMap.clear();
	uint32_t totalTiles = 0;
	uint32_t emptyTiles = 0;

	string_t indent = "            ";

	std::ostringstream json;
	json << indent << "\"mapSize\": " << m_paddedMapSize << ",\n";
	json << indent << "\"tileSize\": " << m_tileSize << ",\n";
	json << indent << "\n";
	json << indent << "\"levels\": [\n"; // levels array begin

	for (int level = m_levels - 1; level >= 0; --level)
	{
		FImage& levelMap = m_pyramid[level];
		uint32_t nx = levelMap.width() / m_tileSize;
		uint32_t ny = levelMap.height() / m_tileSize;

		json << indent << "    { \n"; // level object begin
		json << indent << "        \"level\": " << (m_levels - level) << ",\n";
		json << indent << "        \"levelSize\": " << levelMap.width() << ",\n";
		json << indent << "        \"tilesPerSide\": " << nx << ",\n";
		json << indent << "        \"tileCount\": " << (nx * ny) << ",\n";
		json << indent << "        \"tiles\": [ "; // tiles array begin

		uint32_t tileIndex = 0;
		for (uint32_t y = 0; y < ny; ++y)
		{
			for (uint32_t x = 0; x < nx; ++x)
			{
				bool empty = (m_componentType == FComponentType::Alpha)
					? _tileEmpty(levelMap, x, y) : false;

				m_tileMap.push_back(!empty);

				if (tileIndex > 0)
					json << ", ";

				if (empty)
				{
					emptyTiles++;
					json << "false";
				}
				else
				{
					json << "true";
				}

				totalTiles++;
				tileIndex++;
			}
		}

		json << " ]\n"; // tiles array end

		// level object end
		if (level == 0)
			json << indent << "    }\n";
		else
			json << indent << "    },\n";
	}

	json << indent << "]\n"; // levels array end
	m_mapReportJSON = json.str();

	std::ostringstream oss;
	oss << "total tiles: " << totalTiles
		<< ", valid tiles: " << (totalTiles - emptyTiles)
		<< ", empty tiles: " << emptyTiles;
	_logMessage(oss.str());

	return true;
}

void FMapComponent::convertTo8Bit()
{
	_logMessage("16-bit to 8-bit conversion");
	F_ASSERT(m_levels == m_pyramid.size());

	for (uint32_t level = 0; level < m_levels; ++level) {
		m_pyramid[level] = m_pyramid[level].convert(FImageType::RGB_UInt8);
	}

	m_sourceMap = m_sourceMap.convert(FImageType::RGB_UInt8);
}

void FMapComponent::convertTo8BitCombineDepthAlpha()
{
	_logMessage("16-bit to 8-bit depth/alpha conversion");
	F_ASSERT(m_levels == m_pyramid.size());
	F_ASSERT(m_pAlphaMap);
	std::vector<FImage>& alphaPyramid = m_pAlphaMap->m_pyramid;
	F_ASSERT(m_levels == alphaPyramid.size());

	for (uint32_t level = 0; level < m_levels; ++level) {
		m_pyramid[level] = _combineDepthAlpha(m_pyramid[level], alphaPyramid[level]);
	}

	m_sourceMap = _combineDepthAlpha(m_sourceMap, m_pAlphaMap->m_sourceMap);
}

void FMapComponent::convertTo8BitAlphaOnly()
{
	_logMessage("16-bit to 8-bit alpha only conversion");
	F_ASSERT(m_levels == m_pyramid.size());

	for (uint32_t level = 0; level < m_levels; ++level) {
		m_pyramid[level] = _convertAlphaOnly(m_pyramid[level]);
	}

	m_sourceMap = _convertAlphaOnly(m_sourceMap);
}

bool FMapComponent::saveTargetMap()
{
	string_t filePath = m_outputPrefix + "/map-" + FString::toLower(m_componentType.name()) + ".png";
	path op(m_outputPrefix);
	create_directories(op);

	_logMessage(string_t("save 8-bit converted map: ") + filePath);

	int flags = PNG_Z_BEST_COMPRESSION;
	FImageFileFormat format = FImageFileFormat::PNG;

	if (!m_sourceMap.save(FString::toUtf(filePath), format, flags)) {
		return _logError(string_t("failed to write file: ") + filePath);
	}

	return true;
}

bool FMapComponent::saveTiles()
{
	if (!m_createTileMap && !m_pTileMapSource)
		return _logError("no tile map available");

	uint32_t tileIndex = 0;
	boolVec_t& tileMap = m_createTileMap ? m_tileMap : m_pTileMapSource->m_tileMap;
	F_ASSERT(!tileMap.empty());

	for (int level = m_levels - 1; level >= 0; --level)
	{
		FImage& levelMap = m_pyramid[level];
		uint32_t nx = levelMap.width() / m_tileSize;
		uint32_t ny = levelMap.height() / m_tileSize;
		uint32_t tileCount = nx * ny;

		std::ostringstream oss;
		oss << "hierarchy level " << (m_levels - level)
			<< " - level size " << levelMap.width()
			<< ", tile size " << m_tileSize
			<< ", creating " << tileCount << " tiles";
		_logMessage(oss.str());

		for (uint32_t y = 0; y < ny; ++y)
		{
			for (uint32_t x = 0; x < nx; ++x)
			{
				if (tileMap[tileIndex]) // tile not empty
				{
					uint32_t left = x * m_tileSize;
					uint32_t top = y * m_tileSize;

					FImage tile = levelMap.copy(left, top, m_tileSize, m_tileSize);
					if (!_saveTile(tile, level, x, y))
						return false;
				}

				tileIndex++;
			}
		}
	}

	F_ASSERT(tileIndex == tileMap.size());

	return true;
}

// Public queries --------------------------------------------------------------

string_t FMapComponent::componentName() const
{
	return string_t(m_componentType.name());
}

// Internal functions ----------------------------------------------------------

FImage FMapComponent::_combineDepthAlpha(const FImage& depth, const FImage& alpha) const
{
	uint32_t width = depth.width();
	uint32_t height = depth.height();

	F_ASSERT(width == alpha.width() && height == alpha.height());

	FImage imageDDA8;
	imageDDA8.create(width, height, FImageType::RGB_UInt8);

	for (uint32_t y = 0; y < height; ++y)
	{
		const FIRGB16* pSrcDepthLine = (const FIRGB16*)depth.line(y);
		const FIRGB16* pSrcAlphaLine = (const FIRGB16*)alpha.line(y);
		uint8_t* pDstLine = (uint8_t*)imageDDA8.line(y);

		for (uint32_t x = 0; x < width; ++x)
		{
			FIRGB16 srcDepthPixel = pSrcDepthLine[x];
			FIRGB16 srcAlphaPixel = pSrcAlphaLine[x];
			uint8_t* pDstPixel = pDstLine + x * 3;
			uint16_t depth = srcDepthPixel.red;
			uint16_t alpha = srcAlphaPixel.red;
			pDstPixel[FI_RGBA_RED] = (uint8_t)((depth >> 8) & 0xff);
			pDstPixel[FI_RGBA_GREEN] = (uint8_t)(depth & 0xff);
			pDstPixel[FI_RGBA_BLUE] = (uint8_t)((alpha >> 8) & 0xff);
		}
	}

	return imageDDA8;
}

FImage FMapComponent::_convertAlphaOnly(const FImage& alpha) const
{
	uint32_t width = alpha.width();
	uint32_t height = alpha.height();

	FImage imageDDA8;
	imageDDA8.create(width, height, FImageType::RGB_UInt8);

	for (uint32_t y = 0; y < height; ++y)
	{
		const FIRGB16* pSrcAlphaLine = (const FIRGB16*)alpha.line(y);
		uint8_t* pDstLine = (uint8_t*)imageDDA8.line(y);

		for (uint32_t x = 0; x < width; ++x)
		{
			FIRGB16 srcAlphaPixel = pSrcAlphaLine[x];
			uint8_t* pDstPixel = pDstLine + x * 3;
			uint16_t alpha = srcAlphaPixel.red;
			pDstPixel[FI_RGBA_RED] = 0; // depth LSB disabled
			pDstPixel[FI_RGBA_GREEN] = 0; // depth MSB disabled
			pDstPixel[FI_RGBA_BLUE] = (uint8_t)((alpha >> 8) & 0xff);
		}
	}

	return imageDDA8;
}

bool FMapComponent::_tileEmpty(const FImage& map, uint32_t tx, uint32_t ty) const
{
	uint32_t xa = tx * m_tileSize;
	uint32_t xe = xa + m_tileSize;
	
	uint32_t ya = map.height() - ty * m_tileSize - m_tileSize;
	uint32_t ye = ya + m_tileSize;

	bool empty = true;

	for (uint32_t y = ya; y < ye; ++y)
	{
		const FIRGB16* pLine = (const FIRGB16*)map.line(y);

		for (uint32_t x = xa; x < xe; ++x)
		{
			FIRGB16 pixel = pLine[x];
			empty = empty && (pixel.red < ALPHA_THRESHOLD);
		}

		if (!empty)
			break;
	}

	return empty;
}

bool FMapComponent::_saveTile(const FImage& tile, uint32_t level, uint32_t x, uint32_t y)
{
	FImageFileFormat format = m_fileFormat;
	string_t extension;
	int flags;

	if (format == FImageFileFormat::JPEG)
	{
		if (m_componentType == FComponentType::Normal
			|| m_componentType == FComponentType::Occlusion) {
				flags = 95;
		}
		else {
			flags = 90;
		}

		flags += (JPEG_OPTIMIZE | JPEG_BASELINE | JPEG_SUBSAMPLING_444);
		extension = ".jpg";
	}
	else 
	{
		format = FImageFileFormat::PNG;
		flags = PNG_Z_BEST_COMPRESSION;
		extension = ".png";
	}

	level = m_levels - level;

	string_t outputPath = m_outputPrefix.size() ? m_outputPrefix + "/tiles" : "./tiles";
	path op(outputPath);
	create_directories(op);

	std::ostringstream oss;
	
	// alpha only components should be named depthAlpha to ensure viewer compatibility
	FComponentType compTypeDepthAlpha = FComponentType::DepthAlpha;
	const char* pCompName = (m_componentType == FComponentType::Alpha)
		? compTypeDepthAlpha.shortName() : m_componentType.shortName();

	oss << FString::toLower(pCompName) << "-" << level;
	oss << "-" << x << "-" << y << extension;
	string_t tileFilePath = outputPath + "/t-" + oss.str();
	//std::cout << "save tile " << tileFilePath << std::endl;

	if (!tile.save(FString::toUtf(tileFilePath), format, flags))
	{
		return _logError(string_t("failed to save tile: ")
			+ tileFilePath);
	}

	return true;
}

void FMapComponent::_logMessage(const string_t& message)
{
	std::cout << "Component: " << m_componentType.name()
		<< " - " << message << std::endl;
}

bool FMapComponent::_logError(const string_t& message)
{
	std::ostringstream oss;
	oss << "Component: " << m_componentType.name()
		<< " - ERROR: " << message << std::endl;
	m_lastError = oss.str();
	return false;
}


// -----------------------------------------------------------------------------