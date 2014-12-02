// -----------------------------------------------------------------------------
//  File        TypeInfo.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/12 $
// -----------------------------------------------------------------------------

#include "FlowCore/TypeInfo.h"
#include "FlowCore/TypeRegistry.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FTypeInfo
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FTypeInfo::FTypeInfo(const char* typeName,
    std::size_t objectSize,
    std::size_t version,
	FObject*(*pfnCreateObject)(),
	const FTypeInfo* pBaseType)
: m_typeName(typeName),
  m_objectSize(objectSize),
  m_version(version),
  m_pfnCreateObject(pfnCreateObject),
  m_pBaseType(pBaseType)
{
	m_typeId = FTypeRegistry::instance()->registerType(this);
}

// Public members --------------------------------------------------------------

FObject* FTypeInfo::createObject() const
{
	F_ASSERT(m_pfnCreateObject);
	F_ASSERT(m_version != 0xffff);

	if (!m_pfnCreateObject)
		return NULL;

	FObject* pObject = (*m_pfnCreateObject)();
	F_ASSERT(pObject);

	return pObject;
}

// -----------------------------------------------------------------------------
