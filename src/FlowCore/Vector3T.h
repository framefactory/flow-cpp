// -----------------------------------------------------------------------------
//  File        Vector3T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_VECTOR3T_H
#define FLOWCORE_VECTOR3T_H

#include "FlowCore/Library.h"

#include <QString>
#include <stdlib.h>
#include <cmath>
#include <float.h>

template <typename REAL>
class FVector2T;

template <typename REAL>
class FVector4T;

// -----------------------------------------------------------------------------
//  Class FVector3T
// -----------------------------------------------------------------------------

template <typename REAL>
class FVector3T
{
	//  Static members -----------------------------------------------

public:
	static const FVector3T<REAL> zero;
	static const FVector3T<REAL> ones;
	static const FVector3T<REAL> unitX;
	static const FVector3T<REAL> unitY;
	static const FVector3T<REAL> unitZ;

	//  Constructors and destructor ----------------------------------

	/// Default constructor. Creates an uninitialized 3-vector.
	FVector3T() { }
	/// Creates a 3-vector from the given values.
	FVector3T(REAL x, REAL y, REAL z);
	/// Creates a 3-vector from the given array of values.
	explicit FVector3T(const REAL* pValues);

	//  Conversions --------------------------------------------------

	/// Returns a pointer to the vector's array of values.
	REAL* ptr() { return &x; }
	/// Constant access to the vector's array of values.
	const REAL* ptr() const { return &x; }

	/// Conversion between 3-vectors of different types.
	template<typename T>
	operator FVector3T<T>() const {
		return FVector3T<T>((T)x, (T)y, (T)z);
	}

	/// Returns a text representation of the vector.
	QString toString() const;

	//  Access -------------------------------------------------------
	//  
	/// Sets the vector's components to the given values.
	void set(REAL x, REAL y, REAL z);
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
	FVector3T<REAL>& operator+=(const FVector3T<REAL>& vec);
	/// Component-wise addition of a scalar: Compound-assignment.
	FVector3T<REAL>& operator+=(REAL scalar);
	/// Component-wise subtraction of two vectors: Compound-assignment.
	FVector3T<REAL>& operator-=(const FVector3T<REAL>& vec);
	/// Component-wise subtraction of a scalar: Compound-assignment.
	FVector3T<REAL>& operator-=(REAL scalar);
	/// Component-wise scalar multiplication: Compound assignment.
	FVector3T<REAL>& operator*=(REAL scalar);
	/// Component-wise scalar division: Compound assignment.
	FVector3T<REAL>& operator/=(REAL scalar);

	/// Returns true if all components of two vectors are equal.
	bool operator==(const FVector3T<REAL>& vec) const;
	/// Returns true if at least one component of the two vectors is different.
	bool operator!=(const FVector3T<REAL>& vec) const;

	//  Public commands ----------------------------------------------

	/// Sets all components of the vector to zero.
	void setZero();
	/// Normalizes the vector to unit length.
	void normalize();
	/// Homogenization of the vector by dividing it by its last component.
	void homogenize();

	//  Public queries -----------------------------------------------

	/// Returns the 2-norm (length) of the vector.
	REAL length() const;
	/// Returns the squared 2-norm of the vector.
	REAL lengthSquared() const;
	/// Returns the normalized vector (unit length).
	FVector3T<REAL> normalized() const;
	/// Returns the homogenized vector.
	FVector3T<REAL> homogenized() const;

	/// Returns the minimum component of the vector.
	inline REAL min() const;
	/// Returns the maximum component of the vector.
	inline REAL max() const;

	/// Returns the dot product of this and the given vector.
	REAL dot(const FVector3T<REAL>& other) const;
	/// Returns the cross product of this and the given vector.
	FVector3T<REAL> cross(const FVector3T<REAL>& other) const;

	/// Returns true if all components are equal to zero.
	bool allZero() const;
	/// Returns true if all components are equal to one.
	bool allOne() const;

	//  Public data --------------------------------------------------

	REAL x;
	REAL y;
	REAL z;
};

// Static members --------------------------------------------------------------

template <typename REAL>
const FVector3T<REAL> FVector3T<REAL>::zero(REAL(0.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const FVector3T<REAL> FVector3T<REAL>::ones(REAL(1.0), REAL(1.0), REAL(1.0));

template <typename REAL>
const FVector3T<REAL> FVector3T<REAL>::unitX(REAL(1.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const FVector3T<REAL> FVector3T<REAL>::unitY(REAL(0.0), REAL(1.0), REAL(0.0));

template <typename REAL>
const FVector3T<REAL> FVector3T<REAL>::unitZ(REAL(0.0), REAL(0.0), REAL(1.0));

// Constructors ----------------------------------------------------------------

template <typename REAL>
inline FVector3T<REAL>::FVector3T(REAL _x, REAL _y, REAL _z)
: x(_x),
  y(_y),
  z(_z)
{
}

template <typename REAL>
inline FVector3T<REAL>::FVector3T(const REAL* pValues)
: x(pValues[0]),
  y(pValues[1]),
  z(pValues[2])
{
}

// Conversions -----------------------------------------------------------------

template <typename REAL>
inline QString FVector3T<REAL>::toString() const
{
	return QString("[%1, %2, %3]").arg(x).arg(y).arg(z);
}

// Access ----------------------------------------------------------------------

template <typename REAL>
inline void FVector3T<REAL>::set(REAL _x, REAL _y, REAL _z)
{
	x = _x;
	y = _y;
	z = _z;
}

template <typename REAL>
inline void FVector3T<REAL>::setAll(REAL scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
}

template <typename REAL>
inline REAL& FVector3T<REAL>::operator[](size_t index)
{
	F_ASSERT(index < 3);
	return (&x)[index];
}

template <typename REAL>
inline const REAL& FVector3T<REAL>::operator[](size_t index) const
{
	F_ASSERT(index < 3);
	return (&x)[index];
}

template <typename REAL>
inline void FVector3T<REAL>::copyTo(REAL* pValues) const
{
	pValues[0] = x;
	pValues[1] = y;
	pValues[2] = z;
}

template <typename REAL>
inline void FVector3T<REAL>::copyFrom(const REAL* pValues)
{
	x = pValues[0];
	y = pValues[1];
	z = pValues[2];
}

// Operators -------------------------------------------------------------------

template <typename REAL>
inline FVector3T<REAL>& FVector3T<REAL>::operator+=(const FVector3T<REAL>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

template <typename REAL>
inline FVector3T<REAL>& FVector3T<REAL>::operator+=(REAL scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}

template <typename REAL>
inline FVector3T<REAL>& FVector3T<REAL>::operator-=(const FVector3T<REAL>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

template <typename REAL>
inline FVector3T<REAL>& FVector3T<REAL>::operator-=(REAL scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

template <typename REAL>
inline FVector3T<REAL>& FVector3T<REAL>::operator*=(REAL scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

template <typename REAL>
inline FVector3T<REAL>& FVector3T<REAL>::operator/=(REAL scalar)
{
	REAL s = (REAL)1.0 / scalar;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

template <typename REAL>
inline bool FVector3T<REAL>::operator==(const FVector3T<REAL>& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

template <typename REAL>
inline bool FVector3T<REAL>::operator!=(const FVector3T<REAL>& vec) const
{
	return x != vec.x || y != vec.y || z != vec.z;
}

// Public commands -------------------------------------------------------------

template <typename REAL>
inline void FVector3T<REAL>::setZero()
{
	x = y = z = REAL(0.0);
}

template <typename REAL>
inline void FVector3T<REAL>::normalize()
{
	REAL invLength = REAL(1.0) / length();
	x *= invLength;
	y *= invLength;
	z *= invLength;
}

template <typename REAL>
inline void FVector3T<REAL>::homogenize()
{
	x /= z;
	y /= z;
	z = REAL(1.0);
}

// Public queries --------------------------------------------------------------

template <typename REAL>
inline REAL FVector3T<REAL>::length() const
{
	return sqrt(x*x + y*y + z*z);
}

template <typename REAL>
inline REAL FVector3T<REAL>::lengthSquared() const
{
	return x*x + y*y + z*z;
}

template <typename REAL>
inline FVector3T<REAL> FVector3T<REAL>::normalized() const
{
	REAL invLength = REAL(1.0) / length();
	return FVector3T<REAL>(x * invLength, y * invLength, z * invLength);
}

template <typename REAL>
inline FVector3T<REAL> FVector3T<REAL>::homogenized() const
{
	return FVector3T<REAL>(x / z, y / z, REAL(1.0));
}

template <typename REAL>
inline REAL FVector3T<REAL>::min() const
{
	return fTripleMin(x, y, z);
}

template <typename REAL>
inline REAL FVector3T<REAL>::max() const
{
	return fTripleMax(x, y, z);
}

template <typename REAL>
inline REAL FVector3T<REAL>::dot(const FVector3T<REAL>& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

template <typename REAL>
inline FVector3T<REAL> FVector3T<REAL>::cross(const FVector3T<REAL>& other) const
{
	return FVector3T<REAL>(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

template <typename REAL>
inline bool FVector3T<REAL>::allZero() const
{
	return x == REAL(0.0) && y == REAL(0.0) && z == REAL(0.0);
}

template <typename REAL>
inline bool FVector3T<REAL>::allOne() const
{
	return x == REAL(1.0) && y == REAL(1.0) && z == REAL(1.0);
}

// Related non-member functions ------------------------------------------------

/// Unary minus.
template <typename REAL>
inline FVector3T<REAL> operator-(const FVector3T<REAL>& vec)
{
	return FVector3T<REAL>(-vec.x, -vec.y, -vec.z);
}

/// Addition of two vectors.
template <typename REAL>
inline FVector3T<REAL> operator+(const FVector3T<REAL>& lhs, const FVector3T<REAL>& rhs)
{
	return FVector3T<REAL>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

/// Component-wise addition of a vector and a scalar.
template <typename REAL>
inline FVector3T<REAL> operator+(const FVector3T<REAL>& vec, REAL scalar)
{
	return FVector3T<REAL>(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

/// Component-wise addition of a scalar and a a vector.
template <typename REAL>
inline FVector3T<REAL> operator+(REAL scalar, const FVector3T<REAL>& vec)
{
	return FVector3T<REAL>(scalar + vec.x, scalar + vec.y, scalar + vec.z);
}

/// Subtraction of two vectors.
template <typename REAL>
inline FVector3T<REAL> operator-(const FVector3T<REAL>& lhs, const FVector3T<REAL>& rhs)
{
	return FVector3T<REAL>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

/// Component-wise subtraction of a vector and a scalar.
template <typename REAL>
inline FVector3T<REAL> operator-(const FVector3T<REAL>& vec, REAL scalar)
{
	return FVector3T<REAL>(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}

/// Component-wise subtraction of a scalar and a vector.
template <typename REAL>
inline FVector3T<REAL> operator-(REAL scalar, const FVector3T<REAL>& vec)
{
	return FVector3T<REAL>(scalar - vec.x, scalar - vec.y, scalar - vec.z);
}

/// Component-wise multiplication of a vector and a scalar.
template <typename REAL>
inline FVector3T<REAL> operator*(const FVector3T<REAL>& vec, REAL scalar)
{
	return FVector3T<REAL>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

/// Component-wise multiplication of a scalar and a vector.
template <typename REAL>
inline FVector3T<REAL> operator*(REAL scalar, const FVector3T<REAL>& vec)
{
	return FVector3T<REAL>(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

/// Component-wise division of a vector and a scalar.
template <typename REAL>
inline FVector3T<REAL> operator/(const FVector3T<REAL>& vec, REAL scalar)
{
	REAL inv = REAL(1.0) / scalar;
	return FVector3T<REAL>(vec.x * inv, vec.y * inv, vec.z * inv);
}

/// Component-wise division of a scalar and a vector.
template <typename REAL>
inline FVector3T<REAL> operator/(REAL scalar, const FVector3T<REAL>& vec)
{
	return FVector3T<REAL>(scalar / vec.x, scalar / vec.y, scalar / vec.z);
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL operator*(const FVector3T<REAL>& v1, const FVector3T<REAL>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL fDot(const FVector3T<REAL>& v1, const FVector3T<REAL>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// Cross product of two vectors.
template <typename REAL>
inline FVector3T<REAL> fCross(const FVector3T<REAL>& v1, const FVector3T<REAL>& v2)
{
	return FVector3T<REAL>(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

/// Returns the component-wise minimum of two vectors.
template <typename REAL>
inline FVector3T<REAL> fMin(const FVector3T<REAL>& v1, const FVector3T<REAL>& v2)
{
	return FVector3T<REAL>(fMin(v1.x, v2.x), fMin(v1.y, v2.y), fMin(v1.z, v2.z));
}

/// Returns the component-wise maximum of two vectors.
template <typename REAL>
inline FVector3T<REAL> fMax(const FVector3T<REAL>& v1, const FVector3T<REAL>& v2)
{
	return FVector3T<REAL>(fMax(v1.x, v2.x), fMax(v1.y, v2.y), fMax(v1.z, v2.z));
}

/// Linear interpolation between two vectors.
template <typename REAL>
inline FVector3T<REAL> lerp(const FVector3T<REAL>& v1, const FVector3T<REAL>& v2, REAL factor)
{
	return FVector3T<REAL>(
		v1.x + factor * (v2.x - v1.x),
		v1.y + factor * (v2.y - v1.y),
		v1.z + factor * (v2.z - v1.z));
}

/// Writes a text representation of the vector to the given stream.
template <typename REAL, typename C>
std::basic_ostream<C, std::char_traits<C>>& operator<<(
	std::basic_ostream<C, std::char_traits<C>>& stream, const FVector3T<REAL>& vec)
{
	stream << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
	return stream;
}

// Typedefs --------------------------------------------------------------------

/// 3-component vector of type float
typedef FVector3T<float> FVector3f;

/// 3-component vector of type double
typedef FVector3T<double> FVector3d;

/// 3-component vector of type integer
typedef FVector3T<int> FVector3i;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_VECTOR3T_H