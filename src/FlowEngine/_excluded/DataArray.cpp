// -----------------------------------------------------------------------------
//  File        DataArray.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.10 $
// -----------------------------------------------------------------------------

#include "FlowEngine/DataArray.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"


// -----------------------------------------------------------------------------
//  Class FDataArray
// -----------------------------------------------------------------------------

// Public commands -------------------------------------------------------------

void FDataArray::serialize(FArchive& ar, bool serializeRawData /* = true */)
{
	m_data.serialize(ar, serializeRawData);

	if (ar.isReading())
		_allocate(channelCapacity());
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FDataArray::dump(std::wostream& stream) const
{
	stream << L"--- FDataArray ---";
	stream << L"\n     Changed: " << hasChanged()
		<< L", Fire Count: " << fireCount() << std::endl;
	m_data.dump(stream);
}
#endif

// Internal functions ----------------------------------------------------------

void FDataArray::_copy(const FDataArray* pSource)
{
	size_type capacity = pSource->channelCapacity();

	if (capacity <= 1)
		m_changeCount.val.all = pSource->m_changeCount.val.all;
	else
	{
		m_changeCount.ptr = new changeVal_t[capacity];
		for (size_t i = 0; i < capacity; ++i)
			m_changeCount.ptr[i].all = pSource->m_changeCount.ptr[i].all;
	}
}

void FDataArray::_allocate(size_t capacity)
{
	if (capacity <= 1)
	{
		m_changeCount.val.count = 0;
		m_changeCount.val.hasChanged = 1;
	}
	else
	{
		m_changeCount.ptr = new changeVal_t[capacity];
		for (size_t i = 0; i < capacity; i++)
		{
			m_changeCount.ptr[i].count = 0;
			m_changeCount.ptr[i].hasChanged = 1;
		}
	}
}

void FDataArray::_delete()
{
	if (_isCountArray())
		delete[] m_changeCount.ptr;
}

void FDataArray::_reallocate(size_type newChannelCapacity, bool preserveData)
{
	if (newChannelCapacity == 0)
	{
		_delete();
		m_changeCount.ptr = NULL;
	}
	else if (!preserveData)
	{
		_delete();
		_allocate(newChannelCapacity);
	}
	else
	{
		if (newChannelCapacity == 1)
		{
			if (_isCountArray())
			{
				uint32_t val = m_changeCount.ptr[0].all;
				delete[] m_changeCount.ptr;
				m_changeCount.val.all = val;
			}
		}
		else
		{
			changeVal_t* pNew = new changeVal_t[newChannelCapacity];

			if (_isCountArray())
			{
				size_type copySize = fMin(newChannelCapacity, m_data.channelCount());
				for (size_type i = 0; i < copySize; ++i)
					pNew[i].all = m_changeCount.ptr[i].all;
				delete[] m_changeCount.ptr;
			}
			else
			{
				pNew[0] = m_changeCount.val;
			}

			m_changeCount.ptr = pNew;
		}
	}
}

void FDataArray::_resize(size_type newChannelCount)
{
	for (size_type i = m_data.channelCount(); i < newChannelCount; i++)
	{
		m_changeCount.ptr[i].count = 0;
		m_changeCount.ptr[i].hasChanged = 1;
	}
}

void FDataArray::_copyFrom(const FDataArray* pSource,
						   size_type sourceChannelStart,
						   size_type destinationChannelStart,
						   size_type channelCount,
						   size_type sourceChannelStride /* = 1 */,
						   size_type destinationChannelStride /* = 1 */)
{
	const changeVal_t* pSrc = pSource->_changePtr() + sourceChannelStart;
	changeVal_t* pDst = _changePtr() + destinationChannelStart;

	for (size_type i = 0; i < channelCount; ++i)
	{
		pDst[i * destinationChannelStride].count = pSrc[i * sourceChannelStride].count;
		pDst[i * destinationChannelStride].hasChanged = 1;
	}

	m_data.setChanged();
}

// -----------------------------------------------------------------------------