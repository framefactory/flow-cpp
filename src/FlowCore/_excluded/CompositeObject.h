// -----------------------------------------------------------------------------
//  File        CompositeObject.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.24 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_COMPOSITEOBJECT_H
#define FLOWCORE_COMPOSITEOBJECT_H

#include "FlowCore/Library.h"
#include "FlowCore/Object.h"
#include "FlowCore/Archive.h"

#include <vector>
#include <iostream>

class FCompositeObject;
typedef std::vector<FCompositeObject*> FCompositeObjectVec;

// -----------------------------------------------------------------------------
//  Class FCompositeObject
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FCompositeObject : public FObject
{
	F_DECLARE_ABSTRACT_SERIALIZABLE_CUSTOM_DC(FCompositeObject);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a new composite object as a child of the given parent.
	FCompositeObject(FCompositeObject* pParent = NULL);
	/// Virtual destructor.
	virtual ~FCompositeObject();

	//  Public commands ----------------------------------------------

public:
	/// Assigns this object to a new parent. The new parent can be null.
	void setParent(FCompositeObject* pNewParent);
	/// Adds a child object. This object takes ownership.
	void addChild(FCompositeObject* pChild);
	/// Inserts a child at the given index. This object takes ownership.
	void insertChild(size_t index, FCompositeObject* pChild);
	/// Removes the given child object.
	void removeChild(FCompositeObject* pChild);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the parent object.
	virtual FCompositeObject* parent() const { return m_pParent; }
	/// Returns the number of child objects.
	size_t childCount() const { return m_children.size(); }
	/// Returns true if this object owns the given child object.
	bool hasChild(FCompositeObject* pChild) const;
	/// Returns the child object at the given index.
	virtual FCompositeObject* childAt(size_t index) const { return m_children[index]; }
	/// Returns a list with all child objects.
	const FCompositeObjectVec& children() const { return m_children; }

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overrides ----------------------------------------------------

	virtual FCompositeObject* clone() const;

	//  Overridables -------------------------------------------------

protected:
	/// Called after a new child has been added.
	virtual void onAddChild(size_t index, FCompositeObject* pChild) { }
	/// Called before a child is removed.
	virtual void onRemoveChild(size_t index, FCompositeObject* pChild) { }
	/// Called if the parent is about to change.
	/// parent() still returns the old parent object.
	virtual void onSetParent(FCompositeObject* pNewParent) { }

	//  Internal functions -------------------------------------------

private:
	void _addChild(FCompositeObject* pChild);
	void _insertChild(size_t index, FCompositeObject* pChild);
	void _removeChild(FCompositeObject* pChild);

	//  Internal data members ----------------------------------------

	FCompositeObject* m_pParent;
	FCompositeObjectVec m_children;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_COMPOSITEOBJECT_H