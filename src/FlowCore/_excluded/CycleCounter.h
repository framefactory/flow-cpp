// -----------------------------------------------------------------------------
//  File        CycleCounter.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/06 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_CYCLECOUNTER_H
#define FLOWCORE_CYCLECOUNTER_H

#include "FlowCore/Library.h"


// -----------------------------------------------------------------------------
//  RDTSC Counter
// -----------------------------------------------------------------------------

#if (FLOW_COMPILER & FLOW_COMPILER_VC)

#if (FLOW_ARCH & FLOW_ARCH_64)

#include <intrin.h>
#define F_RDTSC(cnt) cnt = __rdtsc();
#else // 32bit
#define F_RDTSC(cnt)   \
	__asm { rdtsc \
			mov (cnt).uint32.lo, eax \
			mov (cnt).uint32.hi, edx }
#endif

#elif (FLOW_COMPILER && FLOW_COMPILER_GCC)

#define F_RDTSC(tsc) __asm__ __volatile__ ("mov %0=ar.itc" : "=r" ((tsc).int64))

#elif (FLOW_COMPILER && FLOW_COMPILER_INTEL)

#define F_RDTSC(tsc) (tsc).int64=__getReg(3116)

#endif

// -----------------------------------------------------------------------------
//  Class FCycleCounter
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FCycleCounter
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FCycleCounter();
	/// Virtual destructor.
	virtual ~FCycleCounter();

	//  Public commands ----------------------------------------------

public:
	void start();
	void stop();

	//  Public queries -----------------------------------------------

	/// Returns the number of cycles from the last measurement.
	double cycles() const;
	/// Returns the number of cycles per run.
	double cyclesPerRun(uint32_t numRuns) const;

	//  Internal data members ----------------------------------------

private:
	union largeInt_t
	{
		uint64_t uint64;
		struct { uint32_t lo, hi; } uint32;
	};

	largeInt_t m_cycleStart;
	largeInt_t m_cycleStop;
	int64_t m_cycles;
};

// Inline members --------------------------------------------------------------

inline void FCycleCounter::start()
{
	F_RDTSC(m_cycleStart.uint64);
}

inline void FCycleCounter::stop()
{
	F_RDTSC(m_cycleStop.uint64);
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_CYCLECOUNTER_H