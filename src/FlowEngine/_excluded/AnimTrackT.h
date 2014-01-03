// -----------------------------------------------------------------------------
//  File        AnimTrackT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_ANIMTRACKT_H
#define FLOWENGINE_ANIMTRACKT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/ValueTrackT.h"
#include "FlowEngine/AnimKeyT.h"
#include "FlowEngine/AnimTrackIteratorT.h"

// -----------------------------------------------------------------------------
//  Class FAnimTrackT
// -----------------------------------------------------------------------------

template <typename TimeT, typename ValueT>
class FAnimTrackT : public FValueTrackT<TimeT, ValueT>
{
	//  Public types -------------------------------------------------

public:
	typedef FAnimKeyT<TimeT, ValueT> key_type;
	typedef FAnimTrackIteratorT<TimeT, ValueT> track_iterator;

	//  Constructors and destructor ----------------------------------

	/// Default Constructor.
	FAnimTrackT();
	/// Virtual destructor.
	virtual ~FAnimTrackT();

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
FAnimTrackT<TimeT, ValueT>::FAnimTrackT()
{
}

template <typename TimeT, typename ValueT>
FAnimTrackT<TimeT, ValueT>::~FAnimTrackT()
{
}

// Public commands -------------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FAnimTrackT<TimeT, ValueT>::key_type*
	FAnimTrackT<TimeT, ValueT>::insertKey(const time_type& time, const value_type& val)
{
	key_type* pKey = dynamic_cast<key_type*>(FKeyTrackT<TimeT>::insertKey(time));
	F_ASSERT(pKey);
	pKey->setValue(val);
	return pKey;
}

template <typename TimeT, typename ValueT>
typename FAnimTrackT<TimeT, ValueT>::key_type*
	FAnimTrackT<TimeT, ValueT>::takeKey(const time_type& time)
{
	return dynamic_cast<key_type*>(FKeyTrackT<TimeT>::takeKey(time));
}

// Public queries --------------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FAnimTrackT<TimeT, ValueT>::track_iterator*
	FAnimTrackT<TimeT, ValueT>::createIterator()
{
	return new track_iterator(&m_keys);
}

// Internal functions ----------------------------------------------------------

template <typename TimeT, typename ValueT>
typename FAnimTrackT<TimeT, ValueT>::key_type*
	FAnimTrackT<TimeT, ValueT>::_createKey(const time_type& time) const
{
	return new key_type(time);
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_ANIMTRACKT_H