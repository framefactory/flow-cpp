// -----------------------------------------------------------------------------
//  File        CompositeObject.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.24 $
// -----------------------------------------------------------------------------

#include "FlowCore/CompositeObject.h"
#include "FlowCore/MemoryTracer.h"


// -----------------------------------------------------------------------------
//  Class FCompositeObject
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FCompositeObject, FObject);

// Constructors and destructor -------------------------------------------------

FCompositeObject::FCompositeObject(FCompositeObject* pParent /* = NULL */)
	: m_pParent(pParent)
{
	if (pParent)
		pParent->_addChild(this);
}

FCompositeObject::FCompositeObject(const FCompositeObject& other)
	: m_pParent(NULL)
{
	for (size_t i = 0, n = other.m_children.size(); i < n; ++i)
	{
		FCompositeObject* pClone = other.m_children[i]->clone();
		m_children.push_back(pClone);
		onAddChild(i, pClone);
	}
}

FCompositeObject::~FCompositeObject()
{
	// detach from parent
	if (m_pParent)
		m_pParent->_removeChild(this);

	// delete all children
	for (size_t i = 0, n = m_children.size(); i < n; ++i)
		F_SAFE_DELETE(m_children[i]);
}

// Public commands -------------------------------------------------------------

void FCompositeObject::setParent(FCompositeObject* pNewParent)
{
	onSetParent(pNewParent);

	if (m_pParent)
		m_pParent->_removeChild(this);

	if (pNewParent)
		pNewParent->_addChild(this);

	m_pParent = pNewParent;
}

void FCompositeObject::addChild(FCompositeObject* pChild)
{
	F_ASSERT(pChild->m_pParent != this);

	if (pChild->m_pParent)
	{
		pChild->onSetParent(this);
		pChild->m_pParent->_removeChild(pChild);
		pChild->m_pParent = this;
	}

	_addChild(pChild);
}

void FCompositeObject::insertChild(size_t index, FCompositeObject* pChild)
{
	F_ASSERT(pChild->m_pParent != this);

	if (pChild->m_pParent)
	{
		pChild->onSetParent(this);
		pChild->m_pParent->_removeChild(pChild);
		pChild->m_pParent = this;
	}

	_insertChild(index, pChild);
}

void FCompositeObject::removeChild(FCompositeObject* pChild)
{
	F_ASSERT(pChild->m_pParent == this);

	pChild->onSetParent(NULL);
	_removeChild(pChild);
	pChild->m_pParent = NULL;
}

void FCompositeObject::serialize(FArchive& ar)
{
	if (ar.isWriting())
	{
		ar << m_children.size();
		for (size_t i = 0, n = m_children.size(); i < n; ++i)
			ar << m_children[i];
	}
	else // is reading
	{
		size_t n;
		ar >> n;
		m_children.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			ar >> m_children[i];
			m_children[i]->m_pParent = this;
		}
	}
}

// Public queries --------------------------------------------------------------

bool FCompositeObject::hasChild(FCompositeObject* pChild) const
{
	for (size_t i = 0, n = m_children.size(); i < n; ++i)
	{
		if (m_children[i] == pChild)
			return true;
	}

	return false;
}

#ifdef FLOW_DEBUG
void FCompositeObject::dump(std::wostream& stream) const
{
	FObject::dump(stream);
	stream << "\n--- FCompositeObject ---";
	stream << "\n     Has parent:  " << (m_pParent != NULL);
	stream << "\n     Child count: " << m_children.size();
}
#endif

// Overrides -------------------------------------------------------------------

FCompositeObject* FCompositeObject::clone() const
{
	return new FCompositeObject(*this);
}

// Internal functions ----------------------------------------------------------

void FCompositeObject::_addChild(FCompositeObject* pChild)
{
	F_ASSERT(!hasChild(pChild));

	m_children.push_back(pChild);
	onAddChild(m_children.size() - 1, pChild);
}

void FCompositeObject::_insertChild(size_t index, FCompositeObject* pChild)
{
	F_ASSERT(index <= m_children.size());
	F_ASSERT(!hasChild(pChild));

	m_children.insert(m_children.begin() + index, pChild);
	onAddChild(index, pChild);
}

void FCompositeObject::_removeChild(FCompositeObject* pChild)
{
	F_ASSERT(hasChild(pChild));

	for (size_t i = 0, n = m_children.size(); i < n; ++i)
	{
		if (m_children[i] == pChild)
		{
			onRemoveChild(i, pChild);
			m_children.erase(m_children.begin() + i);
			return;
		}
	}
}

// -----------------------------------------------------------------------------