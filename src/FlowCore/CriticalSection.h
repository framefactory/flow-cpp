// -----------------------------------------------------------------------------
//  File        CriticalSection.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_CRITICALSECTION_H
#define FLOWCORE_CRITICALSECTION_H

#include "FlowCore/Library.h"

#if FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS
#  include "FlowCore/Windows.h"
#else
#  include <QMutex>
#endif


// -----------------------------------------------------------------------------
//  Class FCriticalSection
// -----------------------------------------------------------------------------

class FCriticalSection
{
	F_DISABLE_COPY(FCriticalSection);

#if FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS

public:
	FCriticalSection() { InitializeCriticalSection(&m_critSect); }
	~FCriticalSection() { DeleteCriticalSection(&m_critSect); }

	void lock() { EnterCriticalSection(&m_critSect); }
	bool tryLock() { return TryEnterCriticalSection(&m_critSect); }
	void unlock() { LeaveCriticalSection(&m_critSect); }

private:
	CRITICAL_SECTION m_critSect;

#else

public:
	void lock() { m_mutex.lock(); }
	bool tryLock() { return m_mutex.tryLock(); }
	void unlock() { m_mutex.unlock(); }

private:
	QMutex m_mutex;

#endif
};

// -----------------------------------------------------------------------------
//  Class FSectionLock
// -----------------------------------------------------------------------------

/// The section lock automatically protects a block of code. The constructor
/// locks the given FCriticalSection. As soon as the object goes out of scope
/// the section is unlocked.
class FSectionLock
{
	//  Constructors and destructor ----------------------------------

public:
	FSectionLock(FCriticalSection* pCriticalSection, bool initialLock = true)
		: m_pCriticalSection(pCriticalSection), m_isLocked(initialLock)
	{
		if (m_isLocked)
			m_pCriticalSection->lock();
	}

	~FSectionLock()
	{
		if (m_isLocked)
			m_pCriticalSection->unlock();
	}

	//  Public commands ----------------------------------------------

public:
	/// Acquires a lock for the critical section.
	void lock()
	{
		if (!m_isLocked)
		{
			m_pCriticalSection->lock();
			m_isLocked = true;
		}
	}
	/// Tries to lock the critical section. Returns immediately if no lock can be obtained.
	bool tryLock()
	{
		if (!m_isLocked) {
			m_isLocked = m_pCriticalSection->tryLock();
		}

		return m_isLocked;
	}
	/// Unlocks the critical section.
	void unlock()
	{
		if (m_isLocked)	{
			m_pCriticalSection->unlock();
			m_isLocked = false;
		}
	}

	//  Internal data members ----------------------------------------

private:
	FCriticalSection* m_pCriticalSection;
	bool m_isLocked;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_CRITICALSECTION_H