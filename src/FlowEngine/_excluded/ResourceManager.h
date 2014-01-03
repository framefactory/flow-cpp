// -----------------------------------------------------------------------------
//  File        ResourceManager.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/04 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_RESOURCEMANAGER_H
#define FLOWENGINE_RESOURCEMANAGER_H

#include "FlowEngine/Library.h"
#include "FlowEngine/Resource.h"

#include <unordered_set>

// -----------------------------------------------------------------------------
//  Class FResourceManager
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FResourceManager
{
	friend class FResource;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FResourceManager();
	/// Virtual destructor.
	virtual ~FResourceManager();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

	struct hash_t {
		size_t operator()(const FResource* pResource) {
			return pResource->description().hashCode();
		}
	};

	struct equal_t {
		size_t operator()(FResource* pRes1, FResource* pRes2) {
			return pRes1->description().isEqual(pRes2->description());
		}
	};

	typedef std::unordered_set<FResource*, hash_t, equal_t> resourceMap_t;
	resourceMap_t m_resources;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_RESOURCEMANAGER_H