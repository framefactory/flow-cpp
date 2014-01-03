// -----------------------------------------------------------------------------
//  File        TypeRegistry.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/06 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TYPEREGISTRY_H
#define FLOWCORE_TYPEREGISTRY_H

#include "FlowCore/Library.h"
#include "FlowCore/SingletonT.h"

#include <QDebug>
#include <vector>

class FObject;
class FTypeInfo;

// -----------------------------------------------------------------------------
//  Class FTypeRegistry
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FTypeRegistry : public FSingletonAutoT<FTypeRegistry>
{
	friend class FSingletonAutoT<FTypeRegistry>;
	friend class FTypeInfo;

	//  Constructors and destructor ----------------------------------

protected:
	FTypeRegistry();
	virtual ~FTypeRegistry();

	//  Public queries -----------------------------------------------

public:
	/// Returns the runtime class object for a class with given id.
	/// Returns null if the class with given id is not registered.
	const FTypeInfo* classFromId(size_t classId) const;

	/// Returns the runtime class object for a given class name.
	/// Returns null if the class with given name is not registered.
	const FTypeInfo* classFromName(const char* className) const;

	/// Creates and returns an object of the class type with given id.
	FObject* createObject(size_t classId) const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given debug object.
	virtual void dump(QDebug& stream) const;
#endif

	//  Protected commands -------------------------------------------

protected:
	/// Registers a class type at the object manager.
	size_t registerType(FTypeInfo* pClass);

	//  Internal data members ----------------------------------------

	std::vector<FTypeInfo*> m_classList;
};

// -----------------------------------------------------------------------------


#endif // FLOWCORE_TYPEREGISTRY_H