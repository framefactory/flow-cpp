// -----------------------------------------------------------------------------
//  File        StopWatch.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_STOPWATCH_H
#define FLOWCORE_STOPWATCH_H

#include "FlowCore/Library.h"
#include "FlowCore/Time.h"

// -----------------------------------------------------------------------------
//  Class FStopWatch
// -----------------------------------------------------------------------------

/// A high precision stop watch providing start, stop and lapse functionality.
/// Based on the FTime time facilities and QueryPerformanceCounter().
class FLOWCORE_EXPORT FStopWatch
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	FStopWatch();

	//  Public commands ----------------------------------------------

	/// Starts or continues the stop watch.
	/// If the stop watch is already running, this function has no effect.
	void start(FTime offset = FTime(0.0));
	/// Stops the watch and returns the accumulated runtime since the last reset.
	FTime stop();
	/// Returns the time since the last start or lapse without stopping the watch.
	FTime lapse();
	/// Resets the stop watch. The next measurement begins at zero.
	void reset();

	//  Public queries -----------------------------------------------

	/// Returns the accumulated runtime since the last reset.
	FTime time() const;
	/// Returns true if the stop watch is running.
	bool isRunning() const { return m_isRunning; }

	//  Internal data members ----------------------------------------

private:
	bool m_isRunning;

	FTime m_timeStarted;
	FTime m_timeLapse;
	FTime m_timeCumulated;
	FTime m_lastLapse;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_STOPWATCH_H

