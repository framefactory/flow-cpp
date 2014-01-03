// -----------------------------------------------------------------------------
//  File        Grid2T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_GRID2T_H
#define FLOWCORE_GRID2T_H

#include "FlowCore/Library.h"
#include "FlowCore/Vector2T.h"

// -----------------------------------------------------------------------------
//  Class FGrid2T
// -----------------------------------------------------------------------------

template <typename T>
class FGrid2T
{
	//  Public types -------------------------------------------------
	
public:
	typedef T element_t; 

	//  Constructors and destructor ----------------------------------

	FGrid2T() : m_pData(NULL), m_size(0, 0), m_pitch(0) { }
	FGrid2T(const FVector2i& size, element_t* pData = NULL, int pitch = 0);
	FGrid2T(int width, int height, element_t* pData = NULL, int pitch = 0);
	FGrid2T(const FGrid2T<T>& other);
	~FGrid2T() { clear(); }

	FGrid2T<T>& operator=(const FGrid2T<T>& other);

	//  Public commands ----------------------------------------------

	/// Resizes the grid and allocates memory for the new size.
	void resize(const FVector2i& size);
	/// Resizes the grid and allocates memory for the new size.
	void resize(int width, int height);

	/// Clears the grid and frees all memory.
	void clear();

	//  Public queries -----------------------------------------------

	/// Returns a pointer to the data of the grid.
	element_t* data() { return m_pData; }
	/// Returns a const pointer to the data of the grid.
	const element_t* data() const { return m_pData; }

	/// Returns a pointer to the pixel data at the given position.
	element_t* dataAt(const FVector2i& pos);
	/// Returns a const pointer to the pixel data at the given position.
	const element_t* dataAt(const FVector2i& pos) const;

	/// Returns the size of the grid.
	const FVector2i& size() const { return m_size; }

	/// Returns the number of elements in the grid.
	size_t elementCount() const { return m_size.x * m_size.y; }
	/// Returns the amount of memory the grid consumes in bytes.
	size_t byteCount() const { return elementCount() * sizeof(T); }

	//  Internal data members ----------------------------------------

private:
	void _copyFrom(T* pSrc, int pitch);

	T* m_pData;
	FVector2i m_size;
};

// Template members ------------------------------------------------------------

template <typename T>
FGrid2T<T>::FGrid2T(const FVector2i& size,
	element_t* pData /* = NULL */, int pitch /* = 0 */)
: m_size(size)
{
	F_ASSERT(m_size.x > 0 && m_size.y > 0);
	m_pData = new T[elementCount()];

	if (pData)
		_copyFrom(pData, pitch);
}

template <typename T>
FGrid2T<T>::FGrid2T(int width, int height,
	element_t* pData /* = NULL */, int pitch /* = 0 */)
: m_size(width, height)
{
	F_ASSERT(m_size.x > 0 && m_size.y > 0);
	m_pData = new T[elementCount()];

	if (pData)
		_copyFrom(pData, pitch);
}

template <typename T>
FGrid2T<T>::FGrid2T(const FGrid2T<T>& other)
: m_pData(NULL),
  m_size(other.m_size)
{
	if (other.m_pData)
	{
		m_pData = new T[elementCount()];
		memcpy(m_pData, other.m_pData, byteCount());
	}
}

template <typename T>
FGrid2T<T>& FGrid2T<T>::operator=(const FGrid2T<T>& other)
{
	if (this == &other)
		return *this;

	clear();
	m_size = other.m_size;

	if (other.m_pData)
	{
		m_pData = new T[elementCount()];
		memcpy(m_pData, other.m_pData, byteCount());
	}
}

template <typename T>
void FGrid2T<T>::resize(const FVector2i& size)
{
	F_ASSERT(size.x > 0 && size.y > 0);

	clear();

	m_size = size;
	m_pData = new T[elementCount()];
}

template <typename T>
inline void FGrid2T<T>::resize(int width, int height)
{
	resize(FVector2i(width, height));
}

template <typename T>
void FGrid2T<T>::clear()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
		m_size.setZero();
	}
}

template <typename T>
inline typename FGrid2T<T>::element_t* FGrid2T<T>::dataAt(const FVector2i& pos)
{
	return m_pData + pos.y * size.x + pos.x;
}

template <typename T>
inline const typename FGrid2T<T>::element_t* FGrid2T<T>::dataAt(const FVector2i& pos) const
{
	return m_pData + pos.y * size.x + pos.x;
}

template <typename T>
void FGrid2T<T>::_copyFrom(T* pSrc, int pitch)
{
	F_ASSERT(pSrc);

	int dy = fMax(m_size.x, pitch);
	T* pDst = m_pData;

	for (int y = 0; y < m_size.y; ++y)
	{
		for (int x = 0; x < m_size.x; ++x)
			pDst[x] = pSrc[x];

		pSrc += dy;
		pDst += m_size.y;
	}
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_GRID2T_H