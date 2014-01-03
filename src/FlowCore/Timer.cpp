// -----------------------------------------------------------------------------
//  File        Timer.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------


#include "FlowCore/Timer.h"

// -----------------------------------------------------------------------------
//  Class FTimer
// -----------------------------------------------------------------------------

FTimer::FTimer(FTime time)
: m_targetTime(time),
  m_isElapsed(false)
{
	m_stopWatch.start();
}

// Public commands -------------------------------------------------------------

void FTimer::start(FTime time)
{
	m_isElapsed = false;
	m_targetTime = time;
	m_stopWatch.reset();
	m_stopWatch.start();
}

void FTimer::pause()
{
	m_stopWatch.stop();
}

void FTimer::resume()
{
	m_stopWatch.start();
}

// Public queries --------------------------------------------------------------

FTime FTimer::remainingTime() const
{
	if (m_isElapsed || !m_stopWatch.isRunning())
		return FTime::zero();

	FTime result = m_targetTime - m_stopWatch.time();
	if (result < FTime::zero())
		m_isElapsed = true;

	return result;
}

bool FTimer::isElapsed() const
{
	if (m_isElapsed)
		return true;
	if (!m_stopWatch.isRunning())
		return false;

	if (m_targetTime - m_stopWatch.time() < FTime::zero())
		m_isElapsed = true;

	return m_isElapsed;
}

// -----------------------------------------------------------------------------
