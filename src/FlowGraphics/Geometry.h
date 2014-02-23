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

#include "FlowCore/ValueArray.h"

#include <QString>

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
	/// Default constructor.
	FGeometry();
	/// Copy constructor.
	FGeometry(const FGeometry& other);
	/// Assignment operator.
	FGeometry& operator=(const FGeometry& other);

	/// Virtual destructor.
	virtual ~FGeometry();

	//  Public commands ----------------------------------------------

public:
	void allocate(FVertexLayout layout, size_t vertexCount,
		FValueType indexType, size_t indexCount);

	void allocateVertices(FVertexLayout layout, size_t count);
	
	void allocateIndices(FValueType indexType, size_t count);

	void resizeVertices(size_t count);

	void copyVertex(size_t fromIndex, size_t toIndex);
	
	void setPrimitiveType(FPrimitiveType primitiveType);

	template<typename T>
	void setValue(const FVertexAttribute& attrib, size_t vertexIndex, const T& value);
	template<typename T>
	void setVector2(const FVertexAttribute& attrib, size_t vertexIndex,	const FVector2T<T>& vector);
	template<typename T>
	void setVector3(const FVertexAttribute& attrib, size_t vertexIndex,	const FVector3T<T>& vector);
	template<typename T>
	void setVector4(const FVertexAttribute& attrib, size_t vertexIndex,	const FVector4T<T>& vector);

	template<typename T>
	const T& getValue(const FVertexAttribute& attrib, size_t vertexIndex) const;
	template<typename T>
	const FVector2T<T>& getVector2(const FVertexAttribute& attrib, size_t vertexIndex) const;
	template<typename T>
	const FVector3T<T>& getVector3(const FVertexAttribute& attrib, size_t vertexIndex) const;
	template<typename T>
	const FVector4T<T>& getVector4(const FVertexAttribute& attrib, size_t vertexIndex) const;

	template<typename T>
	void setIndex(size_t index, const T& vertexIndex);
	template<typename T>
	const T& getIndex(size_t index) const;

	//  Public queries -----------------------------------------------

	/// Returns true if this geometry object contains no data.
	bool isNull() const { return !m_pImpl; }

	/// Returns a byte array with the vertex data of the given attribute.
	QByteArray vertexData(const FVertexAttribute& attrib) const;
	/// Returns a byte array with interleaved vertex data.
	QByteArray interleavedVertexData() const;
	/// Returns a byte array with index data.
	QByteArray indexData() const;

	/// Returns the vertex layout.
	const FVertexLayout& vertexLayout() const;
	/// Returns the primitive type for this mesh.
	FPrimitiveType primitiveType() const;
	/// Returns the value type of the index data.
	FValueType indexType() const;

	/// Returns the total number of vertices.
	size_t vertexCount() const;
	/// Returns the total number of indices.
	size_t indexCount() const;

	/// Returns a text representation of the geometry.
	QString toString() const;

	//  Internal functions -------------------------------------------

private:
	void _createRef();
	void _addRef();
	void _releaseRef();

	//  Internal data members ----------------------------------------

	struct _geometryImpl_t
	{
		FVertexLayout vertexLayout;
		FPrimitiveType primitiveType;

		std::vector<FValueArray> vertexData;
		FValueArray indexData;

		uint32_t refCount;
	};

	_geometryImpl_t* m_pImpl;

	static FVertexLayout s_invalidLayout;
};

// Template members ------------------------------------------------------------

template<typename T>
inline void FGeometry::setValue(const FVertexAttribute& attrib,
								size_t vertexIndex,
								const T& value)
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	F_ASSERT(vertexIndex < va.channelCount());
	va.as<T>(vertexIndex) = value;
}

template<typename T>
inline void FGeometry::setVector2(const FVertexAttribute& attrib,
								  size_t vertexIndex,
								  const FVector2T<T>& vector)
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	F_ASSERT(vertexIndex < va.channelCount() && attrib.size() == 2);
	va.asVector2<T>(vertexIndex) = vector;
}

template<typename T>
inline void FGeometry::setVector3(const FVertexAttribute& attrib,
								  size_t vertexIndex,
								  const FVector3T<T>& vector)
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	F_ASSERT(vertexIndex < va.channelCount() && attrib.size() == 3);
	va.asVector3<T>(vertexIndex) = vector;
}

template<typename T>
inline void FGeometry::setVector4(const FVertexAttribute& attrib,
								  size_t vertexIndex,
								  const FVector4T<T>& vector)
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	F_ASSERT(vertexIndex < va.channelCount() && attrib.size() == 4);
	va.asVector4<T>(vertexIndex) = vector;
}

template<typename T>
inline const T& FGeometry::getValue(const FVertexAttribute& attrib,
									size_t vertexIndex) const
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	return va.as<T>(vertexIndex);
}

template<typename T>
inline const FVector2T<T>& FGeometry::getVector2(const FVertexAttribute& attrib,
												 size_t vertexIndex) const
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	return va.asVector2<T>(vertexIndex);
}

template<typename T>
inline const FVector3T<T>& FGeometry::getVector3(const FVertexAttribute& attrib,
												 size_t vertexIndex) const
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	return va.asVector3<T>(vertexIndex);
}

template<typename T>
inline const FVector4T<T>& FGeometry::getVector4(const FVertexAttribute& attrib,
												 size_t vertexIndex) const
{
	FValueArray& va = m_pImpl->vertexData[attrib.index()];
	return va.asVector4<T>(vertexIndex);
}

template <typename T>
inline void FGeometry::setIndex(size_t index, const T& vertexIndex)
{
	m_pImpl->indexData.as<T>(index) = vertexIndex;
}

template <typename T>
inline const T& FGeometry::getIndex(size_t index) const
{
	return m_pImpl->indexData.as<T>(index);
}
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_GEOMETRY_H