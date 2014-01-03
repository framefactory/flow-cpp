// -----------------------------------------------------------------------------
//  File        MapComponent.h
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/02 $
// -----------------------------------------------------------------------------

#ifndef TILATOR_MAPCOMPONENT_H
#define TILATOR_MAPCOMPONENT_H

#include "Tilator/Application.h"
#include "Tilator/ComponentType.h"
#include "Tilator/ViewType.h"
#include "FlowGraphics/Image.h"
#include "FlowCore/Vector2T.h"
#include "FlowCore/String.h"

#include <vector>

// -----------------------------------------------------------------------------
//  Class FMapComponent
// -----------------------------------------------------------------------------

class FMapComponent
{
	//  Public types -------------------------------------------------

public:
	enum channel_t
	{
		Red,
		Green,
		Blue,
		Alpha
	};

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMapComponent(FComponentType componentType, FViewType viewType);
	/// Virtual destructor.
	virtual ~FMapComponent();

	//  Public commands ----------------------------------------------

public:
	void setPrefix(const string_t& inputPrefix, const string_t& outputPrefix);
	void setTileSize(uint32_t tileSize);
	void setOptions(const string_t& normalLayout, bool autoContrast,
		bool saveMaps, bool saveTiles);
	void setFileFormat(FImageFileFormat fileFormat);

	void setCreateTileMap(bool enable);
	void setTileMapSource(FMapComponent* pComponent);
	void setAlphaMap(FMapComponent* pAlphaMap);

	bool process();
	bool saveAlphaOnly();

	bool loadSourceMap();
	FVector2f normalizeSourceChannel(channel_t channel, bool ignoreTransparentPixels = true);
	void swizzleNormals();
	//void autoRotateNormals();
	bool createPyramid();
	bool createTileMap();
	void convertTo8Bit();
	void convertTo8BitCombineDepthAlpha();
	void convertTo8BitAlphaOnly();
	bool saveTargetMap();
	bool saveTiles();

	//  Public queries -----------------------------------------------

	const string_t& lastError() const { return m_lastError; }
	bool hasError() const { return !m_lastError.empty(); }

	uint32_t sourceWidth() const { return m_sourceMap.width(); }
	uint32_t sourceHeight() const { return m_sourceMap.height(); }

	FComponentType componentType() const { return m_componentType; }
	string_t componentName() const;
	FImageFileFormat fileFormat() const { return m_fileFormat; }
	const string_t& mapReportJSON() const { return m_mapReportJSON; }
	const std::vector<bool>& tileMap() const { return m_tileMap; }

	float depthMin() const { return m_depthMin; }
	float depthMax() const { return m_depthMax; }

	//  Internal functions -------------------------------------------

private:
	FImage _combineDepthAlpha(const FImage& depth, const FImage& alpha) const;
	FImage _convertAlphaOnly(const FImage& alpha) const;
	bool _tileEmpty(const FImage& map, uint32_t tx, uint32_t ty) const;
	bool _saveTile(const FImage& tile, uint32_t level, uint32_t x, uint32_t y);
	void _logMessage(const string_t& message);
	bool _logError(const string_t& message);

	//  Internal data members ----------------------------------------

private:
	FComponentType m_componentType;
	FViewType m_viewType;

	string_t m_inputPrefix;
	string_t m_outputPrefix;
	FImageFileFormat m_fileFormat;

	uint32_t m_tileSize;
	string_t m_normalLayout;
	bool m_autoContrast;
	bool m_saveMaps;
	bool m_saveTiles;

	uint32_t m_paddedMapSize;
	uint32_t m_levels;
	bool m_createTileMap;

	FImage m_sourceMap;
	FMapComponent* m_pTileMapSource;
	FMapComponent* m_pAlphaMap;
	float m_depthMin;
	float m_depthMax;

	typedef std::vector<FImage> imageVec_t;
	imageVec_t m_pyramid;

	typedef std::vector<bool> boolVec_t;
	boolVec_t m_tileMap;
	string_t m_mapReportJSON;

	string_t m_lastError;
};
	
// -----------------------------------------------------------------------------

#endif // TILATOR_MAPCOMPONENT_H