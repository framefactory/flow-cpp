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

#include <QString>

class FObject;
class FArchive;

// -----------------------------------------------------------------------------
//  Class FValueArray
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FValueArray
{
	//  Public types -------------------------------------------------
  
public:
	typedef int32_t size_type;

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
	const T* ptr(size_type channel, size_type dimension) const;

	/// Returns a pointer to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	T* ptr(size_type channel, size_type dimension);
	
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
	const T& as(size_type channel, size_type dimension) const;

	/// Returns a reference to the data element at the given
	/// channel and dimension. Types must match, no type conversion provided.
	template <typename T>
	T& as(size_type channel, size_type dimension);

	/// Returns the first data element, converted to the given type.
	template <typename T>
	T to() const;

	/// Returns the data element at the given channel and dimension,
	/// converted to the given type.
	template <typename T>
	T to(size_type channel, size_type dimension) const;

	/// Sets the first data element and provides conversion if necessary.
	template <typename T>
	void set(const T& val);

	/// Sets the data element at the given channel and dimension
	/// and provides conversion if necessary.
	template <typename T>
	void set(size_type channel, size_type dimension, const T& val);

	/// Returns true if this value array is of the given type.
	template <typename T>
	bool is() const;

	//  Public commands ----------------------------------------------

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
	void setChanged(uint32_t state = 1) { m_hasChanged = state; }
	/// Clears the changed flag on the data.
	void clearChanged() { m_hasChanged = 0; }

	/// Serialization. If serializeRawData is false, only type and dimensionality
	/// information is stored, and after loading, memory is reserved but not initialized.
	void serialize(FArchive& ar, bool serializeRawData = true);

	//  Public queries -----------------------------------------------

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
		int64_t val;
	} m_raw;

	size_type m_dimensionCount;
	size_type m_channelCount;
	size_type m_dimensionCapacity;
	size_type m_channelCapacity;

	FValueType m_type;

	uint8_t   m_isArray			:  1;
	uint8_t   m_isReference		:  1;
	uint8_t   m_hasChanged      :  1;
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
T FValueArray::to() const
{
	if (is<T>())
		return as<T>();

	switch (m_type)
	{
	case FValueType::Float:   return auto_convert<T, float    >(as<float    >());
	case FValueType::Double:  return auto_convert<T, double   >(as<double   >());
	case FValueType::Bool:    return auto_convert<T, bool     >(as<bool     >());
	case FValueType::Int8:    return auto_convert<T, int8_t   >(as<int8_t   >());
	case FValueType::UInt8:   return auto_convert<T, uint8_t  >(as<uint8_t  >());
	case FValueType::Int16:   return auto_convert<T, int16_t  >(as<int16_t  >());
	case FValueType::UInt16:  return auto_convert<T, uint16_t >(as<uint16_t >());
	case FValueType::Int32:   return auto_convert<T, int32_t  >(as<int32_t  >());
	case FValueType::UInt32:  return auto_convert<T, uint32_t >(as<uint32_t >());
	case FValueType::Int64:   return auto_convert<T, int64_t  >(as<int64_t  >());
	case FValueType::UInt64:  return auto_convert<T, uint64_t >(as<uint64_t >());
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
	case FValueType::Int8:    return auto_convert<T, int8_t   >(as<int8_t   >(channel, dimension));
	case FValueType::UInt8:   return auto_convert<T, uint8_t  >(as<uint8_t  >(channel, dimension));
	case FValueType::Int16:   return auto_convert<T, int16_t  >(as<int16_t  >(channel, dimension));
	case FValueType::UInt16:  return auto_convert<T, uint16_t >(as<uint16_t >(channel, dimension));
	case FValueType::Int32:   return auto_convert<T, int32_t  >(as<int32_t  >(channel, dimension));
	case FValueType::UInt32:  return auto_convert<T, uint32_t >(as<uint32_t >(channel, dimension));
	case FValueType::Int64:   return auto_convert<T, int64_t  >(as<int64_t  >(channel, dimension));
	case FValueType::UInt64:  return auto_convert<T, uint64_t >(as<uint64_t >(channel, dimension));
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
	case FValueType::Int8:    as<int8_t   >() = auto_convert<int8_t   , T>(val); return;
	case FValueType::UInt8:   as<uint8_t  >() = auto_convert<uint8_t  , T>(val); return;
	case FValueType::Int16:   as<int16_t  >() = auto_convert<int16_t  , T>(val); return;
	case FValueType::UInt16:  as<uint16_t >() = auto_convert<uint16_t , T>(val); return;
	case FValueType::Int32:   as<int32_t  >() = auto_convert<int32_t  , T>(val); return;
	case FValueType::UInt32:  as<uint32_t >() = auto_convert<uint32_t , T>(val); return;
	case FValueType::Int64:   as<int64_t  >() = auto_convert<int64_t  , T>(val); return;
	case FValueType::UInt64:  as<uint64_t >() = auto_convert<uint64_t , T>(val); return;
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
	case FValueType::Int8:    as<int8_t   >(channel, dimension) = auto_convert<int8_t   , T>(val); return;
	case FValueType::UInt8:   as<uint8_t  >(channel, dimension) = auto_convert<uint8_t  , T>(val); return;
	case FValueType::Int16:   as<int16_t  >(channel, dimension) = auto_convert<int16_t  , T>(val); return;
	case FValueType::UInt16:  as<uint16_t >(channel, dimension) = auto_convert<uint16_t , T>(val); return;
	case FValueType::Int32:   as<int32_t  >(channel, dimension) = auto_convert<int32_t  , T>(val); return;
	case FValueType::UInt32:  as<uint32_t >(channel, dimension) = auto_convert<uint32_t , T>(val); return;
	case FValueType::Int64:   as<int64_t  >(channel, dimension) = auto_convert<int64_t  , T>(val); return;
	case FValueType::UInt64:  as<uint64_t >(channel, dimension) = auto_convert<uint64_t , T>(val); return;
	case FValueType::String:  as<QString  >(channel, dimension) = auto_convert<QString  , T>(val); return;
	case FValueType::Object:  as<FObject* >(channel, dimension) = auto_convert<FObject* , T>(val); return;
	case FValueType::Invalid:
	default: F_ASSERT(false);
	}
}

template <typename T>
inline bool FValueArray::is() const
{
	return m_type == FValueType::fromType<T>();
}

// Public commands -------------------------------------------------------------

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