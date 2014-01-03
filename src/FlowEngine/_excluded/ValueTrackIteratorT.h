// -----------------------------------------------------------------------------
//  File        ValueTrackIteratorT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_VALUETRACKITERATORT_H
#define FLOWENGINE_VALUETRACKITERATORT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/ValueKeyT.h"
#include "FlowEngine/KeyTrackIteratorT.h"

// -----------------------------------------------------------------------------
//  Class FValueTrackIteratorT
// -----------------------------------------------------------------------------

template <typename TimeT, typename ValueT>
class FValueTrackIteratorT : public FKeyTrackIteratorT<TimeT>
{
	//  Public types -------------------------------------------------

public:
	typedef FValueKeyT<TimeT, ValueT> key_type;
	typedef ValueT value_type;

	//  Constructors and destructor ----------------------------------

	/// Default Constructor.
	FValueTrackIteratorT(key_map_type* m_pKeys);
	/// Virtual destructor.
	~FValueTrackIteratorT();

	//  Public commands ----------------------------------------------

	/// Sets the current evaluation time.
	/// Returns true if the key interval has been changed.
	virtual bool setTime(const time_type& time);

	/// Moves forward or backward to the given evaluation time.
	/// Returns the number of keys that have been passed.
	/// Must not be called if the track is empty.
	virtual int32_t advanceTime(const time_type& time);

	//  Public queries -----------------------------------------------

	/// Returns the value of the track at the current evaluation time.
	virtual value_type evaluate() { return m_evalValue; }

	/// Returns the key at the left side of the current interval.
	/// Must not be called at the begin of the track.
	key_type* leftKey() const;
	/// Returns the key at the right side of the current interval.
	/// Must not be called at the end of the track.
	key_type* rightKey() const;
	/// Returns the value of the key at the left side of the current interval.
	/// Must not be called at the begin of the track.
	value_type leftKeyValue() const { return leftKey()->value(); }
	/// Returns the vale of the key at the left side of the current interval.
	/// Must not be called at the end of the track.
	value_type rightKeyValue() const { return rightKey()->value(); }

	//  Internal data members ----------------------------------------

protected:
	value_type m_evalValue;
};

// Constructors and destructor -------------------------------------------------

template <typename TimeT, typename ValueT>
inline FValueTrackIteratorT<TimeT, ValueT>::FValueTrackIteratorT(
	key_map_type* pKeys)
	: FKeyTrackIteratorT<TimeT>(pKeys)
{
}

template <typename TimeT, typename ValueT>
FValueTrackIteratorT<TimeT, ValueT>::~FValueTrackIteratorT()
{
}

// Public commands -------------------------------------------------------------

template <typename TimeT, typename ValueT>
bool FValueTrackIteratorT<TimeT, ValueT>::setTime(const time_type& time)
{
	bool changed = FKeyTrackIteratorT<TimeT>::setTime(time);

	if (changed)
	{
		if (atBegin())
			m_evalValue = rightKeyValue();
		else
			m_evalValue = leftKeyValue();
	}

	return changed;
}

template <typename TimeT, typename ValueT>
int32_t FValueTrackIteratorT<TimeT, ValueT>::advanceTime(const time_type& time)
{
	int32_t count = FKeyTrackIteratorT<TimeT>::advanceTime(time);

	if (count != 0)
	{
		if (atBegin())
			m_evalValue = rightKeyValue();
		else
			m_evalValue = leftKeyValue();
	}

	return count;
}

// Public queries --------------------------------------------------------------

template <typename TimeT, typename ValueT>
inline typename FValueTrackIteratorT<TimeT, ValueT>::key_type*
	FValueTrackIteratorT<TimeT, ValueT>::leftKey() const
{
	return dynamic_cast<key_type*>(m_leftKeyIt->second);
}

template <typename TimeT, typename ValueT>
inline typename FValueTrackIteratorT<TimeT, ValueT>::key_type*
	FValueTrackIteratorT<TimeT, ValueT>::rightKey() const
{
	return dynamic_cast<key_type*>(m_rightKeyIt->second);
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_VALUETRACKITERATORT_H