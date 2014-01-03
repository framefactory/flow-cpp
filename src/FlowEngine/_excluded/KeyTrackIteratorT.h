// -----------------------------------------------------------------------------
//  File        KeyTrackIteratorT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_KEYTRACKITERATORT_H
#define FLOWENGINE_KEYTRACKITERATORT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/TimeKeyT.h"

#include <map>

// -----------------------------------------------------------------------------
//  Class FKeyTrackIteratorT
// -----------------------------------------------------------------------------

template <typename TimeT>
class FKeyTrackIteratorT
{
	//  Public types -------------------------------------------------

public:
	typedef typename FTimeKeyT<TimeT> key_type;
	typedef TimeT time_type;
	typedef std::map<time_type, key_type*> key_map_type;
	typedef typename key_map_type::iterator key_iterator;
	typedef typename key_map_type::const_iterator key_const_iterator;

	//  Constructors and destructor ----------------------------------

	/// Default Constructor.
	FKeyTrackIteratorT(key_map_type* pKeys);
	/// Virtual destructor.
	~FKeyTrackIteratorT();

	//  Public commands ----------------------------------------------

	/// Resets the state of the iterator. Must be called whenever
	/// keys have been inserted or removed from the track.
	virtual void reset();

	/// Sets the current evaluation time.
	/// Returns true if the key interval has been changed.
	/// Must not be called if the track is empty.
	virtual bool setTime(const time_type& time);

	/// Moves forward or backward to the given evaluation time.
	/// Returns the number of keys that have been passed.
	/// Must not be called if the track is empty.
	virtual int32_t advanceTime(const time_type& time);

	//  Public queries -----------------------------------------------

	/// Returns the key at the left side of the current interval.
	/// Must not be called at the begin of the track.
	key_type* leftKey() const { return m_leftKeyIt->second; }
	/// Returns the key at the right side of the current interval.
	/// Must not be called at the end of the track.
	key_type* rightKey() const { return m_rightKeyIt->second; }

	/// Returns the time of the key at the left side of the current interval.
	/// Must not be called at the begin of the track.
	time_type leftKeyTime() const { return m_leftKeyIt->first; }
	/// Returns the time of the key at the right side of the current interval.
	/// Must not be called at the end of the track.
	time_type rightKeyTime() const { return m_rightKeyIt->first; }

	/// Returns the iterator of the key at the left side of the current interval.
	const key_iterator& leftKeyIterator() const { return m_leftKeyIt; }
	/// Returns the iterator of the key at the right side of the current interval.
	const key_iterator& rightKeyIterator() const { return m_rightKeyIt; }

	/// Returns true if the iterator points to the interval before the first key.
	bool atBegin() const { return m_rightKeyIt == m_pKeys->begin(); }
	/// Returns true if the iterator points to the interval past the last key.
	bool atEnd() const { return m_rightKeyIt == m_pKeys->end(); }

	/// Returns true if the track contains no keys.
	bool empty() const { return m_pKeys->empty(); }

	//  Internal data members ----------------------------------------

protected:
	key_map_type* m_pKeys;
	key_iterator m_leftKeyIt;
	key_iterator m_rightKeyIt;
	time_type m_evalTime;
};

// Constructors and destructor -------------------------------------------------

template <typename TimeT>
inline FKeyTrackIteratorT<TimeT>::FKeyTrackIteratorT(key_map_type* pKeys)
	: m_pKeys(pKeys),
	  m_leftKeyIt(pKeys->begin()),
	  m_rightKeyIt(pKeys->begin())
{
}

template <typename TimeT>
FKeyTrackIteratorT<TimeT>::~FKeyTrackIteratorT()
{
}

// Public commands -------------------------------------------------------------

template <typename TimeT>
void FKeyTrackIteratorT<TimeT>::reset()
{
	m_leftKeyIt = m_pKeys->begin();
	m_rightKeyIt = m_pKeys->begin();
}

template <typename TimeT>
bool FKeyTrackIteratorT<TimeT>::setTime(const time_type& time)
{
	F_ASSERT(!m_pKeys->empty());

	// if the time is unchanged, do nothing
	if (time == m_evalTime)
		return false;

	m_evalTime = time;

	key_iterator it = m_pKeys->upper_bound(time);
	if (it == m_rightKeyIt && m_leftKeyIt != m_rightKeyIt)
		return false;

	m_rightKeyIt = it;

	if (m_rightKeyIt == m_pKeys->begin())
	{
		m_leftKeyIt = m_pKeys->end();
	}
	else
	{
		m_leftKeyIt = m_rightKeyIt;
		--m_leftKeyIt;
	}

	return true;
}

template <typename TimeT>
int32_t FKeyTrackIteratorT<TimeT>::advanceTime(const time_type& time)
{
	F_ASSERT(!m_pKeys->empty());

	// if the time is unchanged, do nothing
	if (time == m_evalTime)
		return 0;

	// if we have no valid interval yet
	if (m_leftKeyIt == m_rightKeyIt)
	{
		setTime(time);
		return -1;
	}

	int32_t count = 0;

	if (time > m_evalTime)
	{
		// move forward until we are past the end or found the right interval
		while (m_rightKeyIt != m_pKeys->end() && time > rightKeyTime())
		{
			m_leftKeyIt = m_rightKeyIt;
			++m_rightKeyIt;
			count++;
		}
	}
	else
	{
		// move backward until we are past the begin or found the right interval
		while (m_leftKeyIt != m_pKeys->begin() && time < leftKeyTime())
		{
			m_rightKeyIt = m_leftKeyIt;
			--m_leftKeyIt;
			count++;
		}

		if (time < leftKeyTime())
		{
			m_rightKeyIt = m_leftKeyIt;
			m_leftKeyIt = m_pKeys->end();
			count++;
		}
	}

	m_evalTime = time;
	return count;
}
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_KEYTRACKITERATORT_H