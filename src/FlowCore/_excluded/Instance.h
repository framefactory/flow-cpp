// -----------------------------------------------------------------------------
//  File        Instance.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/03 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_INSTANCE_H
#define FLOWCORE_INSTANCE_H

#include "FlowCore/Library.h"
#include "FlowCore/NamedObject.h"

#include <vector>
#include <iosfwd>


// -----------------------------------------------------------------------------
//  Class FInstance
// -----------------------------------------------------------------------------

/// An instance is either a master or a reference. Each reference points
/// to a master object. A master itself can reference another master.
class FLOWCORE_EXPORT FInstance : public FNamedObject
{
	F_DECLARE_ABSTRACT_SERIALIZABLE(FInstance);

	//  Public types -------------------------------------------------

public:
	typedef std::vector<FInstance*> instanceVec_t;

	//  Constructors and destructor ----------------------------------

	/// Creates a new instance that references the given master.
	/// The name of the new instance is taken from the master.
	FInstance(const FUniqueId& id, FInstance* pMaster = NULL);
	/// Creates a new named instance that references the given master.
	FInstance(const FUniqueId& id, const wstring_t& name, FInstance* pMaster = NULL);
	/// Virtual destructor.
	virtual ~FInstance();

	//  Public commands ----------------------------------------------

	/// Detaches this reference from its master and turns it into a unique copy.
	void makeUnique();

	/// If set to true, this master is automatically deleted
	/// after the last reference is removed.
	void setAutoDelete(bool state);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the master instance.
	FInstance* master() const { return m_pMaster; }
	/// Returns the list of instance that reference this master.
	const instanceVec_t& references() const { return m_references; }
	/// Returns the number of references.
	size_t referenceCount() const { return m_references.size(); }
	/// Returns the reference at the given index.
	FInstance* referenceAt(size_t index) const;

	/// Returns true if this instance is master.
	/// An instance is master if it has any references pointing to it.
	bool isMaster() const { return !m_references.empty(); }
	/// Returns true if this instance is a reference pointing to master.
	bool isReference() const { return m_pMaster != NULL; }
	
	/// Returns true if this is master of the given instance.
	bool isMasterOf(FInstance* pInstance) const;
	/// Returns true if this is an instance of the same master.
	bool isSiblingOf(FInstance* pInstance) const;
	/// Returns true if this references the given master.
	bool isReferenceOf(FInstance* pInstance) const;

	/// Returns true if this master is automatically deleted after
	/// the last reference is removed.
	bool autoDelete() const { return m_autoDelete; }

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overridables -------------------------------------------------

protected:
	/// Called after the state of the master has been changed.
	virtual void onMasterChanged(FInstance* pMaster) { }
	/// Called after the state of one of the references has been changed.
	virtual void onReferenceChanged(FInstance* pReference) { }
	/// Called after a new reference has been added to this master.
	virtual void onReferenceAdded(FInstance* pReference) { }
	/// Called after a reference is removed from this master.
	virtual void onReferenceRemoved(FInstance* pReference) { }
	/// Called before this reference is detached from its master.
	/// Derived classes must copy data held in the master.
	virtual void onMakeUnique() = 0;

	//  Internal functions -------------------------------------------

	/// Informs the master that this instance has been changed.
	/// onReferenceChanged() will be called on the master.
	void notifyMaster();
	/// Informs all references that this instance has been changed.
	/// onMasterChanged() will be called on all references.
	void notifyReferences();

private:
	void _addReference(FInstance* pInstance);
	void _removeReference(FInstance* pInstance);

	//  Internal data members ----------------------------------------

private:
	FInstance* m_pMaster;
	instanceVec_t m_references;
	bool m_autoDelete;
};

// Public members --------------------------------------------------------------

inline FInstance* FInstance::referenceAt(size_t index) const
{
	F_ASSERT(index < m_references.size());
	return m_references[index];
}

inline bool FInstance::isReferenceOf(FInstance* pInstance) const
{
	return pInstance == m_pMaster;
}
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_INSTANCE_H