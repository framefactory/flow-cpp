// -----------------------------------------------------------------------------
//  File        ValueArray.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/15 $
// -----------------------------------------------------------------------------

#include "FlowCore/ValueArray.h"
#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FValueArray
// -----------------------------------------------------------------------------

// Public commands -------------------------------------------------------------

void FValueArray::setDimensionCount(size_type newDimensionCount)
{
	F_ASSERT(!m_isReference);

	size_type newSize = newDimensionCount * m_channelCount;
	size_type capacity = m_dimensionCapacity * m_channelCapacity;

	if (newSize > capacity)
		_reallocate(m_channelCapacity, newDimensionCount, false);

	m_dimensionCount = newDimensionCount;
}

void FValueArray::setDimensionCapacity(size_type newDimensionCapacity)
{
	F_ASSERT(!m_isReference);

	_reallocate(m_channelCapacity, newDimensionCapacity, false);
}

void FValueArray::setChannelCount(size_type newChannelCount,
	bool preserveData /* = false */)
{
	F_ASSERT(!m_isReference);

	size_type newSize = m_dimensionCount * newChannelCount;
	size_type capacity = m_dimensionCapacity * m_channelCapacity;

	if (newSize > capacity)
		_reallocate(newChannelCount, m_dimensionCapacity, preserveData);

	if (preserveData && newChannelCount > m_channelCount)
		_resize(newChannelCount);

	m_channelCount = newChannelCount;
}

void FValueArray::setChannelCapacity(size_type newChannelCapacity,
	bool preserveData /* = false */)
{
	F_ASSERT(!m_isReference);

	_reallocate(newChannelCapacity, m_dimensionCapacity, preserveData);
}

#define _F_VA_READ_DATA(valueType, rawType) \
	case FValueType::valueType: { rawType* pData = _ptr<rawType>(); \
	for (size_type i = 0; i < size; ++i) ar >> pData[i]; } break;

#define _F_VA_WRITE_DATA(valueType, rawType) \
	case FValueType::valueType: { rawType* const pData = _ptr<rawType>(); \
	for (size_type i = 0; i < size; ++i) ar << pData[i]; } break;

void FValueArray::serialize(FArchive& ar, bool serializeRawData /* = true */)
{
	if (ar.isReading())
	{
		F_ASSERT(m_type == FValueType::Invalid);
		_delete();

		uint8_t type, isReference;
		size_type dimensions, channels;
		ar >> type;
		ar >> isReference;
		ar >> dimensions;
		ar >> channels;

		FValueType valueType((FValueType::enum_type)type);
		_initialize(valueType, channels, dimensions, isReference != 0);

		size_type size = m_dimensionCount * m_channelCount;
		F_ASSERT(size == dimensions * channels);

		switch(m_type)
		{
			_F_VA_READ_DATA(Float,   float    );
			_F_VA_READ_DATA(Double,  double   );
			_F_VA_READ_DATA(Bool,    bool     );
			_F_VA_READ_DATA(Int8,    int8_t   );
			_F_VA_READ_DATA(UInt8,   uint8_t  );
			_F_VA_READ_DATA(Int16,   int16_t  );
			_F_VA_READ_DATA(UInt16,  uint16_t );
			_F_VA_READ_DATA(Int32,   int32_t  );
			_F_VA_READ_DATA(UInt32,  uint32_t );
			_F_VA_READ_DATA(Int64,   int64_t  );
			_F_VA_READ_DATA(UInt64,  uint64_t );
			_F_VA_READ_DATA(String,  QString  );

		case FValueType::Object:
			{
				FObject** pData = _ptr<FObject*>();
				for (size_type i = 0; i < size; ++i)
					pData[i] = NULL;
			}
			break;

		default:
			F_ASSERT(false);
		}
	}
	else // isWriting
	{
		ar << (uint8_t)m_type;
		ar << (uint8_t)m_isReference;
		ar << m_dimensionCount;
		ar << m_channelCount;

		if (m_type == FValueType::Invalid)
			return;

		size_type size = m_dimensionCount * m_channelCount;

		switch(m_type)
		{
			_F_VA_WRITE_DATA(Float,   float    );
			_F_VA_WRITE_DATA(Double,  double   );
			_F_VA_WRITE_DATA(Bool,    bool     );
			_F_VA_WRITE_DATA(Int8,    int8_t   );
			_F_VA_WRITE_DATA(UInt8,   uint8_t  );
			_F_VA_WRITE_DATA(Int16,   int16_t  );
			_F_VA_WRITE_DATA(UInt16,  uint16_t );
			_F_VA_WRITE_DATA(Int32,   int32_t  );
			_F_VA_WRITE_DATA(UInt32,  uint32_t );
			_F_VA_WRITE_DATA(Int64,   int64_t  );
			_F_VA_WRITE_DATA(UInt64,  uint64_t );
			_F_VA_WRITE_DATA(String,  QString  );

		default:
			F_ASSERT(false);
		}
	}
}

// Public queries --------------------------------------------------------------

QByteArray FValueArray::toByteArray() const
{
	return QByteArray(rawPtr(), byteSize());
}

size_t FValueArray::byteSize() const
{
	return size() * type().byteCount();
}

QString FValueArray::typeDescription() const
{
	return QString("%1 [%2c/%3d]")
		.arg(typeName()).arg(channelCount()).arg(dimensionCount());
}

#ifdef FLOW_DEBUG
QString FValueArray::dump() const
{
	QString result;
	QTextStream stream(&result);

	stream << "\n--- FValueArray ---";
	stream << "\n     Type: " << typeDescription();
	stream << ", Capacity: " << size();
	stream << " [" << channelCapacity() << "c/" << dimensionCapacity() << "d]";
	stream << ", isRef: " << m_isReference;

	size_type nd = fMin((size_type)16, dimensionCount());
	size_type nc = fMin((size_type)16, channelCount());

	for (size_type c = 0; c < nc; c++)
	{
		stream << "\n     Val #" << c << ": " << to<QString>(c, 0);
		for (size_type i = 1; i < nd; i++)
			stream << ", " << to<QString>(c, i);
		if (nd < dimensionCount())
			stream << ", ...";
	}
	if (nc < channelCount())
		stream << "\n------ C (...)";

	stream << "\n";
	return result;
}
#endif

// Internal functions ----------------------------------------------------------

void FValueArray::_copy(const FValueArray* pSource)
{
	_initialize(
		(FValueType::enum_type)pSource->m_type, pSource->m_channelCapacity,
		pSource->m_dimensionCapacity, pSource->m_isReference);

	m_dimensionCount = pSource->m_dimensionCount;
	m_channelCount = pSource->m_channelCount;
	m_hasChanged = pSource->m_hasChanged;

	if (!m_isReference && !isEmpty())
	{
		// copy data from other
		_convert(pSource, 0, 0, m_channelCount, 1, 1, 0, 0, m_dimensionCount);
	}
	else {
		// copy only external reference
		m_raw.ptr = pSource->m_raw.ptr;
	}
}

void FValueArray::_initialize(FValueType type,
	size_type elems, size_type dims, bool isReference)
{
	m_raw.val = 0;

	m_channelCapacity = m_channelCount = elems;
	m_dimensionCapacity = m_dimensionCount = dims;

	m_type = type;
	m_isReference = isReference;
	m_hasChanged = 1;

	if (m_type != FValueType::Invalid)
		_allocate();
}

void FValueArray::_allocate()
{
	size_type cap = capacity();
	if (cap == 0)
	{
		m_raw.val = 0;
		m_isArray = false;
		return;
	}

	if (!m_isReference)
	{
		if (cap == size_type(1))
		{
			m_isArray = false;

			if (m_type == FValueType::String) {
				m_raw.ptr = new QString();
			}
		}
		else
		{
			m_isArray = true;

			switch(m_type)
			{
			case FValueType::Float:   m_raw.ptr = new float[cap];    break;
			case FValueType::Double:  m_raw.ptr = new double[cap];   break;
			case FValueType::Bool:    m_raw.ptr = new bool[cap];     break;
			case FValueType::Int8:    m_raw.ptr = new int8_t[cap];   break;
			case FValueType::UInt8:   m_raw.ptr = new uint8_t[cap];  break;
			case FValueType::Int16:   m_raw.ptr = new int16_t[cap];  break;
			case FValueType::UInt16:  m_raw.ptr = new uint16_t[cap]; break;
			case FValueType::Int32:   m_raw.ptr = new int32_t[cap];  break;
			case FValueType::UInt32:  m_raw.ptr = new uint32_t[cap]; break;
			case FValueType::Int64:   m_raw.ptr = new int64_t[cap];  break;
			case FValueType::UInt64:  m_raw.ptr = new uint64_t[cap]; break;
			case FValueType::String:  m_raw.ptr = new QString[cap];  break;
			case FValueType::Object:  m_raw.ptr = new FObject*[cap]; break;
			default: F_ASSERT(false); break;
			}
		}
	}
	else
	{
		m_isArray = true;
	}
}

#define _F_VA_REALLOCATE_COPY(valueType, rawType) \
	case FValueType::valueType: \
	{ rawType* pOld = _ptr<rawType>(); if (newCap == 1) {  \
	rawType val = *pOld; delete[] pOld; m_isArray = false; *_ptr<rawType>() = val; } \
	else { rawType* pNew = new rawType[newCap]; \
	for (size_type i = 0; i < dataSize; ++i) pNew[i] = pOld[i]; \
	if (m_isArray) delete[] pOld; else m_isArray = true; m_raw.ptr = pNew; } } break

void FValueArray::_reallocate(size_type newChannelCapacity,
	size_type newDimensionCapacity, bool preserveData)
{
	F_ASSERT(!m_isReference);

	size_type oldCap = capacity();
	size_type oldSize = size();
	size_type newCap = newChannelCapacity * newDimensionCapacity;

	F_ASSERT((oldCap <= 1) + (m_isArray == true) == 1);

	if (oldCap == newCap)
		return;

	m_channelCapacity = newChannelCapacity;
	m_dimensionCapacity = newDimensionCapacity;

	if (!preserveData || newCap == 0)
	{
		_delete();
		_allocate();
	}
	else
	{
		// copy only values that remain in use
		size_type dataSize = fMin(newCap, fMax(1, oldSize));

		switch(m_type)
		{
			_F_VA_REALLOCATE_COPY(Float,   float    );
			_F_VA_REALLOCATE_COPY(Double,  double   );
			_F_VA_REALLOCATE_COPY(Bool,    bool     );
			_F_VA_REALLOCATE_COPY(Int8,    int8_t   );
			_F_VA_REALLOCATE_COPY(UInt8,   uint8_t  );
			_F_VA_REALLOCATE_COPY(Int16,   int16_t  );
			_F_VA_REALLOCATE_COPY(UInt16,  uint16_t );
			_F_VA_REALLOCATE_COPY(Int32,   int32_t  );
			_F_VA_REALLOCATE_COPY(UInt32,  uint32_t );
			_F_VA_REALLOCATE_COPY(Int64,   int64_t  );
			_F_VA_REALLOCATE_COPY(UInt64,  uint64_t );
			_F_VA_REALLOCATE_COPY(String,  QString  );
			_F_VA_REALLOCATE_COPY(Object,  FObject* );

		default:
			F_ASSERT(false);
		}
	}

	m_channelCount = fMin(m_channelCapacity, m_channelCount);
	m_dimensionCount = fMin(m_dimensionCapacity, m_dimensionCount);
}

#define _F_VA_RESIZE_COPY(valueType, rawType) \
	case FValueType::valueType: { \
	rawType* ptr = (rawType*)m_raw.ptr; \
	for (size_type i = oldSize; i < newSize; ++i) \
	ptr[i] = ptr[i % oldSize]; } break;

void FValueArray::_resize(size_type newChannelCount)
{
	F_ASSERT(newChannelCount > m_channelCount);
	F_ASSERT(!m_isReference);
	F_ASSERT(m_isArray);

	size_type oldSize = fMax(1, size());
	size_type newSize = newChannelCount * dimensionCount();

	switch(m_type)
	{
		_F_VA_RESIZE_COPY(Float,   float    );
		_F_VA_RESIZE_COPY(Double,  double   );
		_F_VA_RESIZE_COPY(Bool,    bool     );
		_F_VA_RESIZE_COPY(Int8,    int8_t   );
		_F_VA_RESIZE_COPY(UInt8,   uint8_t  );
		_F_VA_RESIZE_COPY(Int16,   int16_t  );
		_F_VA_RESIZE_COPY(UInt16,  uint16_t );
		_F_VA_RESIZE_COPY(Int32,   int32_t  );
		_F_VA_RESIZE_COPY(UInt32,  uint32_t );
		_F_VA_RESIZE_COPY(Int64,   int64_t  );
		_F_VA_RESIZE_COPY(UInt64,  uint64_t );
		_F_VA_RESIZE_COPY(String,  QString  );
		_F_VA_RESIZE_COPY(Object,  FObject* );

	default:
		F_ASSERT(false);
	}

	m_channelCount = newChannelCount;
}

void FValueArray::_delete()
{
	if (!m_isReference)
	{
		if (m_isArray)
		{
			switch(m_type)
			{
			case FValueType::Invalid: break;
			case FValueType::Float:	  delete[] static_cast<float*    >(m_raw.ptr); break;
			case FValueType::Double:  delete[] static_cast<double*   >(m_raw.ptr); break;
			case FValueType::Bool:    delete[] static_cast<bool*     >(m_raw.ptr); break;
			case FValueType::Int8:    delete[] static_cast<int8_t*   >(m_raw.ptr); break;
			case FValueType::UInt8:   delete[] static_cast<uint8_t*  >(m_raw.ptr); break;
			case FValueType::Int16:   delete[] static_cast<int16_t*  >(m_raw.ptr); break;
			case FValueType::UInt16:  delete[] static_cast<uint16_t* >(m_raw.ptr); break;
			case FValueType::Int32:   delete[] static_cast<int32_t*  >(m_raw.ptr); break;
			case FValueType::UInt32:  delete[] static_cast<uint32_t* >(m_raw.ptr); break;
			case FValueType::Int64:   delete[] static_cast<int64_t*  >(m_raw.ptr); break;
			case FValueType::UInt64:  delete[] static_cast<uint64_t* >(m_raw.ptr); break;
			case FValueType::String:  delete[] static_cast<QString*  >(m_raw.ptr); break;
			case FValueType::Object:  delete[] static_cast<FObject** >(m_raw.ptr); break;
			default: F_ASSERT(false); break;
			}
		}
		else if (m_type == FValueType::String) {
			delete static_cast<QString*>(m_raw.ptr);
		}
	}
}

#define _F_VA_CONVERT_FROM(srcVT, srcRT, dstVT, dstRT) \
	case FValueType::srcVT: { \
	srcRT const* pSrc = pSource->_ptr<srcRT>(); \
	for (size_type c = 0; c < channelCount; ++c) { \
	srcRT const* pSrcLine = pSrc + (srcOffset + c * srcStride) % srcSize; \
	dstRT* pDstLine = pDst + (dstOffset + c * dstStride) % dstSize; \
	for (size_type i = 0; i < dimensionCount; ++i) pDstLine[i] = auto_convert<dstRT, srcRT>(pSrcLine[i]); \
	} } break;

#define _F_VA_CONVERT_TO(dstVT, dstRT) \
	case FValueType::dstVT: { \
	dstRT* pDst = pDestination->_ptr<dstRT>(); \
	switch (pSource->m_type) { \
	_F_VA_CONVERT_FROM(Float,   float,     dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Double,  double,    dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Bool,    bool,      dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Int8,    int8_t,    dstVT, dstRT) \
	_F_VA_CONVERT_FROM(UInt8,   uint8_t,   dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Int16,   int16_t,   dstVT, dstRT) \
	_F_VA_CONVERT_FROM(UInt16,  uint16_t,  dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Int32,   int32_t,   dstVT, dstRT) \
	_F_VA_CONVERT_FROM(UInt32,  uint32_t,  dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Int64,   int64_t,   dstVT, dstRT) \
	_F_VA_CONVERT_FROM(UInt64,  uint64_t,  dstVT, dstRT) \
	_F_VA_CONVERT_FROM(String,  QString,   dstVT, dstRT) \
	_F_VA_CONVERT_FROM(Object,  FObject*,  dstVT, dstRT) \
	default: F_ASSERT(false); } } break;

void FValueArray::_convert(
	const FValueArray* pSource,
	size_type sourceChannelStart,
	size_type destinationChannelStart,
	size_type channelCount,
	size_type sourceChannelStride,
	size_type destinationChannelStride,
	size_type sourceDimensionStart,
	size_type destinationDimensionStart,
	size_type dimensionCount)
{
	F_ASSERT(pSource);

	F_ASSERT((!is<FObject*>() && !pSource->is<FObject*>())
		|| (is<FObject*>() && pSource->is<FObject*>())
		|| (is<QString>() && pSource->is<FObject*>()));

	F_ASSERT(sourceDimensionStart + dimensionCount <= pSource->m_dimensionCount);
	F_ASSERT(destinationDimensionStart + dimensionCount <= m_dimensionCount);

	FValueArray* pDestination = this;

	size_type srcSize = pSource->m_channelCount * pSource->m_dimensionCount;
	size_type srcOffset = sourceChannelStart * pSource->m_dimensionCount + sourceDimensionStart;
	size_type srcStride = sourceChannelStride * pSource->m_dimensionCount;

	size_type dstSize = pDestination->m_channelCount * pDestination->m_dimensionCount;
	size_type dstOffset = destinationChannelStart * pDestination->m_dimensionCount + destinationDimensionStart;
	size_type dstStride = destinationChannelStride * pDestination->m_dimensionCount;

	switch (pDestination->m_type)
	{
		_F_VA_CONVERT_TO(Float,   float);
		_F_VA_CONVERT_TO(Double,  double);
		_F_VA_CONVERT_TO(Bool,    bool);
		_F_VA_CONVERT_TO(Int8,    int8_t);
		_F_VA_CONVERT_TO(UInt8,   uint8_t);
		_F_VA_CONVERT_TO(Int16,   int16_t);
		_F_VA_CONVERT_TO(UInt16,  uint16_t);
		_F_VA_CONVERT_TO(Int32,   int32_t);
		_F_VA_CONVERT_TO(UInt32,  uint32_t);
		_F_VA_CONVERT_TO(Int64,   int64_t);
		_F_VA_CONVERT_TO(UInt64,  uint64_t);
		_F_VA_CONVERT_TO(String,  QString);
		_F_VA_CONVERT_TO(Object,  FObject*);

	default:
		F_ASSERT(false);
	}
}

// -----------------------------------------------------------------------------