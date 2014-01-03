// -----------------------------------------------------------------------------
//  File        CycleCounter.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/06 $
// -----------------------------------------------------------------------------

#include "FlowCore/CycleCounter.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FCycleCounter
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FCycleCounter::FCycleCounter()
{
	m_cycleStart.uint64 = 0;
	m_cycleStop.uint64 = 0;
}

FCycleCounter::~FCycleCounter()
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

double FCycleCounter::cycles() const
{
	return (double)(m_cycleStop.uint64 - m_cycleStart.uint64);
}

double FCycleCounter::cyclesPerRun(uint32_t numRuns) const
{
	return (double)(m_cycleStop.uint64 - m_cycleStart.uint64) / (double)numRuns;
}

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------