// -----------------------------------------------------------------------------
//  File        ImageProcessor.cpp
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/02 $
// -----------------------------------------------------------------------------

#include "Tilator/ImageProcessor.h"
#include "Tilator/ComponentType.h"

#include "FlowCore/String.h"
#include "FlowCore/MemoryTracer.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace boost::filesystem;

// -----------------------------------------------------------------------------
//  Class FImageProcessor
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FImageProcessor::FImageProcessor(FViewType viewType)
: m_viewType(viewType)
{
	m_pCompAlpha = new FMapComponent(FComponentType::Alpha, viewType);
	m_pCompDiffuse = new FMapComponent(FComponentType::Diffuse, viewType);
	m_pCompZone = new FMapComponent(FComponentType::Zone, viewType);
	m_pCompNormal = new FMapComponent(FComponentType::Normal, viewType);
	m_pCompOcclusion = new FMapComponent(FComponentType::Occlusion, viewType);
	m_pCompDepth = new FMapComponent(FComponentType::Depth, viewType);
}

FImageProcessor::~FImageProcessor()
{
	F_SAFE_DELETE(m_pCompAlpha);
	F_SAFE_DELETE(m_pCompDiffuse);
	F_SAFE_DELETE(m_pCompZone);
	F_SAFE_DELETE(m_pCompNormal);
	F_SAFE_DELETE(m_pCompOcclusion);
	F_SAFE_DELETE(m_pCompDepth);
}

// Public commands -------------------------------------------------------------

bool FImageProcessor::process(const string_t& inputPrefix,
							  const string_t& outputPrefix,
							  FVector3f bbMin,
							  FVector3f bbMax,
							  uint32_t tileSize,
							  const string_t& normalLayout,
							  bool autoContrast,
							  bool saveMaps,
							  bool saveTiles)
{
	int error = 0;
	FMapComponent* pCompWithTileMap = NULL;

	// Alpha
	m_pCompAlpha->setPrefix(inputPrefix, outputPrefix);
	m_pCompAlpha->setTileSize(tileSize);
	m_pCompAlpha->setOptions(normalLayout, autoContrast, saveMaps, saveTiles);
	m_pCompAlpha->setFileFormat(FImageFileFormat::JPEG);

	m_pCompAlpha->setCreateTileMap(true);

	if (!m_pCompAlpha->process()) {
		std::cout << m_pCompAlpha->lastError();
		error++;
	}
	else {
		pCompWithTileMap = m_pCompAlpha;
	}

	// Diffuse
	m_pCompDiffuse->setPrefix(inputPrefix, outputPrefix);
	m_pCompDiffuse->setTileSize(tileSize);
	m_pCompDiffuse->setOptions(normalLayout, autoContrast, saveMaps, saveTiles);
	m_pCompDiffuse->setFileFormat(FImageFileFormat::JPEG);

	if (pCompWithTileMap) {
		m_pCompDiffuse->setTileMapSource(pCompWithTileMap);
	}
	else {
		m_pCompDiffuse->setCreateTileMap(true);
	}

	if (!m_pCompDiffuse->process()) {
		std::cout << m_pCompDiffuse->lastError();
		error++;
	}
	else if (!pCompWithTileMap) {
		pCompWithTileMap = m_pCompDiffuse;
	}

	// Zone
	m_pCompZone->setPrefix(inputPrefix, outputPrefix);
	m_pCompZone->setTileSize(tileSize);
	m_pCompZone->setOptions(normalLayout, autoContrast, saveMaps, saveTiles);
	m_pCompZone->setFileFormat(FImageFileFormat::JPEG);

	if (pCompWithTileMap) {
		m_pCompZone->setTileMapSource(pCompWithTileMap);
	}
	else {
		m_pCompZone->setCreateTileMap(true);
	}

	if (!m_pCompZone->process()) {
		std::cout << m_pCompZone->lastError();
		error++;
	}
	else if (!pCompWithTileMap) {
		pCompWithTileMap = m_pCompZone;
	}

	// Normal
	m_pCompNormal->setPrefix(inputPrefix, outputPrefix);
	m_pCompNormal->setTileSize(tileSize);
	m_pCompNormal->setOptions(normalLayout, autoContrast, saveMaps, saveTiles);
	m_pCompNormal->setTileMapSource(pCompWithTileMap);
	m_pCompNormal->setAlphaMap(m_pCompAlpha);
	m_pCompNormal->setFileFormat(FImageFileFormat::JPEG);

	if (!m_pCompNormal->process()) {
		std::cout << m_pCompNormal->lastError();
		error++;
	}

	// Occlusion
	m_pCompOcclusion->setPrefix(inputPrefix, outputPrefix);
	m_pCompOcclusion->setTileSize(tileSize);
	m_pCompOcclusion->setOptions(normalLayout, autoContrast, saveMaps, saveTiles);
	m_pCompOcclusion->setTileMapSource(pCompWithTileMap);
	m_pCompOcclusion->setAlphaMap(m_pCompAlpha);
	m_pCompOcclusion->setFileFormat(FImageFileFormat::JPEG);

	if (!m_pCompOcclusion->process()) {
		std::cout << m_pCompOcclusion->lastError();
		error++;
	}

	// Depth
	m_pCompDepth->setPrefix(inputPrefix, outputPrefix);
	m_pCompDepth->setTileSize(tileSize);
	m_pCompDepth->setOptions(normalLayout, autoContrast, saveMaps, saveTiles);
	m_pCompDepth->setTileMapSource(pCompWithTileMap);
	m_pCompDepth->setAlphaMap(m_pCompAlpha);
	m_pCompDepth->setFileFormat(FImageFileFormat::PNG);

	if (!m_pCompDepth->process()) {
		std::cout << m_pCompDepth->lastError();
		error++;
		// if depth with alpha could not be created, create alpha only tiles
		m_pCompAlpha->saveAlphaOnly();
	}

	_generateReport(outputPrefix, bbMin, bbMax);

	if (error)
	{
		std::cout << std::endl << error
			<< " error(s) reported" << std::endl;
		return false;
	}
	else
	{
		std::cout << std::endl << "Job done with no errors" << std::endl;
		return true;
	}
}

// Internal functions ----------------------------------------------------------

void FImageProcessor::_generateReport(const string_t& prefix,
									  const FVector3f& bbMin,
									  const FVector3f& bbMax)
{
	string_t componentReport;

	string_t reportPath = prefix + "/proxy-info.json";
	path rp(prefix);
	create_directories(prefix);

	std::fstream json(reportPath, std::fstream::out);
	
	json << "{\n";
	json << "    \"proxy\": {\n";

	json << "        \"type\": \"" << m_viewType.proxyType() << "\",\n";
	json << "        \"unit\": \"mm\",\n";

	_writeBoundingBox(json, bbMin, bbMax);

	json << "        \"tileset\": {\n";
	json << "            \"path\": \"tiles\",\n";

	json << "            \"maps\": {\n";

	size_t ordinal = 0;
	std::vector<FMapComponent*> components;
	components.push_back(m_pCompAlpha);
	components.push_back(m_pCompDiffuse);
	components.push_back(m_pCompZone);
	components.push_back(m_pCompNormal);
	components.push_back(m_pCompOcclusion);
	components.push_back(m_pCompDepth);

	for (size_t i = 0; i < components.size(); ++i)
	{
		FMapComponent* pComp = components[i];
		if (pComp->lastError().empty()
			&& pComp->componentType() != FComponentType::Alpha)
		{
			if (ordinal > 0)
				json << ",\n";

			string_t compName = pComp->componentName();
			json << "                \"" << compName << "\": { \n";
			json << "                    \"name\": \"t-" << pComp->componentType().shortName() << "\",\n";
			json << "                    \"format\": \"" << pComp->fileFormat().name() << "\"\n";
			json << "                }";
			ordinal++;
		}
	}

	// tile map was generated for alpha component, take report
	FMapComponent* pCompWithReport = components[0];
	if (pCompWithReport->lastError().empty()
		&& !pCompWithReport->mapReportJSON().empty())
	{
		componentReport = pCompWithReport->mapReportJSON();
	}

	json << "\n            },\n\n"; // maps

	json << componentReport;

	json << "        }\n"; // tileset
	json << "    }\n"; // proxy
	json << "}\n"; // root

	json.close();
}

void FImageProcessor::_writeBoundingBox(std::fstream& stream,
										const FVector3f& bbMin,
										const FVector3f& bbMax)
{
	stream << "        \"boundingBox\": {\n";
	stream << "            \"min\": [ " << bbMin.x << ", " << bbMin.y << ", " << bbMin.z << " ],\n";
	stream << "            \"max\": [" << bbMax.x << ", " << bbMax.y << ", " << bbMax.z << " ]\n";
	stream << "        },\n";
}

// -----------------------------------------------------------------------------