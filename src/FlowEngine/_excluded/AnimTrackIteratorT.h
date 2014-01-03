// -----------------------------------------------------------------------------
//  File        AnimTrackIteratorT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_ANIMTRACKITERATORT_H
#define FLOWENGINE_ANIMTRACKITERATORT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/AnimKeyT.h"
#include "FlowEngine/ValueTrackIteratorT.h"

// -----------------------------------------------------------------------------
//  Class FAnimTrackIteratorT
// -----------------------------------------------------------------------------

template <typename TimeT, typename ValueT>
class FAnimTrackIteratorT : public FValueTrackIteratorT<TimeT, ValueT>
{
	//  Public types -------------------------------------------------

public:
	typedef FAnimKeyT<TimeT, ValueT> key_type;

	//  Constructors and destructor ----------------------------------

	/// Default constructor.
	FAnimTrackIteratorT(key_map_type* m_pKeys);
	/// Virtual destructor.
	~FAnimTrackIteratorT();

	//  Public commands ----------------------------------------------

	/// Resets the state of the iterator. Must be called whenever
	/// keys have been inserted or removed from the track.
	virtual void reset();

	/// Sets the current evaluation time.
	/// Returns true if the key interval has been changed.
	virtual bool setTime(const time_type& time);

	/// Moves forward or backward to the given evaluation time.
	/// Returns the number of keys that have been passed.
	/// Must not be called if the track is empty.
	virtual int32_t advanceTime(const time_type& time);

	//  Public queries -----------------------------------------------

	/// Returns the value of the track at the current evaluation time.
	virtual value_type evaluate();

	/// Returns the key at the left side of the current interval.
	/// Must not be called at the begin of the track.
	key_type* leftKey() const;
	/// Returns the key at the right side of the current interval.
	/// Must not be called at the end of the track.
	key_type* rightKey() const;

	//  Internal functions -------------------------------------------

	void _calculateCoefficients();

	//  Internal data members ----------------------------------------

protected:
	value_type m_ct[3];
	value_type m_cv[4];
	value_type m_timeOffset;
	value_type m_timeSpan;
	bool m_hasCoefficients;
	bool m_timeChanged;
};

// Constructors and destructor -------------------------------------------------

template <typename TimeT, typename ValueT>
inline FAnimTrackIteratorT<TimeT, ValueT>::FAnimTrackIteratorT(
	key_map_type* pKeys)
	: FValueTrackIteratorT<TimeT, ValueT>(pKeys),
	  m_hasCoefficients(false),
	  m_timeChanged(true)
{
}

template <typename TimeT, typename ValueT>
FAnimTrackIteratorT<TimeT, ValueT>::~FAnimTrackIteratorT()
{
}

// Public commands -------------------------------------------------------------

template <typename TimeT, typename ValueT>
void FAnimTrackIteratorT<TimeT, ValueT>::reset()
{
	FValueTrackIteratorT<TimeT, ValueT>::reset();

	m_hasCoefficients = false;
	m_timeChanged = true;
}

template <typename TimeT, typename ValueT>
bool FAnimTrackIteratorT<TimeT, ValueT>::setTime(const time_type& time)
{
	if (time != m_evalTime)
		m_timeChanged = true;

	bool changed = FValueTrackIteratorT<TimeT, ValueT>::setTime(time);
	if (changed)
		m_hasCoefficients = false;
	return changed;
}

template <typename TimeT, typename ValueT>
int32_t FAnimTrackIteratorT<TimeT, ValueT>::advanceTime(const time_type& time)
{
	if (time != m_evalTime)
		m_timeChanged = true;

	int32_t count = FValueTrackIteratorT<TimeT, ValueT>::advanceTime(time);
	if (count != 0)
		m_hasCoefficients = false;
	return count;
}

// Public queries --------------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FAnimTrackIteratorT<TimeT, ValueT>::value_type
	FAnimTrackIteratorT<TimeT, ValueT>::evaluate()
{
	if (!m_timeChanged)
		return m_evalValue;

	m_timeChanged = false;

	if (atBegin())
		return rightKey()->value();
	else if (atEnd())
		return leftKey()->value();

	key_type* pLeftKey = leftKey();
	key_type* pRightKey = rightKey();

	F_ASSERT(pLeftKey);
	F_ASSERT(pRightKey);
	F_ASSERT(pLeftKey->time() <= m_evalTime);
	F_ASSERT(m_evalTime < pRightKey->time());

	switch(pLeftKey->interpolationMode())
	{
	case FInterpolationMode::Hold:
		return leftKey()->value();

	case FInterpolationMode::Linear:
		{
			// calculate normalized interpolation factor
			value_type timeOffset = (value_type)pLeftKey->time();
			value_type timeSpan = (value_type)pRightKey->time() - timeOffset;
			value_type t = ((value_type)m_evalTime - timeOffset) / timeSpan;

			// linear interpolation of value between keys
			return pLeftKey->value() * (1.0 - t) + pRightKey->value() * t;
		}

	case FInterpolationMode::Bezier:
		{
			// calculate coefficients of cubic bezier polynomial
			if (!m_hasCoefficients)
				_calculateCoefficients();

			// time interpolation factor
			value_type relTime = ((value_type)m_evalTime - m_timeOffset) / m_timeSpan;
			value_type t = relTime;
			value_type f, df;

			// temp variable initialization
			// time domain cubic polynomial
			value_type ct0 = -relTime;
			value_type ct1 = m_ct[0];
			value_type ct2 = m_ct[1];
			value_type ct3 = m_ct[2];
			// time domain cubic polynomial derivative
			value_type ct22 = ct2 * 2.0;
			value_type ct33 = ct3 * 3.0;

			for (int i = 0; i < 14; ++i)
			{
				// evaluate the polynomial f and its derivative df
				// at t using horner scheme
				f = t * (t * (t * ct3  + ct2 ) + ct1) + ct0;
				df =     t * (t * ct33 + ct22) + ct1;
				t = t - f / df;
			}

			m_evalValue = t * ( t * ( t * m_cv[3] + m_cv[2]) + m_cv[1]) + m_cv[0];
			return m_evalValue;
		}

	default:
		F_ASSERT(false);
		return FValueTrackIteratorT<TimeT, ValueT>::evaluate();
	}
}

template <typename TimeT, typename ValueT>
inline typename FAnimTrackIteratorT<TimeT, ValueT>::key_type*
	FAnimTrackIteratorT<TimeT, ValueT>::leftKey() const
{
	return dynamic_cast<key_type*>(m_leftKeyIt->second);
}

template <typename TimeT, typename ValueT>
inline typename FAnimTrackIteratorT<TimeT, ValueT>::key_type*
	FAnimTrackIteratorT<TimeT, ValueT>::rightKey() const
{
	return dynamic_cast<key_type*>(m_rightKeyIt->second);
}

// Internal functions ----------------------------------------------------------

template <typename TimeT, typename ValueT>
void FAnimTrackIteratorT<TimeT, ValueT>::_calculateCoefficients()
{
	// get left and right key of current interval and ensure they are valid
	key_type* pLeftKey = leftKey();
	key_type* pRightKey = rightKey();

	F_ASSERT(pLeftKey);
	F_ASSERT(pRightKey);

	// calculate coefficients of cubic bezier polynomial in time domain
	value_type t0 = (value_type)pLeftKey->time();
	value_type t1 = (value_type)pLeftKey->rightHandleTime();
	value_type t2 = (value_type)pRightKey->leftHandleTime();
	value_type t3 = (value_type)pRightKey->time();

	m_timeSpan = t3 - t0;
	m_timeOffset = t0;

	value_type tn1 = fMinMax((t1 - t0) / m_timeSpan,  1.0e-4, 1.0 - 1.0e-4);
	value_type tn2 = fMinMax((t2 - t0) / m_timeSpan,  1.0e-4, 1.0 - 1.0e-4);

	m_ct[0] = 3.0 * tn1;
	m_ct[1] = 3.0 * tn2 - 6.0 * tn1;
	m_ct[2] = 3.0 * (tn1 - tn2) + 1.0;

	// calculate coefficients of cubic bezier polynomial in value domain
	value_type v0 = pLeftKey->value();
	value_type v1 = pLeftKey->rightHandleValue();
	value_type v2 = pRightKey->leftHandleValue();
	value_type v3 = pRightKey->value();

	m_cv[0] = v0;
	m_cv[1] = 3.0 * (v1 - v0);
	m_cv[2] = 3.0 * v0 - 6.0 * v1 + 3.0 * v2;
	m_cv[3] = -v0 + 3.0 * (v1 - v2) + v3;

	m_hasCoefficients = true;
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_ANIMTRACKITERATORT_H