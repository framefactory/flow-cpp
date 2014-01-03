// -----------------------------------------------------------------------------
//  File        VertexLayout.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/VertexLayout.h"

#include <sstream>

// -----------------------------------------------------------------------------
//  Class FVertexLayout
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

FVertexLayout FVertexLayout::createP3N3T2()
{
	FVertexLayout layout;
	layout.addChannel(FDataType::Float3, FChannelType::Position);
	layout.addChannel(FDataType::Float3, FChannelType::Normal);
	layout.addChannel(FDataType::Float2, FChannelType::TexCoord);
	return layout;
}

FVertexLayout FVertexLayout::createP3T2()
{
	FVertexLayout layout;
	layout.addChannel(FDataType::Float3, FChannelType::Position);
	layout.addChannel(FDataType::Float2, FChannelType::TexCoord);
	return layout;
}

FVertexLayout FVertexLayout::createP2T2()
{
	FVertexLayout layout;
	layout.addChannel(FDataType::Float2, FChannelType::Position);
	layout.addChannel(FDataType::Float2, FChannelType::TexCoord);
	return layout;
}

// Constructors and destructor -------------------------------------------------

FVertexLayout::FVertexLayout()
: m_bytesPerVertex(0)
{
	for (size_t i = 0; i < CHANNELTYPE_COUNT; ++i)
		m_channelIndex[i] = -1;
}

// Public commands -------------------------------------------------------------

void FVertexLayout::addChannel(FDataType dataType,
							 FChannelType channelType /* = FChannelType::Custom */)
{
	channel_t channel = { dataType, channelType, m_bytesPerVertex };
	m_channels.push_back(channel);
	m_bytesPerVertex += dataType.size();
}

void FVertexLayout::addPosition(FDataType dataType /* = FDataType::Float3 */)
{
	if (m_channelIndex[FChannelType::Position] < 0)
		m_channelIndex[FChannelType::Position] = (int)m_channels.size();
	
	addChannel(dataType, FChannelType::Position);
}

void FVertexLayout::addNormal(FDataType dataType /* = FDataType::Float3 */)
{
	if (m_channelIndex[FChannelType::Normal] < 0)
		m_channelIndex[FChannelType::Normal] = (int)m_channels.size();
	
	addChannel(dataType, FChannelType::Normal);
}

void FVertexLayout::addTangentAndBitangent(FDataType dataType /* = FDataType::Float3 */)
{
	if (m_channelIndex[FChannelType::Tangent] < 0)
		m_channelIndex[FChannelType::Tangent] = (int)m_channels.size();
	
	addChannel(dataType, FChannelType::Tangent);

	if (m_channelIndex[FChannelType::Bitangent] < 0)
		m_channelIndex[FChannelType::Bitangent] = (int)m_channels.size();

	addChannel(dataType, FChannelType::Bitangent);
}

void FVertexLayout::addTextureCoords(FDataType dataType /* = FDataType::Float2 */)
{
	if (m_channelIndex[FChannelType::TexCoord] < 0)
		m_channelIndex[FChannelType::TexCoord] = (int)m_channels.size();

	addChannel(dataType, FChannelType::TexCoord);
}

void FVertexLayout::addColor(FDataType dataType /* = FDataType::UByte4 */)
{
	if (m_channelIndex[FChannelType::Color] < 0)
		m_channelIndex[FChannelType::Color] = (int)m_channels.size();
	
	addChannel(dataType, FChannelType::Color);
}

// Public queries --------------------------------------------------------------

int FVertexLayout::channelIndex(FChannelType type) const
{
	return m_channelIndex[type];
}

FChannelType FVertexLayout::channelType(size_t index) const
{
	F_ASSERT(index < m_channels.size());
	return m_channels[index].channelType;
}

FDataType FVertexLayout::dataType(size_t index) const
{
	F_ASSERT(index < m_channels.size());
	return m_channels[index].dataType;
}

FDataType FVertexLayout::dataType(FChannelType type) const
{
	F_ASSERT(hasChannel(type));
	int index = m_channelIndex[type];
	return m_channels[index].dataType;
}

size_t FVertexLayout::bytesPerChannel(size_t index) const
{
	F_ASSERT(index < m_channels.size());
	return m_channels[index].dataType.size();
}

size_t FVertexLayout::bytesPerChannel(FChannelType type) const
{
	F_ASSERT(hasChannel(type));
	int index = m_channelIndex[type];
	return m_channels[index].dataType.size();
}

size_t FVertexLayout::channelByteOffset(size_t index) const
{
	F_ASSERT(index < m_channels.size());
	return m_channels[index].byteOffset;
}

size_t FVertexLayout::channelByteOffset(FChannelType type) const
{
	F_ASSERT(hasChannel(type));
	int index = m_channelIndex[type];
	return m_channels[index].byteOffset;
}

wstring_t FVertexLayout::toString() const
{
	std::wostringstream stream;

	stream << "Vertex Layout, " << m_bytesPerVertex << " bytes per vertex" << std::endl;
	for (size_t i = 0; i < m_channels.size(); ++i)
	{
		stream << i << ": " << m_channels[i].dataType.name();
		stream << " (" << m_channels[i].channelType.name();
		stream << "), Offset: " << m_channels[i].byteOffset << " bytes" << std::endl;
	}

	return stream.str();
}

// -----------------------------------------------------------------------------