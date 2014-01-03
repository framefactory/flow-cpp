// -----------------------------------------------------------------------------
//  File        ObjectRegistry.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_OBJECTREGISTRY_H
#define FLOWCORE_OBJECTREGISTRY_H

#include "FlowCore/Library.h"
#include "FlowCore/UniqueId.h"
#include "FlowCore/SingletonT.h"
#include "FlowCore/HashT.h"

#include <unordered_map>

namespace boost { class mutex; }

// -----------------------------------------------------------------------------
//  Class FObjectRegistry
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FObjectRegistry : public FSingletonAutoT<FObjectRegistry>
{
	friend class FSingletonAutoT<FObjectRegistry>;
	friend class FNamedObject;

	//  Constructors and destructor ----------------------------------

protected:
	/// Default Constructor.
	FObjectRegistry();
	/// Virtual destructor.
	virtual ~FObjectRegistry();

	//  Public queries -----------------------------------------------

public:
	/// Returns the entity with the given id.
	FNamedObject* find(const FUniqueId& id) const;
	/// Returns true if an entity with the given id exists.
	bool contains(const FUniqueId& id) const;
	/// Returns the number of registered entities.
	size_t count() const { return m_registry.size(); }

	//  Protected commands (FNamedObject) ----------------------------

protected:
	/// Adds the given object to the registry.
	void registerObject(FNamedObject* pObject);
	/// Removes the given object from the registry.
	void unregisterObject(FNamedObject* pObject);

	//  Internal data members ----------------------------------------

private:
	typedef FHashT<FUniqueId> idHasher_t;
	typedef std::unordered_map<FUniqueId, FNamedObject*, idHasher_t> objectHash_t;
	objectHash_t m_registry;

	boost::mutex* m_pRegistryAccess;
};

// -----------------------------------------------------------------------------

#endif // FLOWCORE_OBJECTREGISTRY_H