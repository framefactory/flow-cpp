// -----------------------------------------------------------------------------
//  File        Mesh.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/Mesh.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FMesh
// -----------------------------------------------------------------------------

// Implementation --------------------------------------------------------------

struct _meshComponent_t
{
	size_t indexOffset;
	size_t indexCount;
};

struct _meshImpl_t
{
	FVertexLayout layout;
	FPrimitiveType primitiveType;
	FDataType indexType;
	uint8_t* pVertexData;
	uint8_t* pIndexData;
	uint32_t vertexCount;
	uint32_t indexCount;
	std::vector<_meshComponent_t> components;
	uint32_t refCount;
};

// Constructors and destructor -------------------------------------------------

FMesh::FMesh()
: m_pImpl(NULL)
{
	_createRef();
}

FMesh::FMesh(const FMesh& other)
{
	m_pImpl = other.m_pImpl;
	_addRef();
}

FMesh::~FMesh()
{
	_releaseRef();
}

FMesh& FMesh::operator=(const FMesh& other)
{
	if (&other == this)
		return *this;

	_releaseRef();
	m_pImpl = other.m_pImpl;
	_addRef();
	return *this;
}

// Public commands -------------------------------------------------------------

void FMesh::setVertexLayout(const FVertexLayout& layout)
{
	F_ASSERT(layout.bytesPerVertex() > 0);

	if (m_pImpl->pVertexData)
	{
		delete[] m_pImpl->pVertexData;
		m_pImpl->pVertexData = NULL;
	}

	m_pImpl->layout = layout;
}

void FMesh::allocateData(uint32_t vertexCount,
						 uint32_t indexCount,
						 FPrimitiveType primitiveType,
						 FDataType indexType)
{
	F_ASSERT(vertexCount > 0);
	F_ASSERT(indexCount > 0);
	F_ASSERT(indexType == FDataType::UShort || indexType == FDataType::UInt);
	F_ASSERT(m_pImpl->layout.bytesPerVertex() > 0);

	if (m_pImpl->pVertexData)
		delete[] m_pImpl->pVertexData;

	if (m_pImpl->pIndexData)
		delete[] m_pImpl->pIndexData;

	m_pImpl->primitiveType = primitiveType;
	m_pImpl->vertexCount = vertexCount;
	m_pImpl->indexCount = indexCount;

	size_t numBytes = m_pImpl->layout.bytesPerVertex() * vertexCount;
	m_pImpl->pVertexData = new uint8_t[numBytes];

	m_pImpl->indexType = indexType;
	numBytes = indexType.size() * indexCount;
	m_pImpl->pIndexData = new uint8_t[numBytes];
}

void FMesh::addComponent(size_t indexOffset, size_t indexCount)
{
	_meshComponent_t component;
	component.indexOffset = indexOffset;
	component.indexCount = indexCount;
	m_pImpl->components.push_back(component);
}

// Public queries --------------------------------------------------------------

bool FMesh::isValid() const
{
	bool isValid = m_pImpl && m_pImpl->pVertexData && m_pImpl->pIndexData;
	F_ASSERT(!isValid || (isValid && m_pImpl->vertexCount > 0));
	F_ASSERT(!isValid || (isValid && m_pImpl->indexCount > 0));
	return isValid;
}

const FVertexLayout& FMesh::vertexLayout() const
{
	return m_pImpl->layout;
}

FPrimitiveType FMesh::primitiveType() const
{
	return m_pImpl->primitiveType;
}

size_t FMesh::componentCount() const
{
	return m_pImpl->components.size();
}

size_t FMesh::componentIndexOffset(size_t index) const
{
	F_ASSERT(index < m_pImpl->components.size());
	return m_pImpl->components[index].indexOffset;
}

size_t FMesh::componentIndexCount(size_t index) const
{
	F_ASSERT(index < m_pImpl->components.size());
	return m_pImpl->components[index].indexCount;
}

size_t FMesh::componentPrimitiveCount(size_t index) const
{
	F_ASSERT(index < m_pImpl->components.size());
	return m_pImpl->components[index].indexCount / m_pImpl->primitiveType.vertexCount();
}

size_t FMesh::vertexCount() const
{
	return m_pImpl->vertexCount;
}

size_t FMesh::indexCount() const
{
	return m_pImpl->indexCount;
}

size_t FMesh::primitiveCount() const
{
	return m_pImpl->indexCount / m_pImpl->primitiveType.vertexCount();
}

bool FMesh::hasNormals() const
{
	return m_pImpl->layout.hasNormals();
}

bool FMesh::hasTangents() const
{
	return m_pImpl->layout.hasTangents();
}

bool FMesh::hasTextureCoords() const
{
	return m_pImpl->layout.hasTextureCoords();
}

bool FMesh::hasColors() const
{
	return m_pImpl->layout.hasColors();
}

wstring_t FMesh::toString() const
{
	std::wostringstream stream;

	stream << primitiveType().name() << " mesh, " << vertexCount() << " vertices, " << indexCount() << " indices, "
		<< primitiveCount() << " " << primitiveType().name() << "s" << std::endl;
	stream << "Normals: " << (hasNormals() ? "yes" : "no") << ", tangents: " << (hasTangents() ? "yes" : "no")
		<< ", texture coords: " << (hasTextureCoords() ? "yes" : "no") << ", colors: " << (hasColors() ? "yes" : "no") << std::endl;

	return stream.str();
}

// Internal functions ----------------------------------------------------------

uint8_t* FMesh::_ptr(size_t vertexIndex, size_t channelIndex)
{
	size_t byteOffset = 0;
	for (size_t i = 0; i < channelIndex; ++i)
		byteOffset += m_pImpl->layout.bytesPerChannel(i);
	byteOffset *= m_pImpl->vertexCount;
	byteOffset += vertexIndex * m_pImpl->layout.bytesPerChannel(channelIndex);

	return m_pImpl->pVertexData + byteOffset;
}

uint8_t* FMesh::_ptr(size_t vertexIndex, FChannelType channelType)
{
	int channelIndex = m_pImpl->layout.channelIndex(channelType);
	F_ASSERT(channelIndex >= 0);
	if (channelIndex < 0)
		return NULL;

	return _ptr(vertexIndex, channelIndex);
}

uint8_t* FMesh::_indexPtr(size_t index)
{
	return m_pImpl->pIndexData + index * m_pImpl->indexType.size();
}

void FMesh::_createRef()
{
	F_ASSERT(!m_pImpl);
	m_pImpl = new _meshImpl_t();
	m_pImpl->refCount = 1;
	m_pImpl->pVertexData = NULL;
	m_pImpl->pIndexData = NULL;
	m_pImpl->vertexCount = 0;
	m_pImpl->indexCount = 0;
}

void FMesh::_addRef()
{
	if (m_pImpl)
		m_pImpl->refCount++;
}

void FMesh::_releaseRef()
{
	if (m_pImpl)
	{
		m_pImpl->refCount--;
		if (!m_pImpl->refCount)
		{
			if (m_pImpl->pVertexData)
				delete[] m_pImpl->pVertexData;
			if (m_pImpl->pIndexData)
				delete[] m_pImpl->pIndexData;
			delete m_pImpl;
		}

		m_pImpl = NULL;
	}
}

// -----------------------------------------------------------------------------