// -----------------------------------------------------------------------------
//  File        VertexLayout.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2014/02/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_VERTEXLAYOUT_H
#define FLOWGRAPHICS_VERTEXLAYOUT_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/AttributeRole.h"
#include "FlowCore/ValueType.h"

#include <QString>
#include <vector>

// -----------------------------------------------------------------------------
//  Struct FVertexAttribute
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FVertexAttribute
{
	friend class FVertexLayout;

public:
	FVertexAttribute()
		: m_size(0), m_offset(0), m_index(0) { }

	FVertexAttribute(FAttributeRole role, FValueType type, size_t size)
		: m_role(role), m_type(type), m_size(size), m_offset(0) { }

	bool isValid() const { return m_role != FAttributeRole::Undefined; }

	FAttributeRole role() const { return m_role; }
	FValueType type() const { return m_type; }
	size_t size() const { return m_size; }
	size_t index() const { return m_index; }
	size_t byteOffset() const { return m_offset; }
	size_t byteCount() const { return m_size * m_type.byteCount(); } 

	QString toString() const {
		return QString("Attribute #%1: %2 (%3 x %4), bytes: %5, offset: %6")
			.arg(m_index).arg(m_role.name()).arg(m_type.name()).arg(m_size)
			.arg(byteCount()).arg(byteOffset());
	}

private:
	FAttributeRole m_role;
	FValueType m_type;
	size_t m_size;
	size_t m_offset;
	size_t m_index;
};

// -----------------------------------------------------------------------------
//  Class FVertexLayout
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FVertexLayout
{
	//  Static members -----------------------------------------------

public:
	static FVertexLayout createP3N3T2();
	static FVertexLayout createP3T2();
	static FVertexLayout createP2T2();

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FVertexLayout();

	//  Public commands ----------------------------------------------

public:
	void addAttribute(FAttributeRole role, FValueType type, size_t size);
	void addAttribute(const FVertexAttribute& attribute);
	void addPosition(FValueType type = FValueType::Float, size_t size = 3);
	void addNormal(FValueType type = FValueType::Float);
	void addTangent(FValueType type = FValueType::Float);
	void addBitangent(FValueType type = FValueType::Float);
	void addTexCoords(FValueType type = FValueType::Float, size_t size = 2);
	void addColor(FValueType type = FValueType::Float, size_t size = 3);
	void addWeight(FValueType type = FValueType::Float);

	//  Public queries -----------------------------------------------

	size_t bytesPerVertex() const { return m_bytesPerVertex; }
	size_t attributeCount() const { return m_attributes.size(); }
	size_t attributeCount(FAttributeRole role) const;
	const FVertexAttribute& attributeAt(size_t index) const;
	
	const FVertexAttribute& attribute(FAttributeRole role, size_t ordinal = 0) const;
	const FVertexAttribute& position(size_t ordinal = 0) const;
	const FVertexAttribute& normal(size_t ordinal = 0) const;
	const FVertexAttribute& tangent(size_t ordinal = 0) const;
	const FVertexAttribute& bitangent(size_t ordinal = 0) const;
	const FVertexAttribute& texCoords(size_t ordinal = 0) const;
	const FVertexAttribute& color(size_t ordinal = 0) const;
	const FVertexAttribute& weight(size_t ordinal = 0) const;

	bool hasAttribute(FAttributeRole role) const { return m_roleIndex[role] >= 0; }
	bool hasPosition() const { return m_roleIndex[FAttributeRole::Position] >= 0; }
	bool hasNormal() const { return m_roleIndex[FAttributeRole::Normal] >= 0; }
	bool hasTangent() const { return m_roleIndex[FAttributeRole::Tangent] >= 0; }
	bool hasBitangent() const { return m_roleIndex[FAttributeRole::Bitangent] >= 0; }
	bool hasTexCoords() const { return m_roleIndex[FAttributeRole::TexCoords] >= 0; }
	bool hasColor() const { return m_roleIndex[FAttributeRole::Color] >= 0; }
	bool hasWeight() const { return m_roleIndex[FAttributeRole::Weight] >= 0; }

	QString toString(bool verbose = false) const;

	//  Internal data members ----------------------------------------

private:
	static FVertexAttribute s_invalidAttribute;

	typedef std::vector<FVertexAttribute> attribVec_t;
	attribVec_t m_attributes;

	static const size_t ROLE_COUNT = FAttributeRole::Custom + 1;
	int m_roleIndex[ROLE_COUNT];

	size_t m_bytesPerVertex;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_VERTEXLAYOUT_H