// -----------------------------------------------------------------------------
//  File        Vector4T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_VECTOR4T_H
#define FLOWCORE_VECTOR4T_H

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
//  Class FVector4T
// -----------------------------------------------------------------------------

template <typename REAL>
class FVector4T
{
	//  Static members -----------------------------------------------

public:
	static const FVector4T<REAL> zero;
	static const FVector4T<REAL> ones;
	static const FVector4T<REAL> unitX;
	static const FVector4T<REAL> unitY;
	static const FVector4T<REAL> unitZ;
	static const FVector4T<REAL> unitW;

	//  Constructors and destructor ----------------------------------

	/// Default constructor. Creates an uninitialized vector.
	FVector4T() { }
	/// Creates a vector from the given values.
	FVector4T(REAL x, REAL y, REAL z, REAL w);
	/// Creates a vector with all components set to the given scalar.
	explicit FVector4T(REAL v);
	/// Creates a vector from the given array of values.
	explicit FVector4T(const REAL* pValues);

	//  Conversions --------------------------------------------------

	/// Returns a pointer to the vector's array of values.
	REAL* ptr() { return &x; }
	/// Constant access to the vector's array of values.
	const REAL* ptr() const { return &x; }

	/// Conversion between 4-vectors of different types.
	template<typename T>
	operator FVector4T<T>() const {
		return FVector4T<T>((T)x, (T)y, (T)z, (T)w);
	}

	/// Returns a text representation of the vector.
	QString toString() const;

	//  Access -------------------------------------------------------

	/// Sets the vector's components to the given values.
	void set(REAL x, REAL y, REAL z, REAL w);
	/// Sets all components to the given value.
	void setAll(REAL v);

	/// Index access.
	REAL& operator[](size_t index);
	/// Const index access.
	const REAL& operator[](size_t index) const;
	
	/// Copies the vector's elements to the given array.
	void copyTo(REAL* pValues) const;
	/// Copies the elements from the given array.
	void copyFrom(const REAL* pValues);

	//  Operators ----------------------------------------------------

	/// Component-wise addition of two vectors: Compound-assignment.
	FVector4T<REAL>& operator+=(const FVector4T<REAL>& vec);
	/// Component-wise addition of a scalar: Compound-assignment.
	FVector4T<REAL>& operator+=(REAL scalar);
	/// Component-wise subtraction of two vectors: Compound-assignment.
	FVector4T<REAL>& operator-=(const FVector4T<REAL>& vec);
	/// Component-wise subtraction of a scalar: Compound-assignment.
	FVector4T<REAL>& operator-=(REAL scalar);
	/// Component-wise scalar multiplication: Compound assignment.
	FVector4T<REAL>& operator*=(REAL scalar);
	/// Component-wise scalar division: Compound assignment.
	FVector4T<REAL>& operator/=(REAL scalar);

	/// Returns true if all components of two vectors are equal.
	bool operator==(const FVector4T<REAL>& vec) const;
	/// Returns true if at least one component of the two vectors is different.
	bool operator!=(const FVector4T<REAL>& vec) const;

	//  Public commands ----------------------------------------------

	/// Sets all components of the vector to zero.
	void setZero();
	/// Normalizes the vector to unit length.
	void normalize();
	/// Homogenization of the vector by dividing it by its last component.
	void homogenize();
	/// Projects the vector onto the given vector.
	void project(const FVector4T<REAL>& vec);

	//  Public queries -----------------------------------------------

	/// Returns the 2-norm (length) of the vector.
	REAL length() const;
	/// Returns the squared 2-norm of the vector.
	REAL lengthSquared() const;
	/// Returns the normalized vector (unit length).
	FVector4T<REAL> normalized() const;
	/// Returns the homogenized vector.
	FVector4T<REAL> homogenized() const;
	/// Returns the projection of this vector onto the given vector.
	FVector4T<REAL> projected(const FVector4T<REAL>& vec) const;

	/// Returns the component-wise absolute value.
	FVector4T<REAL> abs() const;
	/// Returns the component-wise square root.
	FVector4T<REAL> sqrt() const;
	/// Returns the component-wise floor (each component rounded down
	/// to the nearest integer).
	FVector4T<REAL> floor() const;
	/// Returns the component-wise ceiling (each component rounded up
	/// to the nearest integer).
	FVector4T<REAL> ceil() const;

	/// Returns the minimum component of the vector.
	REAL min() const;
	/// Returns the maximum component of the vector.
	REAL max() const;
	/// Returns the sum of all components of the vector.
	REAL sum() const;

	/// Returns the dot product of this and the given vector.
	REAL dot(const FVector4T<REAL>& other) const;
	/// Returns the cross product of the first 3 components of this and the
	/// given vector. The 4th component of the result is set to zero.
	FVector4T<REAL> cross(const FVector4T<REAL>& other) const;
	/// Linear interpolation between two vectors.
	FVector4T<REAL> lerp(const FVector4T<REAL>& vec, float factor) const;

	/// Returns true if all components are equal to zero.
	bool allZero() const;
	/// Returns true if all components are equal to one.
	bool allOne() const;

	//  Public data --------------------------------------------------

	REAL x;
	REAL y;
	REAL z;
	REAL w;
};

// Static members --------------------------------------------------------------

template <typename REAL>
const FVector4T<REAL> FVector4T<REAL>::zero(REAL(0.0), REAL(0.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const FVector4T<REAL> FVector4T<REAL>::ones(REAL(1.0), REAL(1.0), REAL(1.0), REAL(1.0));

template <typename REAL>
const FVector4T<REAL> FVector4T<REAL>::unitX(REAL(1.0), REAL(0.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const FVector4T<REAL> FVector4T<REAL>::unitY(REAL(0.0), REAL(1.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const FVector4T<REAL> FVector4T<REAL>::unitZ(REAL(0.0), REAL(0.0), REAL(1.0), REAL(0.0));

template <typename REAL>
const FVector4T<REAL> FVector4T<REAL>::unitW(REAL(0.0), REAL(0.0), REAL(0.0), REAL(1.0));

// Constructors ----------------------------------------------------------------

template <typename REAL>
inline FVector4T<REAL>::FVector4T(REAL _x, REAL _y, REAL _z, REAL _w)
: x(_x), y(_y), z(_z), w(_w)
{
}

template <typename REAL>
inline FVector4T<REAL>::FVector4T(REAL v)
: x(v), y(v), z(v), w(v)
{
}

template <typename REAL>
inline FVector4T<REAL>::FVector4T(const REAL* pValues)
: x(pValues[0]),
  y(pValues[1]),
  z(pValues[2]),
  w(pValues[3])
{
}

// Conversions -----------------------------------------------------------------

template <typename REAL>
inline QString FVector4T<REAL>::toString() const
{
	return QString("[%1, %2, %3, %4]").arg(x).arg(y).arg(z).arg(w);
}

// Access ----------------------------------------------------------------------

template <typename REAL>
inline void FVector4T<REAL>::set(REAL x, REAL y, REAL z, REAL w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template <typename REAL>
inline void FVector4T<REAL>::setAll(REAL scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
	w = scalar;
}

template <typename REAL>
inline REAL& FVector4T<REAL>::operator[](size_t index)
{
	F_ASSERT(index < 4);
	return (&x)[index];
}

template <typename REAL>
inline const REAL& FVector4T<REAL>::operator[](size_t index) const
{
	F_ASSERT(index < 4);
	return (&x)[index];
}

template <typename REAL>
inline void FVector4T<REAL>::copyTo(REAL* pValues) const
{
	pValues[0] = x;
	pValues[1] = y;
	pValues[2] = z;
	pValues[3] = w;
}

template <typename REAL>
inline void FVector4T<REAL>::copyFrom(const REAL* pValues)
{
	x = pValues[0];
	y = pValues[1];
	z = pValues[2];
	w = pValues[3];
}

// Operators -------------------------------------------------------------------

template <typename REAL>
inline FVector4T<REAL>& FVector4T<REAL>::operator+=(const FVector4T<REAL>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}

template <typename REAL>
inline FVector4T<REAL>& FVector4T<REAL>::operator+=(REAL scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
	return *this;
}

template <typename REAL>
inline FVector4T<REAL>& FVector4T<REAL>::operator-=(const FVector4T<REAL>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}

template <typename REAL>
inline FVector4T<REAL>& FVector4T<REAL>::operator-=(REAL scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	return *this;
}

template <typename REAL>
inline FVector4T<REAL>& FVector4T<REAL>::operator*=(REAL scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

template <typename REAL>
inline FVector4T<REAL>& FVector4T<REAL>::operator/=(REAL scalar)
{
	REAL s = (REAL)1.0 / scalar;
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

template <typename REAL>
inline bool FVector4T<REAL>::operator==(const FVector4T<REAL>& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

template <typename REAL>
inline bool FVector4T<REAL>::operator!=(const FVector4T<REAL>& vec) const
{
	return x != vec.x || y != vec.y || z != vec.z || w != vec.w;
}

// Public commands -------------------------------------------------------------

template <typename REAL>
inline void FVector4T<REAL>::setZero()
{
	x = y = z = w = REAL(0.0);
}

template <typename REAL>
inline void FVector4T<REAL>::normalize()
{
	REAL invLength = REAL(1.0) / length();
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
}

template <typename REAL>
inline void FVector4T<REAL>::homogenize()
{
	x /= w;
	y /= w;
	z /= w;
	w = REAL(1.0);
}

template <typename REAL>
inline void FVector4T<REAL>::project(const FVector4T<REAL>& vec)
{
	*this = vec * (this->dot(vec) / vec.lengthSquared());
}

// Public queries --------------------------------------------------------------

template <typename REAL>
inline REAL FVector4T<REAL>::length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

template <typename REAL>
inline REAL FVector4T<REAL>::lengthSquared() const
{
	return x*x + y*y + z*z + w*w;
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::normalized() const
{
	REAL invLength = REAL(1.0) / length();
	return FVector4T<REAL>(
		x * invLength, y * invLength, z * invLength, w * invLength);
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::homogenized() const
{
	return FVector4T<REAL>(x/w, y/w, z/w, REAL(1.0));
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::projected(const FVector4T<REAL>& vec) const
{
	return vec * (this->dot(vec) / vec.lengthSquared());
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::abs() const
{
	return FVector4T<REAL>(fabs(x), fabs(y), fabs(z), fabs(w));
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::sqrt() const
{
	return FVector4T<REAL>(sqrt(x), sqrt(y), sqrt(z), sqrt(w));
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::floor() const
{
	return FVector4T<REAL>(floor(x), floor(y), floor(z), floor(w));
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::ceil() const
{
	return FVector4T<REAL>(ceil(x), ceil(y), ceil(z), ceil(w));
}

template <typename REAL>
inline REAL FVector4T<REAL>::min() const
{
	return x < w ? (x < z ? (x < y ? x : y) : (z < y ? z : y))
		: (w < z ? (w < y ? w : y) : (z < y ? z : y));
}

template <typename REAL>
inline REAL FVector4T<REAL>::max() const
{
	return x > w ? (x > z ? (x > y ? x : y) : (z > y ? z : y))
		: (w > z ? (w > y ? w : y) : (z > y ? z : y));
}

template <typename REAL>
inline REAL FVector4T<REAL>::sum() const
{
	return x + y + z + w;
}

template <typename REAL>
inline REAL FVector4T<REAL>::dot(const FVector4T<REAL>& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::cross(const FVector4T<REAL>& other) const
{
	return FVector4T<REAL>(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x,
		REAL(0.0));
}

template <typename REAL>
inline FVector4T<REAL> FVector4T<REAL>::lerp(const FVector4T<REAL>& vec, float factor) const
{
	return *this + factor * (vec - *this); 
}

template <typename REAL>
inline bool FVector4T<REAL>::allZero() const
{
	return x == REAL(0.0) && y == REAL(0.0) && z == REAL(0.0) && w == REAL(0.0);
}

template <typename REAL>
inline bool FVector4T<REAL>::allOne() const
{
	return x == REAL(1.0) && y == REAL(1.0) && z == REAL(1.0) && w == REAL(1.0);
}

// Related non-member functions ------------------------------------------------

/// Unary minus.
template <typename REAL>
inline FVector4T<REAL> operator-(const FVector4T<REAL>& vec)
{
	return FVector4T<REAL>(-vec.x, -vec.y, -vec.z, -vec.w);
}

/// Addition of two vectors.
template <typename REAL>
inline FVector4T<REAL> operator+(const FVector4T<REAL>& lhs, const FVector4T<REAL>& rhs)
{
	return FVector4T<REAL>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

/// Component-wise addition of a vector and a scalar.
template <typename REAL>
inline FVector4T<REAL> operator+(const FVector4T<REAL>& vec, REAL scalar)
{
	return FVector4T<REAL>(vec.x + scalar, vec.y + scalar, vec.z + scalar, vec.w + scalar);
}

/// Component-wise addition of a scalar and a a vector.
template <typename REAL>
inline FVector4T<REAL> operator+(REAL scalar, const FVector4T<REAL>& vec)
{
	return FVector4T<REAL>(scalar + vec.x, scalar + vec.y, scalar + vec.z, scalar + vec.w);
}

/// Subtraction of two vectors.
template <typename REAL>
inline FVector4T<REAL> operator-(const FVector4T<REAL>& lhs, const FVector4T<REAL>& rhs)
{
	return FVector4T<REAL>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

/// Component-wise subtraction of a vector and a scalar.
template <typename REAL>
inline FVector4T<REAL> operator-(const FVector4T<REAL>& vec, REAL scalar)
{
	return FVector4T<REAL>(vec.x - scalar, vec.y - scalar, vec.z - scalar, vec.w - scalar);
}

/// Component-wise subtraction of a scalar and a vector.
template <typename REAL>
inline FVector4T<REAL> operator-(REAL scalar, const FVector4T<REAL>& vec)
{
	return FVector4T<REAL>(scalar - vec.x, scalar - vec.y, scalar - vec.z, scalar - vec.w);
}

/// Component-wise multiplication of a vector and a scalar.
template <typename REAL>
inline FVector4T<REAL> operator*(const FVector4T<REAL>& vec, REAL scalar)
{
	return FVector4T<REAL>(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

/// Component-wise multiplication of a scalar and a vector.
template <typename REAL>
inline FVector4T<REAL> operator*(REAL scalar, const FVector4T<REAL>& vec)
{
	return FVector4T<REAL>(scalar * vec.x, scalar * vec.y, scalar * vec.z, scalar * vec.w);
}

/// Component-wise division of a vector and a scalar.
template <typename REAL>
inline FVector4T<REAL> operator/(const FVector4T<REAL>& vec, REAL scalar)
{
	REAL inv = REAL(1.0) / scalar;
	return FVector4T<REAL>(vec.x * inv, vec.y * inv, vec.z * inv, vec.w * inv);
}

/// Component-wise division of a scalar and a vector.
template <typename REAL>
inline FVector4T<REAL> operator/(REAL scalar, const FVector4T<REAL>& vec)
{
	return FVector4T<REAL>(scalar / vec.x, scalar / vec.y, scalar / vec.z, scalar / vec.w);
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL operator*(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL fDot(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

/// Cross product of two vectors.
template <typename REAL>
inline FVector4T<REAL> fCross(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return FVector4T<REAL>(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
		REAL(0.0));
}

/// Returns the component-wise minimum of two vectors.
template <typename REAL>
inline FVector4T<REAL> fMin(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return FVector4T<REAL>(
		fMin(v1.x, v2.x), fMin(v1.y, v2.y), fMin(v1.z, v2.z), fMin(v1.w, v2.w));
}

/// Returns the component-wise maximum of two vectors.
template <typename REAL>
inline FVector4T<REAL> fMax(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return FVector4T<REAL>(
		fMax(v1.x, v2.x), fMax(v1.y, v2.y), fMax(v1.z, v2.z), fMax(v1.w, v2.w));
}

/// Linear interpolation between two vectors.
template <typename REAL>
inline FVector4T<REAL> fLerp(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2, REAL factor)
{
	return FVector4T<REAL>(
		v1.x + factor * (v2.x - v1.x),
		v1.y + factor * (v2.y - v1.y),
		v1.z + factor * (v2.z - v1.z),
		v1.w + factor * (v2.w - v1.w));
}

/// Component-wise multiplication of two vectors.
template <typename REAL>
inline FVector4T<REAL> fCompMul(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return FVector4T<REAL>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

/// Component-wise division of two vectors.
template <typename REAL>
inline FVector4T<REAL> fCompDiv(const FVector4T<REAL>& v1, const FVector4T<REAL>& v2)
{
	return FVector4T<REAL>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

/// Writes a text representation of the vector to the given stream.
template <typename REAL, typename C>
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& stream, const FVector4T<REAL>& vec)
{
	stream << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
	return stream;
}

// Typedefs --------------------------------------------------------------------

/// 4-component vector of type float
typedef F_ALIGN(16) FVector4T<float> FVector4f;

/// 4-component vector of type double
typedef FVector4T<double> FVector4d;

/// 4-component vector of type integer
typedef FVector4T<int> FVector4i;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_VECTOR4T_H