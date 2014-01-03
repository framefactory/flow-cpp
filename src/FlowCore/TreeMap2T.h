// -----------------------------------------------------------------------------
//  File        TreeMap2T.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TREEMAP2T_H
#define FLOWCORE_TREEMAP2T_H

#include "FlowCore/Library.h"
#include "FlowCore/Rect2T.h"

#include <vector>

// -----------------------------------------------------------------------------
//  Class FTreeMap2T
// -----------------------------------------------------------------------------

// Source: http://www.blackpawn.com/texts/lightmaps/default.html

/// Packs a rectangular area with rectangles of arbitrary size.
/// The algorithm tries to tightly pack the rectangles within the
/// available area. To best serve the greedy algorithm, insert
/// the rectangles sorted by decreasing height or width.
template <typename T>
class FTreeMap2T
{
	//  Public types -------------------------------------------------
	
public:
	/// The type of the coordinate values.
	typedef T value_t;
	/// The type of a rectangle.
	typedef typename FRect2T<T> rect_t;
	/// Const iterator.
	typedef typename std::vector<const rect_t*>::const_iterator const_iterator;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates an empty map for a rectangular area of the given size.
	FTreeMap2T(T width, T height);
	/// Creates an empty map for a rectangular area of the given size.
	FTreeMap2T(const FVector2T<T>& size);
	/// Destructor.
	~FTreeMap2T() { clear(); }

	//  Public commands ----------------------------------------------

public:
		/// Inserts a rectangle of the given size. Returns the position
	/// and size of the rectangle within the map. If the rectangle
	/// doesn't fit, null is returned.
	const rect_t* insert(T width, T height);
	/// Inserts a rectangle of the given size. Returns the position
	/// and size of the rectangle within the map. If the rectangle
	/// doesn't fit, null is returned.
	const rect_t* insert(const FVector2T<T>& size);

	/// Clears the map.
	void clear();
	/// Clears and resizes the map.
	void reset(T width, T height);
	/// Clears and resizes the map.
	void reset(const FVector2T<T>& size);


	//  Public queries -----------------------------------------------

	/// Returns the number of rectangles in the map.
	size_t size() const { return m_rects.size(); }
	/// Returns true if the map is empty.
	bool empty() const { return m_rects.empty(); }

	/// Returns the width of the map.
	const T width() const { return m_width; }
	/// Returns the height of the map.
	const T height() const { return m_height; }
	/// Returns the coverage of the map.
	const double coverage() const {
		return m_areaUsed / (double)(m_width * m_height); }

	/// Returns a const iterator to the first rectangle in the map.
	const_iterator cbegin() const { return m_rects.cbegin(); }
	/// Returns a const iterator to one past the last rectangle in the map.
	const_iterator cend() const { return m_rects.cend(); }

	//  Internal data members ----------------------------------------

private:
	struct node_t
	{
		node_t() : taken(false), pLeftChild(NULL), pRightChild(NULL) { }
		const rect_t* insert(const FVector2T<T>& size);
		void clear();

		rect_t rect;
		bool taken;
		node_t* pLeftChild;
		node_t* pRightChild;
	};

	node_t m_root;
	T m_width;
	T m_height;

	typedef std::vector<const rect_t*> rectVec_t;
	rectVec_t m_rects;
	value_t m_areaUsed;
};

// Members ---------------------------------------------------------------------

template <typename T>
FTreeMap2T<T>::FTreeMap2T(T width, T height)
	: m_width(width), m_height(height), m_areaUsed(T(0))
{
	F_ASSERT(m_width > T(0) && m_height > T(0));
	m_root.rect.set(m_width, m_height);
}

template <typename T>
FTreeMap2T<T>::FTreeMap2T(const FVector2T<T>& size)
	: m_width(size.x), m_height(size.y), m_areaUsed(T(0))
{
	F_ASSERT(m_width > T(0) && m_height > T(0));
	m_root.rect.set(m_width, m_height);
}

template <typename T>
inline typename const FTreeMap2T<T>::rect_t*
	FTreeMap2T<T>::insert(T width, T height)
{
	insert(FVector2T<T>(width, height));
}

template <typename T>
typename const FTreeMap2T<T>::rect_t*
	FTreeMap2T<T>::insert(const FVector2T<T>& size)
{
	const rect_t* pRect = m_root.insert(size);
	
	if (pRect)
	{
		m_rects.push_back(pRect);
		m_areaUsed += pRect->area();

		F_ASSERT(pRect->width() == size.x);
		F_ASSERT(pRect->height() == size.y);
		F_ASSERT(pRect->xMin() >= 0);
		F_ASSERT(pRect->yMin() >= 0);
		F_ASSERT(pRect->xMax() <= m_width);
		F_ASSERT(pRect->yMax() <= m_height);
	}

	return pRect;
}

template <typename T>
void FTreeMap2T<T>::clear()
{
	m_root.clear();
	m_rects.clear();
	m_areaUsed = T(0);
}

template <typename T>
void FTreeMap2T<T>::reset(T width, T height)
{
	clear();
	m_width = width;
	m_height = height;
	m_root.rect.set(m_width, m_height);
}

template <typename T>
inline void FTreeMap2T<T>::reset(const FVector2T<T>& size)
{
	reset(size.x, size.y);
}

template <typename T>
typename const FTreeMap2T<T>::rect_t*
	FTreeMap2T<T>::node_t::insert(const FVector2T<T>& size)
{
	if (pLeftChild != NULL) // not a leaf node
	{
		// try to insert in left branch
		const rect_t* pNewRect = pLeftChild->insert(size);
		if (pNewRect)
			return pNewRect;

		// try to insert in right branch
		return pRightChild->insert(size);
	}
	else // leaf node
	{
		if (taken)
			return NULL;

		if (size.x > rect.width() || size.y > rect.height())
			return NULL;

		if (size == rect.size())
		{
			taken = true;
			return &rect;
		}

		pLeftChild = new node_t();
		pRightChild = new node_t();

		T dw = rect.width() - size.x;
		T dh = rect.height() - size.y;

		if (dw > dh)
		{
			pLeftChild->rect.set(rect.xMin(), rect.yMin(),
				rect.xMin() + size.x, rect.yMax());
			pRightChild->rect.set(rect.xMin() + size.x, rect.yMin(),
				rect.xMax(), rect.yMax());
		}
		else
		{
			pLeftChild->rect.set(rect.xMin(), rect.yMin(),
				rect.xMax(), rect.yMin() + size.y);
			pRightChild->rect.set(rect.xMin(), rect.yMin() + size.y,
				rect.xMax(), rect.yMax());
		}

		return pLeftChild->insert(size);
	}
}

template <typename T>
void FTreeMap2T<T>::node_t::clear()
{
	if (pLeftChild)
	{
		pLeftChild->clear();
		delete pLeftChild;
		pLeftChild = NULL;
	}

	if (pRightChild)
	{
		pRightChild->clear();
		delete pRightChild;
		pRightChild = NULL;
	}
}

// Typedefs --------------------------------------------------------------------

typedef FTreeMap2T<float> FTreeMap2f;
typedef FTreeMap2T<double> FTreeMap2d;
typedef FTreeMap2T<int32_t> FTreeMap2i;
typedef FTreeMap2T<uint32_t> FTreeMap2ui;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_TREEMAP2T_H