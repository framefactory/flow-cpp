// -----------------------------------------------------------------------------
//  File        ModelProcessor.cpp
//  Project     ModelConverter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "ModelConverter/ModelProcessor.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "FlowCore/Base64.h"
#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FModelProcessor
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FModelProcessor::FModelProcessor()
{
}

FModelProcessor::~FModelProcessor()
{
}

// Public commands -------------------------------------------------------------

bool FModelProcessor::process(const string_t& inputFile,
							  const string_t& outputFile)
{
	std::cout << "Opening source file: " << inputFile << std::endl;
	const aiScene* pScene = _loadScene(inputFile);

	if (!pScene) {
		m_lastError = string_t("Could not open ") + inputFile;
		return false;
	}

	if (!pScene->HasMeshes()) {
		m_lastError = string_t("Input file contains no mesh data.");
		return false;
	}

	for (uint32_t i = 0; i < pScene->mNumMeshes; ++i)
	{
		const aiMesh* pMesh = pScene->mMeshes[i];
		string_t name(pMesh->mName.C_Str());
		if (name.empty() && pScene->mNumMeshes > 1) {
			std::ostringstream oss; oss << i; name = oss.str(); 
		}

		boost::filesystem::path path(outputFile);
		string_t parentPath = path.parent_path().string();
		string_t fileBase = path.stem().string();

		if (!parentPath.empty() && parentPath.back() != '/')
			parentPath.push_back('/');

		string_t fileName = fileBase + (name[0] ? string_t("_") + name : "") + ".json";
		std::cout << "Writing mesh: " << parentPath << fileName << std::endl;

		bool result = _processMesh(pMesh, parentPath, fileName);
		if (!result) {
			return false;
		}
	}

	return true;
}

// Public queries --------------------------------------------------------------

// Internal functions ----------------------------------------------------------

const aiScene* FModelProcessor::_loadScene(const string_t& filePath)
{
	uint32_t flags = aiProcess_PreTransformVertices
		| aiProcess_ValidateDataStructure
		| aiProcess_JoinIdenticalVertices
		| aiProcess_SortByPType
		| aiProcess_ImproveCacheLocality
		| aiProcess_Triangulate;

	const aiScene* pScene = aiImportFile(filePath.c_str(), flags);
	return pScene;
}

bool FModelProcessor::_writeMesh(const aiMesh* pMesh, const string_t  pathName, const string_t& fileName)
{
	if (!pMesh->HasPositions()) {
		m_lastError = string_t("Mesh has no position data.");
		return false;
	}

	// mesh components
	const aiVector3D* pPositions = pMesh->mVertices;
	const aiVector3D* pNormals = pMesh->HasNormals() ? pMesh->mNormals : NULL;
	const aiVector3D* pTexCoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0] : NULL;
	uint32_t texComp = pTexCoord ? pMesh->mNumUVComponents[0] : 0;
	uint32_t numVert = pMesh->mNumVertices;
	uint32_t numFaces = pMesh->mNumFaces;
	uint32_t numIdx = numFaces * 3;

	std::cout << "\n   Number of vertices: " << numVert << std::endl;
	std::cout << "   Number of triangles: " << numFaces << std::endl;
	std::cout << "   Number of indices: " << numIdx << std::endl;
	std::cout << "   Has normals: " << (pNormals ? "yes" : "no") << std::endl;
	std::cout << "   Has texture coords: " << (pTexCoord ? "yes" : "no") << std::endl;
	if (pTexCoord)
		std::cout << "      Number of components: " << texComp << std::endl;

	std::cout << "\n   Creating interleaved buffer..." << std::endl;

	// temporary binary buffer for interleaved data
	uint32_t vertBufElems = numVert * (3 + (pNormals ? 3 : 0) + (pTexCoord ? texComp : 0));
	uint32_t vertBufSize = vertBufElems * sizeof(float);
	uint32_t idxElemSize = numVert > 0xffff ? sizeof(uint32_t) : sizeof(uint16_t);
	uint32_t idxBufSize = numIdx * idxElemSize;
	uint32_t bufSize = vertBufSize + idxBufSize;
	
	uint8_t* pBuffer = new uint8_t[bufSize];
	float* pBufFloat = (float*)pBuffer;
	uint16_t* pBufUint16 = numVert > 0xffff ? NULL : (uint16_t*)(pBuffer + vertBufSize);
	uint32_t* pBufUint32 = numVert > 0xffff ? (uint32_t*)(pBuffer + vertBufSize) : NULL;
	uint32_t bufPtr = 0;

	for (uint32_t i = 0; i < numVert; ++i) {
		const aiVector3D& v = pPositions[i];
		pBufFloat[bufPtr++] = v[0];
		pBufFloat[bufPtr++] = v[1];
		pBufFloat[bufPtr++] = v[2];
		if (pNormals) {
			const aiVector3D& n = pNormals[i];
			pBufFloat[bufPtr++] = n[0];
			pBufFloat[bufPtr++] = n[1];
			pBufFloat[bufPtr++] = n[2];
		}
		if (pTexCoord) {
			for (uint32_t j = 0; j < texComp; ++j)
				pBufFloat[bufPtr++] = (j == 1 ? -1 : 1) * pTexCoord[i][j];
		}
	}

	F_ASSERT(bufPtr == vertBufElems);
	bufPtr = 0;

	for (uint32_t i = 0; i < numFaces; ++i)
	{
		const aiFace& face = pMesh->mFaces[i];
		F_ASSERT(face.mNumIndices == 3);

		if (pBufUint16) {
			for (uint32_t j = 0; j < 3; ++j)
				pBufUint16[bufPtr++] = (uint16_t)face.mIndices[j];
		}
		else {
			for (uint32_t j = 0; j < 3; ++j)
				pBufUint32[bufPtr++] = (uint32_t)face.mIndices[j];
		}
	}

	F_ASSERT(bufPtr == idxBufSize / idxElemSize);

	std::cout << "   Base64 encoding..." << std::endl;
	string_t encodedBuffer = FBase64::encode(pBuffer, bufSize);
	delete[] pBuffer;

	// write output
	std::cout << "   Writing output file..." << std::endl;
	boost::filesystem::path path(pathName);
	boost::filesystem::create_directories(path);

	std::fstream json(pathName + "/" + fileName, std::fstream::out);

	json << "{\n";
	json << "    \"mesh\": {\n";
	json << "        \"vertices\": " << numVert << ",\n";
	json << "        \"indices\": " << numIdx << ",\n";
	json << "        \"components\": {\n";
	json << "            \"normals\": " << (pNormals ? "true,\n" : "false,\n");
	json << "            \"texCoords\": " << texComp << "\n";
	json << "        },\n";
	json << "        \"data\": [\n" + encodedBuffer + "\n        ]\n";
	json << "    }\n";
	json << "}\n";

	json.close();

	return true;
}

bool FModelProcessor::_processMesh(const aiMesh* pMesh,
								   const string_t pathName,
								   const string_t& fileName)
{
	const aiVector3D* pPositions = pMesh->mVertices;
	const aiVector3D* pNormals = pMesh->HasNormals() ? pMesh->mNormals : NULL;
	const aiVector3D* pTexCoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0] : NULL;
	int32_t texComp = pTexCoord ? pMesh->mNumUVComponents[0] : 0;

	int32_t vertexCount = pMesh->mNumVertices;
	int32_t faceCount = pMesh->mNumFaces;
	int32_t indexCount = faceCount * 3;
	int32_t vertexSize = 3 + (pNormals ? 3 : 0) + (pTexCoord ? texComp : 0);

	std::cout << "Number of vertices: " << vertexCount << std::endl;
	std::cout << "Number of triangle faces: " << faceCount << std::endl;
	std::cout << "Number of indices: " << indexCount << std::endl;
	std::cout << "Has normals: " << (pNormals ? "yes" : "no") << std::endl;
	std::cout << "Has texture coordinates: ";
	if (pTexCoord)
		std::cout << "yes (" << texComp << " components)\n\n";
	else
		std::cout << "no\n\n";

	int32_t viDst = 0;
	int32_t biDst = -1;

	bool nextBuffer = true;
	indexMap_t indexMap(vertexCount);

	meshBuffer_t* pBuffer = NULL;

	for (int32_t f = 0; f < faceCount; ++f)
	{
		if (nextBuffer) {
			std::cout << "Starting new buffer..." << std::endl;
			nextBuffer = false;
			m_meshBuffers.push_back(meshBuffer_t());
			pBuffer = &m_meshBuffers.back();
			viDst = 0;
			biDst++;
		}

		const aiFace& face = pMesh->mFaces[f];
		if (face.mNumIndices != 3) {
			m_lastError = "Non-triangular face found.";
			return false;
		}

		size_t faceVertexStart = pBuffer->vertexData.size();
		size_t faceIndexStart = pBuffer->indexData.size();

		for (int32_t fi = 0; fi < 3; ++fi)
		{
			int32_t viSrc = (int32_t)face.mIndices[fi];
			F_ASSERT(viSrc < indexCount);
			
			//std::cout << f << "[" << fi << "]: " << viSrc << ": " << indexMap[viSrc].index << std::endl;
			if (indexMap[viSrc].index == -1 || indexMap[viSrc].buffer != biDst) {

				// vertex data
				const aiVector3D& v = pPositions[viSrc];
				for (int32_t vi = 0; vi < 3; ++vi)
					pBuffer->vertexData.push_back(v[vi]);
				if (pNormals) {
					const aiVector3D& n = pNormals[viSrc];
					for (int32_t ni = 0; ni < 3; ++ni)
						pBuffer->vertexData.push_back(n[ni]);
				}
				if (pTexCoord) {
					for (int32_t tc = 0; tc < texComp; ++tc)
						pBuffer->vertexData.push_back((tc == 1 ? -1 : 1) * pTexCoord[viSrc][tc]);
				}

				// index data
				pBuffer->indexData.push_back((uint16_t)viDst);
				indexMap[viSrc].buffer = biDst;
				indexMap[viSrc].index = viDst;
				viDst++;

				if (pBuffer->vertexData.size() != viDst * vertexSize) {
					m_lastError = "Buffer size error.";
					return false;
				}

				// check for buffer overflow
				if (viDst > 0xffff) {
					if (fi < 2) {
						// remove data written for current face and
						// make sure face vertices are added to next buffer
						pBuffer->vertexData.resize(faceVertexStart);
						pBuffer->indexData.resize(faceIndexStart);
						f--;
					}

					nextBuffer = true; // create new buffer
					break; // terminate face index loop
				}
			}
			else {
				int32_t vi = indexMap[viSrc].index;
				pBuffer->indexData.push_back((uint16_t)vi);
			}
		}
	}

	std::cout << "\nTotal buffers created: " << m_meshBuffers.size() << std::endl;

	// vertex and index buffer size
	size_t bufferSize = 0;
	std::ostringstream vbSizeText;
	std::ostringstream ibSizeText;

	for (size_t b = 0; b < m_meshBuffers.size(); ++b) {
		meshBuffer_t* pMeshBuffer = &m_meshBuffers[b];
		size_t vbSize = pMeshBuffer->vertexData.size();
		size_t ibSize = pMeshBuffer->indexData.size();

		vbSizeText << (b == 0 ? "" : ", ") << (vbSize / vertexSize);
		ibSizeText << (b == 0 ? "" : ", ") << (ibSize);
		std::cout << "   Buffer #" << b << ": " << (vbSize / vertexSize) << " vertices and "
			<< ibSize << " indices.\n";

		// ensure we are 4-aligned for the next float buffer
		if (pMeshBuffer->indexData.size() % 2) {
			pMeshBuffer->indexData.push_back(0);
			ibSize += 1;
		}

		bufferSize += vbSize * sizeof(float) + ibSize * sizeof(uint16_t);

		if (vbSize % vertexSize != 0 || ibSize % 2 != 0) {
			m_lastError = "Buffer size error.";
			return false;
		}
	}

	uint8_t* pDataBuffer = new uint8_t[bufferSize];
	size_t bufPos = 0;

	for (size_t b = 0; b < m_meshBuffers.size(); ++b) {
		meshBuffer_t* pMeshBuffer = &m_meshBuffers[b];
		size_t vbChunkSize = pMeshBuffer->vertexData.size() * sizeof(float);
		size_t ibChunkSize = pMeshBuffer->indexData.size() * sizeof(uint16_t);
		memcpy(pDataBuffer + bufPos, &pMeshBuffer->vertexData.front(), vbChunkSize);
		bufPos += vbChunkSize;
		memcpy(pDataBuffer + bufPos, &pMeshBuffer->indexData.front(), ibChunkSize);
		bufPos += ibChunkSize;
	}

	if (bufPos != bufferSize) {
		m_lastError = "Buffer size error.";
		return false;
	}

	std::cout << "\nBase64 encoding..." << std::endl;
	string_t encodedBuffer = FBase64::encode(pDataBuffer, bufferSize);
	delete[] pDataBuffer;

	// write output
	std::cout << "Writing mesh to " << pathName << fileName << std::endl;

	if (!pathName.empty()) {
		boost::filesystem::path path(pathName);
		boost::filesystem::create_directories(path);
	}

	std::fstream json(pathName + fileName, std::fstream::out);

	json << "{\n";
	json << "    \"mesh\": {\n";
	json << "        \"vertices\": [" << vbSizeText.str() << "],\n";
	json << "        \"indices\": [" << ibSizeText.str() << "],\n";
	json << "        \"components\": {\n";
	json << "            \"normals\": " << (pNormals ? "true,\n" : "false,\n");
	json << "            \"texCoords\": " << texComp << "\n";
	json << "        },\n";
	json << "        \"data\": [\n" + encodedBuffer + "\n        ]\n";
	json << "    }\n";
	json << "}\n";

	json.close();

	return true;
}


// -----------------------------------------------------------------------------