// -----------------------------------------------------------------------------
//  File        MeshLoader.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/MeshLoader.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FMeshLoader
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FMeshLoader::FMeshLoader()
{
}

FMeshLoader::~FMeshLoader()
{
}

// Public commands -------------------------------------------------------------

bool FMeshLoader::load(const wstring_t& filePath)
{
	const aiScene* pScene = _loadScene(filePath);
	if (!pScene)
		return false;

	if (!pScene->HasMeshes())
		return false;

	for (uint32_t i = 0; i < pScene->mNumMeshes; ++i)
	{
		aiMesh* pMesh = pScene->mMeshes[i];
		m_meshes.push_back(_createMesh(pMesh));
	}

	for (uint32_t i = 0; i < pScene->mNumMaterials; ++i)
	{
		aiMaterial* pMaterial = pScene->mMaterials[i];
		m_materials.push_back(_createMaterial(pMaterial));
	}

	return true;
}

// Public queries --------------------------------------------------------------

const char* FMeshLoader::lastErrorString() const
{
	return aiGetErrorString();
}

// Internal functions ----------------------------------------------------------

const aiScene* FMeshLoader::_loadScene(const wstring_t& filePath)
{
	string_t ansiPath = FString::fromUtf(filePath);
	const char* pAnsiPath = ansiPath.c_str();

	uint32_t flags = aiProcess_PreTransformVertices
		| aiProcess_ValidateDataStructure
		| aiProcess_JoinIdenticalVertices
		| aiProcess_SortByPType
		| aiProcess_ImproveCacheLocality
		| aiProcess_Triangulate;

	const aiScene* pScene = aiImportFile(pAnsiPath, flags);
	return pScene;
}

FMesh FMeshLoader::_createMesh(const aiMesh* pMesh)
{
	// create vertex layout
	FVertexLayout layout;
	
	if (pMesh->HasPositions())
		layout.addPosition();
	
	if (pMesh->HasNormals())
		layout.addNormal();

	if (pMesh->HasTangentsAndBitangents())
		layout.addTangentAndBitangent();

	for (uint32_t i = 0; i < pMesh->GetNumUVChannels(); ++i)
	{
		uint32_t numDim = pMesh->mNumUVComponents[i];
		FDataType type = (numDim == 1 ? FDataType::Float
			: (numDim == 2 ? FDataType::Float2 : FDataType::Float3));
		layout.addTextureCoords(type);
	}

	for (uint32_t i = 0; i < pMesh->GetNumColorChannels(); ++i)
		layout.addColor();

	// create and prepare mesh
	FMesh mesh;
	mesh.setVertexLayout(layout);

	FPrimitiveType primitiveType = FPrimitiveType::Triangle;
	uint32_t vertexCount = pMesh->mNumVertices;
	uint32_t indexCount = pMesh->mNumFaces * primitiveType.vertexCount();
	mesh.allocateData(vertexCount, indexCount, primitiveType, FDataType::UInt);

	// copy vertex data
	if (pMesh->HasPositions())
	{
		float* pPosition = mesh.dataPtr<float>(0, FChannelType::Position);
		memcpy(pPosition, pMesh->mVertices, vertexCount * 12);
	}

	if (pMesh->HasNormals())
	{
		float* pNormal = mesh.dataPtr<float>(0, FChannelType::Normal);
		memcpy(pNormal, pMesh->mNormals, vertexCount * 12);
	}

	if (pMesh->HasTangentsAndBitangents())
	{
		float* pTangent = mesh.dataPtr<float>(0, FChannelType::Tangent);
		memcpy(pTangent, pMesh->mTangents, vertexCount * 12);

		float* pBitangent = mesh.dataPtr<float>(0, FChannelType::Bitangent);
		memcpy(pBitangent, pMesh->mBitangents, vertexCount * 12);
	}

	for (uint32_t i = 0; i < pMesh->GetNumUVChannels(); ++i)
	{
		uint32_t firstChannel = mesh.vertexLayout().channelIndex(FChannelType::TexCoord);
		float* pTexCoord = mesh.dataPtr<float>(0, firstChannel + i);
		uint32_t numComp = pMesh->mNumUVComponents[i];

		for (uint32_t v = 0; v < vertexCount; ++v)
		{
			for (uint32_t c = 0; c < numComp; ++c)
				pTexCoord[v * numComp + c] = pMesh->mTextureCoords[i][v][c];
		}
	}

	for (uint32_t i = 0; i < pMesh->GetNumColorChannels(); ++i)
	{
		uint32_t firstChannel = mesh.vertexLayout().channelIndex(FChannelType::Color);
		uint32_t* pColor = mesh.dataPtr<uint32_t>(0, firstChannel + i);

		for (uint32_t v = 0; v < vertexCount; ++v)
		{
			uint32_t color = (uint8_t)(pMesh->mColors[i][v].r * 255.0f);
			color += (uint8_t)(pMesh->mColors[i][v].g * 255.0f) << 8;
			color += (uint8_t)(pMesh->mColors[i][v].b * 255.0f) << 16;
			color += (uint8_t)(pMesh->mColors[i][v].a * 255.0f) << 24;
			pColor[v] = color;
		}
	}

	// copy index data
	uint32_t* pIndex = mesh.indexPtr<uint32_t>(0);
	uint32_t j = 0;

	for (uint32_t i = 0; i < pMesh->mNumFaces; ++i)
	{
		const aiFace& face = pMesh->mFaces[i];
		pIndex[j++] = face.mIndices[0];
		pIndex[j++] = face.mIndices[1];
		pIndex[j++] = face.mIndices[2];
	}

	F_TRACE << layout.toString();
	F_TRACE << mesh.toString() << std::endl;

	return mesh;
}

FMaterial FMeshLoader::_createMaterial(const aiMaterial* pMaterial)
{
	return FMaterial();
}

// -----------------------------------------------------------------------------