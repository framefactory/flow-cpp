// -----------------------------------------------------------------------------
//  File        Resource.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/04 $
// -----------------------------------------------------------------------------

#include "FlowEngine/Resource.h"
#include "FlowEngine/ResourceManager.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FResource
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FResource::FResource(FResourceManager* pManager)
: m_pManager(pManager),
  m_systemMemory(0),
  m_deviceMemory(0),
  m_refCount(1),
  m_isValid(false)
{
	F_ASSERT(pManager);
}

FResource::~FResource()
{
}

// Public commands -------------------------------------------------------------

void FResource::release()
{
}

// Internal functions ----------------------------------------------------------

void FResource::setConsumedMemory(size_t systemBytes, size_t deviceBytes)
{
	m_systemMemory = systemBytes;
	m_deviceMemory = deviceBytes;
}

bool FResource::create()
{
	if (m_isValid)
		onRelease();

	m_isValid = onCreate();
	return m_isValid;
}

void FResource::addRef()
{
	m_refCount++;
}

void FResource::releaseRef()
{
	m_refCount--;
	if (!m_refCount)
		delete this;
}

// -----------------------------------------------------------------------------