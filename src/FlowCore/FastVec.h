// -----------------------------------------------------------------------------
//  File        FastVec.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/19 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_FASTVEC_H
#define FLOWCORE_FASTVEC_H

#include "FlowCore/Library.h"
#include "FlowCore/Intrinsics.h"
#include "FlowCore/Vector4T.h"

// -----------------------------------------------------------------------------
//  Class FFastVec4f
// -----------------------------------------------------------------------------

class FFastVec4f;
class FFastMat4f;

FFastMat4f operator+(const FFastMat4f& v1, const FFastMat4f& v2);
FFastMat4f operator+(const FFastMat4f& mat, float scalar);
FFastMat4f operator+(float scalar, const FFastMat4f& mat);
FFastMat4f operator-(const FFastMat4f& v1, const FFastMat4f& v2);
FFastMat4f operator-(const FFastMat4f& mat, float scalar);
FFastMat4f operator-(float scalar, const FFastMat4f& mat);
FFastMat4f operator*(const FFastMat4f& v1, const FFastMat4f& v2);
FFastVec4f operator*(const FFastMat4f& mat, const FFastVec4f& vec);
FFastVec4f operator*(const FFastVec4f& vec, const FFastMat4f& mat);
FFastMat4f operator*(const FFastMat4f& mat, float scalar);
FFastMat4f operator*(float scalar, const FFastMat4f& mat);
FFastMat4f operator/(const FFastMat4f& mat, float scalar);
FFastMat4f fOuterProduct(const FFastVec4f& v1, const FFastVec4f& v2);


class FLOWCORE_EXPORT FFastVec4f
{
	friend class FFastMat4f;

	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor. Creates an uninitialized vector.
	FFastVec4f() { }
	/// Creates a vector from the given values.
	FFastVec4f(float x, float y, float z, float w);
	/// Creates a vector with all components set to the given scalar.
	explicit FFastVec4f(float v);
	/// Creates a vector from the given array of values.
	explicit FFastVec4f(const float* pValues);
	/// Loads a fast vector with the given vector.
	explicit FFastVec4f(const FVector4f& vec);

private:
	explicit FFastVec4f(__m128 reg);

	//  Conversions and access ---------------------------------------

public:
	/// Conversion to FVector4f.
	operator FVector4f() const;
	/// Returns a text representation of the vector.
	QString toString() const;

	/// Sets the vector's components to the given values.
	void set(float x, float y, float z, float w);
	/// Sets all components to the given value.
	void setAll(float v);
	/// Copies the values from the given FVector4f.
	void set(const FVector4f& vec);

	/// Index access.
	float& operator[](size_t index);
	/// Const index access.
	const float& operator[](size_t index) const;

	/// Copies the vector's components to the given 16-byte aligned array.
	void copyToAligned(float* pValues) const;
	/// Copies the vector's components to the given unaligned array.
	void copyTo(float* pValues) const;
	/// Copies the vector's components from the given 16-byte aligned array.
	void copyFromAligned(const float* pValues);
	/// Copies the vector's components from the given unaligned array.
	void copyFrom(const float* pValues);

	//  Operators ----------------------------------------------------

	/// Component-wise addition of two vectors: Compound-assignment.
	FFastVec4f& operator+=(const FFastVec4f& vec);
	/// Component-wise addition of a scalar: Compound-assignment.
	FFastVec4f& operator+=(float scalar);
	/// Component-wise subtraction of two vectors: Compound-assignment.
	FFastVec4f& operator-=(const FFastVec4f& vec);
	/// Component-wise subtraction of a scalar: Compound-assignment.
	FFastVec4f& operator-=(float scalar);
	/// Component-wise scalar multiplication: Compound assignment.
	FFastVec4f& operator*=(float scalar);
	/// Component-wise scalar division: Compound assignment.
	FFastVec4f& operator/=(float scalar);

	/// Returns true if all components of two vectors are equal.
	bool operator==(const FFastVec4f& vec) const;
	/// Returns true if at least one component of the two vectors is different.
	bool operator!=(const FFastVec4f& vec) const;

	//  Public commands ----------------------------------------------

	/// Sets all components of the vector to zero.
	void setZero();
	/// Normalizes the vector to unit length.
	void normalize();
	/// Homogenization of the vector by dividing it by its last component.
	void homogenize();
	/// Projects the vector onto the given vector.
	void project(const FFastVec4f& vec);

	//  Public queries -----------------------------------------------

	/// Returns the 2-norm (length) of the vector.
	float length() const;
	/// Returns the squared 2-norm of the vector.
	float lengthSquared() const;
	/// Returns the normalized vector (unit length).
	FFastVec4f normalized() const;
	/// Returns the homogenized vector.
	FFastVec4f homogenized() const;
	/// Returns the projection of this vector onto the given vector.
	FFastVec4f projected(const FFastVec4f& vec) const;

	/// Returns the component-wise absolute value.
	FFastVec4f abs() const;
	/// Returns the component-wise square root.
	FFastVec4f sqrt() const;
	/// Returns the component-wise floor (each component rounded down
	/// to the nearest integer).
	FFastVec4f floor() const;
	/// Returns the component-wise ceiling (each component rounded up
	/// to the nearest integer).
	FFastVec4f ceil() const;

	/// Returns the minimum component of the vector.
	float min() const;
	/// Returns the maximum component of the vector.
	float max() const;
	/// Returns the sum of all components of the vector.
	float sum() const;

	/// Returns the dot product of this and the given vector.
	float dot(const FFastVec4f& vec) const;
	/// Returns the cross product of the first 3 components of this and the
	/// given vector. The 4th component of the result is set to zero.
	FFastVec4f cross(const FFastVec4f& vec) const;
	/// Linear interpolation between two vectors.
	FFastVec4f lerp(const FFastVec4f& vec, float factor) const;

	//  Related non-member functions ---------------------------------

	/// Unary minus.
	friend FFastVec4f operator-(const FFastVec4f& vec);
	/// Addition of two vectors.
	friend FFastVec4f operator+(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Component-wise addition of a vector and a scalar.
	friend FFastVec4f operator+(const FFastVec4f& vec, float scalar);
	/// Component-wise addition of a scalar and a vector.
	friend FFastVec4f operator+(float scalar, const FFastVec4f& vec);
	/// Subtraction of two vectors.
	friend FFastVec4f operator-(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Component-wise subtraction of a vector and a scalar.
	friend FFastVec4f operator-(const FFastVec4f& vec, float scalar);
	/// Component-wise subtraction of a scalar and a vector.
	friend FFastVec4f operator-(float scalar, const FFastVec4f& vec);
	/// Component-wise multiplication of a vector and a scalar.
	friend FFastVec4f operator*(const FFastVec4f& vec, float scalar);
	/// Component-wise multiplication of a scalar and a vector.
	friend FFastVec4f operator*(float scalar, const FFastVec4f& vec);
	/// Component-wise division of a vector and a scalar.
	friend FFastVec4f operator/(const FFastVec4f& vec, float scalar);
	/// Component-wise division of a scalar and a vector.
	friend FFastVec4f operator/(float scalar, const FFastVec4f& vec);
	/// Dot product (inner products) of two vectors.
	friend float operator*(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Dot product (inner product) of two vectors.
	friend float fDot(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Cross product (outer product) of two vectors.
	friend FFastVec4f fCross(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Returns the component-wise minimum of two vectors.
	friend FFastVec4f fMin(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Returns the component-wise maximum of two vectors.
	friend FFastVec4f fMax(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Linear interpolation between two vectors.
	friend FFastVec4f fLerp(const FFastVec4f& v1, const FFastVec4f& v2, float factor);
	/// Component-wise multiplication of two vectors.
	friend FFastVec4f fCompMul(const FFastVec4f& v1, const FFastVec4f& v2);
	/// Component-wise division of two vectors.
	friend FFastVec4f fCompDiv(const FFastVec4f& v1, const FFastVec4f& v2);

	//  Implemented in FFastMat4f ------------------------------------

	/// Component-wise addition of two matrices.
	friend FFastMat4f operator+(const FFastMat4f& v1, const FFastMat4f& v2);
	/// Component-wise addition of a matrix and a scalar.
	friend FFastMat4f operator+(const FFastMat4f& mat, float scalar);
	/// Component-wise addition of a scalar and a matrix.
	friend FFastMat4f operator+(float scalar, const FFastMat4f& mat);
	/// Component-wise subtraction of two matrices.
	friend FFastMat4f operator-(const FFastMat4f& v1, const FFastMat4f& v2);
	/// Component-wise subtraction of a scalar from a matrix.
	friend FFastMat4f operator-(const FFastMat4f& mat, float scalar);
	/// Component-wise subtraction of a matrix from a scalar.
	friend FFastMat4f operator-(float scalar, const FFastMat4f& mat);
	/// Matrix-matrix multiplication.
	friend FFastMat4f operator*(const FFastMat4f& v1, const FFastMat4f& v2);
	/// Matrix-vector multiplication.
	friend FFastVec4f operator*(const FFastMat4f& mat, const FFastVec4f& vec);
	/// Vector-matrix multiplication.
	friend FFastVec4f operator*(const FFastVec4f& vec, const FFastMat4f& mat);
	/// Component-wise multiplication of a matrix with a scalar.
	friend FFastMat4f operator*(const FFastMat4f& mat, float scalar);
	/// Component-wise multiplication of a scalar with a matrix.
	friend FFastMat4f operator*(float scalar, const FFastMat4f& mat);
	/// Component-wise division of a matrix by a scalar.
	friend FFastMat4f operator/(const FFastMat4f& mat, float scalar);
	/// Outer product of two vectors.
	friend FFastMat4f fOuterProduct(const FFastVec4f& v1, const FFastVec4f& v2);

	//  Internal data members ----------------------------------------

private:
	__m128 m_reg;
};

// Constructors ----------------------------------------------------------------

inline FFastVec4f::FFastVec4f(float x, float y, float z, float w)
{
	F_ALIGN(16) float vec[4] = { x, y, z, w };
	m_reg = _mm_load_ps(vec);
}

inline FFastVec4f::FFastVec4f(float v)
{
	m_reg = _mm_load_ps1(&v);
}

inline FFastVec4f::FFastVec4f(const float* pValues)
{
	m_reg = _mm_load_ps(pValues);
}

inline FFastVec4f::FFastVec4f(const FVector4f& vec)
{
	m_reg = _mm_load_ps(vec.ptr());
}

inline FFastVec4f::FFastVec4f(__m128 reg)
{
	m_reg = reg;
}

// Conversion ------------------------------------------------------------------

inline FFastVec4f::operator FVector4f() const
{
	FVector4f result;
	copyToAligned(result.ptr());
	return result;
}

inline QString FFastVec4f::toString() const
{
	return FVector4f(*this).toString();
}

// Access ----------------------------------------------------------------------

inline void FFastVec4f::set(float x, float y, float z, float w)
{
	F_ALIGN(16) float vec[4] = { x, y, z, w };
	m_reg = _mm_load_ps(vec);
	//m_reg = _mm_set_ps(w, z, y, x);
}

inline void FFastVec4f::setAll(float v)
{
	m_reg = _mm_set_ss(v);
}

inline void FFastVec4f::set(const FVector4f& vec)
{
	m_reg = _mm_load_ps(vec.ptr());
}

inline float& FFastVec4f::operator[](size_t index)
{
	F_ASSERT(index < 4);
	return F_MM_GET_ELEM(m_reg, index);
}

inline const float& FFastVec4f::operator[](size_t index) const
{
	F_ASSERT(index < 4);
	return F_MM_GET_ELEM(m_reg, index);
}

inline void FFastVec4f::copyToAligned(float* pValues) const
{
	_mm_store_ps(pValues, m_reg);
}

inline void FFastVec4f::copyTo(float* pValues) const
{
	_mm_storeu_ps(pValues, m_reg);
}

inline void FFastVec4f::copyFromAligned(const float* pValues)
{
	m_reg = _mm_load_ps(pValues);
}

inline void FFastVec4f::copyFrom(const float* pValues)
{
	m_reg = _mm_loadu_ps(pValues);
}

// Operators -------------------------------------------------------------------

inline FFastVec4f& FFastVec4f::operator+=(const FFastVec4f& vec) {
	m_reg = _mm_add_ps(m_reg, vec.m_reg);
	return *this;
}

inline FFastVec4f& FFastVec4f::operator+=(float scalar) {
	__m128 s = _mm_load_ps1(&scalar);
	m_reg = _mm_add_ps(m_reg, s);
	return *this;
}

inline FFastVec4f& FFastVec4f::operator-=(const FFastVec4f& vec) {
	m_reg = _mm_sub_ps(m_reg, vec.m_reg);
	return *this;
}

inline FFastVec4f& FFastVec4f::operator-=(float scalar) {
	__m128 s = _mm_load_ps1(&scalar);
	m_reg = _mm_sub_ps(m_reg, s);
	return *this;
}

inline FFastVec4f& FFastVec4f::operator*=(float scalar) {
	__m128 s = _mm_load_ps1(&scalar);
	m_reg = _mm_mul_ps(m_reg, s);
	return *this;
}

inline FFastVec4f& FFastVec4f::operator/=(float scalar) {
	__m128 s = _mm_load_ps1(&scalar);
	m_reg = _mm_div_ps(m_reg, s);
	return *this;
}

inline bool FFastVec4f::operator==(const FFastVec4f& vec) const {
	F_ASSERT(false);
	// TODO: Implement!!
	__m128 t0 = _mm_cmpeq_ps(m_reg, vec.m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	__m128 t2 = _mm_hadd_ps(t1, t1);
}

inline bool FFastVec4f::operator!=(const FFastVec4f& vec) const {
	return !(*this == vec);
}

// Public commands -------------------------------------------------------------

inline void FFastVec4f::setZero()
{
	m_reg = _mm_setzero_ps();
}

inline void FFastVec4f::normalize()
{
	__m128 t0 = _mm_mul_ps(m_reg, m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	__m128 t2 = _mm_hadd_ps(t1, t1);
	__m128 t3 = _mm_sqrt_ss(t2);
	__m128 t4 = _mm_shuffle_ps(t3, t3, _MM_SHUFFLE(0, 0, 0, 0));
	m_reg = _mm_div_ps(m_reg, t4);
}

inline void FFastVec4f::homogenize()
{
	__m128 t0 = _mm_shuffle_ps(m_reg, m_reg, _MM_SHUFFLE(3, 3, 3, 3));
	m_reg = _mm_div_ps(m_reg, t0);
}

inline void FFastVec4f::project(const FFastVec4f& vec)
{
	*this = vec * (this->dot(vec) / vec.lengthSquared());
}

// Public queries --------------------------------------------------------------

inline float FFastVec4f::length() const
{
	__m128 t0 = _mm_mul_ps(m_reg, m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	__m128 t2 = _mm_hadd_ps(t1, t1);
	__m128 t3 = _mm_sqrt_ss(t2);

	float result;
	_mm_store_ss(&result, t3);
	return result;
}

inline float FFastVec4f::lengthSquared() const
{
	__m128 t0 = _mm_mul_ps(m_reg, m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	__m128 t2 = _mm_hadd_ps(t1, t1);

	float result;
	_mm_store_ss(&result, t2);
	return result;
}

inline FFastVec4f FFastVec4f::normalized() const
{
	FFastVec4f t(*this);
	t.normalize();
	return t;
}

inline FFastVec4f FFastVec4f::homogenized() const
{
	FFastVec4f t(*this);
	t.homogenize();
	return t;
}

inline FFastVec4f FFastVec4f::projected(const FFastVec4f& vec) const
{
	return vec * (this->dot(vec) / vec.lengthSquared());
}

inline FFastVec4f FFastVec4f::abs() const
{
	__m128 t0 = _mm_set_ps1(-1.0f);
	__m128 t1 = _mm_mul_ps(m_reg, t0);
	__m128 t2 = _mm_max_ps(m_reg, t1);
	return FFastVec4f(t2);
}

inline FFastVec4f FFastVec4f::sqrt() const
{
	return FFastVec4f(_mm_sqrt_ps(m_reg));
}

inline FFastVec4f FFastVec4f::floor() const
{
	return FFastVec4f(_mm_floor_ps(m_reg));
}

inline FFastVec4f FFastVec4f::ceil() const
{
	return FFastVec4f(_mm_ceil_ps(m_reg));
} 

inline float FFastVec4f::min() const
{
	__m128 t0 = _mm_shuffle_ps(m_reg, m_reg, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 t1 = _mm_min_ps(m_reg, t0);
	__m128 t2 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	__m128 t3 = _mm_min_ps(t1, t2);
	float result;
	_mm_store_ss(&result, t3);
	return result;
}

inline float FFastVec4f::max() const
{
	__m128 t0 = _mm_shuffle_ps(m_reg, m_reg, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 t1 = _mm_max_ps(m_reg, t0);
	__m128 t2 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	__m128 t3 = _mm_max_ps(t1, t2);
	float result;
	_mm_store_ss(&result, t3);
	return result;
}

inline float FFastVec4f::sum() const
{
	__m128 t0 = _mm_hadd_ps(m_reg, m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	float result;
	_mm_store_ss(&result, t1);
	return result;
}

inline float FFastVec4f::dot(const FFastVec4f& vec) const
{
	__m128 t0 = _mm_mul_ps(m_reg, vec.m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	__m128 t2 = _mm_hadd_ps(t1, t1);
	float result;
	_mm_store_ss(&result, t2);
	return result;
}

inline FFastVec4f FFastVec4f::cross(const FFastVec4f& vec) const
{
	__m128 t0 = _mm_shuffle_ps(m_reg, m_reg, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 t1 = _mm_shuffle_ps(m_reg, m_reg, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 t2 = _mm_shuffle_ps(vec.m_reg, vec.m_reg, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 t3 = _mm_shuffle_ps(vec.m_reg, vec.m_reg, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 t4 = _mm_mul_ps(t0, t2);
	__m128 t5 = _mm_mul_ps(t1, t3);
	__m128 t6 = _mm_sub_ps(t4, t5);
	return FFastVec4f(t6);
}

inline FFastVec4f FFastVec4f::lerp(const FFastVec4f& vec, float factor) const
{
	return *this + factor * (vec - *this);
}

// Related non-member functions ------------------------------------------------

inline FFastVec4f operator-(const FFastVec4f& vec)
{
	__m128 t = _mm_load_ps((float*)_fSignNNNN);
	return FFastVec4f(_mm_xor_ps(vec.m_reg, t));
}

inline FFastVec4f operator+(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return FFastVec4f(_mm_add_ps(v1.m_reg, v2.m_reg));
}

inline FFastVec4f operator+(const FFastVec4f& vec, float scalar)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_add_ps(vec.m_reg, t));
} 

inline FFastVec4f operator+(float scalar, const FFastVec4f& vec)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_add_ps(t, vec.m_reg));
}

inline FFastVec4f operator-(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return FFastVec4f(_mm_sub_ps(v1.m_reg, v2.m_reg));
}

inline FFastVec4f operator-(const FFastVec4f& vec, float scalar)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_sub_ps(vec.m_reg, t));
}

inline FFastVec4f operator-(float scalar, const FFastVec4f& vec)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_sub_ps(t, vec.m_reg));
}

inline FFastVec4f operator*(const FFastVec4f& vec, float scalar)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_mul_ps(vec.m_reg, t));
}

inline FFastVec4f operator*(float scalar, const FFastVec4f& vec)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_mul_ps(t, vec.m_reg));
}

inline FFastVec4f operator/(const FFastVec4f& vec, float scalar)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_div_ps(vec.m_reg, t));
}

inline FFastVec4f operator/(float scalar, const FFastVec4f& vec)
{
	__m128 t = _mm_load_ps1(&scalar);
	return FFastVec4f(_mm_div_ps(t, vec.m_reg));
}

inline float operator*(const FFastVec4f& v1, const FFastVec4f& v2)
{
	__m128 t0 = _mm_mul_ps(v1.m_reg, v2.m_reg);
	__m128 t1 = _mm_hadd_ps(t0, t0);
	__m128 t2 = _mm_hadd_ps(t1, t1);
	float result;
	_mm_store_ss(&result, t2);
	return result;
}

inline float fDot(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return v1 * v2;
}

inline FFastVec4f fCross(const FFastVec4f& v1, const FFastVec4f& v2)
{
	__m128 t0 = _mm_shuffle_ps(v1.m_reg, v1.m_reg, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 t1 = _mm_shuffle_ps(v1.m_reg, v1.m_reg, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 t2 = _mm_shuffle_ps(v2.m_reg, v2.m_reg, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 t3 = _mm_shuffle_ps(v2.m_reg, v2.m_reg, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 t4 = _mm_mul_ps(t0, t2);
	__m128 t5 = _mm_mul_ps(t1, t3);
	__m128 t6 = _mm_sub_ps(t4, t5);
	return FFastVec4f(t6);
}

inline FFastVec4f fMin(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return FFastVec4f(_mm_min_ps(v1.m_reg, v2.m_reg));
}

inline FFastVec4f fMax(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return FFastVec4f(_mm_max_ps(v1.m_reg, v2.m_reg));
}

inline FFastVec4f fLerp(const FFastVec4f& v1, const FFastVec4f& v2, float factor)
{
	return v1 + factor * (v2 - v1);
}

inline FFastVec4f fCompMul(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return FFastVec4f(_mm_mul_ps(v1.m_reg, v2.m_reg));
}

inline FFastVec4f fCompDiv(const FFastVec4f& v1, const FFastVec4f& v2)
{
	return FFastVec4f(_mm_div_ps(v1.m_reg, v2.m_reg));
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_FASTVEC_H