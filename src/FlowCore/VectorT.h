// -----------------------------------------------------------------------------
//  File        VectorT.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_VECTORT_H
#define FLOWCORE_VECTORT_H

#include "FlowCore/Library.h"

#include <QString>
#include <stdlib.h>
#include <cmath>
#include <float.h>

// -----------------------------------------------------------------------------
//  Class FVectorT
// -----------------------------------------------------------------------------

/// Vector of arbitrary size
template <typename REAL>
class FVectorT
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	inline FVectorT() : m_size(0), m_pV(NULL) { }
	/// Create new vector with given size.
	FVectorT(size_t size);
	/// Create from array.
	FVectorT(size_t size, REAL* pValues);
	/// Copy constructor.
	FVectorT(const FVectorT<REAL>& other);

	/// Default destructor.
	~FVectorT();

	//  Conversions --------------------------------------------------

	inline REAL* ptr() { return m_pV; }
	inline const REAL* ptr() const { return m_pV; }

	/// Returns a text representation of the vector.
	QString toString() const;

	//  Operators ----------------------------------------------------

	/// Assignment operator.
	FVectorT<REAL>& operator=(const FVectorT<REAL>& other);
	/// Subscript operator.
	REAL& operator[](size_t index);
	/// Const subscript operator.
	const REAL& operator[](size_t index) const;
	/// Component-wise addition of two vectors.
	FVectorT<REAL> operator+(const FVectorT<REAL>& other) const;
	/// Component-wise addition of two vectors: Compound-assignment.
	FVectorT<REAL>& operator+=(const FVectorT<REAL>& other);
	/// Component-wise subtraction of two vectors.
	FVectorT<REAL> operator-(const FVectorT<REAL>& other) const;
	/// Component-wise subtraction of two vectors: Compound-assignment.
	FVectorT<REAL>& operator-=(const FVectorT<REAL>& other);
	/// Component-wise scalar multiplication.
	FVectorT<REAL> operator*(REAL scalar) const;
	/// Component-wise scalar multiplication: Compound assignment.
	FVectorT<REAL>& operator*=(REAL scalar);
	/// Component-wise scalar division.
	FVectorT<REAL> operator/(REAL scalar) const;
	/// Component-wise scalar division: Compound assignment.
	FVectorT<REAL>& operator/=(REAL scalar);

	//  Public commands ----------------------------------------------

	/// Sets all elements to zero.
	void setZero();
	/// Normalizes this vector to unit length.
	void normalize();
	/// Resizes the vector.
	void resize(size_t size);

	//  Public queries -----------------------------------------------

	/// Returns the number of components.
	size_t size() const { return m_size; }
	
	/// Returns the 2-norm (euclidean length).
	REAL length() const;
	/// Returns the squared 2-norm.
	REAL lengthSquared() const;
	
	/// Returns the smallest component.
	REAL min() const;
	/// Returns the smallest component and its index.
	REAL min(size_t& index) const;
	/// Returns the largest component.
	REAL max() const;
	/// Returns the largest component and its index.
	REAL max(size_t index) const;

	//  Data members -------------------------------------------------

private:
	REAL*	m_pV;
	size_t	m_size;
};

// Typedefs --------------------------------------------------------------------

/// Vector of type double.
typedef FVectorT<double> FVector_d;
/// Vector of type float.
typedef FVectorT<float> FVector_f;

// Constructors and destructor -------------------------------------------------

template <typename REAL>
FVectorT<REAL>::FVectorT(size_t size)
{
	m_size = size;

	if (size > 0)
		m_pV = new REAL[size];
	else
		m_pV = NULL;
}

template <typename REAL>
FVectorT<REAL>::FVectorT(const FVectorT<REAL>& other)
{
	m_size = other.size();

	if (m_size > 0)
	{
		m_pV = new REAL[m_size];

		for (size_t i = 0; i < m_size; i++)
			m_pV[i] = other[i];
	}
	else
	{
		m_pV = NULL;
	}
}

template <typename REAL>
FVectorT<REAL>::FVectorT(size_t size, REAL* pValues)
{
	m_size = size;

	if (m_size > 0)
	{
		m_pV = new REAL[size];
		for (size_t i = 0; i < size; i++)
			m_pV[i] = pValues[i];
	}
	else
		m_pV = NULL;
}

template <typename REAL>
FVectorT<REAL>::~FVectorT()
{
	if (m_pV)
		delete m_pV;
}

// Conversions -----------------------------------------------------------------

template <typename REAL>
inline QString FVectorT<REAL>::toString() const
{
	if (vec.size() == 0) {
		return QStringLiteral("[empty vector]");
	}

	QString result;
	QTextStream stream(&result);

	stream << "[" << vec[0];
	for (size_t i = 1; i < vec.size(); ++i)
		stream << ", " << vec[i];
	stream << "]";

	return result;	
}

// Operators -------------------------------------------------------------------

template <typename REAL>
FVectorT<REAL>& FVectorT<REAL>::operator=(const FVectorT<REAL>& other)
{
	if (m_pV)
		delete m_pV;

	m_size = other.Size();

	if (m_size > 0)
	{
		m_pV = new REAL[m_size];

		for (size_t i = 0; i < m_size; i++)
			m_pV[i] = other[i];
	}
	else
	{
		m_pV = NULL;
	}

	return *this;
}

template <typename REAL>
inline REAL& FVectorT<REAL>::operator[](size_t index)
{
	F_ASSERT(index < m_size);
	return m_pV[index];
}

template <typename REAL>
inline const REAL& FVectorT<REAL>::operator[](size_t index) const
{
	F_ASSERT(index < m_size);
	return m_pV[index];
}

template <typename REAL>
FVectorT<REAL> FVectorT<REAL>::operator+(const FVectorT<REAL>& other) const
{
	F_ASSERT(m_size == other.m_size);
	FVectorT<REAL> result(m_size);
	for (size_t i = 0; i < n; i++)
		result[i] = m_pV[i] + other[i];

	return result;
}

template <typename REAL>
FVectorT<REAL>& FVectorT<REAL>::operator+=(const FVectorT<REAL>& other)
{
	F_ASSERT(m_size == other.m_size);
	for (size_t i = 0; i < m_size; i++)
		m_pV[i] += other[i];

	return *this;
}

template <typename REAL>
FVectorT<REAL> FVectorT<REAL>::operator-(const FVectorT<REAL>& other) const
{
	F_ASSERT(m_size == other.m_size);
	FVectorT<REAL> result(n);
	for (size_t i = 0; i < n; i++)
		result[i] = m_pV[i] - other[i];

	return result;
}

template <typename REAL>
FVectorT<REAL>& FVectorT<REAL>::operator-=(const FVectorT<REAL>& other)
{
	F_ASSERT(m_size == other.m_size);
	for (size_t i = 0; i < m_size; i++)
		m_pV[i] -= other[i];

	return *this;
}

template <typename REAL>
FVectorT<REAL> FVectorT<REAL>::operator*(REAL scalar) const
{
	FVectorT<REAL> result(m_size);
	for (size_t i = 0; i < m_size; i++)
		result[i] = m_pV[i] * scalar;

	return result;
}

template <typename REAL>
FVectorT<REAL>& FVectorT<REAL>::operator*=(REAL scalar)
{
	for (size_t i = 0; i < m_size; i++)
		m_pV[i] *= scalar;

	return *this;
}

template <typename REAL>
FVectorT<REAL> FVectorT<REAL>::operator/(REAL scalar) const
{
	FVectorT<REAL> result(m_size);
	REAL s = (REAL)1.0 / scalar;
	for (size_t i = 0; i < m_size; i++)
		result[i] = m_pV[i] * s;

	return result;
}

template <typename REAL>
FVectorT<REAL>& FVectorT<REAL>::operator/=(REAL scalar)
{
	REAL s = (REAL)1.0 / scalar;
	for (size_t i = 0; i < m_size; i++)
		m_pV[i] *= s;

	return *this;
}

// Public commands -------------------------------------------------------------

template <typename REAL>
void FVectorT<REAL>::setZero()
{
	for (size_t i = 0; i < m_size; i++)
		m_pV[i] = REAL(0.0);
}

template <typename REAL>
void FVectorT<REAL>::normalize()
{
	REAL invLength = REAL(1.0) / length();
	for (size_t i = 0; i < m_size; i++)
		m_pV[i] *= invLength;
}

template <typename REAL>
void FVectorT<REAL>::resize(size_t size)
{
	REAL* pV2 = new REAL[size];

	for (size_t i = m_size; i < size; i++)
		pV2[i] = REAL(0.0);

	if (m_pV)
	{
		size_t count = m_size < size ? m_size : size;
		for (size_t i = 0; i < count; i++)
			pV2[i] = m_pV[i];
		delete[] m_pV;
	}

	m_pV = pV2;
	m_size = size;
}

// Public queries --------------------------------------------------------------

template <typename REAL>
inline REAL FVectorT<REAL>::length() const
{
	REAL s = REAL(0.0);
	for (size_t i = 0; i < m_size; i++)
		s += m_pV[i] * m_pV[i];
	return sqrt(s);
}

template <typename REAL>
inline REAL FVectorT<REAL>::lengthSquared() const
{
	REAL s = REAL(0.0);
	for (size_t i = 0; i < m_size; i++)
		s += m_pV[i] * m_pV[i];
	return s;
}

template <typename REAL>
inline REAL FVectorT<REAL>::min() const
{
	REAL m = (REAL)FLT_MAX;
	for (size_t i = 0; i < m_size; i++)
	{
		if (m > m_pV[i])
			m = m_pV[i];
	}
	return m;
}

template <typename REAL>
inline REAL FVectorT<REAL>::min(size_t& index) const
{
	REAL m = (REAL)FLT_MAX;
	for (size_t i = 0; i < m_size; i++)
	{
		if (m > m_pV[i])
		{
			m = m_pV[i];
			index = i;
		}
	}
	return m;
}

template <typename REAL>
inline REAL FVectorT<REAL>::max() const
{
	REAL m = (REAL)-FLT_MAX;
	for (size_t i = 0; i < m_size; i++)
	{
		if (m < m_pV[i])
			m = m_pV[i];
	}
	return m;
}

template <typename REAL>
inline REAL FVectorT<REAL>::max(size_t index) const
{
	REAL m = (REAL)-FLT_MAX;
	for (size_t i = 0; i < m_size; i++)
	{
		if (m < m_pV[i])
		{
			m = m_pV[i];
			index = i;
		}
	}
	return m;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_VECTORT_H
