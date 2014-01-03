// -----------------------------------------------------------------------------
//  File        StopWatch.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------


#include "FlowCore/StopWatch.h"
#include "FlowCore/Log.h"

// -----------------------------------------------------------------------------
// Performance counter query, implementation for Windows / MSVC
// -----------------------------------------------------------------------------

#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)

#define F_USE_PERFORMANCE_COUNTER
#pragma comment(lib, "Winmm.lib")
#include <Windows.h>


/// Returns the performance counter frequency (the number of ticks per second).
__inline uint64_t fPerformanceFrequency()
{
	uint64_t freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	return freq;
}

#ifdef F_USE_PERFORMANCE_COUNTER

/// Returns the number of seconds elapsed since the computer was started
/// using the QueryPerformanceCounter() function.
__inline double fElapsedSeconds()
{
	static double freq = (double)fPerformanceFrequency();
	static uint64_t lastTicks = 0;
	static double cumulatedSeconds = 0.0;

	uint64_t ticks;
	QueryPerformanceCounter((LARGE_INTEGER*)&ticks);

	return (double)ticks / freq;
}
#else // F_USE_PERFORMANCE_COUNTER

/// Returns the number of CPU ticks since startup.
__inline quint64 GetCpuTicks()
{
	struct { quint32 low, high; } counter;

	__asm {
		RDTSC
			mov counter.low, EAX
			mov counter.high, EDX
	}

	return *(quint64*)(&counter);
}

/// Returns the number of seconds elapsed since the computer was started
/// using the RDTSC assembly instruction.
__inline double fElapsedSeconds()
{
	static DWORD startMsec = timeGetTime();
	static DWORD lastMsec = 0;

	static quint64 startTicks = GetCpuTicks();
	static double scaleFactor = 1.0;

	static bool firstMeasure = true;

	if (firstMeasure)
		Sleep(100);

	DWORD currentMsec = timeGetTime() - startMsec;
	DWORD deltaMsec = lastMsec - currentMsec;
	lastMsec = currentMsec;

	quint64 currentTicks = GetCpuTicks() - startTicks;

	if (deltaMsec > 1000)
	{
		if (firstMeasure) {
			scaleFactor = (double)currentTicks / ((double)currentMsec / 1000.0);
			firstMeasure = false; }
		else
			scaleFactor = scaleFactor * 0.9999
			+ ((double)currentTicks / ((double)currentMsec / 1000.0)) * 0.0001;
	}

	return (double)currentTicks / scaleFactor;
}
#endif // F_USE_PERFORMANCE_COUNTER
#else // (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)

// TODO: Implement performance counter query for Linux and OSX
/// Returns the performance counter frequency (the number of ticks per second).
__inline double fElapsedSeconds()
{
	// TODO: Implement
	return 0.0;
}

#endif // (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)

// -----------------------------------------------------------------------------
//  Class FStopWatch
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FStopWatch::FStopWatch()
: m_isRunning(false),
  m_timeStarted(0.0),
  m_timeLapse(0.0),
  m_timeCumulated(0.0),
  m_lastLapse(0.0)
{
}

// Public commands -------------------------------------------------------------

void FStopWatch::start(FTime offset)
{
	if (!m_isRunning)
	{
		if (offset > FTime(0.0))
			m_timeCumulated = FTime(0.0);

		m_isRunning = true;
		m_timeLapse = FTime(fElapsedSeconds());
		m_timeStarted = m_timeLapse - offset;
	}
}

FTime FStopWatch::stop()
{
	if (m_isRunning)
	{
		FTime currentTime = FTime(fElapsedSeconds());
		m_timeCumulated += (currentTime - m_timeStarted);
		m_lastLapse = currentTime - m_timeLapse;
		m_isRunning = false;
	}

	return m_timeCumulated;
}

FTime FStopWatch::lapse()
{
	if (m_isRunning)
	{
		FTime currentTime = FTime(fElapsedSeconds());
		m_lastLapse = currentTime - m_timeLapse;
		m_timeLapse = currentTime;
	}

	return m_lastLapse;
}

void FStopWatch::reset()
{
	m_isRunning = false;
	m_timeCumulated = m_timeLapse = m_timeStarted = m_lastLapse = FTime(0.0);
}

// Public queries --------------------------------------------------------------

FTime FStopWatch::time() const
{
	if (m_isRunning)
		return FTime(fElapsedSeconds()) - m_timeStarted + m_timeCumulated;
	else
		return m_timeCumulated;
}

// -----------------------------------------------------------------------------