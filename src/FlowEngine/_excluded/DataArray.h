// -----------------------------------------------------------------------------
//  File        DataArray.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.10 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_DATAARRAY_H
#define FLOWENGINE_DATAARRAY_H

#include "FlowEngine/Library.h"
#include "FlowCore/ValueArray.h"

// -----------------------------------------------------------------------------
//  Class FDataArray
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FDataArray
{
	//  Public types -------------------------------------------------

public:
	typedef FValueArray::size_type size_type;

	//  Constructors and destructor ----------------------------------

	/// Default constructor.
	FDataArray();
	/// Copy constructor.
	FDataArray(const FDataArray& other);
	/// Creates a data array with the given type and storage space.
	FDataArray(FValueType type, size_type channels, size_type dimensions);

	/// Creates a singular value of the given type.
	template <typename T>
	explicit FDataArray(const T& val);

	/// Creates a value holding an array of values of the given type.
	template <typename T>
	FDataArray(T* pVal, size_type channels,
		size_type dimensions, bool reference);

	/// Destructor.
	~FDataArray() { _delete(); }

	//  Operators ----------------------------------------------------

	/// Assignment operator.
	FDataArray& operator=(const FDataArray& other) {
		if (this == &other) return *this;
		{
			_delete();
			_copy(&other);
		}
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

public:
	/// Fires an event on the given channel.
	inline void fire(size_type channel, uint32_t count);
	/// Fires an event on all channels.
	inline void fire(uint32_t count);

	/// Sets the global change flag.
	inline void setChanged();
	/// Marks the given channel as changed.
	inline void setChanged(size_type channel);
	/// Marks all channels as changed.
	inline void setAllChanged();

	/// Marks the data as unchanged and resets the fire count.
	void clearChanged();

	/// Copy/convert the data from the given source.
	/// Dimensions must agree and the types must be compatible.
	void convertFrom(const FDataArray& source);

	/// Copy/convert one dimension on all channels from the given source.
	void convertFrom(const FDataArray& source,
		size_type sourceDimensionIndex, size_type destinationDimensionIndex);

	/// Copy/convert one dimension on one channel from the given source.
	void convertFrom(const FDataArray& source,
		size_type sourceChannelIndex, size_type destinationChannelIndex,
		size_type sourceDimensionIndex, size_type destinationDimensionIndex);

	/// Copy/convert from the given source with maximum flexibility.
	void convertFrom(const FDataArray& source,
		size_type sourceChannelStart,
		size_type destinationChannelStart,
		size_type channelCount,
		size_type sourceChannelStride,
		size_type destinationChannelStride,
		size_type sourceDimensionStart,
		size_type destinationDimensionStart,
		size_type dimensionCount);

	/// Copy/convert the data from the given source.
	/// Dimensions must agree and the types must be compatible.
	void convertFromValueArray(const FValueArray& source);

	/// Copy/convert one dimension on all channels from the given source.
	void convertFromValueArray(const FValueArray& source,
		size_type sourceDimensionIndex, size_type destinationDimensionIndex);

	/// Copy/convert one dimension on one channel from the given source.
	void convertFromValueArray(const FValueArray& source,
		size_type sourceChannelIndex, size_type destinationChannelIndex,
		size_type sourceDimensionIndex, size_type destinationDimensionIndex);

	/// Copy/convert from the given source with maximum flexibility.
	void convertFromValueArray(const FValueArray& source,
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

	/// Serialization. If serializeRawData is false, only type and dimensionality
	/// information is stored, and after loading, memory is reserved but not initialized.
	void serialize(FArchive& ar, bool serializeRawData = true);

	//  Public queries -----------------------------------------------

	/// Returns true if the data of any channel has changed.
	bool hasChanged() const { return m_data.hasChanged(); }
	/// Returns true if the data of the given channel has changed.
	bool hasChanged(size_type channel) const;

	/// Returns how many times the event on this object has been fired.
	/// The total of all channels is returned.
	uint32_t fireCount() const;
	/// Returns how many times the event on the given channel has been fired.
	uint32_t fireCount(size_type channel) const;

	bool canConvertFrom(const FDataArray& source) const;
	bool canConvertFrom(const FValueArray& source) const;

	/// Returns the type of the data.
	FValueType type() const { return m_data.type(); }
	/// Returns the name of the data type.	
	const char* typeName() const { return m_data.typeName(); }
	/// Returns a description of the data type.
	wstring_t typeDescription() const { return m_data.typeDescription(); }

	/// Returns the number of dimensions of one channel.
	size_type dimensionCount() const { return m_data.dimensionCount(); }
	/// Returns the number of channels.
	size_type channelCount() const { return m_data.channelCount(); }
	/// Returns the total number of data primitives.
	size_type size() const { return m_data.size(); }
	/// Returns true if the array contains no values.
	bool isEmpty() const { return m_data.isEmpty(); }
	/// Returns the number of reserved dimensions.
	size_type dimensionCapacity() const { return m_data.dimensionCapacity(); }
	/// Returns the number of reserved channels.
	size_type channelCapacity() const { return m_data.channelCapacity(); }
	/// Returns the total capacity.
	size_type capacity() const { return m_data.capacity(); }

	/// Returns true if the data array is referenced and will not be deleted.
	bool isReference() const { return m_data.isReference(); }

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given debug object.
	void dump(std::wostream& stream) const;
#endif

	//  Internal functions -------------------------------------------

private:
	void _copy(const FDataArray* pSource);

	void _allocate(size_t newChannelCapacity);
	void _delete();

	void _reallocate(size_type newChannelCapacity, bool preserveData);
	void _resize(size_type newChannelCount);

	void _copyFrom(const FDataArray* pSource, size_type sourceChannelStart,
		size_type destinationChannelStart, size_type channelCount,
		size_type sourceChannelStride = 1, size_type destinationChannelStride = 1);

	bool _isCountArray() const { return m_data.channelCapacity() > 1; }

	//  Internal types -----------------------------------------------

private:
	FValueArray m_data;

	union changeVal_t
	{
		struct  
		{
			uint32_t count      : 31;
			uint32_t hasChanged :  1;
		};

		uint32_t all;
	};

	union change_t
	{
		changeVal_t val;
		changeVal_t* ptr;
	};

	changeVal_t* _changePtr() {
		return _isCountArray() ? m_changeCount.ptr : &m_changeCount.val;
	}

	const changeVal_t* _changePtr() const {
		return _isCountArray() ? m_changeCount.ptr : &m_changeCount.val;
	}

	//  Internal data members ----------------------------------------

	change_t m_changeCount;
};

// Constructors and destructor -------------------------------------------------

inline FDataArray::FDataArray()
{
	_allocate(0);
}

inline FDataArray::FDataArray(const FDataArray& other)
: m_data(other.m_data)
{
	_copy(&other);
}

inline FDataArray::FDataArray(FValueType type, size_type channels, size_type dimensions)
: m_data(type, channels, dimensions)
{
	_allocate(channels);
}

template <typename T>
inline FDataArray::FDataArray(const T& val)
: m_data(val)
{
	_allocate(1);
}

template <typename T>
inline FDataArray::FDataArray(T* pVal, size_type channels,
	size_type dimensions, bool reference)
: m_data(pVal, channels, dimensions, reference)
{
	_allocate(channels);
}

// Data access -----------------------------------------------------------------

template <typename T>
inline const T* FDataArray::ptr() const
{
	return m_data.ptr<T>();
}

template <typename T>
inline T* FDataArray::ptr()
{
	return m_data.ptr<T>();
}

template <typename T>
inline const T* FDataArray::ptr(size_type channel, size_type dimension) const
{
	return m_data.ptr<T>(channel, dimension);
}

template <typename T>
inline T* FDataArray::ptr(size_type channel, size_type dimension)
{
	return m_data.ptr<T>(channel, dimension);
}

template <typename T>
inline const T& FDataArray::as() const
{
	return m_data.as<T>();
}

template <typename T>
inline T& FDataArray::as()
{
	return m_data.as<T>();
}

template <typename T>
inline const T& FDataArray::as(size_type channel, size_type dimension) const
{
	return m_data.as<T>(channel, dimension);
}

template <typename T>
inline T& FDataArray::as(size_type channel, size_type dimension)
{
	return m_data.as<T>(channel, dimension);
}

template <typename T>
inline T FDataArray::to() const
{
	return m_data.to<T>();
}

template <typename T>
inline T FDataArray::to(size_type channel, size_type dimension) const
{
	return m_data.to<T>(channel, dimension);
}

template <typename T>
inline void FDataArray::set(const T& val)
{
	m_data.set<T>(val);
}

template <typename T>
inline void FDataArray::set(size_type channel, size_type dimension, const T& val)
{
	m_data.set<T>(channel, dimension, val);
}

template <typename T>
inline bool FDataArray::is() const
{
	return m_data.is<T>();
}

// Public commands -------------------------------------------------------------

inline void FDataArray::fire(size_type channel, uint32_t count)
{
	_changePtr()[channel % channelCount()].count += count;
}

inline void FDataArray::fire(uint32_t count)
{
	changeVal_t* pChangePtr = _changePtr();
	for (size_type c = 0, n = channelCount(); c < n; ++c)
			pChangePtr[c].count += count;
}

inline void FDataArray::setChanged()
{
	m_data.setChanged();
}

inline void FDataArray::setChanged(size_type channel)
{
	m_data.setChanged();
	_changePtr()[channel % channelCount()].hasChanged = 1;
}

inline void FDataArray::setAllChanged()
{
	m_data.setChanged();

	changeVal_t* pChangePtr = _changePtr();
	for (size_type c = 0, n = channelCount(); c < n; ++c)
		pChangePtr[c].hasChanged = 1;
}

inline void FDataArray::clearChanged()
{
	m_data.clearChanged();

	changeVal_t* pChangePtr = _changePtr();
	for (size_type c = 0, n = channelCount(); c < n; ++c)
		pChangePtr[c].all = 0;
}

inline void FDataArray::convertFrom(const FDataArray& source)
{
	m_data.convertFrom(source.m_data);
	_copyFrom(&source, 0, 0, channelCount());
}

inline void FDataArray::convertFrom(const FDataArray& source,
	size_type sourceDimensionIndex,
	size_type destinationDimensionIndex)
{
	m_data.convertFrom(source.m_data,
		sourceDimensionIndex, destinationDimensionIndex);
	_copyFrom(&source, 0, 0, channelCount());
}

inline void FDataArray::convertFrom(const FDataArray& source,
	size_type sourceChannelIndex,
	size_type destinationChannelIndex,
	size_type sourceDimensionIndex,
	size_type destinationDimensionIndex)
{
	m_data.convertFrom(source.m_data,
		sourceChannelIndex, destinationChannelIndex,
		sourceDimensionIndex, destinationDimensionIndex);
	_copyFrom(&source, sourceChannelIndex, destinationChannelIndex, 1, 1, 1);	
}

inline void FDataArray::convertFrom(const FDataArray& source,
	size_type sourceChannelStart,
	size_type destinationChannelStart,
	size_type channelCount,
	size_type sourceChannelStride,
	size_type destinationChannelStride,
	size_type sourceDimensionStart,
	size_type destinationDimensionStart,
	size_type dimensionCount)
{
	m_data.convertFrom(source.m_data,
		sourceChannelStart, destinationChannelStart, channelCount,
		sourceChannelStride, destinationChannelStride,
		sourceDimensionStart, destinationDimensionStart, dimensionCount);
	_copyFrom(&source, sourceChannelStart, destinationChannelStart,
		channelCount, sourceChannelStride, destinationChannelStride);
}

inline void FDataArray::convertFromValueArray(const FValueArray& source)
{
	m_data.convertFrom(source);
	setAllChanged();
}

inline void FDataArray::convertFromValueArray(const FValueArray& source,
	size_type sourceDimensionIndex, size_type destinationDimensionIndex)
{
	m_data.convertFrom(source,
		sourceDimensionIndex, destinationDimensionIndex);
	setAllChanged();
}

inline void FDataArray::convertFromValueArray(const FValueArray& source,
	size_type sourceChannelIndex, size_type destinationChannelIndex,
	size_type sourceDimensionIndex, size_type destinationDimensionIndex)
{
	m_data.convertFrom(source,
		sourceChannelIndex, destinationChannelIndex,
		sourceDimensionIndex, destinationDimensionIndex);
	setChanged(destinationChannelIndex);
}

inline void FDataArray::convertFromValueArray(const FValueArray& source,
	size_type sourceChannelStart,
	size_type destinationChannelStart,
	size_type channelCount,
	size_type sourceChannelStride,
	size_type destinationChannelStride,
	size_type sourceDimensionStart,
	size_type destinationDimensionStart,
	size_type dimensionCount)
{
	m_data.convertFrom(source,
		sourceChannelStart, destinationChannelStart, channelCount,
		sourceChannelStride, destinationChannelStride,
		sourceDimensionStart, destinationDimensionStart, dimensionCount);

	for (size_type c = 0; c < channelCount; c += destinationChannelStride)
		setChanged(destinationChannelStart + c);
}


inline void FDataArray::setDimensionCount(size_type dimensionCount)
{
	m_data.setDimensionCount(dimensionCount);
}

inline void FDataArray::setDimensionCapacity(size_type dimensionCapacity)
{
	m_data.setDimensionCapacity(dimensionCapacity);
}

inline void FDataArray::setChannelCount(
	size_type channelCount, bool preserveData)
{
	if (channelCount > m_data.channelCount())
		_reallocate(channelCount, preserveData);

	m_data.setChannelCount(channelCount, preserveData);
}

inline void FDataArray::setChannelCapacity(
	size_type channelCapacity, bool preserveData)
{
	_reallocate(channelCapacity, preserveData);
	m_data.setChannelCapacity(channelCapacity, preserveData);
}

// Public queries --------------------------------------------------------------

inline bool FDataArray::hasChanged(size_type channel) const
{
	return _changePtr()[channel % m_data.channelCount()].hasChanged;
}

inline uint32_t FDataArray::fireCount() const
{
	if (_isCountArray())
	{
		uint32_t result = m_changeCount.ptr[0].count;
		for (size_type c = 1, n = m_data.channelCount(); c < n; ++c)
			result += m_changeCount.ptr[c].count;
		return result;
	}

	return m_changeCount.val.count;
}

inline uint32_t FDataArray::fireCount(size_type channel) const
{
	return _changePtr()[channel % m_data.channelCount()].count;
}

inline bool FDataArray::canConvertFrom(const FDataArray& source) const
{
	return m_data.canConvertFrom(source.m_data);
}

inline bool FDataArray::canConvertFrom(const FValueArray& source) const
{
	return m_data.canConvertFrom(source);
}

// Related non-member functions ------------------------------------------------

inline FArchive& operator<<(FArchive& ar, const FDataArray& da)
{
	const_cast<FDataArray&>(da).serialize(ar);
	return ar;
}

inline FArchive& operator>>(FArchive& ar, FDataArray& da)
{
	da.serialize(ar);
	return ar;
}

#ifdef FLOW_DEBUG
inline std::wostream& operator<<(std::wostream& stream, const FDataArray& da)
{
	da.dump(stream);
	return stream;
}
#endif

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_DATAARRAY_H