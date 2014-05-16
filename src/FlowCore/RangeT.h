// -----------------------------------------------------------------------------
//  File        RangeT.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_RANGET_H
#define FLOWCORE_RANGET_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Class FRangeT
// -----------------------------------------------------------------------------

/// Represents an interval between a lower and an upper
/// boundary value. Both boundaries are included.
template <typename T>
class FRangeT
{
	//  Constructors and destructor ----------------------------------

public:
	FRangeT() { }
	FRangeT(T lowerBound, T upperBound)
		: m_lowerBound(lowerBound), m_upperBound(upperBound) { }

	//  Public commands ----------------------------------------------

public:
	void set(T lowerBound, T upperBound);
	void setLowerBound(T lowerBound);
	void setUpperBound(T upperBound);

	/// Moves the upper and lower bound by the given offset.
	void move(T offset);

	/// Unites this with the given range. The result is a range that
	/// covers both input ranges.
	void uniteWith(const FRangeT<T>& other);

	/// Intersects this with the given range. The range is set to
	/// zero if there is no overlap between the ranges.
	void intersectWith(const FRangeT<T>& other);
	
	/// Normalizes the range, i.e. swaps the lower and upper bound
	/// if the lower bound is greater than the upper bound.
	void normalize();

	//  Public queries -----------------------------------------------

	/// Returns the lower bound of the range.
	const T& lowerBound() const { return m_lowerBound; }
	
	/// Returns the upper bound of the range.
	const T& upperBound() const { return m_upperBound; }

	/// Returns the distance between lower and upper bound. The result can
	/// be negative if the range is not normal, i.e. upper bound is smaller
	/// than lower bound.
	const T size() const { return m_upperBound - m_lowerBound; }

	/// Same as size().
	const T length() const { return size(); }

	bool isEmpty() const { return m_lowerBound == m_upperBound; }
	bool isNull() const { return isEmpty(); }

	/// Returns true if the given range is fully included in this one.
	bool includes(const FRangeT<T>& other) const;

	/// Returns true if this and the given range overlap. Also returns
	/// true if the overlap consists of a single point, e.g. if
	/// this range's upper bound equals other range's lower bound.
	bool intersects(const FRangeT<T>& other) const;

	//  Internal data members ----------------------------------------

private:
	T m_lowerBound;
	T m_upperBound;
};

// Members ---------------------------------------------------------------------

template <typename T>
inline void FRangeT<T>::set(T lowerBound, T upperBound)
{
	m_lowerBound = lowerBound;
	m_upperBound = upperBound;
}

template <typename T>
inline void FRangeT<T>::setLowerBound(T lowerBound)
{
	m_lowerBound = lowerBound;
}

template <typename T>
inline void FRangeT<T>::setUpperBound(T upperBound)
{
	m_upperBound = upperBound;
}

template <typename T>
inline void FRangeT<T>::move(T offset)
{
	m_lowerBound += offset;
	m_upperBound += offset;
}

template <typename T>
inline void FRangeT<T>::uniteWith(const FRangeT<T>& other)
{
	m_lowerBound = fMin(m_lowerBound, other.m_lowerBound);
	m_upperBound = fMax(m_upperBound, other.m_upperBound);
}

template <typename T>
inline void FRangeT<T>::intersectWith(const FRangeT<T>& other)
{
	m_lowerBound = fMax(m_lowerBound, other.m_lowerBound);
	m_upperBound = fMin(m_upperBound, other.m_upperBound);

	if (m_lowerBound > m_upperBound)
		m_upperBound = m_lowerBound;
}

template <typename T>
inline void FRangeT<T>::normalize()
{
	if (m_lowerBound > m_upperBound)
		std::swap(m_lowerBound, m_upperBound);
}

template <typename T>
inline bool FRangeT<T>::includes(const FRangeT<T>& other)
{
	return m_lowerBound <= other.m_lowerBound
		&& m_upperBound >= other.m_upperBound;
}

template <typename T>
inline bool FRangeT<T>::intersects(const FRangeT<T>& other)
{
	return m_lowerBound <= other.m_upperBound
		|| m_upperBound >= other.m_lowerBound;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_RANGET_H