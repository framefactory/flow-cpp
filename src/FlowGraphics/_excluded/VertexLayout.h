// -----------------------------------------------------------------------------
//  File        VertexLayout.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_VERTEXLAYOUT_H
#define FLOWGRAPHICS_VERTEXLAYOUT_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/DataType.h"
#include "FlowGraphics/ChannelType.h"

#include "FlowCore/String.h"

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

	/// Default Constructor.
	FVertexLayout();

	//  Public commands ----------------------------------------------

	void addChannel(FDataType dataType, FChannelType channelType = FChannelType::Custom);
	void addPosition(FDataType dataType = FDataType::Float3);
	void addNormal(FDataType dataType = FDataType::Float3);
	void addTangentAndBitangent(FDataType dataType = FDataType::Float3);
	void addTextureCoords(FDataType dataType = FDataType::Float2);
	void addColor(FDataType dataType = FDataType::UByte4);

	//  Public queries -----------------------------------------------

	size_t bytesPerVertex() const { return m_bytesPerVertex; }
	int channelIndex(FChannelType type) const;
	FChannelType channelType(size_t index) const;
	FDataType dataType(size_t index) const;
	FDataType dataType(FChannelType type) const;
	size_t bytesPerChannel(size_t index) const;
	size_t bytesPerChannel(FChannelType type) const;
	size_t channelByteOffset(size_t index) const;
	size_t channelByteOffset(FChannelType type) const;

	bool hasChannel(FChannelType type) const { return m_channelIndex[type] >= 0; }
	bool hasPositions() const { return m_channelIndex[FChannelType::Position] >= 0; }
	bool hasNormals() const { return m_channelIndex[FChannelType::Normal] >= 0; }
	bool hasTangents() const { return m_channelIndex[FChannelType::Tangent] >= 0; }
	bool hasBitangents() const { return m_channelIndex[FChannelType::Bitangent] >= 0; }
	bool hasTextureCoords() const { return m_channelIndex[FChannelType::TexCoord] >= 0; }
	bool hasColors() const { return m_channelIndex[FChannelType::Color] >= 0; }

	wstring_t toString() const;

	//  Internal data members ----------------------------------------

private:
	struct channel_t
	{
		FDataType dataType;
		FChannelType channelType;
		size_t byteOffset;
	};

	std::vector<channel_t> m_channels;
	static const size_t CHANNELTYPE_COUNT = FChannelType::Custom + 1;
	int m_channelIndex[CHANNELTYPE_COUNT];
	size_t m_bytesPerVertex;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_VERTEXLAYOUT_H