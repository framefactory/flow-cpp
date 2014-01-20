// -----------------------------------------------------------------------------
//  File        MemoryTracer.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/MemoryTracer.h"
#include "FlowCore/Log.h"

#ifdef FLOW_DEBUG

#include <cstring>

// -----------------------------------------------------------------------------
//  Class FMemoryTracer
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

FMemoryTracer* FMemoryTracer::s_pInstance = NULL;

// Constructors and destructor -------------------------------------------------

FMemoryTracer::FMemoryTracer()
: m_totalSize(0),
  m_totalAllocs(0),
  m_totalFrees(0),
  m_enabled(true),
  m_hashInUse(false)
{
	F_TRACE << "\n***** MEMORY TRACER ACTIVE *****\n";
}

FMemoryTracer::~FMemoryTracer()
{
}

// Internal functions ----------------------------------------------------------

void FMemoryTracer::_registerNew(void* p,
	                             size_t size,
								 const char* typeName,
	                             const char* fileName,
								 int line)
{
	F_ASSERT(p);

	if (!m_enabled)
		return;

	FSectionLock lock(&m_hashAccess);
	if (m_hashInUse)
		return;

	m_hashInUse = true;

	alloc_t* pReport = (alloc_t*)malloc(sizeof(alloc_t));
	pReport->Address = p;
	pReport->Size = size;
#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
	strncpy_s(pReport->TypeName, typeName, STR_MAX - 1);
	strncpy_s(pReport->FileName, fileName, STR_MAX - 1);
#else
	strncpy(pReport->TypeName, typeName, STR_MAX - 1);
	strncpy(pReport->FileName, fileName, STR_MAX - 1);
#endif
	pReport->Line = line;

	// F_TRACE << "NEW\n" << _dumpElement(pReport);
	m_allocs.insert(allocMap_t::value_type(p, pReport));
	m_totalAllocs++;
	m_totalSize += size;

	m_hashInUse = false;
}

void FMemoryTracer::_registerDelete(void* p)
{
	if (!m_enabled)
		return;

	FSectionLock lock(&m_hashAccess);
	if (m_hashInUse)
		return;

	m_hashInUse = true;

	allocMap_t::iterator it = m_allocs.find(p);
	bool found = (it != m_allocs.end() && it->second->Address == p);

	if (found)
	{
		// F_TRACE << "DELETE\n" << _dumpElement(it->second);
		free(it->second);
		m_allocs.erase(it);
		m_totalFrees++;
	}

	m_hashInUse = false;
}

QString FMemoryTracer::_dump()
{
	FSectionLock lock(&m_hashAccess);
	QString message;
	QTextStream stream(&message);

	if (m_allocs.empty())
	{
		stream << "\n***** NO MEMORY LEAKS DETECTED *****\n\n";
		stream << "Total " << m_totalAllocs << " allocations with ";
		stream << m_totalSize << " bytes.\n";
		if (m_totalAllocs != m_totalFrees)
			stream << "Number of allocations (" << m_totalAllocs
			<< ") differs from number of frees (" << m_totalFrees << ")!\n";
		return message;
	}

	stream << "\n***** MEMORY LEAKS DETECTED *****\n\n";
	stream << "Total " << m_totalAllocs << " allocations with ";
	stream << m_totalSize << " bytes.\n";
	stream << "Number of unfreed allocations: " << m_totalAllocs - m_totalFrees << "\n";

	allocMap_t::iterator it;
	for (it = m_allocs.begin(); it != m_allocs.end(); it++)
		stream << _dumpElement(it->second);

	return message;
}

void FMemoryTracer::_enable(bool state)
{
	m_enabled = state;
}

QString FMemoryTracer::_dumpElement(alloc_t* pAllocInfo)
{
	return QString("   Object of type %1\n   Address: 0x%2, Size: %3\n   File: %4, Line: %5\n\n")
		.arg(pAllocInfo->TypeName)
		.arg((size_t)(pAllocInfo->Address), 0, 16)
		.arg(pAllocInfo->Size)
		.arg(pAllocInfo->FileName)
		.arg(pAllocInfo->Line);
}

// -----------------------------------------------------------------------------

#endif // FLOW_DEBUG