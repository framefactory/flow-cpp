// -----------------------------------------------------------------------------
//  File        Range3T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2014/05/14 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_RANGE3T_H
#define FLOWCORE_RANGE3T_H

#include "FlowCore/Library.h"
#include "FlowCore/Vector3T.h"

#include <QString>
#include <limits>

// -----------------------------------------------------------------------------
//  Class FRange3T
// -----------------------------------------------------------------------------

template <typename T>
class FRange3T
{
	//  Constructors and destructor ----------------------------------

public:
	FRange3T() { }
	FRange3T(const FVector3T<T>& lowerBound, const FVector3T<T>& upperBound)
		: m_lowerBound(lowerBound), m_upperBound(upperBound) { }
	FRange3T(T xMin, T yMin, T zMin, T xMax, T yMax, T zMax)
		: m_lowerBound(xMin, yMin, zMin), m_upperBound(xMax, yMax, zMax) { }

	//  Public commands ----------------------------------------------

public:
	void set(const FVector3T<T>& lowerBound, const FVector3T<T>& upperBound);
	void set(T xMin, T yMin, T zMin, T xMax, T yMax, T zMax);
	void setZero();

	void setLowerBound(const FVector3T<T>& lowerBound);
	void setLowerBound(T xMin, T yMin, T zMin);
	void setUpperBound(const FVector3T<T>& upperBound);
	void setUpperBound(T xMax, T yMax, T zMax);

	/// Invalidates the range by setting the lower bound to the maximum value
	/// and the upper bound to the minimum value.
	void invalidate();

	/// Moves the upper and lower bound by the given offset.
	void move(const FVector3T<T>& offset);

	/// Includes the given point. The range is extended such that
	/// the given point lies inside.
	void include(const FVector3T<T>& point);

	/// Unites this with the given range. The result is a range that
	/// covers both input ranges.
	void uniteWith(const FRange3T<T>& other);

	/// Intersects this with the given range. The range is set to
	/// zero if there is no overlap between the ranges.
	void intersectWith(const FRange3T<T>& other);

	/// Normalizes the range, i.e. for each component swaps the lower and upper bound
	/// if the lower bound is greater than the upper bound.
	void normalize();

	//  Public queries -----------------------------------------------

	const FVector3T<T>& lowerBound() const { return m_lowerBound; }
	const FVector3T<T>& upperBound() const { return m_upperBound; }

	/// Returns the distance between lower and upper bound. The result can
	/// be negative if the range is not normal, i.e. upper bound is smaller
	/// than lower bound.
	const FVector3T<T> size() const;

	/// Interprets the range as a 3D box and returns its volume.
	const T volume() const;

	/// Returns the difference between upper and lower bound of the x component.
	const T sizeX() const { return m_upperBound.x - m_lowerBound.x; }
	
	/// Returns the difference between upper and lower bound of the y component.
	const T sizeY() const { return m_upperBound.y - m_lowerBound.y; }

	/// Returns the difference between upper and lower bound of the z component.
	const T sizeZ() const { return m_upperBound.z - m_lowerBound.z; }

	/// A range is valid if for each component the upper bound is greater
	/// or equal to the lower bound.
	bool isValid() const;
	/// A range is empty if the upper bound is equal to the lower bound.
	bool isEmpty() const;
	/// Same as isEmpty().
	bool isNull() const { return isEmpty(); }

	/// Returns true if the given range is fully included in this one.
	bool includes(const FRange3T<T>& range) const;

	/// Returns true if the given point is included in the range.
	bool includes(const FVector3T<T>& point) const;

	/// Returns true if this and the given range overlap. Also returns
	/// true if the overlap consists of a single point, e.g. if
	/// this range's upper bound equals other range's lower bound.
	bool intersects(const FRange3T<T>& range) const;

	/// Returns a text representation of the range.
	QString toString() const;

	//  Internal data members ----------------------------------------

private:
	FVector3T<T> m_lowerBound;
	FVector3T<T> m_upperBound;
};

// Members ---------------------------------------------------------------------

template <typename T>
inline void FRange3T<T>::set(const FVector3T<T>& lowerBound, const FVector3T<T>& upperBound)
{
	m_lowerBound = lowerBound;
	m_upperBound = upperBound;
}

template <typename T>
inline void FRange3T<T>::set(T xMin, T yMin, T zMin, T xMax, T yMax, T zMax)
{
	m_lowerBound.set(xMin, yMin, zMin);
	m_upperBound.set(xMax, yMax, zMax);
}

template <typename T>
inline void FRange3T<T>::setZero()
{
	m_lowerBound.setZero();
	m_upperBound.setZero();
}

template <typename T>
inline void FRange3T<T>::setLowerBound(const FVector3T<T>& lowerBound)
{
	m_lowerBound = lowerBound;
}

template <typename T>
inline void FRange3T<T>::setLowerBound(T xMin, T yMin, T zMin)
{
	m_lowerBound.set(xMin, yMin, zMin);
}

template <typename T>
inline void FRange3T<T>::setUpperBound(const FVector3T<T>& upperBound)
{
	m_upperBound = upperBound;
}

template <typename T>
inline void FRange3T<T>::setUpperBound(T xMax, T yMax, T zMax)
{
	m_upperBound.set(xMax, yMax, zMax);
}

template <typename T>
inline void FRange3T<T>::invalidate()
{
	m_lowerBound.setAll(std::numeric_limits<T>::max());
	m_upperBound.setAll(std::numeric_limits<T>::lowest());
}

template <typename T>
inline void FRange3T<T>::move(const FVector3T<T>& offset)
{
	m_lowerBound += offset;
	m_upperBound += offset;
}

template <typename T>
inline void FRange3T<T>::include(const FVector3T<T>& point)
{
	m_lowerBound = fMin(m_lowerBound, point);
	m_upperBound = fMax(m_upperBound, point);
}

template <typename T>
inline void FRange3T<T>::uniteWith(const FRange3T<T>& other)
{
	m_lowerBound = fMin(m_lowerBound, other.m_lowerBound);
	m_upperBound = fMax(m_upperBound, other.m_upperBound);
}

template <typename T>
inline void FRange3T<T>::intersectWith(const FRange3T<T>& other)
{
	m_lowerBound = fMax(m_lowerBound, other.m_lowerBound);
	m_upperBound = fMin(m_upperBound, other.m_upperBound);

	if (m_lowerBound.x > m_upperBound.x) m_upperBound.x = m_lowerBound.x;
	if (m_lowerBound.y > m_upperBound.y) m_upperBound.y = m_lowerBound.y;
	if (m_lowerBound.z > m_upperBound.z) m_upperBound.z = m_lowerBound.z;
}

template <typename T>
inline void FRange3T<T>::normalize()
{
	if (m_lowerBound.x > m_upperBound.x) std::swap(m_lowerBound.x, m_upperBound.x);
	if (m_lowerBound.y > m_upperBound.y) std::swap(m_lowerBound.y, m_upperBound.y);
	if (m_lowerBound.z > m_upperBound.z) std::swap(m_lowerBound.z, m_upperBound.z);
}

template <typename T>
inline const FVector3T<T> FRange3T<T>::size() const
{
	return m_upperBound - m_lowerBound;
}

template <typename T>
inline const T FRange3T<T>::volume() const
{
	FVector3T<T> size = m_upperBound - m_lowerBound;
	return size.x * size.y * size.z;
}

template <typename T>
inline bool FRange3T<T>::isValid() const
{
	return m_lowerBound.x <= m_upperBound.x
		&& m_lowerBound.y <= m_upperBound.y
		&& m_lowerBound.z <= m_upperBound.z;
}

template <typename T>
inline bool FRange3T<T>::isEmpty() const
{
	FVector3T<T> size = m_upperBound - m_lowerBound;
	return (size.x * size.y * size.z) == 0;
}

template <typename T>
inline bool FRange3T<T>::includes(const FRange3T<T>& other) const
{
	return m_lowerBound.x <= other.m_lowerBound.x
		&& m_lowerBound.y <= other.m_lowerBound.y
		&& m_lowerBound.z <= other.m_lowerBound.z
		&& m_upperBound.x >= other.m_upperBound.x
		&& m_upperBound.y >= other.m_upperBound.y
		&& m_upperBound.z >= other.m_upperBound.z;
}

template <typename T>
inline bool FRange3T<T>::includes(const FVector3T<T>& point) const
{
	return m_lowerBound.x <= point.x
		&& m_lowerBound.y <= point.y
		&& m_lowerBound.z <= point.z
		&& m_upperBound.x >= point.x
		&& m_upperBound.y >= point.y
		&& m_upperBound.z >= point.z;
}

template <typename T>
inline bool FRange3T<T>::intersects(const FRange3T<T>& other) const
{
	return (m_lowerBound.x <= other.m_upperBound.x
		 && m_lowerBound.y <= other.m_upperBound.y
		 && m_lowerBound.z <= other.m_upperBound.z)
		|| (m_upperBound.x >= other.m_lowerBound.x
		 && m_upperBound.y >= other.m_lowerBound.y
		 && m_upperBound.z >= other.m_lowerBound.z);
}

template <typename T>
QString FRange3T<T>::toString() const
{
	return QString("%1 - %2")
		.arg(m_lowerBound.toString())
		.arg(m_upperBound.toString());
}

// Typedefs --------------------------------------------------------------------

/// 3-component range of type float
typedef FRange3T<float> FRange3f;

/// 3-component range of type double
typedef FRange3T<double> FRange3d;

/// 3-component range of type integer
typedef FRange3T<int> FRange3i;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_RANGE3T_H