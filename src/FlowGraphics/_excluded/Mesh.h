// -----------------------------------------------------------------------------
//  File        Mesh.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_MESH_H
#define FLOWGRAPHICS_MESH_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/PrimitiveType.h"
#include "FlowGraphics/VertexLayout.h"

#include "FlowCore/String.h"
#include "FlowCore/Vector2T.h"
#include "FlowCore/Vector3T.h"

#include <vector>

struct _meshImpl_t;

// -----------------------------------------------------------------------------
//  Class FMesh
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FMesh
{
	friend class FMeshLoader;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMesh();
	/// Copy constructor.
	FMesh(const FMesh& other);
	/// Virtual destructor.
	virtual ~FMesh();

	/// Assignment operator.
	FMesh& operator=(const FMesh& other);

	//  Public commands ----------------------------------------------

public:
	void setVertexLayout(const FVertexLayout& layout);
	void allocateData(uint32_t vertexCount, uint32_t indexCount,
		FPrimitiveType primitiveType, FDataType indexType);
	void addComponent(size_t indexOffset, size_t indexCount);

	//  Public queries -----------------------------------------------

	/// Returns true if the mesh has valid layout and data.
	bool isValid() const;

	/// Returns the vertex layout.
	const FVertexLayout& vertexLayout() const;
	/// Returns the primitive type for this mesh.
	FPrimitiveType primitiveType() const; 

	/// Returns the number of components of this mesh.
	size_t componentCount() const;
	/// Returns the position of the first index of the given component.
	size_t componentIndexOffset(size_t index) const;
	/// Returns the number of indices of the given component.
	size_t componentIndexCount(size_t index) const;
	/// Returns the number of primitives of the given component.
	size_t componentPrimitiveCount(size_t index) const;

	/// Returns the total number of vertices.
	size_t vertexCount() const;
	/// Returns the total number of indices.
	size_t indexCount() const;
	/// Returns the total number of indexed primitives.
	size_t primitiveCount() const;

	/// Returns true if the vertex data contains normals.
	bool hasNormals() const;
	/// Returns true if the vertex data contains tangents and bitangents.
	bool hasTangents() const;
	/// Returns true if the vertex data contains texture coordinates.
	bool hasTextureCoords() const;
	/// Returns true if the vertex data contains vertex colors.
	bool hasColors() const;

	/// Returns a pointer to the vertex data buffer.
	template <typename T>
	T* dataPtr(size_t vertexIndex, size_t channelIndex)
	{
		return (T*)_ptr(vertexIndex, channelIndex);
	}

	/// Returns a pointer to the vertex data buffer.
	template <typename T>
	T* dataPtr(size_t vertexIndex, FChannelType channelType)
	{
		return (T*)_ptr(vertexIndex, channelType);
	}

	/// Returns a pointer to the index data buffer.
	template <typename T>
	T* indexPtr(size_t index)
	{
		return (T*)_indexPtr(index);
	}

	/// Returns a text description of the mesh.
	wstring_t toString() const;

	//  Internal functions -------------------------------------------

private:
	uint8_t* _ptr(size_t vertexIndex, size_t channelIndex);
	uint8_t* _ptr(size_t vertexIndex, FChannelType channelType);
	uint8_t* _indexPtr(size_t index);

	void _createRef();
	void _addRef();
	void _releaseRef();

	//  Internal data members ----------------------------------------

	_meshImpl_t* m_pImpl;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_MESH_H