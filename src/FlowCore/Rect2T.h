// -----------------------------------------------------------------------------
//  File        Rect2T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/24 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_RECT2T_H
#define FLOWCORE_RECT2T_H

#include "FlowCore/Library.h"
#include "FlowCore/Vector2T.h"

// -----------------------------------------------------------------------------
//  Class FRect2T
// -----------------------------------------------------------------------------

template <typename REAL>
class FRect2T
{
	//  Constructors and destructor ----------------------------------

public:
	FRect2T() { }

	FRect2T(const FVector2T<REAL>& pMin, const FVector2T<REAL> pMax)
		: m_p0(pMin), m_p1(pMax) { }

	FRect2T(REAL xMin, REAL yMin, REAL xMax, REAL yMax)
		: m_p0(xMin, yMin), m_p1(xMax, yMax) { }

	FRect2T(REAL width, REAL height)
		: m_p0(REAL(0.0), REAL(0.0)), m_p1(width, height) { }

	//  Conversions --------------------------------------------------

	REAL* ptr() { return m_p0.ptr(); }
	const REAL* ptr() const { return m_p0.ptr(); }

	//  Access -------------------------------------------------------

	void set(const FVector2T<REAL>& pMin, const FVector2T<REAL>& pMax) {
		m_p0 = pMin;
		m_p1 = pMax;
	}

	void set(REAL xMin, REAL yMin, REAL xMax, REAL yMax) {
		m_p0.set(xMin, yMin);
		m_p1.set(xMax, yMax);
	}

	void set(REAL width, REAL height) {
		m_p0.set(REAL(0), REAL(0));
		m_p1.set(width, height);
	}
	
	void setPMin(const FVector2T<REAL>& pMin) { m_p0 = pMin; }
	
	void setPMax(const FVector2T<REAL>& pMax) { m_p1 = pMax; }
	
	const FVector2T<REAL>& pMin() const { return m_p0; }
	const FVector2T<REAL>& pMax() const { return m_p1; }

	void setXMin(REAL xMin) { m_p0.x = xMin; }
	const REAL xMin() const { return m_p0.x; }

	void setYMin(REAL yMin) { m_p0.y = yMin; }
	const REAL yMin() const { return m_p0.y; }
	
	void setXMax(REAL xMax) { m_p1.x = xMax; }
	const REAL xMax() const { return m_p1.x; }
	
	void setYMax(REAL yMax) { m_p1.y = yMax; }
	const REAL yMax() const { return m_p1.y; }


	void setBottomLeft(const FVector2T<REAL>& bottomLeft) {
		m_p0 = bottomLeft;
	}
	const FVector2T<REAL>& bottomLeft() const {
		return m_p0;
	}

	void setBottomRight(const FVector2T<REAL>& bottomRight) {
		m_p1.setX(bottomRight.x); m_p0.setY(bottomRight.y);
	}
	const FVector2T<REAL> bottomRight() const {
		return FVector2T<REAL>(m_p1.x, m_p0.y);
	}

	void setTopLeft(const FVector2T<REAL>& topLeft) {
		m_p0.setX(topLeft.x); m_p1.setY(topLeft.y);
	}
	const FVector2T<REAL> topLeft() const {
		return FVector2T<REAL>(m_p0.x, m_p1.y);
	}

	void setTopRight(const FVector2T<REAL>& topRight) {
		m_p1 = topRight;
	}
	const FVector2T<REAL>& topRight() const {
		return m_p1;
	}

	/// Returns the minimum coordinates given index 0 or
	/// the maximum coordinates given index 1.
	FVector2T<REAL>& operator[](size_t index) {
		F_ASSERT(index < 2);
		return (&m_p0)[index];
	}

	/// Returns the minimum coordinates given index 0 or
	/// the maximum coordinates given index 1.
	const FVector2T<REAL>& operator[](size_t index) const {
		F_ASSERT(index < 2);
		return (&m_p0)[index];
	}

	bool operator==(const FRect2T<REAL>& other) const {
		return m_p0 == other.m_p0 && m_p1 == other.m_p1;
	}

	bool operator!=(const FRect2T<REAL>& other) const {
		return m_p0 != other.m_p0 || m_p1 != other.m_p1; 
	}

	//  Public commands ----------------------------------------------

	/// Sets all coordinates to zero.
	void setZero()
	{
		m_p0.setZero();
		m_p1.setZero();
	}
	
	/// Sets the width of the rectangle. This changes only xMax.
	void setWidth(REAL width)
	{
		m_p1.x = m_p0.x + width; 
	}

	/// Sets the height of the rectangle. This changes only yMax.
	void setHeight(REAL height)
	{
		m_p1.y = m_p0.y + height; 
	}
	
	/// Sets the size of the rectangle. This changes only pMax.
	void setSize(const FVector2T<REAL>& size)
	{
		m_p1 = m_p0 + size;
	}

	/// Translates the rectangle by the given translation vector.
	void move(const FVector2T<REAL>& offset)
	{
		m_p0 += offset;
		m_p1 += offset;
	}

	/// Grows the boundaries of the rectangle equally by the given factor.
	FRect2T<REAL>& grow(REAL factor)
	{
		m_p0 -= factor;
		m_p1 += factor;
		return *this;
	}

	/// Grows the boundaries of the rectangle by the given factors.
	FRect2T<REAL>& grow(float x0, float y0, float x1, float y1)
	{
		m_p0 -= FVector2T<REAL>(x0, y0);
		m_p1 += FVector2T<REAL>(x1, y1);
		return *this;
	}

	/// Shrinks the boundaries of the rectangle equally by the given factor.
	FRect2T<REAL>& shrink(REAL factor)
	{
		m_p0 += factor;
		m_p1 -= factor;
		return *this;
	}

	/// Shrinks the boundaries of the rectangle by the given factors.
	FRect2T<REAL>& shrink(float x0, float y0, float x1, float y1)
	{
		m_p0 += FVector2T<REAL>(x0, y0);
		m_p1 -= FVector2T<REAL>(x1, y1);
		return *this;
	}

	/// Intersects this rectangle with the given rectangle and replaces this rectangle
	/// with the intersection result.
	FRect2T<REAL>& intersect(const FRect2T<REAL>& other)
	{
		m_p0.set(fMax(m_p0.x, other.m_p0.x), fMax(m_p0.y, other.m_p0.y));
		m_p1.set(fMin(m_p1.x, other.m_p1.x), fMin(m_p1.y, other.m_p1.y));
		return *this;
	}

	/// Unites this rectangle with the given rectangle and replaces this rectangle
	/// with the union result.
	FRect2T<REAL>& unite(const FRect2T<REAL>& other)
	{
		m_p0.set(fMin(m_p0.x, other.m_p0.x), fMin(m_p0.y, other.m_p0.y));
		m_p1.set(fMax(m_p1.x, other.m_p1.x), fMax(m_p1.y, other.m_p1.y));
		return *this;
	}

	/// Extends the rectangle if necessary to include the given point.
	FRect2T<REAL>& include(const FVector2T<REAL>& point)
	{
		m_p0.set(fMin(m_p0.x, point.x), fMin(m_p0.y, point.y));
		m_p1.set(fMax(m_p1.x, point.x), fMax(m_p1.y, point.y));
		return *this;
	}

	/// Ensures that coordinates of point0 are smaller than coordinates of point1,
	/// i.e. p0.x <= p1.x, p0.y <= p1.y and p0.z <= p1.z.
	FRect2T<REAL>& normalize()
	{
		if (m_p0.x > m_p1.x) {
			REAL t = m_p0.x; m_p0.x = m_p1.x; m_p1.x = t;
		}
		if (m_p0.y > m_p1.y) {
			REAL t = m_p0.y; m_p0.y = m_p1.y; m_p1.y = t;
		}

		return *this;
	}

	//  Public queries -----------------------------------------------

	/// Returns the size of the rectangle.
	FVector2T<REAL> size() const {
		return m_p1 - m_p0;
	}
	/// Returns the width of the rectangle.
	REAL width() const { return m_p1.x - m_p0.x; }

	/// Returns the height of the rectangle.
	REAL height() const { return m_p1.y - m_p0.y; }

	/// Returns the area of the rectangle.
	REAL area() const {
		FVector2T<REAL> sz = size(); return sz.x * sz.y;
	}
	/// Returns true if the area of the rectangle is zero.
	bool isNull() const {
		return m_p0.x == m_p1.x || m_p0.y == m_p1.y;
	}
	/// Returns true if the volume of the box is zero.
	bool isZero() const { return isNull(); }

	/// Returns true if the box has normalized form, i.e. the components of
	/// point0 are smaller than those of point1.
	bool isNormal() const {
		return m_p0.x <= m_p1.x && m_p0.y <= m_p1.y;
	}

	/// Returns true if the given point lies inside the rectangle,
	/// i.e. if xMin <= p.x < xMax and yMin <= p.y < yMax.
	bool contains(const FVector2T<REAL>& p) const {
		return m_p0.x <= p.x && p.x < m_p1.x && m_p0.y <= p.y && p.y < m_p1.y;
	}

	/// Returns true if the given rectangle lies inside this rectangle.
	bool contains(const FRect2T<REAL>& r) const {
		return m_p0.x <= r.m_p0.x && r.m_p1.x <= m_p1.x
			&& m_p0.y <= r.m_p0.y && r.m_p1.y <= m_p1.y;
	}

	//  Data members -------------------------------------------------

private:
	FVector2T<REAL> m_p0;
	FVector2T<REAL> m_p1;
};

// Typedefs --------------------------------------------------------------------

/// Rectangle of type float
typedef FRect2T<float> FRect2f;

/// Rectangle of type double
typedef FRect2T<double> FRect2d;

/// Rectangle of type integer
typedef FRect2T<int> FRect2i;

// -----------------------------------------------------------------------------


#endif // FLOWCORE_RECT2T_H