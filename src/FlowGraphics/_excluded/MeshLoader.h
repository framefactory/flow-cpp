// -----------------------------------------------------------------------------
//  File        MeshLoader.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_MESHLOADER_H
#define FLOWGRAPHICS_MESHLOADER_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/Mesh.h"
#include "FlowGraphics/Material.h"

#include "FlowCore/String.h"
#include <vector>

struct aiScene;
struct aiMesh;

// -----------------------------------------------------------------------------
//  Class FMeshLoader
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FMeshLoader
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMeshLoader();
	/// Virtual destructor.
	virtual ~FMeshLoader();

	//  Public commands ----------------------------------------------

public:
	bool load(const wstring_t& filePath);

	//  Public queries -----------------------------------------------

	size_t meshCount() const { return m_meshes.size(); }
	const FMesh& mesh(size_t index) const { return m_meshes[index]; }

	const char* lastErrorString() const;

	//  Internal functions -------------------------------------------

private:
	const aiScene* _loadScene(const wstring_t& filePath);
	FMesh _createMesh(const aiMesh* pMesh);
	FMaterial _createMaterial(const aiMaterial* pMaterial);

	//  Internal data members ----------------------------------------

private:
	std::vector<FMesh> m_meshes;
	std::vector<FMaterial> m_materials;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_MESHLOADER_H