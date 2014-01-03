// -----------------------------------------------------------------------------
//  File        ImageResource.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/04 $
// -----------------------------------------------------------------------------

#include "FlowEngine/ImageResource.h"
#include "FlowCore/MemoryTracer.h"

#include <functional>

// -----------------------------------------------------------------------------
//  Class FImageResourceDesc
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FImageResourceDesc::FImageResourceDesc()
{
}

FImageResourceDesc::~FImageResourceDesc()
{
}

// Public queries --------------------------------------------------------------

bool FImageResourceDesc::isEqual(const FResourceDesc& other) const
{
	const FImageResourceDesc* pImageDesc
		= dynamic_cast<const FImageResourceDesc*>(&other);
	if (!pImageDesc)
		return false;

	return m_filePath == pImageDesc->m_filePath;
}

size_t FImageResourceDesc::hashCode() const
{
	return std::hash_value(m_filePath);
}

// -----------------------------------------------------------------------------
//  Class FImageResource
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FImageResource::FImageResource(
	FResourceManager* pManager, const FImageResourceDesc& desc)
: FResource(pManager),
  m_desc(desc)
{
}

FImageResource::~FImageResource()
{
}

// Public queries --------------------------------------------------------------

const FImage* FImageResource::image() const
{
	return &m_image;
}

const FImageResourceDesc& FImageResource::description() const
{
	return m_desc;
}

// Overrides -------------------------------------------------------------------

bool FImageResource::onCreate()
{
	if (!m_image.load(m_desc.filePath()))
		return false;

	size_t sysMem = m_image.bytesPerLine() * m_image.height();
	setConsumedMemory(sysMem, 0);
	return true;
}

void FImageResource::onRelease()
{
	m_image.release();
	setConsumedMemory(0, 0);
}

// -----------------------------------------------------------------------------