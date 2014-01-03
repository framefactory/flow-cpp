// -----------------------------------------------------------------------------
//  File        NamedObject.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/NamedObject.h"
#include "FlowCore/Archive.h"
#include "FlowCore/ObjectRegistry.h"

#include <ostream>
#include <sstream>

// -----------------------------------------------------------------------------
//  Class FNamedObject
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FNamedObject, FObject);

// Constructors and destructor -------------------------------------------------

FNamedObject::FNamedObject(const FUniqueId& id)
: m_objectId(id)
{
	FObjectRegistry::instance()->registerObject(this);
}

FNamedObject::FNamedObject(const wstring_t& name)
: m_objectName(name)
{
	FObjectRegistry::instance()->registerObject(this);
}

FNamedObject::FNamedObject(const FUniqueId& id, const wstring_t& name)
: m_objectId(id),
  m_objectName(name)
{
	FObjectRegistry::instance()->unregisterObject(this);
}

FNamedObject::~FNamedObject()
{
}

// Public commands -------------------------------------------------------------

void FNamedObject::setName(const wstring_t& name)
{
	m_objectName = name;
	onNameChanged(name);
}

void FNamedObject::serialize(FArchive& ar)
{
	FObject::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_objectId;
		ar << m_objectName;
	}
	else // is reading
	{
		ar >> m_objectId;
		ar >> m_objectName;
	}
}

// Public queries --------------------------------------------------------------

wstring_t FNamedObject::toString() const
{
	std::wostringstream stream;
	stream << FObject::toString() << " (" << m_objectName << ")";
	return stream.str();
}

#ifdef FLOW_DEBUG
void FNamedObject::dump(std::wostream& stream) const
{
	FObject::dump(stream);
	stream << "\n--- FNamedObject ---";
	stream << "\n     Id:   " << m_objectId;
	stream << "\n     Name: " << m_objectName;
}
#endif

// -----------------------------------------------------------------------------