// -----------------------------------------------------------------------------
//  File        Resource.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/31 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_RESOURCE_H
#define FLOWENGINE_RESOURCE_H

#include "FlowEngine/Library.h"


// -----------------------------------------------------------------------------
//  Class FResourceDesc
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FResourceDesc
{
	//  Constructors and destructor ----------------------------------

public:
	/// Virtual destructor.
	virtual ~FResourceDesc() { }

	//  Public queries -----------------------------------------------

	/// Returns true if the given resource's parameters are equal.
	virtual bool isEqual(const FResourceDesc& other) const = 0;

	/// Returns a hash code for this resource description.
	virtual size_t hashCode() const = 0;
};
	
// -----------------------------------------------------------------------------
//  Class FResource
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FResource
{
	friend class FResourceManager;

	//  Constructors and destructor ----------------------------------

protected:
	FResource(FResourceManager* pManager);
	FResource(const FResource& other);
	virtual ~FResource();

	FResource& operator=(const FResource& other);

	//  Public commands ----------------------------------------------

public:
	/// Releases the resource.
	void release();

	//  Public queries -----------------------------------------------

	/// Returns true if the resource has been created successfully.
	bool isValid() const { return m_isValid; }
	/// Returns the resource description.
	virtual const FResourceDesc& description() const;

	/// Returns the amount of system memory this resource occupies.
	size_t systemMemory() const { return m_systemMemory; }
	/// Returns the amount of device memory this resource occupies.
	size_t deviceMemory() const { return m_deviceMemory; }

	//  Overridables -------------------------------------------------

protected:
	/// Override to allocate memory and create the resource.
	virtual bool onCreate() = 0;
	/// Override to release the resource.
	virtual void onRelease() = 0;

	//  Internal functions -------------------------------------------

	void setConsumedMemory(size_t systemBytes, size_t deviceBytes);
	

private:
	bool create();
	void addRef();
	void releaseRef();

	//  Internal data members ----------------------------------------

private:
	FResourceManager* m_pManager;
	size_t m_systemMemory;
	size_t m_deviceMemory;
	uint32_t m_refCount;
	bool m_isValid;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_RESOURCE_H