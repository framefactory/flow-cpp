// -----------------------------------------------------------------------------
//  File        ValueTrackT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_VALUETRACKT_H
#define FLOWENGINE_VALUETRACKT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/KeyTrackT.h"
#include "FlowEngine/ValueKeyT.h"
#include "FlowEngine/ValueTrackIteratorT.h"

// -----------------------------------------------------------------------------
//  Class FValueTrackT
// -----------------------------------------------------------------------------

template <typename TimeT, typename ValueT>
class FValueTrackT : public FKeyTrackT<TimeT>
{
	//  Public types -------------------------------------------------
	  
public:
	typedef FValueKeyT<TimeT, ValueT> key_type;
	typedef ValueT value_type;
	typedef FValueTrackIteratorT<TimeT, ValueT> track_iterator;

	//  Constructors and destructor ----------------------------------

	/// Default Constructor.
	FValueTrackT();
	/// Virtual destructor.
	virtual ~FValueTrackT();

	//  Public commands ----------------------------------------------

	/// Inserts a key with the given value at the given time.
	key_type* insertKey(const time_type& time, const value_type& val);

	/// Removes and returns the key at the given time.
	/// The caller takes ownership of the key object.
	key_type* takeKey(const time_type& time);

	//  Public queries -----------------------------------------------

	/// Creates and returns an iterator for this track.
	/// The caller takes ownership.
	virtual track_iterator* createIterator();

	//  Internal functions -------------------------------------------

protected:
	virtual key_type* _createKey(const time_type& time) const;
};

// Constructors and destructor -------------------------------------------------

template <typename TimeT, typename ValueT>
FValueTrackT<TimeT, ValueT>::FValueTrackT()
{
}

template <typename TimeT, typename ValueT>
FValueTrackT<TimeT, ValueT>::~FValueTrackT()
{
}

// Public commands -------------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FValueTrackT<TimeT, ValueT>::key_type*
	FValueTrackT<TimeT, ValueT>::insertKey(const time_type& time, const value_type& val)
{
	key_type* pKey = dynamic_cast<key_type*>(FKeyTrackT<TimeT>::insertKey(time));
	F_ASSERT(pKey);
	pKey->setValue(val);
	return pKey;
}

template <typename TimeT, typename ValueT>
typename FValueTrackT<TimeT, ValueT>::key_type*
	FValueTrackT<TimeT, ValueT>::takeKey(const time_type& time)
{
	return dynamic_cast<key_type*>(FKeyTrackT<TimeT>::takeKey(time));
}

// Public queries --------------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FValueTrackT<TimeT, ValueT>::track_iterator*
	FValueTrackT<TimeT, ValueT>::createIterator()
{
	return new track_iterator(&m_keys);
}

// Internal functions ----------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FValueTrackT<TimeT, ValueT>::key_type*
	FValueTrackT<TimeT, ValueT>::_createKey(const time_type& time) const
{
	return new key_type(time);
}
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_VALUETRACKT_H