// -----------------------------------------------------------------------------
//  File        ValueArray.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_VALUEARRAY_H
#define FLOWCORE_VALUEARRAY_H

#include "FlowCore/Library.h"
#include "FlowCore/ValueType.h"
#include "FlowCore/AutoConvert.h"

#include "FlowCore/Vector2T.h"
#include "FlowCore/Vector3T.h"
#include "FlowCore/Vector4T.h"

#include <QString>
#include <QByteArray>

class FObject;
class FArchive;

// -----------------------------------------------------------------------------
//  Class FValueArray
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FValueArray
{
	//  Public types -------------------------------------------------
  
public:
	typedef qint32 size_type;

	//  Constructors and destructor ----------------------------------

	/// Default Constructor.
	FValueArray();
	/// Copy constructor.
	FValueArray(const FValueArray& other);
	/// Creates a value array with the given type and storage space.
	FValueArray(FValueType type, size_type channels, size_type dimensions);

	/// Creates a singular value of the given type.
	template <typename T>
	explicit FValueArray(const T& val);

	/// Creates a value holding an array of values of the given type.
	template <typename T>
	FValueArray(T* pVal, size_type channels,
		size_type dimensions, bool reference);

	/// Destructor.
	~FValueArray() { _delete(); }

	//  Operators ----------------------------------------------------

	/// Assignment operator.
	FValueArray& operator=(const FValueArray& other) {
		if (this == &other) return *this;

		_delete(); _copy(&other);
		return *this;
	}

	//  Data access --------------------------------------------------

	/// Returns a const pointer to the first data element.
	/// Types must match, no type conversion provided.
	template <typename T>
	const T* ptr() const;

	/// Returns a pointer to the first data element.
	/// Types must match, no type conversion provided.
	template <typename T>
	T* ptr();

	/// Returns a const pointer to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	const T* ptr(size_type channel, size_type dimension = 0) const;

	/// Returns a pointer to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	T* ptr(size_type channel, size_type dimension = 0);
	
	/// Returns a const reference to the first data element.
	/// Types must match, no type conversion provided.
	template <typename T>
	const T& as() const;

	/// Returns a reference to the first data element.
	/// Types must match, no type conversion provided.
	template <typename T>
	T& as();

	/// Returns a const reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	const T& as(size_type channel, size_type dimension = 0) const;

	/// Returns a reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	T& as(size_type channel, size_type dimension = 0);

	/// Returns a const 2-vector reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	const FVector2T<T>& asVector2(size_t channel, size_t dimension = 0) const;

	/// Returns a 2-vector reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	FVector2T<T>& asVector2(size_t channel, size_t dimension = 0);

	/// Returns a const 3-vector reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	const FVector3T<T>& asVector3(size_t channel, size_t dimension = 0) const;

	/// Returns a 3-vector reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	FVector3T<T>& asVector3(size_t channel, size_t dimension = 0);

	/// Returns a const 4-vector reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	const FVector4T<T>& asVector4(size_t channel, size_t dimension = 0) const;

	/// Returns a 4-vector reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	FVector4T<T>& asVector4(size_t channel, size_t dimension = 0);

	/// Returns the first data element, converted to the given type.
	template <typename T>
	T to() const;

	/// Returns the data element at the given channel and dimension,
	/// converted to the given type.
	template <typename T>
	T to(size_type channel, size_type dimension = 0) const;

	/// Sets the first data element and provides conversion if necessary.
	template <typename T>
	void set(const T& val);

	/// Sets the data element at the given channel and dimension
	/// and provides conversion if necessary.
	template <typename T>
	void set(size_type channel, size_type dimension, const T& val);

	/// Sets the data elements at the given channel from the given 2-vector.
	template <typename T>
	void setVector2(size_type channel, const FVector2T<T>& vector);

	/// Sets the data elements at the given channel from the given 3-vector.
	template <typename T>
	void setVector3(size_type channel, const FVector3T<T>& vector);

	/// Sets the data elements at the given channel from the given 4-vector.
	template <typename T>
	void setVector4(size_type channel, const FVector4T<T>& vector);

	/// Returns true if this value array is of the given type.
	template <typename T>
	bool is() const;

	/// Returns a raw pointer to the data of the value array.
	char* rawPtr();
	/// Returns a const raw pointer to the data of the value array.
	const char* rawPtr() const;

	//  Public commands ----------------------------------------------

	/// Allocates space for the given type.
	void allocate(FValueType type, size_type channels, size_type dimensions = 1);

	/// Allocates space for an array of values of the given type.
	template <typename T>
	void allocate(T* pVal, size_type channels, size_type dimensions, bool reference);
	
	/// Deletes the content of the array.
	void clear();

	/// Copy/convert the data from the given source.
	/// Dimensions must agree and the types must be compatible.
	void convertFrom(const FValueArray& source);

	/// Copy/convert one dimension on all channels from the given source.
	void convertFrom(const FValueArray& source,
		size_type sourceDimensionIndex, size_type destinationDimensionIndex);

	/// Copy/convert one dimension on one channel from the given source.
	void convertFrom(const FValueArray& source,
		size_type sourceChannelIndex, size_type destinationChannelIndex,
		size_type sourceDimensionIndex, size_type destinationDimensionIndex);

	/// Copy/convert from the given source with maximum flexibility.
	void convertFrom(
		const FValueArray& source,
		size_type sourceChannelStart,
		size_type destinationChannelStart,
		size_type channelCount,
		size_type sourceChannelStride,
		size_type destinationChannelStride,
		size_type sourceDimensionStart,
		size_type destinationDimensionStart,
		size_type dimensionCount);

	/// Resizes the data to the given number of dimensions. Data is not preserved!
	void setDimensionCount(size_type dimensionCount);
	/// Allocates space for the given number of dimensions.
	void setDimensionCapacity(size_type dimensionCapacity);

	/// Resizes the data to the given number of channels.
	void setChannelCount(size_type channelCount, bool preserveData = false);
	/// Allocates space for the given number of channels.
	void setChannelCapacity(size_type channelCapacity, bool preserveData = false);

	/// Sets the changed flag on the data.
	void setChanged(quint32 state = 1) { m_hasChanged = state; }
	/// Clears the changed flag on the data.
	void clearChanged() { m_hasChanged = 0; }

	/// Serialization. If serializeRawData is false, only type and dimensionality
	/// information is stored, and after loading, memory is reserved but not initialized.
	void serialize(FArchive& ar, bool serializeRawData = true);

	//  Public queries -----------------------------------------------

	/// Returns a buffer with the raw data.
	QByteArray toByteArray() const;

	/// Returns true if it is possible to convert the given type to the
	/// type of this value array.
	bool canConvertFrom(const FValueArray& source) const;

	/// Returns the type of the data.
	FValueType type() const { return (FValueType::enum_type)m_type; }
	/// Returns the name of the data type.	
	const char* typeName() const { return type().name(); }
	/// Returns a description of the data type.
	QString typeDescription() const;

	/// Returns the number of dimensions of one channel.
	size_type dimensionCount() const { return m_dimensionCount; }
	/// Returns the number of channels.
	size_type channelCount() const { return m_channelCount; }
	/// Returns the total number of data primitives.
	size_type size() const { return m_dimensionCount * m_channelCount; }
	/// Returns true if the array contains no values.
	bool isEmpty() const { return m_dimensionCount == 0 || m_channelCount == 0; }
	/// Returns the number of reserved dimensions.
	size_type dimensionCapacity() const { return m_dimensionCapacity; }
	/// Returns the number of reserved channels.
	size_type channelCapacity() const { return m_channelCapacity; }
	/// Returns the total capacity.
	size_type capacity() const { return m_dimensionCapacity * m_channelCapacity; }

	/// Returns the size of the data in bytes.
	size_t byteSize() const;

	/// Returns true if the data array is referenced and will not be deleted.
	bool isReference() const { return m_isReference; }

	/// Returns true if the changed flag is set.
	bool hasChanged() const { return m_hasChanged; }

#ifdef FLOW_DEBUG
	/// Returns information about the internal state.
	QString dump() const;
#endif

	//  Internal functions -------------------------------------------

private:
	void _copy(const FValueArray* pSource);
	void _convert(
		const FValueArray* pSource,
		size_type sourceChannelStart,
		size_type destinationChannelStart,
		size_type channelCount,
		size_type sourceChannelStride,
		size_type destinationChannelStride,
		size_type sourceDimensionStart,
		size_type destinationDimensionStart,
		size_type dimensionCount);

	void _initialize(FValueType type, size_type channels,
		size_type dimensions, bool isReference);
	void _allocate();
	void _reallocate(size_type newChannelCapacity,
		size_type newDimensionCapacity, bool preserveData);
	void _resize(size_type newChannelCount);
	void _delete();

	size_type _index(size_type channel, size_type dimension) const;

	template <typename T> const T* _ptr() const;
	template <typename T> T* _ptr();

	template <> const QString* _ptr() const;
	template <> QString* _ptr();

	//  Internal data members ----------------------------------------

	union {
		void* ptr;
		qint64 val;
	} m_raw;

	size_type m_dimensionCount;
	size_type m_channelCount;
	size_type m_dimensionCapacity;
	size_type m_channelCapacity;

	FValueType m_type;

	quint8   m_isArray			:  1;
	quint8   m_isReference		:  1;
	quint8   m_hasChanged      :  1;
};

// Constructors ----------------------------------------------------------------

inline FValueArray::FValueArray()
{
	_initialize(FValueType::Invalid, 0, 0, false);
}

inline FValueArray::FValueArray(const FValueArray& other)
{
	_copy(&other);
}

inline FValueArray::FValueArray(
	FValueType type, size_type channels, size_type dimensions)
{
	_initialize(type, channels, dimensions, false);
}

template <typename T>
inline FValueArray::FValueArray(const T& val)
{
	_initialize(FValueType::fromType<T>(), 1, 1, false);
	set<T>(val);
}

template <typename T>
FValueArray::FValueArray(T* pVal, size_type channels,
	size_type dimensions, bool reference /* = false */)
{
	F_ASSERT(channels * dimensions > 0);
	_initialize(FValueType::fromType<T>(), channels, dimensions, reference);

	if (m_isReference)
	{
		m_raw.ptr = pVal;
	}
	else
	{
		if (m_isArray)
			for (size_type i = 0, n = channels * dimensions; i < n; ++i)
				((T*)(m_raw.ptr))[i] = pVal[i];
		else
			set<T>(*pVal);
	}
}

// Data access -----------------------------------------------------------------

template <typename T>
const T* FValueArray::ptr() const
{
	return _ptr<T>();
}

template <typename T>
T* FValueArray::ptr()
{
	return _ptr<T>();
}

template <typename T>
const T* FValueArray::ptr(size_type channel, size_type dimension) const
{
	return _ptr<T>() + _index(channel, dimension);
}

template <typename T>
T* FValueArray::ptr(size_type channel, size_type dimension)
{
	return _ptr<T>() + _index(channel, dimension);
}

template <typename T>
const T& FValueArray::as() const
{
	return *_ptr<T>();
}

template <typename T>
T& FValueArray::as()
{
	return *_ptr<T>();
}

template <typename T>
const T& FValueArray::as(size_type channel, size_type dimension) const
{
	return *(_ptr<T>() + _index(channel, dimension));
}

template <typename T>
T& FValueArray::as(size_type channel, size_type dimension)
{
	return *(_ptr<T>() + _index(channel, dimension));
}

template <typename T>
const FVector2T<T>& FValueArray::asVector2(size_t channel, size_t dimension) const
{
	F_ASSERT(dimension + 2 <= m_dimensionCount);
	return *((const FVector2T<T>*)(_ptr<T>() + _index(channel, dimension)));
}

template <typename T>
FVector2T<T>& FValueArray::asVector2(size_t channel, size_t dimension)
{
	F_ASSERT(dimension + 2 <= m_dimensionCount);
	return *((FVector2T<T>*)(_ptr<T>() + _index(channel, dimension)));
}

template <typename T>
const FVector3T<T>& FValueArray::asVector3(size_t channel, size_t dimension) const
{
	F_ASSERT(dimension + 3 <= m_dimensionCount);
	return *((const FVector3T<T>*)(_ptr<T>() + _index(channel, dimension)));
}

template <typename T>
FVector3T<T>& FValueArray::asVector3(size_t channel, size_t dimension)
{
	F_ASSERT(dimension + 3 <= m_dimensionCount);
	return *((FVector3T<T>*)(_ptr<T>() + _index(channel, dimension)));
}

template <typename T>
const FVector4T<T>& FValueArray::asVector4(size_t channel, size_t dimension) const
{
	F_ASSERT(dimension + 4 <= m_dimensionCount);
	return *((const FVector4T<T>*)(_ptr<T>() + _index(channel, dimension)));
}

template <typename T>
FVector4T<T>& FValueArray::asVector4(size_t channel, size_t dimension)
{
	F_ASSERT(dimension + 4 <= m_dimensionCount);
	return *((FVector4T<T>*)(_ptr<T>() + _index(channel, dimension)));
}

template <typename T>
T FValueArray::to() const
{
	if (is<T>())
		return as<T>();

	switch (m_type)
	{
	case FValueType::Float:   return auto_convert<T, float    >(as<float    >());
	case FValueType::Double:  return auto_convert<T, double   >(as<double   >());
	case FValueType::Bool:    return auto_convert<T, bool     >(as<bool     >());
	case FValueType::Int8:    return auto_convert<T, qint8   >(as<qint8   >());
	case FValueType::UInt8:   return auto_convert<T, quint8  >(as<quint8  >());
	case FValueType::Int16:   return auto_convert<T, int16_t  >(as<int16_t  >());
	case FValueType::UInt16:  return auto_convert<T, uint16_t >(as<uint16_t >());
	case FValueType::Int32:   return auto_convert<T, qint32  >(as<qint32  >());
	case FValueType::UInt32:  return auto_convert<T, quint32 >(as<quint32 >());
	case FValueType::Int64:   return auto_convert<T, qint64  >(as<qint64  >());
	case FValueType::UInt64:  return auto_convert<T, quint64 >(as<quint64 >());
	case FValueType::String:  return auto_convert<T, QString  >(as<QString  >());
	case FValueType::Object:  return auto_convert<T, FObject* >(as<FObject* >());
	case FValueType::Invalid:
	default: F_ASSERT(false); return T();
	}
}

template <typename T>
T FValueArray::to(size_type channel, size_type dimension) const
{
	if (is<T>())
		return as<T>(channel, dimension);

	switch (m_type)
	{
	case FValueType::Float:   return auto_convert<T, float    >(as<float    >(channel, dimension));
	case FValueType::Double:  return auto_convert<T, double   >(as<double   >(channel, dimension));
	case FValueType::Bool:    return auto_convert<T, bool     >(as<bool     >(channel, dimension));
	case FValueType::Int8:    return auto_convert<T, qint8   >(as<qint8   >(channel, dimension));
	case FValueType::UInt8:   return auto_convert<T, quint8  >(as<quint8  >(channel, dimension));
	case FValueType::Int16:   return auto_convert<T, int16_t  >(as<int16_t  >(channel, dimension));
	case FValueType::UInt16:  return auto_convert<T, uint16_t >(as<uint16_t >(channel, dimension));
	case FValueType::Int32:   return auto_convert<T, qint32  >(as<qint32  >(channel, dimension));
	case FValueType::UInt32:  return auto_convert<T, quint32 >(as<quint32 >(channel, dimension));
	case FValueType::Int64:   return auto_convert<T, qint64  >(as<qint64  >(channel, dimension));
	case FValueType::UInt64:  return auto_convert<T, quint64 >(as<quint64 >(channel, dimension));
	case FValueType::String:  return auto_convert<T, QString  >(as<QString  >(channel, dimension));
	case FValueType::Object:  return auto_convert<T, FObject* >(as<FObject* >(channel, dimension));
	case FValueType::Invalid:
	default: F_ASSERT(false); return T();
	}
}

template <typename T>
void FValueArray::set(const T& val)
{
	if (is<T>())
	{
		as<T>() = val;
		return;
	}

	switch (m_type)
	{
	case FValueType::Float:   as<float    >() = auto_convert<float    , T>(val); return;
	case FValueType::Double:  as<double   >() = auto_convert<double   , T>(val); return;
	case FValueType::Bool:    as<bool     >() = auto_convert<bool     , T>(val); return;
	case FValueType::Int8:    as<qint8   >() = auto_convert<qint8   , T>(val); return;
	case FValueType::UInt8:   as<quint8  >() = auto_convert<quint8  , T>(val); return;
	case FValueType::Int16:   as<int16_t  >() = auto_convert<int16_t  , T>(val); return;
	case FValueType::UInt16:  as<uint16_t >() = auto_convert<uint16_t , T>(val); return;
	case FValueType::Int32:   as<qint32  >() = auto_convert<qint32  , T>(val); return;
	case FValueType::UInt32:  as<quint32 >() = auto_convert<quint32 , T>(val); return;
	case FValueType::Int64:   as<qint64  >() = auto_convert<qint64  , T>(val); return;
	case FValueType::UInt64:  as<quint64 >() = auto_convert<quint64 , T>(val); return;
	case FValueType::String:  as<QString  >() = auto_convert<QString  , T>(val); return;
	case FValueType::Object:  as<FObject* >() = auto_convert<FObject* , T>(val); return;
	case FValueType::Invalid:
	default: F_ASSERT(false);
	}
}

template <typename T>
void FValueArray::set(size_type channel, size_type dimension, const T& val)
{
	if (is<T>())
	{
		as<T>(channel, dimension) = val;
		return;
	}

	switch (m_type)
	{
	case FValueType::Float:   as<float    >(channel, dimension) = auto_convert<float    , T>(val); return;
	case FValueType::Double:  as<double   >(channel, dimension) = auto_convert<double   , T>(val); return;
	case FValueType::Bool:    as<bool     >(channel, dimension) = auto_convert<bool     , T>(val); return;
	case FValueType::Int8:    as<qint8   >(channel, dimension) = auto_convert<qint8   , T>(val); return;
	case FValueType::UInt8:   as<quint8  >(channel, dimension) = auto_convert<quint8  , T>(val); return;
	case FValueType::Int16:   as<int16_t  >(channel, dimension) = auto_convert<int16_t  , T>(val); return;
	case FValueType::UInt16:  as<uint16_t >(channel, dimension) = auto_convert<uint16_t , T>(val); return;
	case FValueType::Int32:   as<qint32  >(channel, dimension) = auto_convert<qint32  , T>(val); return;
	case FValueType::UInt32:  as<quint32 >(channel, dimension) = auto_convert<quint32 , T>(val); return;
	case FValueType::Int64:   as<qint64  >(channel, dimension) = auto_convert<qint64  , T>(val); return;
	case FValueType::UInt64:  as<quint64 >(channel, dimension) = auto_convert<quint64 , T>(val); return;
	case FValueType::String:  as<QString  >(channel, dimension) = auto_convert<QString  , T>(val); return;
	case FValueType::Object:  as<FObject* >(channel, dimension) = auto_convert<FObject* , T>(val); return;
	case FValueType::Invalid:
	default: F_ASSERT(false);
	}
}

template <typename T>
void FValueArray::setVector2(size_type channel, const FVector2T<T>& vector)
{
	F_ASSERT(m_dimensionCount >= 2);
	set(channel, 0, vector.x);
	set(channel, 1, vector.y);
}

template <typename T>
void FValueArray::setVector3(size_type channel, const FVector3T<T>& vector)
{
	F_ASSERT(m_dimensionCount >= 3);
	set(channel, 0, vector.x);
	set(channel, 1, vector.y);
	set(channel, 2, vector.z);
}

template <typename T>
void FValueArray::setVector4(size_type channel, const FVector4T<T>& vector)
{
	F_ASSERT(m_dimensionCount >= 4);
	set(channel, 0, vector.x);
	set(channel, 1, vector.y);
	set(channel, 2, vector.z);
	set(channel, 3, vector.w);
}

template <typename T>
inline bool FValueArray::is() const
{
	return m_type == FValueType::fromType<T>();
}

inline char* FValueArray::rawPtr()
{
	return m_isArray ? (char*)m_raw.ptr : (char*)(&m_raw.ptr);
}

inline const char* FValueArray::rawPtr() const
{
	return m_isArray ? (const char*)m_raw.ptr : (const char*)(&m_raw.ptr);
}

// Public commands -------------------------------------------------------------

inline void FValueArray::allocate(
	FValueType type, size_type channels, size_type dimensions)
{
	_delete();
	_initialize(type, channels, dimensions, false);
}

template <typename T>
void FValueArray::allocate(
	T* pVal, size_type channels, size_type dimensions, bool reference)
{
	_delete();
	F_ASSERT(channels * dimensions > 0);
	_initialize(FValueType::fromType<T>(), channels, dimensions, reference);

	if (m_isReference)
	{
		m_raw.ptr = pVal;
	}
	else
	{
		if (m_isArray)
			for (size_type i = 0, n = channels * dimensions; i < n; ++i)
				((T*)(m_raw.ptr))[i] = pVal[i];
		else
			set<T>(*pVal);
	}
}

inline void FValueArray::clear()
{
	_delete();
	_initialize(FValueType::Invalid, 0, 0, false);
}

inline void FValueArray::convertFrom(const FValueArray& source)
{
	_convert(&source, 0, 0, channelCount(), 1, 1, 0, 0, dimensionCount());
}

inline void FValueArray::convertFrom(
	const FValueArray& source,
	size_type sourceDimensionIndex,
	size_type destinationDimensionIndex)
{
	_convert(&source, 0, 0, channelCount(), 1, 1,
		sourceDimensionIndex, destinationDimensionIndex, 1);
}

inline void FValueArray::convertFrom(
	const FValueArray& source,
	size_type sourceChannelIndex,
	size_type destinationChannelIndex,
	size_type sourceDimensionIndex,
	size_type destinationDimensionIndex)
{
	_convert(&source, sourceChannelIndex, destinationChannelIndex, 1,
		1, 1, sourceDimensionIndex, destinationDimensionIndex, 1);
}

inline void FValueArray::convertFrom(
	const FValueArray& source,
	size_type sourceChannelStart,
	size_type destinationChannelStart,
	size_type channelCount,
	size_type sourceChannelStride,
	size_type destinationChannelStride,
	size_type sourceDimensionStart,
	size_type destinationDimensionStart,
	size_type dimensionCount)
{
	_convert(&source,
		sourceChannelStart, destinationChannelStart, channelCount,
		sourceChannelStride, destinationChannelStride,
		sourceDimensionStart, destinationDimensionStart, dimensionCount);
}

// Public queries --------------------------------------------------------------

inline bool FValueArray::canConvertFrom(const FValueArray& source) const
{
	return !((is<FObject*>() && !source.is<FObject*>())
		|| (source.is<FObject*>() && !is<QString>()));
}

// Internal functions ----------------------------------------------------------

inline FValueArray::size_type FValueArray::_index(
	size_type channel, size_type dimension) const
{
	F_ASSERT(dimension < m_dimensionCount);
	return (channel % m_channelCount) * m_dimensionCount + dimension;
}

template <typename T>
inline const T* FValueArray::_ptr() const
{
	F_ASSERT(is<T>());
	return m_isArray ? (const T*)m_raw.ptr : (const T*)(&m_raw.ptr);
}

template <typename T>
inline T* FValueArray::_ptr()
{
	F_ASSERT(is<T>());
	return m_isArray ? (T*)m_raw.ptr : (T*)(&m_raw.ptr);
}

template <>
inline const QString* FValueArray::_ptr() const
{
	F_ASSERT(is<QString>());
	return (const QString*)m_raw.ptr;
}

template <>
inline QString* FValueArray::_ptr()
{
	F_ASSERT(is<QString>());
	return (QString*)m_raw.ptr;
}

// Related non-member functions ------------------------------------------------

inline FArchive& operator<<(FArchive& ar, const FValueArray& va)
{
	const_cast<FValueArray&>(va).serialize(ar);
	return ar;
}

inline FArchive& operator>>(FArchive& ar, FValueArray& va)
{
	va.serialize(ar);
	return ar;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_VALUEARRAY_H