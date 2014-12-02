// -----------------------------------------------------------------------------
//  File        Archive.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/06 $
// -----------------------------------------------------------------------------

#include "FlowCore/Archive.h"
#include "FlowCore/Object.h"
#include "FlowCore/TypeInfo.h"
#include "FlowCore/TypeRegistry.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FArchive
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FArchive::FArchive(QIODevice* pDevice, bool checkRefs /* = true */)
: m_currentVersion(0),
  m_archiveMode(pDevice->isWritable() ? Write : Read),
  m_checkRefs(checkRefs),
  m_stream(pDevice)
{
	F_ASSERT(pDevice);
	_initialize();
}

FArchive::FArchive(QByteArray* pBuffer, mode_t mode, bool checkRefs /* = true */)
: m_currentVersion(0),
  m_archiveMode(mode),
  m_checkRefs(checkRefs),
  m_stream(pBuffer, mode == Read ? QIODevice::ReadOnly : QIODevice::WriteOnly)
{
	F_ASSERT(pBuffer);
	_initialize();
}

FArchive::FArchive(const QByteArray& buffer, bool checkRefs /* = true */)
: m_currentVersion(0),
  m_archiveMode(Read),
  m_checkRefs(checkRefs),
  m_stream(buffer)
{
	_initialize();
}

FArchive::~FArchive()
{
	F_SAFE_DELETE(m_pReadClassTable);
	F_SAFE_DELETE(m_pReadObjectTable);
	F_SAFE_DELETE(m_pWriteClassTable);
	F_SAFE_DELETE(m_pWriteObjectTable);
}

// Public commands -------------------------------------------------------------

FObject* FArchive::readObject(const FTypeInfo* pBaseClass /* = NULL */)
{
	F_ASSERT(isReading());

	if (!m_checkRefs) {

		m_stream >> m_currentVersion;

		// if the version is 0, a null pointer was stored, i.e. return a null pointer.
		if (m_currentVersion == 0) {
			return NULL;
		}

		// read the class name
		char* className;
		m_stream >> className;

		// get the runtime class from the object manager
		const FTypeInfo* pClass = FTypeRegistry::instance()->classFromName(className);
		delete[] className;

		if (!pClass) {
			F_ASSERT(!"FStaticArchive - Could not find runtime class");
			return NULL;
		}

		// now we can create an instance of the class and read its values
		FObject* pObject = pClass->createObject();
		F_ASSERT(pObject);

		if (pBaseClass && !pObject->isKindOf(pBaseClass)) {
			F_ASSERT(!"FStaticArchive - Dynamic type does not match");
			return NULL;
		}

		pObject->serialize(*this);
		m_currentVersion = 0;
		return pObject;
	}

	F_ASSERT(m_pReadClassTable);
	F_ASSERT(m_pReadObjectTable);

	// read the object tag
	quint32 objTag;
	m_stream >> objTag;

	// if it's the zero tag, we simply return a null pointer
	if (objTag == 0) {
		return NULL;
	}

	// check if the object has already been read
	tagObjTable_t::iterator it = m_pReadObjectTable->find(objTag);
	if (it != m_pReadObjectTable->end()) {

		// we found the object, so we can return the pointer from the table
		FObject* pObject = it->second;
		F_ASSERT(!pBaseClass || pObject->isKindOf(pBaseClass));
		return pObject;
	}
	else {

		// it's a previously unseen object, so read the class tag
		uint16_t classTag;
		m_stream >> classTag;

		// check if we already know this class tag
		tagClassTable_t::iterator it = m_pReadClassTable->find(classTag);
		const FTypeInfo* pClass = NULL;
		if (it != m_pReadClassTable->end())	{
			// we found the class, so we can use it to read the object
			pClass = it->second.pClass;
			m_currentVersion = it->second.Version;
		}
		else {
			// it's a previously unseen class, so read the class info
			char* className;
			m_stream >> m_currentVersion;
			m_stream >> className;

			// get the runtime class from the object manager
			pClass = FTypeRegistry::instance()->classFromName(className);
			delete[] className;
			F_ASSERT(pClass);
			m_pReadClassTable->insert(tagClassTable_t::value_type(
				classTag, classInfo_t(pClass, m_currentVersion)));
		}

		// now we can create an instance of the class and read it's values
		FObject* pObject = pClass->createObject();
		F_ASSERT(pObject);
		F_ASSERT(!pBaseClass || pObject->isKindOf(pBaseClass));
		m_pReadObjectTable->insert(tagObjTable_t::value_type(objTag, pObject));
		pObject->serialize(*this);
		m_currentVersion = 0;
		return pObject;
	}
}

void FArchive::writeObject(const FObject* pObject)
{
	F_ASSERT(isWriting());

	if (!m_checkRefs) {

		// If we have a null pointer, we write a zero version number and return
		if (pObject == NULL) {
			m_stream << quint32(0);
			return;
		}

		// write class and object information.
		const FTypeInfo* pClass = pObject->dynamicType();
		F_ASSERT(pClass->version() > 0); // 0 is reserved for the null pointer.
		m_stream << (quint32)pClass->version();
		m_stream << pClass->typeName();

		// need to cast away the const because serialize is for reading and writing
		(const_cast<FObject*>(pObject))->serialize(*this);

		return;
	}

	F_ASSERT(m_pWriteClassTable);
	F_ASSERT(m_pWriteObjectTable);

	// If we have a null pointer, we write a zero tag and return
	if (pObject == NULL) {
		m_stream << quint32(0);
		return;
	}

	// check if the object has already been serialized
	objTagTable_t::iterator it = m_pWriteObjectTable->find(pObject);
	if (it == m_pWriteObjectTable->end()) {

		// not serialized: insert new object/tag pair into hash and write tag to stream
		m_pWriteObjectTable->insert(objTagTable_t::value_type(pObject, m_nextObjectTag));
		m_stream << m_nextObjectTag;
		m_nextObjectTag++;

		// check if the runtime class has already been serialized
		const FTypeInfo* pClass = pObject->dynamicType();
		classTagTable_t::iterator it = m_pWriteClassTable->find(pClass);

		if (it == m_pWriteClassTable->end()) {

			// not yet serialized: insert new class/tag pair into hash and
			// write tag and class info to stream
			m_pWriteClassTable->insert(classTagTable_t::value_type(pClass, m_nextClassTag));
			m_stream << m_nextClassTag;
			m_nextClassTag++;
			m_stream << (quint32)pClass->version();
			m_stream << pClass->typeName();
		}
		else
		{
			// class is serialized: only write existing class tag to stream
			m_stream << it->second;
		}
	}
	else
	{
		// object is serialized: only write existing object tag to stream
		m_stream << it->second;
		return;
	}

	// object hasn't been seen yet, so write it to the stream
	(const_cast<FObject*>(pObject))->serialize(*this);
}

// Operators -------------------------------------------------------------------

/*
FArchive& FArchive::operator<<(const FTypeInfo* pTypeInfo)
{
	F_ASSERT(isWriting());
	if (pTypeInfo)
	{
		size_t length = strlen(pTypeInfo->typeName());
		F_ASSERT(length > 0);
		_writeRaw(&length, sizeof(size_t));
		_writeRaw(pTypeInfo->typeName(), length);
	}
	else
	{
		size_t zero = 0;
		_writeRaw(&zero, sizeof(size_t));
	}
	return *this;
}

FArchive& FArchive::operator>>(const FTypeInfo*& pTypeInfo)
{
	F_ASSERT(isReading());
	size_t length;
	_readRaw(&length, sizeof(size_t));

	if (length == 0)
	{
		pTypeInfo = NULL;
		return *this;
	}

	char* str = new char[length + 1];
	_readRaw(str, length);
	str[length] = 0;

	pTypeInfo = FTypeRegistry::instance()->classFromName(str);
	delete[] str;

	F_ASSERT(pTypeInfo);
	return *this;
}
*/

// Internal functions ----------------------------------------------------------

void FArchive::_initialize()
{
	m_nextClassTag = 1;
	m_nextObjectTag = 1;
	m_pReadClassTable = NULL;
	m_pWriteClassTable = NULL;
	m_pReadObjectTable = NULL;
	m_pWriteObjectTable = NULL;
	m_currentVersion = 0;

	if (m_checkRefs)
	{
		if (isReading())
		{
			// create hash tables needed for reading (inflating)
			m_pReadClassTable = new tagClassTable_t();
			m_pReadObjectTable = new tagObjTable_t();
		}
		else
		{
			// create hash tables needed for writing (deflating)
			m_pWriteClassTable = new classTagTable_t();
			m_pWriteObjectTable = new objTagTable_t();
		}
	}
}



// ----------------------------------------------------------------------------------------------------
