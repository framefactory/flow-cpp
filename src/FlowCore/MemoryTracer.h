// -----------------------------------------------------------------------------
//  File        MemoryTracer.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MEMORYTRACER_H
#define FLOWCORE_MEMORYTRACER_H

#include "FlowCore/Library.h"

#ifdef FLOW_DEBUG // This class is only visible in debug mode

#include "FlowCore/CriticalSection.h"
#include "FlowCore/Log.h"

#include <QString>
#include <QDebug>
#include <unordered_map>

// -----------------------------------------------------------------------------
//  Class FMemoryTracer
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FMemoryStamp
{
public:
	FMemoryStamp(const char* fileName, int line)
		: FileName(fileName), Line(line) { }

	const char*	FileName;
	int Line;
};

/// Static class tracing memory allocations and frees.
/// All public methods of the class are thread-safe.
class FLOWCORE_EXPORT FMemoryTracer
{
	//  Static methods -----------------------------------------------

public:
	/// Returns a pointer to the only instance of this class.
	/// The instance is created the first time this function is called.
	inline static void create()
	{
		if (!s_pInstance)
			s_pInstance = new FMemoryTracer();
		else
			F_ASSERT(false);
	}

	/// Registers a memory allocation from a pointer.
	inline static void registerNew(void* p, size_t size, const char* typeName,
		                           const char* fileName, int line)
	{
		if (s_pInstance)
			s_pInstance->_registerNew(p, size, typeName, fileName, line);
	}

	/// Registers a memory deletion.
	inline static void registerDelete(void* p)
	{
		if (s_pInstance)
			s_pInstance->_registerDelete(p);
	}

	/// Dumps the current memory state.
	inline static QString dump()
	{
		if (s_pInstance)
			return s_pInstance->_dump();

		return QString();
	}

	/// Enables or disables the memory tracer. It is enabled by default.
	inline static void enable(bool state)
	{
		if (s_pInstance)
			s_pInstance->_enable(state);
	}

	//  Constructors and destructor ----------------------------------

private:
	FMemoryTracer();
	~FMemoryTracer();

	//  Internal functions -------------------------------------------

private:
	void _registerNew(void* p, size_t size, const char* typeName,
		const char* fileName, int line);
	void _registerDelete(void* p);
	QString _dump();
	void _enable(bool state);

	//  Internal data members ----------------------------------------

	static const size_t STR_MAX = 128;

	struct alloc_t
	{
		char		TypeName[STR_MAX];
		char		FileName[STR_MAX];
		int			Line;
		void*		Address;
		size_t		Size;
	};

	QString _dumpElement(alloc_t* pAllocInfo);

	typedef std::unordered_map<void*, alloc_t*> allocMap_t;
	allocMap_t m_allocs;

	size_t m_totalSize;
	size_t m_totalAllocs;
	size_t m_totalFrees;
	bool   m_enabled;
	bool   m_hashInUse;

	FCriticalSection m_hashAccess;

	// the one and only instance of this class.
	static FMemoryTracer* s_pInstance;
};
	
//  Global functions and macros 

template <typename T>
inline T* operator*(const FMemoryStamp& stamp, T* p)
{
	FMemoryTracer::registerNew((void*)p, sizeof(T), typeid(T).name(), stamp.FileName, stamp.Line);
	return p;
}

inline void* operator new(size_t size) { return malloc(size); }
inline void* operator new[](size_t size) { return malloc(size); }
inline void operator delete(void* p) { FMemoryTracer::registerDelete(p); free(p); }
inline void operator delete[](void* p) { FMemoryTracer::registerDelete(p); free(p); }

#define new FMemoryStamp(__FILE__, __LINE__) * new

#define F_MEMORY_TRACER_START { FMemoryTracer::create(); }
#define F_MEMORY_TRACER_REPORT { F_TRACE << FMemoryTracer::dump(); }

#else

#define F_MEMORY_TRACER_START
#define F_MEMORY_TRACER_REPORT

#endif // FLOW_DEBUG

// -----------------------------------------------------------------------------

#endif // FLOWCORE_MEMORYTRACER_H
