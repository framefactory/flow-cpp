// -----------------------------------------------------------------------------
//  File        ImageProcessor.h
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/02 $
// -----------------------------------------------------------------------------

#ifndef TILATOR_IMAGEPROCESSOR_H
#define TILATOR_IMAGEPROCESSOR_H

#include "Tilator/Application.h"
#include "Tilator/MapComponent.h"
#include "Tilator/ViewType.h"

#include "FlowCore/String.h"
#include "FlowCore/Vector3T.h"
#include <vector>

// -----------------------------------------------------------------------------
//  Class FImageProcessor
// -----------------------------------------------------------------------------

class FImageProcessor
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FImageProcessor(FViewType viewType);
	/// Virtual destructor.
	virtual ~FImageProcessor();

	//  Public commands ----------------------------------------------

public:
	/// Processes images with the given prefix. Returns true if no errors occurred.
	bool process(const string_t& inputPrefix, const string_t& outputPrefix,
		FVector3f bbMin, FVector3f bbMax, uint32_t tileSize, const string_t& normalLayout,
		bool autoContrast, bool saveMaps, bool saveTiles);
	
	//  Internal data members ----------------------------------------

private:
	void _generateReport(const string_t& path, const FVector3f& bbMin, const FVector3f& bbMax);
	void _writeBoundingBox(std::fstream& stream, const FVector3f& bbMin, const FVector3f& bbMax);

private:
	FViewType m_viewType;

	FMapComponent* m_pCompAlpha;
	FMapComponent* m_pCompDiffuse;
	FMapComponent* m_pCompZone;
	FMapComponent* m_pCompNormal;
	FMapComponent* m_pCompOcclusion;
	FMapComponent* m_pCompDepth;
};
	
// -----------------------------------------------------------------------------

#endif // TILATOR_IMAGEPROCESSOR_H
