// -----------------------------------------------------------------------------
//  File        Geometry.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_GEOMETRY_H
#define FLOWGRAPHICS_GEOMETRY_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/VertexLayout.h"
#include "FlowGraphics/PrimitiveType.h"
#include "FlowGraphics/DataType.h"
#include "FlowGraphics/Transform.h"

struct _geometryImpl_t;

// -----------------------------------------------------------------------------
//  Class FGeometryPart
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FGeometryPart
{
public:
	FGeometryPart(uint32_t start, uint32_t count)
		: m_indexStart(start), m_indexCount(count) { }

	/// Returns the position of the index of the first vertex of this geometry part.
	uint32_t indexStart() const { return m_indexStart; }
	/// Returns the number of indices in this geometry part.
	uint32_t indexCount() const { return m_indexCount; }

private:
	uint32_t m_indexStart;
	uint32_t m_indexCount;
};

// -----------------------------------------------------------------------------
//  Class FGeometry
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FGeometry
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FGeometry();
	/// Virtual destructor.
	virtual ~FGeometry();

	//  Public commands ----------------------------------------------

public:
	/// Transforms all vertices.
	void transform(const FTransform& transform);

	//  Public queries -----------------------------------------------

	/// Returns the vertex layout.
	const FVertexLayout& vertexLayout() const;
	/// Returns the primitive type for this mesh.
	FPrimitiveType primitiveType() const;

	/// Returns the number of parts.
	size_t partCount() const;
	/// Returns the part at the given index.
	const FGeometryPart& partAt(size_t index) const;

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

	//  Protected functions ------------------------------------------

protected:
	/// Allocate memory for vertex and index data.
	void allocate(const FVertexLayout& layout,
		uint32_t vertexCount, uint32_t indexCount,
		FPrimitiveType primitiveType, FDataType indexType);

	/// Adds a part definition to the geometry.
	void addPart(size_t indexStart, size_t indexCount);

	//  Internal functions -------------------------------------------

private:
	uint8_t* _ptr(size_t vertexIndex, size_t channelIndex);
	uint8_t* _ptr(size_t vertexIndex, FChannelType channelType);
	uint8_t* _indexPtr(size_t index);

	//  Internal data members ----------------------------------------

	FVertexLayout m_layout;
	FPrimitiveType m_primitiveType;
	FDataType m_indexType;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_GEOMETRY_H