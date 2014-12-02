// -----------------------------------------------------------------------------
//  File        Vector2T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/17 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_VECTOR2T_H
#define FLOWCORE_VECTOR2T_H

#include "FlowCore/Library.h"

#include <QString>
#include <stdlib.h>
#include <cmath>
#include <float.h>

template <typename REAL>
class FVector3T;

template <typename REAL>
class FVector4T;

// -----------------------------------------------------------------------------
//  Class FVector2T
// -----------------------------------------------------------------------------

template <typename REAL>
class FVector2T
{
	//  Static members -----------------------------------------------

public:
	static const FVector2T<REAL> zero;
	static const FVector2T<REAL> ones;
	static const FVector2T<REAL> unitX;
	static const FVector2T<REAL> unitY;

	//  Constructors and destructor ----------------------------------

	/// Default constructor. Creates an uninitialized 2-vector.
	FVector2T() { }
	/// Creates a 2-vector from the given values.
	FVector2T(REAL x, REAL y);
	/// Creates a 2-vector from the given array of values.
	explicit FVector2T(const REAL* pValues);

	//  Conversions --------------------------------------------------

	/// Returns a pointer to the vector's array of values.
	REAL* ptr() { return &x; }
	/// Constant access to the vector's array of values.
	const REAL* ptr() const { return &x; }

	/// Conversion between vectors of different numeric types.
	template<typename T>
	operator FVector2T<T>() const {
		return FVector2T<T>((T)x, (T)y);
	}

	/// Returns a text representation of the vector.
	QString toString() const;

	//  Access -------------------------------------------------------

	/// Sets the vector's components to the given values.
	void set(REAL x, REAL y);
	/// Sets all components to the given value.
	void setAll(REAL v);
	/// Index access.
	REAL& operator[](size_t index);
	/// Const index access.
	const REAL& operator[](size_t index) const;
	/// Copies the vector's values to the given array.
	void copyTo(REAL* pValues) const;
	/// Copies the values from the given array.
	void copyFrom(const REAL* pValues);

	//  Operators ----------------------------------------------------

	/// Component-wise addition of two vectors: Compound-assignment.
	FVector2T<REAL>& operator+=(const FVector2T<REAL>& vec);
	/// Component-wise addition of a scalar: Compound-assignment.
	FVector2T<REAL>& operator+=(REAL scalar);
	/// Component-wise subtraction of two vectors: Compound-assignment.
	FVector2T<REAL>& operator-=(const FVector2T<REAL>& vec);
	/// Component-wise subtraction of a scalar: Compound-assignment.
	FVector2T<REAL>& operator-=(REAL scalar);
	/// Component-wise scalar multiplication: Compound assignment.
	FVector2T<REAL>& operator*=(REAL scalar);
	/// Component-wise scalar division: Compound assignment.
	FVector2T<REAL>& operator/=(REAL scalar);

	/// Returns true if all components of two vectors are equal.
	bool operator==(const FVector2T<REAL>& vec) const;
	/// Returns true if at least one component of the two vectors is different.
	bool operator!=(const FVector2T<REAL>& vec) const;

	//  Public commands ----------------------------------------------

	/// Sets all components of the vector to zero.
	void setZero();
	/// Normalizes the vector to unit length.
	void normalize();

	//  Public queries -----------------------------------------------

	/// Returns the 2-norm (length) of the vector.
	REAL length() const;
	/// Returns the squared 2-norm of the vector.
	REAL lengthSquared() const;
	/// Returns the normalized vector (unit length).
	FVector2T<REAL> normalized() const;

	/// Returns the angle of the vector.
	REAL angle() const;
	/// Returns the angle of the vector relative to the given origin.
	REAL angle(const FVector2T<REAL>& origin) const;

	/// Returns the minimum component of the vector.
	REAL min() const;
	/// Returns the maximum component of the vector.
	REAL max() const;

	/// Returns the dot product of this and the given vector.
	REAL dot(const FVector2T<REAL>& other) const;
	/// Returns a vector that is orthogonal to this vector.
	FVector2T<REAL> normal() const;

	/// Returns true if all components are equal to zero.
	bool allZero() const;
	/// Returns true if all components are equal to one.
	bool allOne() const;

	//  Public data --------------------------------------------------

	REAL x;
	REAL y;
};

// Static members --------------------------------------------------------------

template <typename REAL>
const FVector2T<REAL> FVector2T<REAL>::zero(REAL(0.0), REAL(0.0));

template <typename REAL>
const FVector2T<REAL> FVector2T<REAL>::ones(REAL(1.0), REAL(1.0));

template <typename REAL>
const FVector2T<REAL> FVector2T<REAL>::unitX(REAL(1.0), REAL(0.0));

template <typename REAL>
const FVector2T<REAL> FVector2T<REAL>::unitY(REAL(0.0), REAL(1.0));

// Constructors ----------------------------------------------------------------

template <typename REAL>
inline FVector2T<REAL>::FVector2T(REAL _x, REAL _y)
: x(_x),
  y(_y)
{
}

template <typename REAL>
inline FVector2T<REAL>::FVector2T(const REAL* pValues)
: x(pValues[0]),
  y(pValues[1])
{
}

// Conversions -----------------------------------------------------------------

template <typename REAL>
inline QString FVector2T<REAL>::toString() const
{
	return QString("[%1, %2]").arg(x).arg(y);
}

// Access ----------------------------------------------------------------------

template <typename REAL>
inline void FVector2T<REAL>::set(REAL _x, REAL _y)
{
	x = _x;
	y = _y;
}

template <typename REAL>
inline void FVector2T<REAL>::setAll(REAL scalar)
{
	x = scalar;
	y = scalar;
}

template <typename REAL>
inline REAL& FVector2T<REAL>::operator[](size_t index)
{
	F_ASSERT(index < 2);
	return (&x)[index];
}

template <typename REAL>
inline const REAL& FVector2T<REAL>::operator[](size_t index) const
{
	F_ASSERT(index < 2);
	return (&x)[index];
}

template <typename REAL>
inline void FVector2T<REAL>::copyTo(REAL* pValues) const
{
	pValues[0] = x;
	pValues[1] = y;
}

template <typename REAL>
inline void FVector2T<REAL>::copyFrom(const REAL* pValues)
{
	x = pValues[0];
	y = pValues[1];
}

// Operators -------------------------------------------------------------------

template <typename REAL>
inline FVector2T<REAL>& FVector2T<REAL>::operator+=(const FVector2T<REAL>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template <typename REAL>
inline FVector2T<REAL>& FVector2T<REAL>::operator+=(REAL scalar)
{
	x += scalar;
	y += scalar;
	return *this;
}

template <typename REAL>
inline FVector2T<REAL>& FVector2T<REAL>::operator-=(const FVector2T<REAL>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template <typename REAL>
inline FVector2T<REAL>& FVector2T<REAL>::operator-=(REAL scalar)
{
	x -= scalar;
	y -= scalar;
	return *this;
}

template <typename REAL>
inline FVector2T<REAL>& FVector2T<REAL>::operator*=(REAL scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template <typename REAL>
inline FVector2T<REAL>& FVector2T<REAL>::operator/=(REAL scalar)
{
	REAL s = (REAL)1.0 / scalar;
	x *= s;
	y *= s;
	return *this;
}

template <typename REAL>
inline bool FVector2T<REAL>::operator==(const FVector2T<REAL>& vec) const
{
	return x == vec.x && y == vec.y;
}

template <typename REAL>
inline bool FVector2T<REAL>::operator!=(const FVector2T<REAL>& vec) const
{
	return x != vec.x || y != vec.y;
}

// Public commands -------------------------------------------------------------

template <typename REAL>
inline void FVector2T<REAL>::setZero()
{
	x = y = REAL(0.0);
}

template <typename REAL>
inline void FVector2T<REAL>::normalize()
{
	REAL invLength = REAL(1.0) / length();
	x *= invLength;
	y *= invLength;
}

// Public queries --------------------------------------------------------------

template <typename REAL>
inline REAL FVector2T<REAL>::length() const
{
	return sqrt(x * x + y * y);
}

template <typename REAL>
inline REAL FVector2T<REAL>::lengthSquared() const
{
	return x * x + y * y;
}

template <typename REAL>
inline FVector2T<REAL> FVector2T<REAL>::normalized() const
{
	REAL invLength = REAL(1.0) / length();
	return FVector2T<REAL>(x * invLength, y * invLength);
}

template <typename REAL>
inline REAL FVector2T<REAL>::angle() const
{
	return atan2(y, x);
}

template <typename REAL>
inline REAL FVector2T<REAL>::angle(const FVector2T<REAL>& origin) const
{
	return atan2(y - origin.y, x - origin.x);
}

template <typename REAL>
inline REAL FVector2T<REAL>::min() const
{
	return fMin(x, y);
}

template <typename REAL>
inline REAL FVector2T<REAL>::max() const
{
	return fMax(x, y);
}

template <typename REAL>
inline REAL FVector2T<REAL>::dot(const FVector2T<REAL>& other) const
{
	return x * other.x + y * other.y;
}

template <typename REAL>
inline FVector2T<REAL> FVector2T<REAL>::normal() const
{
	return FVector2T<REAL>(y, -x);
}

template <typename REAL>
inline bool FVector2T<REAL>::allZero() const
{
	return x == REAL(0.0) && y == REAL(0.0);
}

template <typename REAL>
inline bool FVector2T<REAL>::allOne() const
{
	return x == REAL(1.0) && y == REAL(1.0);
}

// Related non-member functions ------------------------------------------------

/// Unary minus.
template <typename REAL>
inline FVector2T<REAL> operator-(const FVector2T<REAL>& vec)
{
	return FVector2T<REAL>(-vec.x, -vec.y);
}

/// Addition of two vectors.
template <typename REAL>
inline FVector2T<REAL> operator+(const FVector2T<REAL>& lhs, const FVector2T<REAL>& rhs)
{
	return FVector2T<REAL>(lhs.x + rhs.x, lhs.y + rhs.y);
}

/// Component-wise addition of a vector and a scalar.
template <typename REAL>
inline FVector2T<REAL> operator+(const FVector2T<REAL>& vec, REAL scalar)
{
	return FVector2T<REAL>(vec.x + scalar, vec.y + scalar);
}

/// Component-wise addition of a scalar and a a vector.
template <typename REAL>
inline FVector2T<REAL> operator+(REAL scalar, const FVector2T<REAL>& vec)
{
	return FVector2T<REAL>(scalar + vec.x, scalar + vec.y);
}

/// Subtraction of two vectors.
template <typename REAL>
inline FVector2T<REAL> operator-(const FVector2T<REAL>& lhs, const FVector2T<REAL>& rhs)
{
	return FVector2T<REAL>(lhs.x - rhs.x, lhs.y - rhs.y);
}

/// Component-wise subtraction of a vector and a scalar.
template <typename REAL>
inline FVector2T<REAL> operator-(const FVector2T<REAL>& vec, REAL scalar)
{
	return FVector2T<REAL>(vec.x - scalar, vec.y - scalar);
}

/// Component-wise subtraction of a scalar and a vector.
template <typename REAL>
inline FVector2T<REAL> operator-(REAL scalar, const FVector2T<REAL>& vec)
{
	return FVector2T<REAL>(scalar - vec.x, scalar - vec.y);
}

/// Component-wise multiplication of a vector and a scalar.
template <typename REAL>
inline FVector2T<REAL> operator*(const FVector2T<REAL>& vec, REAL scalar)
{
	return FVector2T<REAL>(vec.x * scalar, vec.y * scalar);
}

/// Component-wise multiplication of a scalar and a vector.
template <typename REAL>
inline FVector2T<REAL> operator*(REAL scalar, const FVector2T<REAL>& vec)
{
	return FVector2T<REAL>(scalar * vec.x, scalar * vec.y);
}

/// Component-wise division of a vector and a scalar.
template <typename REAL>
inline FVector2T<REAL> operator/(const FVector2T<REAL>& vec, REAL scalar)
{
	REAL inv = REAL(1.0) / scalar;
	return FVector2T<REAL>(vec.x * inv, vec.y * inv);
}

/// Component-wise division of a scalar and a vector.
template <typename REAL>
inline FVector2T<REAL> operator/(REAL scalar, const FVector2T<REAL>& vec)
{
	return FVector2T<REAL>(scalar / vec.x, scalar / vec.y);
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL operator*(const FVector2T<REAL>& v1, const FVector2T<REAL>& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL fDot(const FVector2T<REAL>& v1, const FVector2T<REAL>& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

/// Returns the component-wise minimum of two vectors.
template <typename REAL>
inline FVector2T<REAL> fMin(const FVector2T<REAL>& v1, const FVector2T<REAL>& v2)
{
	return FVector2T<REAL>(fMin(v1.x, v2.x), fMin(v1.y, v2.y));
}

/// Returns the component-wise maximum of two vectors.
template <typename REAL>
inline FVector2T<REAL> fMax(const FVector2T<REAL>& v1, const FVector2T<REAL>& v2)
{
	return FVector2T<REAL>(fMax(v1.x, v2.x), fMax(v1.y, v2.y));
}

/// Linear interpolation between two vectors.
template <typename REAL>
inline FVector2T<REAL> lerp(const FVector2T<REAL>& v1,
                            const FVector2T<REAL>& v2,
	                        REAL factor)
{
	return FVector2T<REAL>(v1.x + factor * (v2.x - v1.x),
	                       v1.y + factor * (v2.y - v1.y));
}

// Typedefs --------------------------------------------------------------------

/// 2-component vector of type float
typedef FVector2T<float> FVector2f;

/// 2-component vector of type double
typedef FVector2T<double> FVector2d;

/// 2-component vector of type integer
typedef FVector2T<qint32> FVector2i;

/// 2-component vector of type unsigned integer
typedef FVector2T<quint32> FVector2ui;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_VECTOR2T_H