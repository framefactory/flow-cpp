// -----------------------------------------------------------------------------
//  File        VertexLayout.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2014/02/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/VertexLayout.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FVertexLayout
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

FVertexLayout FVertexLayout::createP3N3T2()
{
	FVertexLayout layout;
	layout.addAttribute(FAttributeRole::Position, FValueType::Float, 3);
	layout.addAttribute(FAttributeRole::Normal, FValueType::Float, 3);
	layout.addAttribute(FAttributeRole::TexCoords, FValueType::Float, 2);
	return layout;
}

FVertexLayout FVertexLayout::createP3T2()
{
	FVertexLayout layout;
	layout.addAttribute(FAttributeRole::Position, FValueType::Float, 3);
	layout.addAttribute(FAttributeRole::TexCoords, FValueType::Float, 2);
	return layout;
}

FVertexLayout FVertexLayout::createP2T2()
{
	FVertexLayout layout;
	layout.addAttribute(FAttributeRole::Position, FValueType::Float, 2);
	layout.addAttribute(FAttributeRole::TexCoords, FValueType::Float, 2);
	return layout;
}

FVertexAttribute FVertexLayout::s_invalidAttribute;

// Constructors and destructor -------------------------------------------------

FVertexLayout::FVertexLayout()
: m_bytesPerVertex(0)
{
	for (size_t i = 0; i < ROLE_COUNT; ++i) {
		m_roleIndex[i] = -1;
	}
}

// Public commands -------------------------------------------------------------

void FVertexLayout::addAttribute(FAttributeRole role,
								 FValueType type,
								 size_t size)
{
	addAttribute(FVertexAttribute(role, type, size));
}

void FVertexLayout::addAttribute(const FVertexAttribute& attribute)
{
	m_attributes.push_back(attribute);
	size_t attribIndex = m_attributes.size() - 1;
	FVertexAttribute& attrib = m_attributes.back();

	attrib.m_offset = m_bytesPerVertex;
	attrib.m_index = attribIndex; 
	m_bytesPerVertex += attrib.byteCount();

	int role = attribute.role();
	if (m_roleIndex[role] < 0) {
		m_roleIndex[role] = attribIndex;
	}
}

void FVertexLayout::addPosition(FValueType type /* = FValueType::Float */,
								size_t size /* = 3 */)
{
	addAttribute(FAttributeRole::Position, type, size);
}

void FVertexLayout::addNormal(FValueType type /* = FValueType::Float */)
{
	addAttribute(FAttributeRole::Normal, type, 3);
}

void FVertexLayout::addTangent(FValueType type /* = FValueType::Float */)
{
	addAttribute(FAttributeRole::Tangent, type, 3);
}

void FVertexLayout::addBitangent(FValueType type /* = FValueType::Float */)
{
	addAttribute(FAttributeRole::Bitangent, type, 3);
}

void FVertexLayout::addTexCoords(FValueType type /* = FValueType::Float */,
								 size_t size /* = 2 */)
{
	addAttribute(FAttributeRole::TexCoords, type, size);
}

void FVertexLayout::addColor(FValueType type /* = FValueType::Float */,
							 size_t size /* = 3 */)
{
	addAttribute(FAttributeRole::Color, type, size);
}

void FVertexLayout::addWeight(FValueType type /* = FValueType::Float */)
{
	addAttribute(FAttributeRole::Weight, type, 1);
}

// Public queries --------------------------------------------------------------

const FVertexAttribute& FVertexLayout::attributeAt(size_t index) const
{
	F_ASSERT(index < m_attributes.size());
	return m_attributes[index];
}

size_t FVertexLayout::attributeCount(FAttributeRole role) const
{
	int index = m_roleIndex[role];
	if (index < 0) {
		return 0;
	}

	size_t count = 1;
	for (int i = index + 1; i < m_attributes.size(); ++i) {
		if (m_attributes[i].role() == role) {
			count++;
		}
	}

	return count;
}

const FVertexAttribute& FVertexLayout::attribute(FAttributeRole role,
												 size_t ordinal /* = 0 */) const
{
	int index = m_roleIndex[role];
	if (index < 0) {
		return s_invalidAttribute;
	}
	if (ordinal == 0) {
		return m_attributes[index];
	}

	for (int i = index; i < m_attributes.size(); ++i) {
		if (m_attributes[i].role() == role) {
			ordinal--;
			if (ordinal == 0) {
				return m_attributes[i];
			}
		}
	}

	return s_invalidAttribute;
}

const FVertexAttribute& FVertexLayout::position(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::Position, ordinal);
}

const FVertexAttribute& FVertexLayout::normal(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::Normal, ordinal);
}

const FVertexAttribute& FVertexLayout::tangent(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::Tangent, ordinal);
}

const FVertexAttribute& FVertexLayout::bitangent(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::Bitangent, ordinal);
}

const FVertexAttribute& FVertexLayout::texCoords(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::TexCoords, ordinal);
}

const FVertexAttribute& FVertexLayout::color(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::Color, ordinal);
}

const FVertexAttribute& FVertexLayout::weight(size_t ordinal /* = 0 */) const
{
	return attribute(FAttributeRole::Weight, ordinal);
}

QString FVertexLayout::toString(bool verbose /* = false */) const
{
	QString text = QString("Vertex Layout (%1 attributes, %2 bytes per vertex)")
		.arg(m_attributes.size()).arg(m_bytesPerVertex);

	if (verbose) {
		for (size_t i = 0; i < m_attributes.size(); ++i) {
			text += "\n  " + m_attributes[i].toString();
		}
	}

	return text;
}

// -----------------------------------------------------------------------------