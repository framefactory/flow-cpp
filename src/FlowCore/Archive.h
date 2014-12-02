// -----------------------------------------------------------------------------
//  File        Archive.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_ARCHIVE_H
#define FLOWCORE_ARCHIVE_H

#include "FlowCore/Library.h"

#include <QString>
#include <QDataStream>
#include <unordered_map>
#include <vector>

class FTypeInfo;
class FObject;

// -----------------------------------------------------------------------------
//  Class FArchive
// -----------------------------------------------------------------------------

/// @class FArchive
/// Provides serialization of primitive types and classes derived from FObject.
/// If a dynamic archive is used (see constructors), the archive checks for
/// cyclic object references and writes or reads each object only once.
class FLOWCORE_EXPORT FArchive
{
	//  Public types -------------------------------------------------
	
public:
	enum mode_t
	{
		Read,
		Write
	};

	//  Constructors and destructor ----------------------------------

public:
	/// Creates an archive for serialization, operating on the given device.
	/// If checkRefs is set to true, the archive checks for cyclic pointers.
	FArchive(QIODevice* pDevice, bool checkRefs = true);

	/// Creates an archive for serialization, operating on the given buffer.
	/// If checkRefs is set to true, the archive checks for cyclic pointers.
	FArchive(QByteArray* pBuffer, mode_t mode, bool checkRefs = true);

	/// Creates an archive for serialization, operating on the given buffer.
	/// If checkRefs is set to true, the archive checks for cyclic pointers.
	FArchive(const QByteArray& buffer, bool checkRefs = true);

	/// Virtual destructor.
	virtual ~FArchive();

	//  Public commands ----------------------------------------------

public:
	/// Reads and returns an object from the data stream.
	/// @param pBaseClass If specified, the object read must be a
	/// a subtype of the given class. Null is returned otherwise.
	FObject* readObject(const FTypeInfo* pBaseClass = NULL);
	/// Writes an object to the data stream.
	void writeObject(const FObject* pObject);

	//  Public queries -----------------------------------------------

	/// Returns true if the archive is writing to a stream.
	bool isWriting() const { return m_archiveMode == Write; }
	/// Returns true if the archive is reading from a stream.
	bool isReading() const { return m_archiveMode == Read; }
	/// Returns the version number of the object being deserialized.
	/// Can be called from within the Serialize() function to determine
	/// the version of the object it is reading.
	size_t version() const { return m_currentVersion; }

	/// Returns the underlying data stream.
	QDataStream& stream() { return m_stream; }

	//  Operators ----------------------------------------------------
	
	FArchive& operator<<(bool v);
	FArchive& operator<<(qint8 v);
	FArchive& operator<<(quint8 v);
	FArchive& operator<<(int16_t v);
	FArchive& operator<<(uint16_t v);
	FArchive& operator<<(qint32 v);
	FArchive& operator<<(quint32 v);
	FArchive& operator<<(qint64 v);
	FArchive& operator<<(quint64 v);
	FArchive& operator<<(float v);
	FArchive& operator<<(double v);
	FArchive& operator<<(const char* s);
	FArchive& operator<<(const QString& s);
	FArchive& operator<<(const FObject* pObject);
	//FArchive& operator<<(const FTypeInfo* pTypeInfo);

	template <typename T>
	FArchive& operator<<(const std::vector<T*>& objects);
	template <typename T>
	FArchive& operator<<(const std::vector<T>& values);

	FArchive& operator>>(bool& v);
	FArchive& operator>>(qint8& v);
	FArchive& operator>>(quint8& v);
	FArchive& operator>>(int16_t& v);
	FArchive& operator>>(uint16_t& v);
	FArchive& operator>>(qint32& v);
	FArchive& operator>>(quint32& v);
	FArchive& operator>>(qint64& v);
	FArchive& operator>>(quint64& v);
	FArchive& operator>>(float& v);
	FArchive& operator>>(double& v);
	FArchive& operator>>(char*& s);
	FArchive& operator>>(QString& s);
	FArchive& operator>>(FObject*& pObject);
	//FArchive& operator>>(const FTypeInfo*& pTypeInfo);

	template <typename T>
	FArchive& operator>>(std::vector<T*>& objects);
	template <typename T>
	FArchive& operator>>(std::vector<T>& values);

	//  Internal functions -----------------------------------------------------

private:
	void _initialize();
	void _readRaw(void* pSource, size_t numBytes);
	void _writeRaw(const void* pDest, size_t numBytes);

	//  Internal data members --------------------------------------------------

private:
	struct classInfo_t
	{
		classInfo_t(const FTypeInfo* pC, size_t version)
			: pClass(pC), Version(version) { }
		const FTypeInfo* pClass;
		size_t Version;
	};

	typedef std::unordered_map<const FTypeInfo*, uint16_t> classTagTable_t;
	classTagTable_t *m_pWriteClassTable;
	uint16_t m_nextClassTag;

	typedef std::unordered_map<const FObject*, quint32> objTagTable_t;
	objTagTable_t *m_pWriteObjectTable;
	quint32 m_nextObjectTag;

	typedef std::unordered_map<uint16_t, classInfo_t> tagClassTable_t;
	tagClassTable_t *m_pReadClassTable;

	typedef std::unordered_map<quint32, FObject*> tagObjTable_t;
	tagObjTable_t *m_pReadObjectTable;

	quint32 m_currentVersion;
	mode_t m_archiveMode;
	bool m_checkRefs;

	QDataStream m_stream;
};

// Inline operators ------------------------------------------------------------

inline FArchive& FArchive::operator<<(bool v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(qint8 v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(quint8 v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(int16_t v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(uint16_t v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(qint32 v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(quint32 v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(qint64 v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(quint64 v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(float v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(double v)
{
	F_ASSERT(isWriting());
	m_stream << v;
	return *this;
}

inline FArchive& FArchive::operator<<(const char* s)
{
	F_ASSERT(isWriting());
	m_stream << s;
	return *this;
}

inline FArchive& FArchive::operator<<(const QString& s)
{
	F_ASSERT(isWriting());
	m_stream << s;
	return *this;
}

inline FArchive& FArchive::operator<<(const FObject* pObject)
{
	F_ASSERT(isWriting());
	writeObject(pObject);
	return *this;
}

inline FArchive& FArchive::operator>>(bool& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(qint8& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(quint8& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(int16_t& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;;
}

inline FArchive& FArchive::operator>>(uint16_t& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(qint32& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(quint32& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(qint64& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(quint64& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(float& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(double& v)
{
	F_ASSERT(isReading());
	m_stream >> v;
	return *this;
}

inline FArchive& FArchive::operator>>(char* &s)
{
	F_ASSERT(isReading());
	m_stream >> s;
	return *this;
}

inline FArchive& FArchive::operator>>(QString& s)
{
	F_ASSERT(isReading());
	m_stream >> s;
	return *this;
}

inline FArchive& FArchive::operator>>(FObject* &pObject)
{
	F_ASSERT(isReading());
	pObject = readObject();
	return *this;
}

// Template members ------------------------------------------------------------

template <typename T>
FArchive& FArchive::operator<<(const std::vector<T*>& objects)
{
	operator<<(objects.size());
	for (size_t i = 0, n = objects.size(); i < n; ++i) {
		writeObject(objects[i]);
	}

	return *this;
}

template <typename T>
FArchive& FArchive::operator>>(std::vector<T*>& objects)
{
    typename std::vector<T*>::size_type size;
	operator>>(size);
	objects.resize(size);
	for (size_t i = 0, n = objects.size(); i < n; ++i) {
		objects[i] = static_cast<T*>(readObject(T::staticType()));
	}

	return *this;
}

template <typename T>
FArchive& FArchive::operator<<(const std::vector<T>& values)
{
	operator<<(values.size());
	for (size_t i = 0, n = values.size(); i < n; ++i) {
		operator<<(values[i]);
	}

	return *this;
}

template <typename T>
FArchive& FArchive::operator>>(std::vector<T>& values)
{
    typename std::vector<T>::size_type size;
	operator>>(size);
	values.resize(size);
	for (size_t i = 0, n = values.size(); i < n; ++i) {
		operator>>(values[i]);
	}

	return *this;
}

// Vector and matrix classes ---------------------------------------------------

#ifdef FLOWCORE_VECTOR2T_H
template<typename REAL>
inline FArchive& operator<< (FArchive& ar, const FVector2T<REAL>& v) {
	ar << v.x << v.y; return ar;
}

template<typename REAL>
inline FArchive& operator>> (FArchive& ar, FVector2T<REAL>& v) {
	ar >> v.x >> v.y; return ar;
}
#endif

#ifdef FLOWCORE_VECTOR3T_H
template<typename REAL>
inline FArchive& operator<< (FArchive& ar, const FVector3T<REAL>& v) {
	ar << v.x << v.y << v.z; return ar;
}

template<typename REAL>
inline FArchive& operator>> (FArchive& ar, FVector3T<REAL>& v) {
	ar >> v.x >> v.y >> v.z; return ar;
}
#endif

#ifdef FLOWCORE_VECTOR4T_H
template<typename REAL>
inline FArchive& operator<< (FArchive& ar, const FVector4T<REAL>& v) {
	ar << v.x << v.y << v.z << v.w; return ar;
}

template<typename REAL>
inline FArchive& operator>> (FArchive& ar, FVector4T<REAL>& v) {
	ar >> v.x >> v.y >> v.z >> v.w; return ar;
}
#endif

#ifdef FLOWCORE_MATRIX3T_H
template<typename REAL>
inline FArchive& operator<< (FArchive& ar, const FMatrix3T<REAL>& m) {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			ar << m(r, c);
		}
	}

	return ar;
}

template<typename REAL>
inline FArchive& operator>> (FArchive& ar, FMatrix3T<REAL>& m) {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			ar >> m(r, c);
		}
	}

	return ar;
}
#endif

#ifdef FLOWCORE_MATRIX4T_H
template<typename REAL>
inline FArchive& operator<< (FArchive& ar, const FMatrix4T<REAL>& m) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			ar << m(r, c);
		}
	}

	return ar;
}

template<typename REAL>
inline FArchive& operator>> (FArchive& ar, FMatrix4T<REAL>& m) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			ar >> m(r, c);
		}
	}

	return ar;
}
#endif

// -----------------------------------------------------------------------------

#endif // FLOWCORE_ARCHIVE_H
