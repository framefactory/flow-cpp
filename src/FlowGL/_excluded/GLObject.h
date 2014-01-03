// -----------------------------------------------------------------------------
//  File        GLObject.h
//  Project     FlowGL
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.25 $
// -----------------------------------------------------------------------------

#ifndef FLOWGL_GLOBJECT_H
#define FLOWGL_GLOBJECT_H

#include "FlowGL/Library.h"


// -----------------------------------------------------------------------------
//  Class FGLObject
// -----------------------------------------------------------------------------


class FLOWGL_EXPORT FGLObject
{
	//  Constructors and destructor ----------------------------------

public:
	FGLObject();
	FGLObject(const FGLObject& other);

	~FGLObject();

	FGLObject& operator=(const FGLObject& other);

	//  Public commands ----------------------------------------------

public:
	void create(uint32_t objectId);
	void release();

	//  Public queries -----------------------------------------------

	uint32_t objectId() const { return m_objectId; }

	//  Internal data members ----------------------------------------

private:
	uint32_t* m_pRefCount;
	uint32_t m_objectId;
};

// Inline members --------------------------------------------------------------
	
inline FGLObject::FGLObject()
: m_pRefCount(NULL), m_objectId(0)
{
}

inline FGLObject::FGLObject(const FGLObject& other)
: m_pRefCount(other.m_pRefCount),
  m_objectId(other.m_objectId)
{
	if (m_pRefCount)
		(*m_pRefCount)++;
}

inline FGLObject::~FGLObject()
{
	if (m_pRefCount)
	{
		(*m_pRefCount)--;
		if (!(*m_pRefCount))
			delete m_pRefCount;
	}
}

inline FGLObject& FGLObject::operator=(const FGLObject& other)
{
	if (&other == this)
		return *this;

	if (m_pRefCount)
	{
		(*m_pRefCount)--;
		if (!(*m_pRefCount))
			delete m_pRefCount;
	}

	m_pRefCount = other.m_pRefCount;
	m_objectId = other.m_objectId;
}

inline void FGLObject::create(uint32_t objectId)
{
	if (m_pRefCount)
	{
		(*m_pRefCount)--;
		if (!(*m_pRefCount))
			delete m_pRefCount;
	}

	m_pRefCount = new uint32_t(1);
	m_objectId = objectId;
}

inline void FGLObject::release()
{
	if (m_pRefCount)
	{
		(*m_pRefCount)--;
		if (!(*m_pRefCount))
		{
			delete m_pRefCount;
			m_pRefCount = NULL;
			m_objectId = 0;
		}
	}
}

// -----------------------------------------------------------------------------

#endif // FLOWGL_GLOBJECT_H