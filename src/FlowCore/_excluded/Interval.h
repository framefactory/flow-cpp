// -----------------------------------------------------------------------------
//  File        Interval.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.27 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_INTERVAL_H
#define FLOWCORE_INTERVAL_H

#include "FlowCore/Library.h"
#include "FlowCore/Time.h"

#include <iosfwd>

// -----------------------------------------------------------------------------
//  Class FInterval
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FInterval
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor, creates an uninitialized interval.
	FInterval();
	/// Creates an interval from the given start and end time.
	FInterval(FTime startTime, FTime endTime);

	//  Operators ----------------------------------------------------
	
	/// Adds the given amount of time to this interval.
	FInterval& operator+=(FTime offset);
	/// Subtracts the given amount of time from this interval.
	FInterval& operator-=(FTime offset);

	/// Returns an interval equal to this plus the given offset.
	FInterval operator+(FTime offset) const;
	/// Returns an interval equal to this minus the given offset.
	FInterval operator-(FTime offset) const;

	/// Compares two intervals and returns true if they are equal.
	bool operator==(const FInterval& other) const;
	/// Compares two intervals and returns true if they are different.
	bool operator!=(const FInterval& other) const;

	//  Public commands ----------------------------------------------

	/// Sets the start time of the interval.
	void setStart(FTime startTime);
	/// Sets the end time of the interval.
	void setEnd(FTime endTime);

	/// Intersects this interval with the given one. Returns false and
	/// lets this interval unchanged if the intervals don't overlap.
	bool intersectWith(const FInterval& other);
	/// Unites this interval with the given one. Returns false and
	/// lets this interval unchanged if the intervals don't overlap.
	bool uniteWith(const FInterval& other);

	//  Public queries -----------------------------------------------

	/// Returns the start time of the interval.
	FTime start() const { return m_start; }
	/// Returns the end time of the interval.
	FTime end() const { return m_end; }
	/// Returns the length of the interval.
	FTime length() const { return m_end - m_start; }

	/// Returns true if the given time is within this interval,
	/// i.e. interval.start <= time < interval.end.
	bool contains(FTime time) const;
	/// Returns true if the given interval is contained in this one.
	bool contains(const FInterval& other) const;
	/// Returns true if the given interval overlaps with this one.
	bool intersectsWith(const FInterval& other) const;

	/// Returns true if the interval is zero, i.e. start == end.
	bool isZero() const { return m_start == m_end; };
	/// Returns true if the interval is normal, i.e. start <= end.
	bool isNormal() const { return m_start <= m_end; }

	//  Internal data members ----------------------------------------

private:
	FTime m_start;
	FTime m_end;
};

// Inline members --------------------------------------------------------------

inline FInterval::FInterval()
{
}

inline FInterval::FInterval(FTime startTime, FTime endTime)
	: m_start(startTime), m_end(endTime)
{
}

inline FInterval& FInterval::operator+=(FTime offset)
{
	m_start += offset;
	m_end += offset;
	return *this;
}

inline FInterval& FInterval::operator-=(FTime offset)
{
	m_start -= offset;
	m_end -= offset;
	return *this;
}

inline FInterval FInterval::operator+(FTime offset) const
{
	return FInterval(m_start + offset, m_end + offset);
}

inline FInterval FInterval::operator-(FTime offset) const
{
	return FInterval(m_start - offset, m_end - offset);
}

inline bool FInterval::operator==(const FInterval& other) const
{
	return m_start == other.m_start && m_end == other.m_end;
}

inline bool FInterval::operator!=(const FInterval& other) const
{
	return m_start != other.m_start || m_end != other.m_end;
}

inline void FInterval::setStart(FTime startTime)
{
	m_start = startTime;
}

inline void FInterval::setEnd(FTime endTime)
{
	m_end = endTime;
}

inline bool FInterval::intersectWith(const FInterval& other)
{
	if (!intersectsWith(other))
		return false;

	m_start = fMax(m_start, other.m_start);
	m_end = fMin(m_end, other.m_end);
	return true;
}

inline bool FInterval::uniteWith(const FInterval& other)
{
	if (!intersectsWith(other))
		return false;

	m_start = fMin(m_start, other.m_start);
	m_end = fMax(m_end, other.m_end);
	return true;
}

inline bool FInterval::contains(FTime time) const
{
	return m_start <= time && time < m_end;
}

inline bool FInterval::contains(const FInterval& other) const
{
	return m_start <= other.m_start && other.m_end <= m_end;
}

inline bool FInterval::intersectsWith(const FInterval& other) const
{
	return m_end < other.m_start || other.m_end < m_start;
}

// Related non-member functions ------------------------------------------------

/// Serialization: write operator.
FLOWCORE_EXPORT FArchive& operator<<(FArchive& ar, const FInterval& interval);
/// Serialization: read operator.
FLOWCORE_EXPORT FArchive& operator>>(FArchive& ar, FInterval& interval);

/// Writes a text representation of the given interval to a stream.
FLOWCORE_EXPORT std::wostream& operator<<(
	std::wostream& stream, const FInterval& interval);

// -----------------------------------------------------------------------------

#endif // FLOWCORE_INTERVAL_H