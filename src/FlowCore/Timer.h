// -----------------------------------------------------------------------------
//  File        Timer.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TIMER_H
#define FLOWCORE_TIMER_H

#include "FlowCore/Library.h"
#include "FlowCore/StopWatch.h"
#include "FlowCore/Time.h"

// -----------------------------------------------------------------------------
//  Class FTimer
// -----------------------------------------------------------------------------

/// High-performance timer based on FTime and FStopWatch. After starting the
/// timer, it counts down from the given time to zero. The remaining time can
/// be checked using remainingTime() and isElapsed() returns true once the
/// timer has reached zero.
class FLOWCORE_EXPORT FTimer
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FTimer() : m_isElapsed(false), m_targetTime(0.0) { }
	/// Creates a timer counting from the given time.
	FTimer(FTime time);

	//  Public commands ----------------------------------------------

public:
	/// Starts the timer, counting down the given time.
	void start(FTime time);
	/// Pauses the timer.
	void pause();
	/// Resumes the timer.
	void resume();

	//  Public queries -----------------------------------------------

	/// Returns the remaining time of the timer.
	FTime remainingTime() const;
	/// Returns true if the time is elapsed, i.e. the remaining time reached zero.
	bool isElapsed() const;

	//  Internal data members ----------------------------------------

private:
	FStopWatch m_stopWatch;
	FTime m_targetTime;
	mutable bool m_isElapsed;

};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_TIMER_H
