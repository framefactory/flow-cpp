// -----------------------------------------------------------------------------
//  File        NamedObject.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_NAMEDOBJECT_H
#define FLOWCORE_NAMEDOBJECT_H

#include "FlowCore/Library.h"
#include "FlowCore/Object.h"
#include "FlowCore/UniqueId.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FNamedObject
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FNamedObject : public FObject
{
	F_DECLARE_ABSTRACT_SERIALIZABLE(FNamedObject);
	friend class FObjectRegistry;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates an object with the given unique id.
	FNamedObject(const FUniqueId& id);
	/// Creates an object with the given name. The id is set to null.
	FNamedObject(const wstring_t& name);
	/// Creates an object with the given name and unique id.
	FNamedObject(const FUniqueId& id, const wstring_t& name);
	
	/// Virtual destructor.
	virtual ~FNamedObject();

	//  Public commands ----------------------------------------------

	/// Sets the name of the entity.
	void setName(const wstring_t& name);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the unique id of the entity.
	const FUniqueId& id() const { return m_objectId; }
	/// Returns the name of the entity.
	const wstring_t& name() const { return m_objectName; }

	/// Returns a text representation of the object.
	virtual wstring_t toString() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overridables -------------------------------------------------

protected:
	/// Called after the name of the object has been changed.
	virtual void onNameChanged(const wstring_t& newName) { }

	//  Internal data members ----------------------------------------

private:
	FUniqueId m_objectId;
	wstring_t m_objectName;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_NAMEDOBJECT_H