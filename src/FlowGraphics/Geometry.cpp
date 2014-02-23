// -----------------------------------------------------------------------------
//  File        Geometry.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/Geometry.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FGeometry
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

FVertexLayout FGeometry::s_invalidLayout;

// Constructors and destructor -------------------------------------------------

FGeometry::FGeometry()
: m_pImpl(NULL)
{
}

FGeometry::FGeometry(const FGeometry& other)
{
	m_pImpl = other.m_pImpl;
	_addRef();
}

FGeometry::~FGeometry()
{
	_releaseRef();
}

FGeometry& FGeometry::operator=(const FGeometry& other)
{
	if (this == &other) {
		return *this;
	}

	_releaseRef();
	m_pImpl = other.m_pImpl;
	_addRef();
	return *this;
}

// Public commands -------------------------------------------------------------

void FGeometry::allocate(FVertexLayout layout,
						 size_t vertexCount,
						 FValueType indexType,
						 size_t indexCount)
{
	allocateVertices(layout, vertexCount);
	allocateIndices(indexType, indexCount);
}

void FGeometry::allocateVertices(FVertexLayout layout,
								 size_t count)
{
	if (!m_pImpl) {
		_createRef();
	}

	m_pImpl->vertexLayout = layout;
	size_t attribCount = layout.attributeCount();
	m_pImpl->vertexData.resize(attribCount);

	for (size_t i = 0; i < attribCount; ++i) {
		const FVertexAttribute& attrib = layout.attributeAt(i);
		m_pImpl->vertexData[i].allocate(attrib.type(), count, attrib.size());
	}
}

void FGeometry::allocateIndices(FValueType indexType,
								size_t count)
{
	if (!m_pImpl) {
		_createRef();
	}

	m_pImpl->indexData.allocate(indexType, count, 1);
}

void FGeometry::resizeVertices(size_t count)
{
	if (!m_pImpl) {
		return;
	}

	for (size_t i = 0; i < m_pImpl->vertexData.size(); ++i) {
		m_pImpl->vertexData[i].setChannelCount(count, true);
	}
}

void FGeometry::copyVertex(size_t fromIndex, size_t toIndex)
{
	if (!m_pImpl) {
		return;
	}

	for (size_t i = 0; i < m_pImpl->vertexData.size(); ++i) {
		FValueArray& va = m_pImpl->vertexData[i];
		size_t dimCount = va.dimensionCount();
		va.convertFrom(va, fromIndex, toIndex, 1, 1, 1, 0, 0, dimCount);
	}
}

void FGeometry::setPrimitiveType(FPrimitiveType primitiveType)
{
	if (!m_pImpl) {
		_createRef();
	}

	m_pImpl->primitiveType = primitiveType;
}

// Public queries --------------------------------------------------------------

QByteArray FGeometry::vertexData(const FVertexAttribute& attrib) const
{
	if (!m_pImpl || !m_pImpl->vertexData.size()) {
		return QByteArray();
	}

	const FValueArray& va = m_pImpl->vertexData[attrib.index()];
	return va.toByteArray();
}

QByteArray FGeometry::interleavedVertexData() const
{
	if (!m_pImpl || !m_pImpl->vertexData.size()) {
		return QByteArray();
	}

	const FVertexLayout& layout = m_pImpl->vertexLayout;

	size_t bytesPerVertex = layout.bytesPerVertex();
	size_t vertexCount = m_pImpl->vertexData[0].channelCount();
	QByteArray buffer;
	buffer.resize(vertexCount * bytesPerVertex);
	char* pDstData = buffer.data();

	size_t attribCount = m_pImpl->vertexData.size();
	for (size_t i = 0; i < attribCount; ++i) {
		const FVertexAttribute& attrib = layout.attributeAt(i);
		const FValueArray& va = m_pImpl->vertexData[i];
		size_t attribBytes = va.type().byteCount() * va.dimensionCount();
		size_t attribOffset = attrib.byteOffset();
		const char* pSrcData = va.rawPtr();

		for (size_t j = 0; j < vertexCount; ++j) {
			const char* pSrcAttrib = pSrcData + j * attribBytes;
			char* pDstAttrib = pDstData + j * bytesPerVertex + attribOffset;
			memcpy(pDstAttrib, pSrcAttrib, attribBytes);
		}
	}

	return buffer;
}

QByteArray FGeometry::indexData() const
{
	if (!m_pImpl || !m_pImpl->indexData.channelCount()) {
		return QByteArray();
	}

	return m_pImpl->indexData.toByteArray();
}

const FVertexLayout& FGeometry::vertexLayout() const
{
	if (!m_pImpl) {
		return s_invalidLayout;
	}

	return m_pImpl->vertexLayout;
}

FPrimitiveType FGeometry::primitiveType() const
{
	if (!m_pImpl) {
		return FPrimitiveType::Undefined;
	}

	return m_pImpl->primitiveType;
}

FValueType FGeometry::indexType() const
{
	if (!m_pImpl) {
		return FValueType::Invalid;
	}

	return m_pImpl->indexData.type();
}

size_t FGeometry::vertexCount() const
{
	if (!m_pImpl || !m_pImpl->vertexData.size()) {
		return 0;
	}

	return m_pImpl->vertexData[0].channelCount();
}

size_t FGeometry::indexCount() const
{
	if (!m_pImpl) {
		return 0;
	}

	return m_pImpl->indexData.channelCount();
}

QString FGeometry::toString() const
{
	if (!m_pImpl) {
		return "Invalid geometry";
	}

	return QString("Geometry (Primitive Type: %1, Vertices: %2, Indices: %3)")
		.arg(m_pImpl->primitiveType.name())
		.arg(m_pImpl->vertexData.size() > 0 ? m_pImpl->vertexData[0].channelCount() : 0)
		.arg(m_pImpl->indexData.channelCount());
}

// Internal functions ----------------------------------------------------------

void FGeometry::_createRef()
{
	F_ASSERT(!m_pImpl);
	m_pImpl = new _geometryImpl_t();
	m_pImpl->refCount = 1;
}

void FGeometry::_addRef()
{
	if (m_pImpl) {
		m_pImpl->refCount++;
	}
}

void FGeometry::_releaseRef()
{
	if (m_pImpl) {
		m_pImpl->refCount--;
		if (!m_pImpl->refCount)	{
			delete m_pImpl;
		}

		m_pImpl = NULL;
	}
}

// -----------------------------------------------------------------------------