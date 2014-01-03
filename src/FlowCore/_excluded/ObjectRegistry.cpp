// -----------------------------------------------------------------------------
//  File        ObjectRegistry.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/ObjectRegistry.h"
#include "FlowCore/NamedObject.h"
#include "FlowCore/MemoryTracer.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

// -----------------------------------------------------------------------------
//  Class FObjectRegistry
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FObjectRegistry::FObjectRegistry()
{
	m_pRegistryAccess = new boost::mutex();
}

FObjectRegistry::~FObjectRegistry()
{
	F_ASSERT(m_registry.empty());
	F_SAFE_DELETE(m_pRegistryAccess);
}

// Public queries --------------------------------------------------------------

FNamedObject* FObjectRegistry::find(const FUniqueId& id) const
{
	boost::lock_guard<boost::mutex> lock(*m_pRegistryAccess);

	auto it = m_registry.find(id);
	if (it == m_registry.end())
		return NULL;

	return it->second;
}

bool FObjectRegistry::contains(const FUniqueId& id) const
{
	boost::lock_guard<boost::mutex> lock(*m_pRegistryAccess);

	auto it = m_registry.find(id);
	return (it != m_registry.end());
}

// Protected commands (FNamedObject) -------------------------------------------

void FObjectRegistry::registerObject(FNamedObject* pObject)
{
	boost::lock_guard<boost::mutex> lock(*m_pRegistryAccess);

	if (pObject->m_objectId.isNull())
		pObject->m_objectId = FUniqueId::createRandom();

	F_ASSERT(m_registry.find(pObject->id()) == m_registry.end());
	m_registry.insert(objectHash_t::value_type(pObject->id(), pObject));
}

void FObjectRegistry::unregisterObject(FNamedObject* pObject)
{
	boost::lock_guard<boost::mutex> lock(*m_pRegistryAccess);

	auto it = m_registry.find(pObject->id());
	F_ASSERT(it != m_registry.end());
	m_registry.erase(it);
}

// -----------------------------------------------------------------------------