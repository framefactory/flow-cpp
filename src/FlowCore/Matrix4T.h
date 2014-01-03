// -----------------------------------------------------------------------------
//  File        Matrix4T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MATRIX4T_H
#define FLOWCORE_MATRIX4T_H

#include "FlowCore/Library.h"

#include "FlowCore/Vector4T.h"
#include "FlowCore/QuaternionT.h"
#include "FlowCore/Matrix3T.h"

#include <QString>
#include <stdlib.h>
#include <string>
#include <cmath>

// -----------------------------------------------------------------------------
//  Class FMatrix4T
// -----------------------------------------------------------------------------

template <typename REAL>
class FMatrix4T
{
	//  Public types -------------------------------------------------

public:
	enum storage_t
	{
		RowMajor,
		ColumnMajor
	};

	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	FMatrix4T() { }
	/// Create a 4 by 4 matrix from 16 scalar values.
	FMatrix4T(REAL m00, REAL m01, REAL m02, REAL m03, REAL m10, REAL m11, REAL m12, REAL m13,
		REAL m20, REAL m21, REAL m22, REAL m23, REAL m30, REAL m31, REAL m32, REAL m33);
	/// Create a 4 by 4 matrix from 4 vectors.
	FMatrix4T(const FVector4T<REAL>& v0, const FVector4T<REAL>& v1,
		const FVector4T<REAL>& v2, const FVector4T<REAL>& v3, storage_t storageOrder = RowMajor);
	/// Create a 4 by 4 matrix from an array of 16 scalar values.
	FMatrix4T(const REAL* pValues, storage_t storageOrder = RowMajor);

	//  Conversions --------------------------------------------------

	/// Returns a pointer to an array of 16 scalar values, row-major layout.
	inline REAL* ptr() { return m_row[0].ptr(); }
	/// Returns a pointer to a const array of 16 scalar values, row-major layout.
	inline const REAL* ptr() const { return m_row[0].ptr(); }
	
	/// Conversion between 4 by 4 matrices of different numeric types.
	template <typename T>
	operator FMatrix4T<T>() const {
		return FMatrix4T<T>((FVector4T<T>)m_row[0], (FVector4T<T>)m_row[1],
			(FVector4T<T>)m_row[2], (FVector4T<T>)m_row[3]);
	}

	/// Returns a text representation of the matrix.
	QString toString() const;

	//  Access -------------------------------------------------------

	/// Set all elements to zero.
	void setZero();
	/// Set all elements to zero and diagonal elements to one.
	void setIdentity();

	/// Replaces all components of the matrix by the given scalar values.
	void set(REAL m00, REAL m01, REAL m02, REAL m03, REAL m10, REAL m11, REAL m12, REAL m13,
		REAL m20, REAL m21, REAL m22, REAL m23, REAL m30, REAL m31, REAL m32, REAL m33);
	/// Replaces all elements of the matrix by the given vectors.
	void set(const FVector4T<REAL>& v0, const FVector4T<REAL>& v1,
		const FVector4T<REAL>& v2, const FVector4T<REAL>& v3, storage_t storageOrder = RowMajor);

	/// Replaces one row of the matrix by the given vector.
	void setRow(size_t index, const FVector4T<REAL>& vec);
	/// Replaces one column of the matrix by the given vector.
	void setColumn(size_t index, const FVector4T<REAL>& vec);
	/// Returns the row with the given index.
	const FVector4T<REAL>& row(size_t index) const;
	/// Returns the column with the given index.
	const FVector4T<REAL> column(size_t index) const;

	/// Subscript operator. Returns the row vector at the given index.
	FVector4T<REAL>& operator[](size_t index);
	/// Const subscript operator. Returns the row vector at the given index.
	const FVector4T<REAL>& operator[] (size_t index) const;

	/// Function-call operator. Returns the element at the given row and column.
	REAL& operator()(size_t row, size_t column);
	/// Const function-call operator. Returns the element at the given row and column.
	const REAL& operator()(size_t row, size_t column) const;
	/// Returns the element at the given row and column.
	REAL& at(size_t row, size_t column);
	/// Returns the element at the given row and column.
	const REAL& at(size_t row, size_t column) const;

	/// Replaces all elements of the matrix by the values of the given array.
	void copyFrom(const REAL* pValues, storage_t storageOrder = RowMajor);
	/// Copies all elements of the matrix to the given array.
	void copyTo(REAL* pValues, storage_t storageOrder = RowMajor) const;

	//  Operators ----------------------------------------------------
	
	/// Matrix addition, compound operator.
	FMatrix4T<REAL>& operator+=(const FMatrix4T<REAL>& other);
	/// Addition of a scalar, compound operator.
	FMatrix4T<REAL>& operator+=(REAL scalar);
	/// Matrix subtraction, compound operator.
	FMatrix4T<REAL>& operator-=(const FMatrix4T<REAL>& other);
	/// Subtraction of a scalar, compound operator.
	FMatrix4T<REAL>& operator-=(REAL scalar);
	/// Matrix multiplication, compound operator.
	FMatrix4T<REAL>& operator*=(const FMatrix4T<REAL>& other);
	/// Component-wise multiplication, compound operator.
	FMatrix4T<REAL>& operator*=(REAL scalar);
	/// Component-wise division, compound operator.
	FMatrix4T<REAL>& operator/=(REAL scalar);

	//  Public commands ----------------------------------------------

	/// Transpose the matrix.
	void transpose();
	/// Invert the matrix using LU-decomposition (matrix must be non-singular!)
	void invert();
	/// Homogenizes the matrix by dividing all elements by the last element e[2][2];
	void homogenize();

	/// Replace the upper left 3-by-3 block by the given rotation matrix.
	void replaceRotation(const FMatrix3T<REAL>& rotation);
	/// Replace the upper left 3-by-3 block by the given column vectors.
	void replaceRotation(const FVector3T<REAL>& rCol0, const FVector3T<REAL>& rCol1, const FVector3T<REAL>& rCol2);
	/// Replace the matrix' translation components by the given vector.
	void replaceTranslation(const FVector3T<REAL>& translation);

	/// Multiplies the given matrix from the right side. This
	/// prepends the transformation represented by the matrix.
	void prepend(const FMatrix4T<REAL>& rhs);
	/// Multiplies the given matrix from the left side. This
	/// appends the transformation represented by the matrix.
	void append(const FMatrix4T<REAL>& lhs);

	// TRANSFORMATIONS

	/// Make a translation matrix using the given translation values.
	void makeTranslation(REAL tx, REAL ty, REAL tz);
	/// Make a translation matrix using the given translation vector.
	void makeTranslation(const FVector3T<REAL>& tr)
	{ return makeTranslation(tr.x(), tr.y(), tr.z()); }
	/// Make a rotation matrix (x axis) using the given angle.
	void makeRotationX(REAL angle);
	/// Make a rotation matrix (y axis) using the given angle.
	void makeRotationY(REAL angle);
	/// Make a rotation matrix (z axis) using the given angle.
	void makeRotationZ(REAL angle);
	/// Make a rotation matrix from the given yaw, pitch and roll angles.
	void makeRotationYPR(REAL yaw, REAL pitch, REAL roll);
	/// Make a rotation matrix from the given yaw, pitch and roll angles.
	void makeRotationYPR(const FVector3T<REAL>& angles) {
		return makeRotationYPR(angles.x(), angles.y(), angles.z()); }
	/// Make a rotation about an arbitrary axis by the given angle.
	void makeRotation(FVector3T<REAL>& axis, REAL angle);
	/// Make a rotation matrix using the given quaternion.
	void makeRotation(const FQuaternionT<REAL>& rotation);
	/// Make a rotation matrix that rotates from v1 to v2.
	void makeRotation(FVector3T<REAL> v1, FVector3T<REAL> v2);

	/// Make a scale matrix using the given scaling factors.
	void makeScale(REAL sx, REAL sy, REAL sz);

	// CAMERAS

	/// Makes a look-at camera.
	void makeLookAtCamera(const FVector3T<REAL>& viewer,
		const FVector3T<REAL>& target, const FVector3T<REAL>& up);
	/// Makes an orbit camera.
	void makeOrbitCamera(const FVector3T<REAL>& target,
		const FVector3T<REAL>& yawPitchRoll, REAL distance);

	// PROJECTIONS

	/// Make a left-handed orthogonal projection matrix.
	void makeProjectionOrthogonalLH(REAL width, REAL height, REAL zNear, REAL zFar,
		const FVector2T<REAL> center = FVector2T<REAL>(0, 0));
	/// Make a right-handed orthogonal projection matrix.
	void makeProjectionOrthogonalRH(REAL width, REAL height, REAL zNear, REAL zFar,
		const FVector2T<REAL> center = FVector2T<REAL>(0, 0));

	/// Make a left-handed perspective projection matrix.
	void makeProjectionPerspectiveLH(REAL fov, bool fovVertical, REAL aspect, REAL zNear, REAL zFar,
		const FVector2T<REAL> center = FVector2T<REAL>(0, 0));
	/// Make a right-handed perspective projection matrix.
	void makeProjectionPerspectiveRH(REAL fov, bool fovVertical, REAL aspect, REAL zNear, REAL zFar,
		const FVector2T<REAL> center = FVector2T<REAL>(0, 0));

	//  Public queries -----------------------------------------------

	/// Extracts the upper left 3x3 rotation matrix.
	void extractRotation(OUT FMatrix3T<REAL>& rotationMatrix);
	/// Calculates and returns the determinant of the matrix.
	REAL determinant() const;

	//  Internal data members ----------------------------------------

private:
		FVector4T<REAL> m_row[4];
};

// Constructors ----------------------------------------------------------------

template <typename REAL>
inline FMatrix4T<REAL>::FMatrix4T(REAL m00, REAL m01, REAL m02, REAL m03,
	REAL m10, REAL m11, REAL m12, REAL m13, REAL m20, REAL m21, REAL m22, REAL m23,
	REAL m30, REAL m31, REAL m32, REAL m33)
{
	m_row[0].set(m00, m01, m02, m03);
	m_row[1].set(m10, m11, m12, m13);
	m_row[2].set(m20, m21, m22, m23);
	m_row[3].set(m30, m31, m32, m33);
}

template <typename REAL>
FMatrix4T<REAL>::FMatrix4T(const FVector4T<REAL>& v0, const FVector4T<REAL>& v1,
	const FVector4T<REAL>& v2, const FVector4T<REAL>& v3,
	storage_t storageOrder /* = RowMajor */)
{
	if (storageOrder == RowMajor)
	{
		m_row[0] = v0;
		m_row[1] = v1;
		m_row[2] = v2;
		m_row[3] = v3;
	}
	else // ColumnMajor
	{
		m_row[0].set(v0.x, v1.x, v2.x, v3.x);
		m_row[1].set(v0.y, v1.y, v2.y, v3.y);
		m_row[2].set(v0.z, v1.z, v2.z, v3.z);
		m_row[3].set(v0.w, v1.w, v2.w, v3.w);
	}
}

template <typename REAL>
FMatrix4T<REAL>::FMatrix4T(const REAL* pValues, storage_t storageOrder /* = RowMajor */)
{
	if (storageOrder == RowMajor)
	{
		m_row[0].set(pValues[ 0], pValues[ 1], pValues[ 2], pValues[ 3]);
		m_row[1].set(pValues[ 4], pValues[ 5], pValues[ 6], pValues[ 7]);
		m_row[2].set(pValues[ 8], pValues[ 9], pValues[10], pValues[11]);
		m_row[3].set(pValues[12], pValues[13], pValues[14], pValues[15]);
	}
	else // ColumnMajor
	{
		m_row[0].set(pValues[ 0], pValues[ 4], pValues[ 8], pValues[12]);
		m_row[1].set(pValues[ 1], pValues[ 5], pValues[ 9], pValues[13]);
		m_row[2].set(pValues[ 2], pValues[ 6], pValues[10], pValues[14]);
		m_row[3].set(pValues[ 3], pValues[ 7], pValues[11], pValues[15]);
	}
}

// Conversions -----------------------------------------------------------------

template <typename REAL>
inline QString FMatrix4T<REAL>::toString() const
{
	return QString("[%1, %2, %3, %4]\n[%5, %6, %7, %8]\n")
		.arg(m_row[0].x).arg(m_row[0].y).arg(m_row[0].z).arg(m_row[0].w)
		.arg(m_row[1].x).arg(m_row[1].y).arg(m_row[1].z).arg(m_row[1].w)
		% QString("[%1, %2, %3, %4]\n[%5, %6, %7, %8]")
		.arg(m_row[2].x).arg(m_row[2].y).arg(m_row[2].z).arg(m_row[2].w)
		.arg(m_row[3].x).arg(m_row[3].y).arg(m_row[3].z).arg(m_row[3].w);
}

// Access ----------------------------------------------------------------------

template <typename REAL>
inline void FMatrix4T<REAL>::setZero()
{
	for (size_t i = 0; i < 4; ++i)
		m_row[i].setZero();
}

template <typename REAL>
inline void FMatrix4T<REAL>::setIdentity()
{
	m_row[0].set(REAL(1.0), REAL(0.0), REAL(0.0), REAL(0.0));
	m_row[1].set(REAL(0.0), REAL(1.0), REAL(0.0), REAL(0.0));
	m_row[2].set(REAL(0.0), REAL(0.0), REAL(1.0), REAL(0.0));
	m_row[3].set(REAL(0.0), REAL(0.0), REAL(0.0), REAL(1.0));
}

template <typename REAL>
inline void FMatrix4T<REAL>::set(REAL m00, REAL m01, REAL m02, REAL m03,
	                             REAL m10, REAL m11, REAL m12, REAL m13,
								 REAL m20, REAL m21, REAL m22, REAL m23,
								 REAL m30, REAL m31, REAL m32, REAL m33)
{
	m_row[0].set(m00, m01, m02, m03);
	m_row[1].set(m10, m11, m12, m13);
	m_row[2].set(m20, m21, m22, m23);
	m_row[3].set(m30, m31, m32, m33);
}

template <typename REAL>
void FMatrix4T<REAL>::set(const FVector4T<REAL>& v0, const FVector4T<REAL>& v1,
	                      const FVector4T<REAL>& v2, const FVector4T<REAL>& v3,
	                      storage_t storageOrder /* = RowMajor */)
{
	if (storageOrder == RowMajor)
	{
		m_row[0] = v0;
		m_row[1] = v1;
		m_row[2] = v2;
		m_row[3] = v3;
	}
	else // ColumnMajor
	{
		m_row[0].set(v0.x, v1.x, v2.x, v3.x);
		m_row[1].set(v0.y, v1.y, v2.y, v3.y);
		m_row[2].set(v0.z, v1.z, v2.z, v3.z);
		m_row[3].set(v0.w, v1.w, v2.w, v3.w);
	}
}

template <typename REAL>
inline void FMatrix4T<REAL>::setRow(size_t index, const FVector4T<REAL>& vec)
{
	F_ASSERT(index < 4);
	m_row[index] = vec;
}

template <typename REAL>
inline void FMatrix4T<REAL>::setColumn(size_t index, const FVector4T<REAL>& vec)
{
	F_ASSERT(index < 4);
	m_row[0][index] = vec[0];
	m_row[1][index] = vec[1];
	m_row[2][index] = vec[2];
	m_row[3][index] = vec[3];
}

template <typename REAL>
inline const FVector4T<REAL>& FMatrix4T<REAL>::row(size_t index) const
{
	F_ASSERT(index < 4);
	return m_row[index];
}

template <typename REAL>
inline const FVector4T<REAL> FMatrix4T<REAL>::column(size_t index) const
{
	F_ASSERT(index < 4);
	return FVector4T<REAL>(m_row[0][index], m_row[1][index],
		                   m_row[2][index], m_row[3][index]);
}

template <typename REAL>
inline FVector4T<REAL>& FMatrix4T<REAL>::operator[](size_t index)
{
	F_ASSERT(index < 4);
	return m_row[index];
}

template <typename REAL>
inline const FVector4T<REAL>& FMatrix4T<REAL>::operator[] (size_t index) const
{
	F_ASSERT(index < 4);
	return m_row[index];
}

template <typename REAL>
inline REAL& FMatrix4T<REAL>::operator()(size_t row, size_t column)
{
	F_ASSERT(row < 4 && column < 4);
	return m_row[row][column];
}

template <typename REAL>
inline const REAL& FMatrix4T<REAL>::operator()(size_t row, size_t column) const
{
	F_ASSERT(row < 4 && column < 4);
	return m_row[row][column];
}

template <typename REAL>
inline REAL& FMatrix4T<REAL>::at(size_t row, size_t column)
{
	F_ASSERT(row < 4 && column < 4);
	return m_row[row][column];
}

template <typename REAL>
inline const REAL& FMatrix4T<REAL>::at(size_t row, size_t column) const
{
	F_ASSERT(row < 4 && column < 4);
	return m_row[row][column];
}

template <typename REAL>
void FMatrix4T<REAL>::copyFrom(const REAL* pValues, storage_t storageOrder /* = RowMajor */)
{
	if (storageOrder == RowMajor)
	{
		m_row[0].set(pValues[ 0], pValues[ 1], pValues[ 2], pValues[ 3]);
		m_row[1].set(pValues[ 4], pValues[ 5], pValues[ 6], pValues[ 7]);
		m_row[2].set(pValues[ 8], pValues[ 9], pValues[10], pValues[11]);
		m_row[3].set(pValues[12], pValues[13], pValues[14], pValues[15]);
	}
	else // ColumnMajor
	{
		m_row[0].set(pValues[ 0], pValues[ 4], pValues[ 8], pValues[12]);
		m_row[1].set(pValues[ 1], pValues[ 5], pValues[ 9], pValues[13]);
		m_row[2].set(pValues[ 2], pValues[ 6], pValues[10], pValues[14]);
		m_row[3].set(pValues[ 3], pValues[ 7], pValues[11], pValues[15]);
	}
}

template <typename REAL>
void FMatrix4T<REAL>::copyTo(REAL* pValues, storage_t storageOrder /* = RowMajor */) const
{
	if (storageOrder == RowMajor)
	{
		pValues[ 0] = m_row[0].x; pValues[ 1] = m_row[0].y; pValues[ 2] = m_row[0].z; pValues[ 3] = m_row[0].w;
		pValues[ 4] = m_row[1].x; pValues[ 5] = m_row[1].y; pValues[ 6] = m_row[1].z; pValues[ 7] = m_row[1].w;
		pValues[ 8] = m_row[2].x; pValues[ 9] = m_row[2].y; pValues[10] = m_row[2].z; pValues[11] = m_row[2].w;
		pValues[12] = m_row[3].x; pValues[13] = m_row[3].y; pValues[14] = m_row[3].z; pValues[15] = m_row[3].w;
	}
	else // ColumnMajor
	{
		pValues[ 0] = m_row[0].x; pValues[ 1] = m_row[1].x; pValues[ 2] = m_row[2].x; pValues[ 3] = m_row[3].x;
		pValues[ 4] = m_row[0].y; pValues[ 5] = m_row[1].y; pValues[ 6] = m_row[2].y; pValues[ 7] = m_row[3].y;
		pValues[ 8] = m_row[0].z; pValues[ 9] = m_row[1].z; pValues[10] = m_row[2].z; pValues[11] = m_row[3].z;
		pValues[12] = m_row[0].w; pValues[13] = m_row[1].w; pValues[14] = m_row[2].w; pValues[15] = m_row[3].w;
	}
}

// Operators -------------------------------------------------------------------

template <typename REAL>
inline FMatrix4T<REAL>& FMatrix4T<REAL>::operator+=(const FMatrix4T<REAL>& other)
{
	for (size_t i = 0; i < 4; i++)
		m_row[i] += other.m_row[i];
	return *this;
}

template <typename REAL>
inline FMatrix4T<REAL>& FMatrix4T<REAL>::operator+=(REAL scalar)
{
	for (size_t i = 0; i < 4; i++)
		m_row[i] += scalar;
	return *this;
}

template <typename REAL>
inline FMatrix4T<REAL>& FMatrix4T<REAL>::operator-=(const FMatrix4T<REAL>& other)
{
	for (size_t i = 0; i < 4; i++)
		m_row[i] -= other.m_row[i];
	return *this;
}

template <typename REAL>
inline FMatrix4T<REAL>& FMatrix4T<REAL>::operator-=(REAL scalar)
{
	for (size_t i = 0; i < 4; i++)
		m_row[i] -= scalar;
	return *this;
}

template <typename REAL>
FMatrix4T<REAL>& FMatrix4T<REAL>::operator*=(const FMatrix4T<REAL>& other)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			REAL s = REAL(0.0);
			for (size_t k = 0; k < 4; k++)
				s += m_row[i][k] * other.m_row[k][j];
			result.m_row[i][j] = s;
		}
	}

	*this = result;
	return *this;
}

template <typename REAL>
FMatrix4T<REAL>& FMatrix4T<REAL>::operator*=(REAL scalar)
{
	for (size_t i = 0; i < 4; i++)
		m_row[i] *= scalar;
	return *this;
}

template <typename REAL>
FMatrix4T<REAL>& FMatrix4T<REAL>::operator/=(REAL scalar)
{
	for (size_t i = 0; i < 4; i++)
		m_row[i] /= scalar;
	return *this;
}



// Public commands -------------------------------------------------------------

template <typename REAL>
inline void FMatrix4T<REAL>::transpose()
{
	REAL t;

	t = m_row[0][1]; m_row[0][1] = m_row[1][0]; m_row[1][0] = t;
	t = m_row[0][2]; m_row[0][2] = m_row[2][0]; m_row[2][0] = t;
	t = m_row[0][3]; m_row[0][3] = m_row[3][0]; m_row[3][0] = t;
	t = m_row[1][2]; m_row[1][2] = m_row[2][1]; m_row[2][1] = t;
	t = m_row[1][3]; m_row[1][3] = m_row[3][1]; m_row[3][1] = t;
	t = m_row[2][3]; m_row[2][3] = m_row[3][2]; m_row[3][2] = t;

	return *this;
}

template <typename REAL>
void FMatrix4T<REAL>::invert()
{
	// check if matrix is orthogonal
	// check values of row 4
	if (m_row[3][0] == REAL(0.0) && m_row[3][1] == REAL(0.0) && m_row[3][2] == REAL(0.0) && m_row[3][3] == REAL(1.0))
	{
		// check if the determinant of the upper left 3x3 block is 1 or -1, i.e. if the block is orthogonal.

		if (false)
		{

			// if yes, the transpose the block
			REAL t;

			t = m_row[0][1]; m_row[0][1] = m_row[1][0]; m_row[1][0] = t;
			t = m_row[0][2]; m_row[0][2] = m_row[2][0]; m_row[2][0] = t;
			t = m_row[1][2]; m_row[1][2] = m_row[2][1]; m_row[2][1] = t;

			m_row[0][3] = -m_row[0][3];
			m_row[1][3] = -m_row[1][3];
			m_row[2][3] = -m_row[2][3];

			return *this;
		}
	}
	else
	{
		// we need a full inverse, so calculate it here (using the adjoint method)
		F_ASSERT(false);
	}

	m_row[0][3] = -m_row[0][3];
	m_row[1][3] = -m_row[1][3];
	m_row[2][3] = -m_row[2][3];

	return *this;
}

template <typename REAL>
inline void FMatrix4T<REAL>::homogenize()
{
	REAL f = REAL(1.0) / m_row[3][3];
	for (size_t i = 0; i < 4; ++i)
		m_row[i] *= f;

	return *this;
}

template <typename REAL>
inline void FMatrix4T<REAL>::replaceRotation(const FMatrix3T<REAL>& rotation)
{
	m_row[0][0] = rotation[0][0]; m_row[0][1] = rotation[0][1]; m_row[0][2] = rotation[0][2];
	m_row[1][0] = rotation[1][0]; m_row[1][1] = rotation[1][1]; m_row[1][2] = rotation[1][2];
	m_row[2][0] = rotation[2][0]; m_row[2][1] = rotation[2][1]; m_row[2][2] = rotation[2][2];
}

template <typename REAL>
inline void FMatrix4T<REAL>::replaceRotation(const FVector3T<REAL>& rCol0,
									  const FVector3T<REAL>& rCol1,
									  const FVector3T<REAL>& rCol2)
{
	m_row[0][0] = rCol0[0]; m_row[0][1] = rCol1[0]; m_row[0][2] = rCol2[0];
	m_row[1][0] = rCol0[1]; m_row[1][1] = rCol1[1]; m_row[1][2] = rCol2[1];
	m_row[2][0] = rCol0[2]; m_row[2][1] = rCol1[2]; m_row[2][2] = rCol2[2];
}

template <typename REAL>
inline void FMatrix4T<REAL>::replaceTranslation(const FVector3T<REAL>& translation)
{
	m_row[0][3] = translation.x();
	m_row[1][3] = translation.y();
	m_row[2][3] = translation.z();
}

template <typename REAL>
inline void FMatrix4T<REAL>::prepend(const FMatrix4T<REAL>& rhs)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			REAL s = REAL(0.0);
			for (size_t k = 0; k < 4; k++)
				s += m_row[i][k] * rhs.m_row[k][j];
			result.m_row[i][j] = s;
		}
	}

	*this = result;
}

template <typename REAL>
inline void FMatrix4T<REAL>::append(const FMatrix4T<REAL>& lhs)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			REAL s = REAL(0.0);
			for (size_t k = 0; k < 4; k++)
				s += lhs.m_row[i][k] * m_row[k][j];
			result.m_row[i][j] = s;
		}
	}

	*this = result;
}

// ----- Transformations -----

template <typename REAL>
void FMatrix4T<REAL>::makeTranslation(REAL tx, REAL ty, REAL tz)
{
	m_row[0][0] = REAL(1.0); m_row[0][1] = REAL(0.0); m_row[0][2] = REAL(0.0); m_row[0][3] = tx;
	m_row[1][0] = REAL(0.0); m_row[1][1] = REAL(1.0); m_row[1][2] = REAL(0.0); m_row[1][3] = ty;
	m_row[2][0] = REAL(0.0); m_row[2][1] = REAL(0.0); m_row[2][2] = REAL(1.0); m_row[2][3] = tz;
	m_row[3][0] = REAL(0.0); m_row[3][1] = REAL(0.0); m_row[3][2] = REAL(0.0); m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotationX(REAL angle)
{
	REAL si = sin(angle);
	REAL co = cos(angle);

	m_row[0][0] = REAL(1.0); m_row[0][1] = REAL(0.0); m_row[0][2] = REAL(0.0); m_row[0][3] = REAL(0.0);
	m_row[1][0] = REAL(0.0); m_row[1][1] = co;        m_row[1][2] = -si;       m_row[1][3] = REAL(0.0);
	m_row[2][0] = REAL(0.0); m_row[2][1] = si;        m_row[2][2] = co;        m_row[2][3] = REAL(0.0);
	m_row[3][0] = REAL(0.0); m_row[3][1] = REAL(0.0); m_row[3][2] = REAL(0.0); m_row[3][3] = REAL(1.0);	
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotationY(REAL angle)
{
	REAL si = sin(angle);
	REAL co = cos(angle);

	m_row[0][0] = co;        m_row[0][1] = REAL(0.0); m_row[0][2] = si;        m_row[0][3] = REAL(0.0);
	m_row[1][0] = REAL(0.0); m_row[1][1] = REAL(1.0); m_row[1][2] = REAL(0.0); m_row[1][3] = REAL(0.0);
	m_row[2][0] = -si;       m_row[2][1] = REAL(0.0); m_row[2][2] = co;        m_row[2][3] = REAL(0.0);
	m_row[3][0] = REAL(0.0); m_row[3][1] = REAL(0.0); m_row[3][2] = REAL(0.0); m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotationZ(REAL angle)
{
	REAL si = sin(angle);
	REAL co = cos(angle);

	m_row[0][0] = co;        m_row[0][1] = -si;       m_row[0][2] = REAL(0.0); m_row[0][3] = REAL(0.0);
	m_row[1][0] = si;        m_row[1][1] = co;        m_row[1][2] = REAL(0.0); m_row[1][3] = REAL(0.0);
	m_row[2][0] = REAL(0.0); m_row[2][1] = REAL(0.0); m_row[2][2] = REAL(1.0); m_row[2][3] = REAL(0.0);
	m_row[3][0] = REAL(0.0); m_row[3][1] = REAL(0.0); m_row[3][2] = REAL(0.0); m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotationYPR(REAL yaw, REAL pitch, REAL roll)
{
	REAL sy = (REAL)sin(yaw); REAL cy = (REAL)cos(yaw);
	REAL sp = (REAL)sin(pitch); REAL cp = (REAL)cos(pitch);
	REAL sr = (REAL)sin(roll); REAL cr = (REAL)cos(roll);

	m_row[0][0] = cr * cy - sr * sp * sy;
	m_row[0][1] = -sr * cp;
	m_row[0][2] = cr * sy + sr * sp * cy;
	m_row[1][0] = sr * cy + cr * sp * sy;
	m_row[1][1] = cr * cp;
	m_row[1][2] = sr * sy - cr * sp * cy;
	m_row[2][0] = -cp * sy;
	m_row[2][1] = sp;
	m_row[2][2] = cp * cy;

	m_row[0][3] = m_row[1][3] = m_row[2][3] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][2] = REAL(0.0);
	m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotation(FVector3T<REAL>& axis, REAL angle)
{
	REAL si = (REAL)sin(angle);
	REAL co = (REAL)cos(angle);
	REAL co1 = REAL(1.0) - co;

	m_row[0][0] = co + co1 * axis.x() * axis.x();
	m_row[0][1] = co1 * axis.x() * axis.y() - axis.z() * si;
	m_row[0][2] = co1 * axis.x() * axis.z() + axis.y() * si;
	m_row[1][0] = co1 * axis.x() * axis.y() + axis.z() * si;
	m_row[1][1] = co + co1 * axis.y() * axis.y();
	m_row[1][2] = co1 * axis.y() * axis.z() - axis.x() * si;
	m_row[2][0] = co1 * axis.x() * axis.z() - axis.y() * si;
	m_row[2][1] = co1 * axis.y() * axis.z() + axis.x() * si;
	m_row[2][2] = co + co1 * axis.z() * axis.z();

	m_row[0][3] = m_row[1][3] = m_row[2][3] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][2] = REAL(0.0);
	m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotation(const FQuaternionT<REAL>& rotation)
{
	REAL x = rotation.x;
	REAL y = rotation.y;
	REAL z = rotation.z;
	REAL w = rotation.w;
	REAL xx = x * x;
	REAL yy = y * y;
	REAL zz = z * z;

	m_row[0][0] = REAL(1.0) - REAL(2.0) * (yy + zz);
	m_row[0][1] = REAL(2.0) * (x * y - w * z);
	m_row[0][2] = REAL(2.0) * (x * z + w * y);
	m_row[0][3] = REAL(0.0);

	m_row[1][0] = REAL(2.0) * (x * y + w * z);
	m_row[1][1] = REAL(1.0) - REAL(2.0) * (xx + zz);
	m_row[1][2] = REAL(2.0) * (y * z - w * x);
	m_row[1][3] = REAL(0.0);

	m_row[2][0] = REAL(2.0) * (x * z - w * y);
	m_row[2][1] = REAL(2.0) * (y * z + w * x);
	m_row[2][2] = REAL(1.0) - REAL(2.0) * (xx + yy);
	m_row[2][3] = REAL(0.0);

	m_row[3][0] = m_row[3][1] = m_row[3][2] = REAL(0.0);
	m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeRotation(FVector3T<REAL> s, FVector3T<REAL> t)
{
	s.normalize();
	t.normalize();
	FVector3T<REAL> v = s.cross(t);
	v.normalize();
	REAL e = s * t;
	REAL h = REAL(1.0) / (REAL(1.0) + e);

	m_row[0][0] = e + h * v.x() * v.x();
	m_row[0][1] = h * v.x() * v.y() - v.z();
	m_row[0][2] = h * v.x() * v.z() + v.y();
	m_row[1][0] = h * v.x() * v.y() + v.z();
	m_row[1][1] = e + h * v.y() * v.y();
	m_row[1][2] = h * v.y() * v.z() - v.x();
	m_row[2][0] = h * v.x() * v.z() - v.y();
	m_row[2][1] = h * v.y() * v.z() + v.x();
	m_row[2][2] = e + h * v.z() * v.z();

	m_row[0][3] = m_row[1][3] = m_row[2][3] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][2] = REAL(0.0);
	m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeScale(REAL sx, REAL sy, REAL sz)
{
	m_row[0][0] = sx;        m_row[0][1] = REAL(0.0); m_row[0][2] = REAL(0.0); m_row[0][3] = REAL(0.0);
	m_row[1][0] = REAL(0.0); m_row[1][1] = sy;        m_row[1][2] = REAL(0.0); m_row[1][3] = REAL(0.0);
	m_row[2][0] = REAL(0.0); m_row[2][1] = REAL(0.0); m_row[2][2] = sz;        m_row[2][3] = REAL(0.0);
	m_row[3][0] = REAL(0.0); m_row[3][1] = REAL(0.0); m_row[3][2] = REAL(0.0); m_row[3][3] = REAL(1.0);
}

// ----- Cameras -----

template <typename REAL>
void FMatrix4T<REAL>::makeLookAtCamera(
	const FVector3T<REAL>& viewer, const FVector3T<REAL>& target, const FVector3T<REAL>& up)
{
	F_ASSERT(false);
}

template <typename REAL>
void FMatrix4T<REAL>::makeOrbitCamera(
	const FVector3T<REAL>& target, const FVector3T<REAL>& yawPitchRoll, REAL distance)
{
	F_ASSERT(false);
}

// ----- Projections -----

template <typename REAL>
void FMatrix4T<REAL>::makeProjectionOrthogonalLH(
	REAL width, REAL height, REAL n, REAL f,
	const FVector2T<REAL> center /* = FVector2T<REAL> */)
{
	REAL width2 = width * REAL(0.5);
	REAL height2 = height * REAL(0.5);
	REAL left = center.x() - width2;
	REAL right = center.x() + width2;
	REAL bottom = center.y() - height2;
	REAL top = center.y() + height2;

	m_row[0][0] = REAL(2.0) / width;
	m_row[1][1] = REAL(2.0) / height;
	m_row[2][2] = REAL(2.0) / (f - n);
	m_row[0][3] = -(left + right) / width;
	m_row[1][3] = -(top + bottom) / height;
	m_row[2][3] = -n / (f - n);

	m_row[0][1] = m_row[0][2] = m_row[1][0] = m_row[1][2] = m_row[2][0] = m_row[2][1] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][2] = REAL(0.0);
	m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeProjectionOrthogonalRH(
	REAL width, REAL height, REAL n, REAL f,
	const FVector2T<REAL> center /* = FVector2T<REAL> */)
{
	REAL left = center.x() - width * REAL(0.5);;
	REAL right = center.x() + width * REAL(0.5);;
	REAL bottom = center.y() - height * REAL(0.5);
	REAL top = center.y() + height * REAL(0.5);

	m_row[0][0] = REAL(2.0) / width;
	m_row[1][1] = REAL(2.0) / height;
	m_row[2][2] = -REAL(2.0) / (f - n);
	m_row[0][3] = -(left + right) / width;
	m_row[1][3] = -(top + bottom) / height;
	m_row[2][3] = n / (f - n);

	m_row[0][1] = m_row[0][2] = m_row[1][0] = m_row[1][2] = m_row[2][0] = m_row[2][1] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][2] = REAL(0.0);
	m_row[3][3] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeProjectionPerspectiveLH(
	REAL fov, bool fovVertical, REAL aspect, REAL n, REAL f,
	const FVector2T<REAL> center /* = FVector2T<REAL> */)
{
	REAL width, height;

	if (fovVertical)
	{
		height = tan(fov * REAL(0.5)) * n * REAL(2.0);
		width = height * aspect;
	}
	else
	{
		width = tan(fov * REAL(0.5)) * n * REAL(2.0);
		height = width / aspect;
	}

	REAL left = center.x() - width * REAL(0.5);;
	REAL right = center.x() + width * REAL(0.5);;
	REAL bottom = center.y() - height * REAL(0.5);
	REAL top = center.y() + height * REAL(0.5);

	m_row[0][0] = REAL(2.0) * n / width;
	m_row[0][2] = -(left + right) / width;
	m_row[1][1] = REAL(2.0) * n / height;
	m_row[1][2] = -(top + bottom) / height;
	m_row[2][2] = f / (f - n);
	m_row[2][3] = -f * n / (f - n);

	m_row[0][1] = m_row[0][3] = m_row[1][0] = m_row[1][3] = m_row[2][0] = m_row[2][1] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][3] = REAL(0.0);
	m_row[3][2] = REAL(1.0);
}

template <typename REAL>
void FMatrix4T<REAL>::makeProjectionPerspectiveRH(
	REAL fov, bool fovVertical, REAL aspect, REAL n, REAL f,
	const FVector2T<REAL> center /* = FVector2T<REAL> */)
{
	REAL width, height;

	if (fovVertical)
	{
		height = tan(fov * REAL(0.5)) * n * REAL(2.0);
		width = height * aspect;
	}
	else
	{
		width = tan(fov * REAL(0.5)) * n * REAL(2.0);
		height = width / aspect;
	}

	REAL left = center.x() - width * REAL(0.5);;
	REAL right = center.x() + width * REAL(0.5);;
	REAL bottom = center.y() - height * REAL(0.5);
	REAL top = center.y() + height * REAL(0.5);

	m_row[0][0] = REAL(2.0) * n / width;
	m_row[0][2] = (left + right) / width;
	m_row[1][1] = REAL(2.0) * n / height;
	m_row[1][2] = (top + bottom) / height;
	m_row[2][2] = -f / (f - n);
	m_row[2][3] = f * n / (f - n);

	m_row[0][1] = m_row[0][3] = m_row[1][0] = m_row[1][3] = m_row[2][0] = m_row[2][1] = REAL(0.0);
	m_row[3][0] = m_row[3][1] = m_row[3][3] = REAL(0.0);
	m_row[3][2] = REAL(1.0);
}

// Public queries --------------------------------------------------------------

template <typename REAL>
void FMatrix4T<REAL>::extractRotation(OUT FMatrix3T<REAL>& mat)
{
	mat[0].copyFrom(m_row[0].ptr());
	mat[1].copyFrom(m_row[1].ptr());
	mat[2].copyFrom(m_row[2].ptr());
}

template <typename REAL>
REAL FMatrix4T<REAL>::determinant() const
{
	F_ASSERT(false);
	return REAL(0.0);
}

// Related non-member functions ------------------------------------------------

/// Component-wise addition of two matrices.
template <typename REAL>
inline FMatrix4T<REAL> operator+(const FMatrix4T<REAL>& lhs, const FMatrix4T<REAL>& rhs)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
		result[i] = lhs[i] + rhs[i];
	return result;
}
/// Component-wise subtraction of two matrices.
template <typename REAL>
inline FMatrix4T<REAL> operator-(const FMatrix4T<REAL>& lhs, const FMatrix4T<REAL>& rhs)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
		result[i] = lhs[i] - rhs[i];
	return result;
}
/// Matrix-vector multiplication.
template <typename REAL>
inline FVector4T<REAL> operator*(const FMatrix4T<REAL>& mat, const FVector4T<REAL>& vec)
{
	FVector4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
	{
		REAL s = REAL(0.0);
		for (size_t j = 0; j < 4; j++)
			s += mat[i][j] * vec[j];
		result[i] = s;
	}
	return result;
}

/// Matrix-matrix multiplication.
template <typename REAL>
inline FMatrix4T<REAL> operator*(const FMatrix4T<REAL>& lhs, const FMatrix4T<REAL>& rhs)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			REAL s = REAL(0.0);
			for (size_t k = 0; k < 4; k++)
				s += lhs[i][k] * rhs[k][j];
			result[i][j] = s;
		}
	}
	return result;
}

/// Matrix-scalar multiplication.
template <typename REAL>
inline FMatrix4T<REAL> operator*(const FMatrix4T<REAL>& mat, REAL scalar)
{
	FMatrix4T<REAL> result;
	for (size_t i = 0; i < 4; i++)
		result[i] = mat[i] * scalar;
	return result;
}

/// Writes a text representation of the matrix to the given stream.
template <typename REAL, typename C>
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& stream, const FMatrix4T<REAL>& mat)
{
	stream << "[" << mat[0] << std::endl << mat[1] << std::endl
		<< mat[3] << std::endl << mat[4] << "]";
	return stream;
}

// Typedefs --------------------------------------------------------------------

/// Matrix of type float.
typedef F_ALIGN(16) FMatrix4T<float> FMatrix4f;
/// Matrix of type double.
typedef FMatrix4T<double> FMatrix4d;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_MATRIX4T_H