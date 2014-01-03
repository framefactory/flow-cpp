// -----------------------------------------------------------------------------
//  File        ReferenceCounter.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_REFERENCECOUNTER_H
#define FLOWCORE_REFERENCECOUNTER_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Class FReferenceCounter
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FReferenceCounter
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FReferenceCounter() : m_pRefCount(NULL) { }
	/// Copy constructor.
	FReferenceCounter(const FReferenceCounter& other);

	//  Public commands ----------------------------------------------

public:
	/// Creates a new resource, the counter is initialized to one.
	void create();
	/// Adds a reference; increases the counter by one.
	void add();
	/// Releases a reference; decreases the counter by one.
	/// Returns true if the resource can be freed.
	bool release();
	/// Releases the current resource and references
	/// the given one (increases the given counter by one).
	bool assign(const FReferenceCounter& other);

	//  Public queries -----------------------------------------------

	/// Returns true if the number of references is zero.
	bool isNull() const { return !m_pRefCount || !(*m_pRefCount); }

	/// Returns the current number of references.
	uint32_t count() const { return m_pRefCount ? *m_pRefCount : 0; }

	//  Internal data members ----------------------------------------

private:
	uint32_t* m_pRefCount;
};

// Inline members --------------------------------------------------------------

inline FReferenceCounter::FReferenceCounter(const FReferenceCounter& other)
: m_pRefCount(other.m_pRefCount)
{
	if (m_pRefCount)
		(*m_pRefCount)++;
}

inline void FReferenceCounter::create()
{
	F_ASSERT(!m_pRefCount);
	m_pRefCount = new uint32_t(1);
}

inline void FReferenceCounter::add()
{
	F_ASSERT(m_pRefCount);
	(*m_pRefCount)++;
}

inline bool FReferenceCounter::release()
{
	if (!m_pRefCount || --(*m_pRefCount))
		return false;

	F_ASSERT(*m_pRefCount == 0);
	delete m_pRefCount;
	return true;
}

inline bool FReferenceCounter::assign(const FReferenceCounter& other)
{
	bool result = release();
	m_pRefCount = other.m_pRefCount;
	if (m_pRefCount)
		(*m_pRefCount)++;
	return result;
}
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_REFERENCECOUNTER_H