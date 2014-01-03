// -----------------------------------------------------------------------------
//  File        TypeRegistry.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/06 $
// -----------------------------------------------------------------------------

#include "FlowCore/TypeRegistry.h"
#include "FlowCore/TypeInfo.h"

// -----------------------------------------------------------------------------
//  Class FTypeRegistry
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FTypeRegistry::FTypeRegistry()
{
}

FTypeRegistry::~FTypeRegistry()
{
}

// Public queries --------------------------------------------------------------

const FTypeInfo* FTypeRegistry::classFromId(size_t classId) const
{
	F_ASSERT(false);
	// TODO: The id won't work if not all libraries are loaded.
	
	if (classId < m_classList.size())
		return m_classList[classId];
	else
		return NULL;
}

const FTypeInfo* FTypeRegistry::classFromName(const char* className) const
{
	for (size_t i = 0; i < m_classList.size(); ++i)
	{
		if (strcmp(className, m_classList[i]->typeName()) == 0)
			return m_classList[i];
	}

	return NULL;
}

FObject* FTypeRegistry::createObject(size_t classId) const
{
	F_ASSERT(classId < m_classList.size());
	return m_classList[classId]->createObject();
}

#ifdef FLOW_DEBUG
void FTypeRegistry::dump(QDebug& stream) const
{
	stream << "\n--- FTypeRegistry ---";
	stream << "\n     Registered classes  " << m_classList.size();
	for (size_t i = 0; i < m_classList.size(); ++i)
		stream << "\n#" << m_classList[i]->typeId() << "  " << m_classList[i]->typeName();
	stream << "\n";
}
#endif

// Protected commands ----------------------------------------------------------

size_t FTypeRegistry::registerType(FTypeInfo* pClass)
{
	size_t classId = m_classList.size();
	m_classList.push_back(pClass);
	return classId;
}

// -----------------------------------------------------------------------------