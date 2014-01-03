// -----------------------------------------------------------------------------
//  File        Instance.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/03 $
// -----------------------------------------------------------------------------

#include "FlowCore/Instance.h"
#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <ostream>


// -----------------------------------------------------------------------------
//  Class FInstance
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FInstance, FNamedObject);

// Constructors and destructor -------------------------------------------------

FInstance::FInstance(const FUniqueId& id,
	                 FInstance* pMaster /* = NULL */)
: FNamedObject(id),
  m_pMaster(pMaster),
  m_autoDelete(false)
{
	if (pMaster)
	{
		pMaster->_addReference(this);
		setName(pMaster->name());
	}
}

FInstance::FInstance(const FUniqueId& id,
	                 const wstring_t& name,
					 FInstance* pMaster /* = NULL */)
: FNamedObject(id, name),
  m_pMaster(pMaster),
  m_autoDelete(false)
{
	if (pMaster)
		pMaster->_addReference(this);
}

FInstance::~FInstance()
{
	if (m_pMaster)
		m_pMaster->_removeReference(this);
}

// Public commands -------------------------------------------------------------

void FInstance::makeUnique()
{
	if (!m_pMaster)
		return;

	onMakeUnique();
	m_pMaster->_removeReference(this);
}

void FInstance::setAutoDelete(bool state)
{
	m_autoDelete = state;
}

void FInstance::serialize(FArchive& ar)
{
	FNamedObject::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_pMaster;
		ar << m_references;
	}
	else // is reading
	{
		ar >> m_pMaster;
		ar >> m_references;
	}
}

// Public queries --------------------------------------------------------------

bool FInstance::isMasterOf(FInstance* pInstance) const
{
	for (size_t i = 0, n = m_references.size(); i < n; ++i)
		if (m_references[i] == pInstance)
			return true;

	return false;
}

bool FInstance::isSiblingOf(FInstance* pInstance) const
{
	if (pInstance == this)
		return true;

	if (!m_pMaster)
		return false;

	for (size_t i = 0, n = m_pMaster->m_references.size(); i < n; ++i)
		if (m_pMaster->m_references[i] == pInstance)
			return true;

	return false;
}

#ifdef FLOW_DEBUG
void FInstance::dump(std::wostream& stream) const
{
	FNamedObject::dump(stream);
	stream << "\n--- FInstance ---";
	stream << "\n     Is master:   " << isMaster();
	stream << "\n     #References: " << referenceCount();
}
#endif

// Internal functions ----------------------------------------------------------

void FInstance::notifyMaster()
{
	if (m_pMaster)
		m_pMaster->onReferenceChanged(this);
}

void FInstance::notifyReferences()
{
	for (size_t i = 0, n = m_references.size(); i < n; ++i)
		m_references[i]->onMasterChanged(this);
}

void FInstance::_addReference(FInstance* pInstance)
{
	F_ASSERT(!pInstance->isReference());
	pInstance->m_pMaster = this;
	m_references.push_back(pInstance);
	onReferenceAdded(pInstance);
}

void FInstance::_removeReference(FInstance* pInstance)
{
	F_ASSERT(pInstance->isReferenceOf(this));
	
	pInstance->m_pMaster = NULL;
	for (size_t i = 0, n = m_references.size(); i < n; ++i)
	{
		if (m_references[i] == pInstance)
		{
			m_references.erase(m_references.begin() + i);
			break;
		}
	}

	onReferenceRemoved(pInstance);

	if (m_autoDelete && m_references.empty())
		delete this;
}

// -----------------------------------------------------------------------------