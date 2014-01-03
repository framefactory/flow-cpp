// -----------------------------------------------------------------------------
//  File        FastMat.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/19 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_FASTMAT_H
#define FLOWCORE_FASTMAT_H

#include "FlowCore/Library.h"
#include "FlowCore/Intrinsics.h"
#include "FlowCore/FastVec.h"
#include "FlowCore/Vector4T.h"
#include "FlowCore/Matrix4T.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FFastMat4f
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FFastMat4f
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor. Creates an uninitialized matrix.
	FFastMat4f() { }
	/// Creates a matrix from the given elements.
	FFastMat4f(float m00, float m01, float m02, float m03,
	           float m10, float m11, float m12, float m13,
			   float m20, float m21, float m22, float m23,
			   float m30, float m31, float m32, float m33);
	/// Creates a matrix from the given 16-byte aligned float array.
	FFastMat4f(const float* pValues);
	/// Creates a matrix from the given row vectors.
	FFastMat4f(const FFastVec4f& row0, const FFastVec4f& row1,
	           const FFastVec4f& row2, const FFastVec4f& row3);
	/// Creates a matrix from the given row vectors.
	FFastMat4f(const FVector4f& row0, const FVector4f& row1,
	           const FVector4f& row2, const FVector4f& row3);
	/// Creates a matrix from the given matrix.
	explicit FFastMat4f(const FMatrix4f& mat);

private:
	FFastMat4f(const __m128& row0, const __m128& row1, 
	           const __m128& row2, const __m128& row3);

	//  Access -------------------------------------------------------

public:
	/// Conversion to FMatrix4f.
	operator FMatrix4f() const;
	/// Returns a text representation of the matrix.
	QString toString() const;

	/// Sets all components of the matrix to the given values.
	void set(float m00, float m01, float m02, float m03,
	         float m10, float m11, float m12, float m13,
			 float m20, float m21, float m22, float m23,
			 float m30, float m31, float m32, float m33);
	/// Sets all rows of the matrix to the given values.
	void set(const FFastVec4f& row0, const FFastVec4f& row1,
	         const FFastVec4f& row2, const FFastVec4f& row3);

	void set(const FVector4f& row0, const FVector4f& row1,
	         const FVector4f& row2, const FVector4f& row3);

	void set(const FMatrix4f& mat);

	/// Replaces a row by the given vector.
	void setRow(const FFastVec4f& vec, size_t index);
	/// Replaces a row by the given vector.
	void setRow(const FVector4f& vec, size_t index);
	/// Replaces a column by the given vector.
	void setColumn(const FFastVec4f& vec,size_t index);
	/// Replaces a column by the given vector.
	void setColumn(const FVector4f& vec,size_t index);

	/// Returns the row vector at the given index.
	const FFastVec4f& row(size_t index);
	/// Returns the column vector at the given index.
	const FFastVec4f column(size_t idnex);

	/// Read/write access to the row with the given index in the range [0; 3].
	FFastVec4f& operator[](size_t rowIndex);
	/// Const access to the row with the given index in the range [0; 3].
	const FFastVec4f& operator[](size_t rowIndex) const;
	/// Read/write access to the row with the given index in the range [0; 3].
	float& operator()(size_t rowIndex, size_t columnIndex);
	/// Const access to the row with the given index in the range [0; 3].
	const float& operator()(size_t rowIndex, size_t columnIndex) const;

	/// Writes the matrix' values to the given 16-byte aligned float array.
	void copyToAligned(float* pValues) const;
	/// Writes the matrix' values to the given unaligned float array.
	void copyTo(float* pValues) const;
	/// Replaces the matrix' values by the values of the given 16-byte aligned float array.
	void copyFromAligned(const float* pValues);
	/// Replaces the matrix' values by the values of the given unaligned float array.
	void copyFrom(const float* pValues);

	//  Operators ----------------------------------------------------

	/// Component-wise addition of the right-hand matrix.
	FFastMat4f& operator+=(const FFastMat4f& mat);
	/// Component-wise addition of the right-hand scalar.
	FFastMat4f& operator+=(float scalar);
	/// Component-wise subtraction of the right-hand matrix.
	FFastMat4f& operator-=(const FFastMat4f& mat);
	/// Component-wise addition of the right-hand scalar.
	FFastMat4f& operator-=(float scalar);
	/// Matrix-matrix multiplication.
	FFastMat4f& operator*=(const FFastMat4f& rhs);
	/// Component-wise multiplication of the right-hand scalar.
	FFastMat4f& operator*=(float scalar);
	/// Component-wise division by the right-hand scalar.
	FFastMat4f& operator/=(float scalar);

	//  Public commands ----------------------------------------------

	/// Transposes the matrix, i.e. inverts rows and columns.
	void transpose();
	/// Inverts the matrix.
	void invert();

	//  Public queries -----------------------------------------------

	/// Returns the transposed matrix.
	FFastMat4f transposed() const;
	/// Returns the inverse of the matrix.
	FFastMat4f inverse() const;
	/// Returns the determinant of the matrix.
	float determinant() const;

	//  Related non-member functions ---------------------------------

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
	FFastVec4f m_row[4];
};

// Constructors ----------------------------------------------------------------

inline FFastMat4f::FFastMat4f(float m00, float m01, float m02, float m03,
	                          float m10, float m11, float m12, float m13,
	                          float m20, float m21, float m22, float m23,
	                          float m30, float m31, float m32, float m33)
{
	m_row[0].set(m00, m01, m02, m03);
	m_row[1].set(m10, m11, m12, m13);
	m_row[2].set(m20, m21, m22, m23);
	m_row[3].set(m30, m31, m32, m33);
}

inline FFastMat4f::FFastMat4f(const float* pValues)
{
	m_row[0].copyFrom(pValues);
	m_row[1].copyFrom(pValues + 4);
	m_row[2].copyFrom(pValues + 8);
	m_row[3].copyFrom(pValues + 12);
}

inline FFastMat4f::FFastMat4f(const FFastVec4f& row0, const FFastVec4f& row1,
	                          const FFastVec4f& row2, const FFastVec4f& row3)
{
	m_row[0].m_reg = row0.m_reg;
	m_row[1].m_reg = row1.m_reg;
	m_row[2].m_reg = row2.m_reg;
	m_row[3].m_reg = row3.m_reg;
}

inline FFastMat4f::FFastMat4f(const FVector4f& row0, const FVector4f& row1,
	                          const FVector4f& row2, const FVector4f& row3)
{
	m_row[0].set(row0);
	m_row[1].set(row1);
	m_row[2].set(row2);
	m_row[3].set(row3);
}

inline FFastMat4f::FFastMat4f(const FMatrix4f& mat)
{
	m_row[0].set(mat.row(0));
	m_row[1].set(mat.row(1));
	m_row[2].set(mat.row(2));
	m_row[3].set(mat.row(3));
}

inline FFastMat4f::FFastMat4f(const __m128& row0, const __m128& row1, 
		                      const __m128& row2, const __m128& row3)
{
	m_row[0].m_reg = row0;
	m_row[1].m_reg = row1;
	m_row[2].m_reg = row2;
	m_row[3].m_reg = row3;
}

// Conversion ------------------------------------------------------------------

inline FFastMat4f::operator FMatrix4f() const
{
	FMatrix4f result;
	copyToAligned(result.ptr());
	return result;
}

inline QString FFastMat4f::toString() const
{
	return FMatrix4f(*this).toString();
}

// Access ----------------------------------------------------------------------

inline void FFastMat4f::set(float m00, float m01, float m02, float m03,
	                        float m10, float m11, float m12, float m13,
	                        float m20, float m21, float m22, float m23,
	                        float m30, float m31, float m32, float m33)
{
	m_row[0].set(m00, m01, m02, m03);
	m_row[1].set(m10, m11, m12, m13);
	m_row[2].set(m20, m21, m22, m23);
	m_row[3].set(m30, m31, m32, m33);
}

inline void FFastMat4f::set(const FFastVec4f& row0, const FFastVec4f& row1,
	                        const FFastVec4f& row2, const FFastVec4f& row3)
{
	m_row[0].m_reg = row0.m_reg;
	m_row[1].m_reg = row1.m_reg;
	m_row[2].m_reg = row2.m_reg;
	m_row[3].m_reg = row3.m_reg;
}

inline void FFastMat4f::set(const FVector4f& row0, const FVector4f& row1,
	                        const FVector4f& row2, const FVector4f& row3)
{
	m_row[0].set(row0);
	m_row[1].set(row1);
	m_row[2].set(row2);
	m_row[3].set(row3);
}

inline void FFastMat4f::set(const FMatrix4f& mat)
{
	m_row[0].set(mat.row(0));
	m_row[1].set(mat.row(1));
	m_row[2].set(mat.row(2));
	m_row[3].set(mat.row(3));
}

inline void FFastMat4f::setRow(const FFastVec4f& vec, size_t index)
{
	F_ASSERT(index < 4);
	m_row[index].m_reg = vec.m_reg;
}

inline void FFastMat4f::setRow(const FVector4f& vec, size_t index)
{
	F_ASSERT(index < 4);
	m_row[index].set(vec);
}

inline void FFastMat4f::setColumn(const FFastVec4f& vec,size_t index)
{
	F_ASSERT(index < 4);
	m_row[0][index] = vec[0];
	m_row[1][index] = vec[1];
	m_row[2][index] = vec[2];
	m_row[3][index] = vec[3];
}

inline void FFastMat4f::setColumn(const FVector4f& vec,size_t index)
{
	F_ASSERT(index < 4);
	m_row[0][index] = vec[0];
	m_row[1][index] = vec[1];
	m_row[2][index] = vec[2];
	m_row[3][index] = vec[3];
}

inline const FFastVec4f& FFastMat4f::row(size_t index)
{
	F_ASSERT(index < 4);
	return m_row[index];
}

inline const FFastVec4f FFastMat4f::column(size_t index)
{
	F_ASSERT(index < 4);
	return FFastVec4f(m_row[0][index], m_row[1][index],
		              m_row[2][index], m_row[3][index]);
}

inline FFastVec4f& FFastMat4f::operator[](size_t index)
{
	F_ASSERT(index < 4);
	return m_row[index];
}

inline const FFastVec4f& FFastMat4f::operator[](size_t index) const
{
	F_ASSERT(index < 4);
	return m_row[index];
}

inline float& FFastMat4f::operator()(size_t rowIndex, size_t columnIndex)
{
	F_ASSERT(rowIndex < 4 && columnIndex << 4);
	return m_row[rowIndex][columnIndex];
}

inline const float& FFastMat4f::operator()(size_t rowIndex, size_t columnIndex) const
{
	F_ASSERT(rowIndex < 4 && columnIndex << 4);
	return m_row[rowIndex][columnIndex];
}

inline void FFastMat4f::copyToAligned(float* pValues) const
{
	m_row[0].copyToAligned(pValues     );
	m_row[1].copyToAligned(pValues +  4);
	m_row[2].copyToAligned(pValues +  8);
	m_row[3].copyToAligned(pValues + 12);
}

inline void FFastMat4f::copyTo(float* pValues) const
{
	m_row[0].copyTo(pValues     );
	m_row[1].copyTo(pValues +  4);
	m_row[2].copyTo(pValues +  8);
	m_row[3].copyTo(pValues + 12);
}

inline void FFastMat4f::copyFromAligned(const float* pValues)
{
	m_row[0].copyFromAligned(pValues     );
	m_row[1].copyFromAligned(pValues +  4);
	m_row[2].copyFromAligned(pValues +  8);
	m_row[3].copyFromAligned(pValues + 12);
}

inline void FFastMat4f::copyFrom(const float* pValues)
{
	m_row[0].copyFrom(pValues     );
	m_row[1].copyFrom(pValues +  4);
	m_row[2].copyFrom(pValues +  8);
	m_row[3].copyFrom(pValues + 12);
}

// Operators -------------------------------------------------------------------

inline FFastMat4f& FFastMat4f::operator+=(const FFastMat4f& mat)
{
	m_row[0].m_reg = _mm_add_ps(m_row[0].m_reg, mat.m_row[0].m_reg);
	m_row[1].m_reg = _mm_add_ps(m_row[1].m_reg, mat.m_row[1].m_reg);
	m_row[2].m_reg = _mm_add_ps(m_row[2].m_reg, mat.m_row[2].m_reg);
	m_row[3].m_reg = _mm_add_ps(m_row[3].m_reg, mat.m_row[3].m_reg);

	return *this;
}

inline FFastMat4f& FFastMat4f::operator+=(float scalar)
{
	__m128 t0 = _mm_set_ps1(scalar);

	m_row[0].m_reg = _mm_add_ps(m_row[0].m_reg, t0);
	m_row[1].m_reg = _mm_add_ps(m_row[1].m_reg, t0);
	m_row[2].m_reg = _mm_add_ps(m_row[2].m_reg, t0);
	m_row[3].m_reg = _mm_add_ps(m_row[3].m_reg, t0);

	return *this;
}

inline FFastMat4f& FFastMat4f::operator-=(const FFastMat4f& mat)
{
	m_row[0].m_reg = _mm_sub_ps(m_row[0].m_reg, mat.m_row[0].m_reg);
	m_row[1].m_reg = _mm_sub_ps(m_row[1].m_reg, mat.m_row[1].m_reg);
	m_row[2].m_reg = _mm_sub_ps(m_row[2].m_reg, mat.m_row[2].m_reg);
	m_row[3].m_reg = _mm_sub_ps(m_row[3].m_reg, mat.m_row[3].m_reg);
	
	return *this;
}

inline FFastMat4f& FFastMat4f::operator-=(float scalar)
{
	__m128 t0 = _mm_set_ps1(scalar);

	m_row[0].m_reg = _mm_sub_ps(m_row[0].m_reg, t0);
	m_row[1].m_reg = _mm_sub_ps(m_row[1].m_reg, t0);
	m_row[2].m_reg = _mm_sub_ps(m_row[2].m_reg, t0);
	m_row[3].m_reg = _mm_sub_ps(m_row[3].m_reg, t0);
	
	return *this;
}

inline FFastMat4f& FFastMat4f::operator*=(const FFastMat4f& mat)
{
	*this = *this * mat;
    return *this;
}

inline FFastMat4f& FFastMat4f::operator*=(float scalar)
{
	__m128 t0 = _mm_set_ps1(scalar);

	m_row[0].m_reg = _mm_mul_ps(m_row[0].m_reg, t0);
	m_row[1].m_reg = _mm_mul_ps(m_row[1].m_reg, t0);
	m_row[2].m_reg = _mm_mul_ps(m_row[2].m_reg, t0);
	m_row[3].m_reg = _mm_mul_ps(m_row[3].m_reg, t0);
	
	return *this;
}

inline FFastMat4f& FFastMat4f::operator/=(float scalar)
{
	__m128 t0 = _mm_set_ps1(scalar);

	m_row[0].m_reg = _mm_div_ps(m_row[0].m_reg, t0);
	m_row[1].m_reg = _mm_div_ps(m_row[1].m_reg, t0);
	m_row[2].m_reg = _mm_div_ps(m_row[2].m_reg, t0);
	m_row[3].m_reg = _mm_div_ps(m_row[3].m_reg, t0);
	
	return *this;
}

// Public commands -------------------------------------------------------------

inline void FFastMat4f::transpose()
{
	_MM_TRANSPOSE4_PS(m_row[0].m_reg, m_row[1].m_reg, 
		              m_row[2].m_reg, m_row[3].m_reg);
}

inline void FFastMat4f::invert()
{
	*this = inverse();
}

// Public queries --------------------------------------------------------------

inline FFastMat4f FFastMat4f::transposed() const
{
	FFastMat4f result(*this);
	result.transpose();
	return result;
}

inline FFastMat4f FFastMat4f::inverse() const
{
	__m128 minor0, minor1, minor2, minor3;
	__m128 row0, row1, row2, row3;
	__m128 det, tmp1;

	row0 = m_row[0].m_reg;
	row1 = m_row[1].m_reg;
	row2 = m_row[2].m_reg;
	row3 = m_row[3].m_reg;

	tmp1 = _mm_mul_ps(row2, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor0 = _mm_mul_ps(row1, tmp1);
	minor1 = _mm_mul_ps(row0, tmp1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

	tmp1 = _mm_mul_ps(row1, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
	minor3 = _mm_mul_ps(row0, tmp1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

	tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);
	minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
	minor2 = _mm_mul_ps(row0, tmp1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

	tmp1 = _mm_mul_ps(row0, row1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));

	tmp1 = _mm_mul_ps(row0, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));

	tmp1 = _mm_mul_ps(row0, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);

	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
	tmp1 = _mm_rcp_ss(det);
	det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
	det = _mm_shuffle_ps(det, det, 0x00);

	return FFastMat4f(_mm_mul_ps(det, minor0),
		              _mm_mul_ps(det, minor1),
					  _mm_mul_ps(det, minor2),
					  _mm_mul_ps(det, minor3));
}

inline float FFastMat4f::determinant() const
{
	__m128 tmp00,tmp01,tmp02,tmp03,tmp04,tmp05,tmp06,tmp07,tmp08,tmp09,
		tmp10,tmp11,tmp12,tmp13,tmp14,tmp15, tmp16;

	tmp00 = _mm_shuffle_ps(m_row[3].m_reg, m_row[3].m_reg, F_MM_SHUFFLE4(1,2,3,0));
	tmp01 = _mm_shuffle_ps(m_row[3].m_reg, m_row[3].m_reg, F_MM_SHUFFLE4(2,3,0,1));
	tmp02 = _mm_shuffle_ps(m_row[3].m_reg, m_row[3].m_reg, F_MM_SHUFFLE4(3,0,1,2));

	tmp00 = _mm_mul_ps(m_row[2].m_reg, tmp00);
	tmp01 = _mm_mul_ps(m_row[2].m_reg, tmp01);
	tmp02 = _mm_mul_ps(m_row[2].m_reg, tmp02);

	tmp03 = _mm_sub_ps(tmp00, _mm_shuffle_ps(tmp02, tmp02, F_MM_SHUFFLE4(1,2,3,0))); 
	tmp04 = _mm_sub_ps(tmp01, _mm_shuffle_ps(tmp01, tmp01, F_MM_SHUFFLE4(2,3,0,1))); 

	tmp05 = _mm_shuffle_ps(m_row[1].m_reg, m_row[1].m_reg, F_MM_SHUFFLE4(1,0,1,0));
	tmp06 = _mm_shuffle_ps(m_row[1].m_reg, m_row[1].m_reg, F_MM_SHUFFLE4(2,3,0,1));
	tmp07 = _mm_shuffle_ps(m_row[1].m_reg, m_row[1].m_reg, F_MM_SHUFFLE4(3,2,3,2));

	tmp08 = _mm_shuffle_ps(tmp03, tmp03, F_MM_SHUFFLE4(2,2,3,1));
	tmp09 = _mm_shuffle_ps(tmp04, tmp04, F_MM_SHUFFLE4(3,0,1,2));
	tmp10 = _mm_shuffle_ps(tmp03, tmp03, F_MM_SHUFFLE4(1,3,0,0));

	tmp11 = _mm_mul_ps(tmp05, tmp08);
	tmp12 = _mm_mul_ps(tmp06, tmp09);
	tmp13 = _mm_mul_ps(tmp07, tmp10);

	tmp14 = _mm_add_ps(tmp11, _mm_add_ps(tmp12,tmp13));
	tmp15 = _mm_mul_ps(tmp14, m_row[0].m_reg);
	tmp15 = _mm_hsub_ps(tmp15, tmp15);
	tmp16 = _mm_hadd_ps(tmp15, tmp15);

	return F_MM_GET_ELEM(tmp16, 0);
}

// Related non-member functions ------------------------------------------------

inline FFastMat4f operator+(const FFastMat4f& m1, const FFastMat4f& m2)
{
	FFastMat4f result;
	result.m_row[0].m_reg = _mm_add_ps(m1.m_row[0].m_reg, m2.m_row[0].m_reg);
	result.m_row[1].m_reg = _mm_add_ps(m1.m_row[1].m_reg, m2.m_row[1].m_reg);
	result.m_row[2].m_reg = _mm_add_ps(m1.m_row[2].m_reg, m2.m_row[2].m_reg);
	result.m_row[3].m_reg = _mm_add_ps(m1.m_row[3].m_reg, m2.m_row[3].m_reg);
	return result;
}

inline FFastMat4f operator+(const FFastMat4f& mat, float scalar)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_add_ps(mat.m_row[0].m_reg, t0);
	result.m_row[1].m_reg = _mm_add_ps(mat.m_row[1].m_reg, t0);
	result.m_row[2].m_reg = _mm_add_ps(mat.m_row[2].m_reg, t0);
	result.m_row[3].m_reg = _mm_add_ps(mat.m_row[3].m_reg, t0);
	return result;
}

inline FFastMat4f operator+(float scalar, const FFastMat4f& mat)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_add_ps(t0, mat.m_row[0].m_reg);
	result.m_row[1].m_reg = _mm_add_ps(t0, mat.m_row[1].m_reg);
	result.m_row[2].m_reg = _mm_add_ps(t0, mat.m_row[2].m_reg);
	result.m_row[3].m_reg = _mm_add_ps(t0, mat.m_row[3].m_reg);
	return result;
}

inline FFastMat4f operator-(const FFastMat4f& v1, const FFastMat4f& v2)
{
	FFastMat4f result;
	result.m_row[0].m_reg = _mm_sub_ps(v1.m_row[0].m_reg, v2.m_row[0].m_reg);
	result.m_row[1].m_reg = _mm_sub_ps(v1.m_row[1].m_reg, v2.m_row[1].m_reg);
	result.m_row[2].m_reg = _mm_sub_ps(v1.m_row[2].m_reg, v2.m_row[2].m_reg);
	result.m_row[3].m_reg = _mm_sub_ps(v1.m_row[3].m_reg, v2.m_row[3].m_reg);
	return result;
}

inline FFastMat4f operator-(const FFastMat4f& mat, float scalar)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_sub_ps(mat.m_row[0].m_reg, t0);
	result.m_row[1].m_reg = _mm_sub_ps(mat.m_row[1].m_reg, t0);
	result.m_row[2].m_reg = _mm_sub_ps(mat.m_row[2].m_reg, t0);
	result.m_row[3].m_reg = _mm_sub_ps(mat.m_row[3].m_reg, t0);
	return result;
}

inline FFastMat4f operator-(float scalar, const FFastMat4f& mat)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_sub_ps(t0, mat.m_row[0].m_reg);
	result.m_row[1].m_reg = _mm_sub_ps(t0, mat.m_row[1].m_reg);
	result.m_row[2].m_reg = _mm_sub_ps(t0, mat.m_row[2].m_reg);
	result.m_row[3].m_reg = _mm_sub_ps(t0, mat.m_row[3].m_reg);
	return result;
}

inline FFastMat4f operator*(const FFastMat4f& v1, const FFastMat4f& v2)
{
	__m128 res[4];
	for (int i = 0; i < 4; i++)
	{
		__m128 t0 = _mm_shuffle_ps(v1.m_row[i].m_reg, v1.m_row[i].m_reg, _MM_SHUFFLE(0, 0, 0, 0));
		res[i] = _mm_mul_ps(t0, v2.m_row[0].m_reg);

		__m128 t1 = _mm_shuffle_ps(v1.m_row[i].m_reg, v1.m_row[i].m_reg, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 t2 = _mm_mul_ps(t1, v2.m_row[1].m_reg);
		res[i] = _mm_add_ps(res[i], t2);

		__m128 t3 = _mm_shuffle_ps(v1.m_row[i].m_reg, v1.m_row[i].m_reg, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 t4 = _mm_mul_ps(t3, v2.m_row[2].m_reg);
		res[i] = _mm_add_ps(res[i], t4);

		__m128 t5 = _mm_shuffle_ps(v1.m_row[i].m_reg, v1.m_row[i].m_reg, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 t6 = _mm_mul_ps(t5, v2.m_row[3].m_reg);
		res[i] = _mm_add_ps(res[i], t6);
	}

	return FFastMat4f(res[0], res[1], res[2], res[3]);
}

inline FFastVec4f operator*(const FFastMat4f& mat, const FFastVec4f& vec)
{
	__m128 tmp00 = _mm_mul_ps(mat.m_row[0].m_reg, vec.m_reg);
	__m128 tmp01 = _mm_mul_ps(mat.m_row[1].m_reg, vec.m_reg);
	__m128 tmp02 = _mm_mul_ps(mat.m_row[2].m_reg, vec.m_reg);
	__m128 tmp03 = _mm_mul_ps(mat.m_row[3].m_reg, vec.m_reg);
	__m128 tmp04 = _mm_hadd_ps(tmp00,tmp01);
	__m128 tmp05 = _mm_hadd_ps(tmp02,tmp03);
	__m128 tmp06 = _mm_hadd_ps(tmp04,tmp05);
	return FFastVec4f(tmp06);
}

inline FFastVec4f operator*(const FFastVec4f& vec, const FFastMat4f& mat)
{
	__m128 t0 = _mm_shuffle_ps(vec.m_reg, vec.m_reg, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 t1 = _mm_shuffle_ps(vec.m_reg, vec.m_reg, _MM_SHUFFLE(1, 1, 1, 1));
	__m128 t2 = _mm_shuffle_ps(vec.m_reg, vec.m_reg, _MM_SHUFFLE(2, 2, 2, 2));
	__m128 t3 = _mm_shuffle_ps(vec.m_reg, vec.m_reg, _MM_SHUFFLE(3, 3, 3, 3));
	__m128 t4 = _mm_mul_ps(mat.m_row[0].m_reg, t0);
	__m128 t5 = _mm_mul_ps(mat.m_row[1].m_reg, t1);
	__m128 t6 = _mm_mul_ps(mat.m_row[2].m_reg, t2);
	__m128 t7 = _mm_mul_ps(mat.m_row[3].m_reg, t3);
	__m128 t8 = _mm_add_ps(t4, t5);
	__m128 t9 = _mm_add_ps(t6, t7);
	__m128 t10 = _mm_add_ps(t8, t9);
	return FFastVec4f(t10);
}

inline FFastMat4f operator*(const FFastMat4f& mat, float scalar)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_mul_ps(mat.m_row[0].m_reg, t0);
	result.m_row[1].m_reg = _mm_mul_ps(mat.m_row[1].m_reg, t0);
	result.m_row[2].m_reg = _mm_mul_ps(mat.m_row[2].m_reg, t0);
	result.m_row[3].m_reg = _mm_mul_ps(mat.m_row[3].m_reg, t0);
	return result;
}

inline FFastMat4f operator*(float scalar, const FFastMat4f& mat)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_mul_ps(t0, mat.m_row[0].m_reg);
	result.m_row[1].m_reg = _mm_mul_ps(t0, mat.m_row[1].m_reg);
	result.m_row[2].m_reg = _mm_mul_ps(t0, mat.m_row[2].m_reg);
	result.m_row[3].m_reg = _mm_mul_ps(t0, mat.m_row[3].m_reg);
	return result;
}

inline FFastMat4f operator/(const FFastMat4f& mat, float scalar)
{
	FFastMat4f result;
	__m128 t0 = _mm_set_ps1(scalar);
	result.m_row[0].m_reg = _mm_div_ps(mat.m_row[0].m_reg, t0);
	result.m_row[1].m_reg = _mm_div_ps(mat.m_row[1].m_reg, t0);
	result.m_row[2].m_reg = _mm_div_ps(mat.m_row[2].m_reg, t0);
	result.m_row[3].m_reg = _mm_div_ps(mat.m_row[3].m_reg, t0);
	return result;
}

inline FFastMat4f fOuterProduct(const FFastVec4f& v1, const FFastVec4f& v2)
{
	__m128 tmp0 = _mm_mul_ps(v2.m_reg, _mm_set1_ps(v1[0]));
	__m128 tmp1 = _mm_mul_ps(v2.m_reg, _mm_set1_ps(v1[1]));
	__m128 tmp2 = _mm_mul_ps(v2.m_reg, _mm_set1_ps(v1[2]));
	__m128 tmp3 = _mm_mul_ps(v2.m_reg, _mm_set1_ps(v1[3]));
	return FFastMat4f(tmp0, tmp1, tmp2, tmp3);
}

/// Writes a text representation of the matrix to the given stream.
template <typename C>
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& stream, const FFastMat4f& mat)
{
	stream << "[" << mat[0] << std::endl << mat[1] << std::endl
		<< mat[3] << std::endl << mat[4] << "]";
	return stream;
}
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_FASTMAT_H