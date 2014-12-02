// -----------------------------------------------------------------------------
//  File        TypeInfo.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/12 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TYPEINFO_H
#define FLOWCORE_TYPEINFO_H

#include "FlowCore/Library.h"

class FObject;

// -----------------------------------------------------------------------------
//  Class FTypeInfo
// -----------------------------------------------------------------------------

/// type info objects are automatically created for classes deriving from FObject.
/// They provide a simple runtime typing system. Each object of a class derived
/// from FObject can be asked for its dynamic runtime type.
/// FTypeInfo, together with FObject, FTypeRegistry and FArchive provide a
/// powerful serialization system for complex object graphs.
class FLOWCORE_EXPORT FTypeInfo
{
	//  Constructors and destructor ----------------------------------

public:
    FTypeInfo(const char* typeName, size_t objectSize, size_t version,
		FObject*(*pfnCreateObject)(), const FTypeInfo* pBaseType);

	//  Public commands ----------------------------------------------

public:
	/// Creates and returns an object of the type this runtime class represents.
	FObject* createObject() const;

	//  Public queries -----------------------------------------------

	/// Returns true if the actual type is derived from the given base type.
	bool isDerivedFrom(const FTypeInfo* pBaseType) const;
	/// Returns the type version.
    size_t version() const { return m_version; }
	/// Returns the type id.
    size_t typeId() const { return m_typeId; }
	/// Returns the type name.
	const char* typeName() const { return m_typeName; }
	/// Returns the type of the base class.
	const FTypeInfo* baseType() const { return m_pBaseType; }
    /// Returns the size of the type.
    size_t typeSize() const { return m_objectSize; }

	//  Public members -----------------------------------------------

private:
	const char* m_typeName;
    size_t m_objectSize;
    size_t m_version;
    size_t m_typeId;
	FObject* (*m_pfnCreateObject)();
	const FTypeInfo* m_pBaseType;
};

// Inline members --------------------------------------------------------------

inline bool FTypeInfo::isDerivedFrom(const FTypeInfo* pBaseType) const
{
	F_ASSERT(this);
	F_ASSERT(pBaseType);

	const FTypeInfo* pType = this;
	while(pType != NULL)
	{
		if (pType == pBaseType)
			return true;
		pType = pType->m_pBaseType;
	}

	return false;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_TYPEINFO_H
