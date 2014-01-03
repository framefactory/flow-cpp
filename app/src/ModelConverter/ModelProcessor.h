// -----------------------------------------------------------------------------
//  File        ModelProcessor.h
//  Project     ModelConverter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef MODELCONVERTER_MODELPROCESSOR_H
#define MODELCONVERTER_MODELPROCESSOR_H

#include "ModelConverter/Application.h"
#include "FlowCore/String.h"
#include "FlowCore/Vector3T.h"
#include "FlowCore/Vector2T.h"

struct aiScene;
struct aiMesh;

// -----------------------------------------------------------------------------
//  Class FModelProcessor
// -----------------------------------------------------------------------------

class FModelProcessor
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FModelProcessor();
	/// Virtual destructor.
	virtual ~FModelProcessor();

	//  Public commands ----------------------------------------------

public:
	bool process(const string_t& inputFile, const string_t& outputFile);

	//  Public queries -----------------------------------------------

	string_t lastErrorString() const { return m_lastError; }

	//  Internal functions -------------------------------------------

private:
	const aiScene* _loadScene(const string_t& filePath);
	bool _writeMesh(const aiMesh* pMesh, const string_t  pathName, const string_t& fileName);
	bool _processMesh(const aiMesh* pMesh,  const string_t  pathName, const string_t& fileName);
	uint8_t* _createBuffer();

	//  Internal data members ----------------------------------------

private:
	struct index_t {
		index_t() : buffer(-1), index(-1) { }
		int32_t buffer;
		int32_t index;
	};

	typedef std::vector<index_t> indexMap_t;

	struct meshBuffer_t {
		std::vector<float> vertexData;
		std::vector<uint16_t> indexData;
	};

	std::vector<meshBuffer_t> m_meshBuffers;

	string_t m_lastError;
};
	
// -----------------------------------------------------------------------------

#endif // MODELCONVERTER_MODELPROCESSOR_H

