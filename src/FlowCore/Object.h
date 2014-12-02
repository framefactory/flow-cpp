// -----------------------------------------------------------------------------
//  File        Object.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/06 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_OBJECT_H
#define FLOWCORE_OBJECT_H

#include "FlowCore/Library.h"
#include "FlowCore/TypeInfo.h"

#include <QString>

// -----------------------------------------------------------------------------
//  Class FObject
// -----------------------------------------------------------------------------

class FArchive;
class FTypeInfo;

class FLOWCORE_EXPORT FObject
{
	//  Static members -----------------------------------------------

public:
	/// Returns static type information about the class.
	static const FTypeInfo* staticType();

private:
	static const FTypeInfo typeInfo;

	//  Constructors and destructor ----------------------------------

protected:
	/// Protected default constructor.
	FObject() { }
	/// Protected copy constructor. Use clone() to create a deep copy
	/// of an object derived from FObject.
    FObject(const FObject& /* other */) { }
private:
	/// Private assignment operator. Use clone() to create a deep copy
	/// of an object derived from FObject.
	FObject& operator=(const FObject& other);
public:
	/// Virtual destructor.
	virtual ~FObject() { }

	//  Public commands ----------------------------------------------

	/// Serialization to or from the given archive.
	/// Default implementation does nothing.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Safely casts the object to the type given as template argument. If the
	/// target type is not an ancestor of the object, NULL is returned.
	template<class T>
	T* castTo() const { return isKindOf(T::staticType()) ? (T*)this : NULL; }
	/// Returns true if the runtime type of the object is of the same type
	/// as the class given as template argument.
	template<class T>
	bool isA() const { return this->dynamicType() == T::staticType(); }
	/// Returns true if the runtime type of the object is derived from
	/// the class given as template argument.
	template<class T>
	bool isKindOf() const { return isKindOf(T::staticType()); }
	
	/// Returns true if the runtime type of the object is derived from
	/// the class represented by the given type info.
	bool isKindOf(const FTypeInfo* pClass) const;

	/// Returns the runtime type of the object.
	virtual const FTypeInfo* dynamicType() const;

	/// Returns a string representation of the object.
	virtual QString toString() const;

	/// Returns a deep copy of the object. The base implementation throws
	/// an assertion. You must override clone() to enable cloning in a derived class.
	virtual FObject* clone() const { F_ASSERT(false); return NULL; }

#ifdef FLOW_DEBUG
	/// Returns information about the internal state of the object.
	virtual QString dump() const;
#endif
};

// Macro definitions -----------------------------------------------------------

/// Creates an object of the given class, using its default constructor.
#define F_CREATE_OBJECT(className) \
	((className*)(className::staticType()->createObject()))

// Macros for declaration ------------------------------------------------------

/// Defines dynamic type information for an abstract class.
#define F_DECLARE_ABSTRACT_TYPEINFO(className) \
	F_DISABLE_COPY(className) \
private: \
	static const FTypeInfo typeInfo; \
public: \
	static const FTypeInfo* staticType(); \
	virtual const FTypeInfo* dynamicType() const;

/// Defines dynamic type information for a concrete class.
#define F_DECLARE_TYPEINFO(className) \
public: \
	F_DECLARE_ABSTRACT_TYPEINFO(className) \
	static FObject* createObject();

/// Defines dynamic type information for an abstract class that is serializable.
#define F_DECLARE_ABSTRACT_SERIALIZABLE_CUSTOM_DC(className) \
protected: \
	F_DECLARE_ABSTRACT_TYPEINFO(className) \
	friend FArchive& operator>>(FArchive& ar, className* &pObject);

/// Defines dynamic type information for an abstract class that is serializable.
#define F_DECLARE_ABSTRACT_SERIALIZABLE(className) \
protected: \
	className() { } \
	F_DECLARE_ABSTRACT_SERIALIZABLE_CUSTOM_DC(className)

/// Defines dynamic type information for a serializable class.
#define F_DECLARE_SERIALIZABLE_CUSTOM_DC(className) \
protected: \
	F_DECLARE_ABSTRACT_TYPEINFO(className) \
	static FObject* createObject(); \
	friend FArchive& operator>>(FArchive& ar, className* &pObject);

/// Defines dynamic type information for a serializable class.
#define F_DECLARE_SERIALIZABLE(className) \
protected: \
	className() { } \
	F_DECLARE_SERIALIZABLE_CUSTOM_DC(className)

// Macros for implementation ---------------------------------------------------

#define F_IMPLEMENT_TYPEINFO_CLASS(className, baseClassName, version, pfnCreate) \
	const FTypeInfo className::typeInfo( \
		#className, sizeof(class className), version, pfnCreate, \
		baseClassName::staticType()); \
	const FTypeInfo* className::staticType() \
		{ return &className::typeInfo; } \
	const FTypeInfo* className::dynamicType() const \
		{ return &className::typeInfo; } \

/// Implements dynamic type information for an abstract class.
#define F_IMPLEMENT_ABSTRACT_TYPEINFO(className, baseClassName) \
	F_IMPLEMENT_TYPEINFO_CLASS(className, baseClassName, 0xffff, NULL)

/// Implements dynamic type information for a concrete class.
#define F_IMPLEMENT_TYPEINFO(className, baseClassName) \
	FObject* className::createObject() { return new className(); } \
	F_IMPLEMENT_TYPEINFO_CLASS(className, baseClassName, 0xffff, className::createObject)

/// Implements dynamic type information for an abstract class that is serializable.
#define F_IMPLEMENT_ABSTRACT_SERIALIZABLE(className, baseClassName) \
	FArchive& operator>>(FArchive& ar, className* &pObject) { \
	pObject = static_cast<className*>(ar.readObject(className::staticType())); return ar; } \
    F_IMPLEMENT_TYPEINFO_CLASS(className, baseClassName, 0xffff, NULL)

/// Implements dynamic type information for a serializable class.
#define F_IMPLEMENT_SERIALIZABLE(className, baseClassName, version) \
	FObject* className::createObject() { return new className(); } \
	FArchive& operator>>(FArchive& ar, className* &pObject) { \
	pObject = static_cast<className*>(ar.readObject(className::staticType())); return ar; } \
	F_IMPLEMENT_TYPEINFO_CLASS(className, baseClassName, version, className::createObject)



// -----------------------------------------------------------------------------

#endif // FLOWCORE_OBJECT_H
