// -----------------------------------------------------------------------------
//  File        KeyTrackT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_KEYTRACKT_H
#define FLOWENGINE_KEYTRACKT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/TimeKeyT.h"
#include "FlowEngine/KeyTrackIteratorT.h"

#include <vector>
#include <map>
#include <utility>
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FKeyTrackT
// -----------------------------------------------------------------------------

template <typename TimeT>
class FKeyTrackT
{
	//  Public types -------------------------------------------------

public:
	typedef typename FTimeKeyT<TimeT> key_type;
	typedef TimeT time_type;
	typedef std::vector<key_type*> key_vector_type;
	typedef std::pair<key_type*, key_type*> key_range_type;
	typedef std::map<time_type, key_type*> key_map_type;
	typedef typename key_map_type::iterator key_iterator;
	typedef typename key_map_type::const_iterator key_const_iterator;
	typedef FKeyTrackIteratorT<TimeT> track_iterator;

	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	FKeyTrackT();
	/// Virtual destructor.
	virtual ~FKeyTrackT();

protected:
	/// Copy constructor.
	FKeyTrackT(const FKeyTrackT<TimeT>& other);
	/// Assignment operator.
	FKeyTrackT<TimeT>& operator=(const FKeyTrackT<TimeT>& other);

	//  Public commands ----------------------------------------------

public:
	/// Inserts a key with uninitialized value at the given time.
	virtual key_type* insertKey(const time_type& time);
	/// Inserts the given key. The track takes ownership of the key.
	key_type* insertKey(key_type* pKey);
	/// Removes and returns the key at the given time.
	/// The caller takes ownership of the key.
	key_type* takeKey(const time_type& time);
	/// Deletes the key at the given time.
	/// Returns true if a key was present and has been deleted.
	bool removeKey(const time_type& time);
	/// Deletes the key at the given time.
	/// Returns true if a key was present and has been deleted.
	bool removeKey(key_type* pKey);

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Creates and returns an iterator for this track.
	/// The caller takes ownership.
	virtual track_iterator* createIterator();

	/// Returns true if a key is available at the given time.
	bool hasKey(const time_type& time) const;

	/// Returns the key at the given time.
	key_type* keyAt(const time_type& time) const;
	/// Returns the first key with a time smaller than the given time.
	key_type* keyBefore(const time_type& time) const;
	/// Returns the first key with a time greater than the given time.
	key_type* keyAfter(const time_type& time) const;
	/// Returns two keys where the time of the first key is smaller
	/// or equal, the time of the second key is greater than the given time.
	key_range_type keyRange(const time_type& time) const;

	/// Returns a clone of the track.
	virtual FKeyTrackT<TimeT>* clone() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Iterators ----------------------------------------------------

	/// Returns an iterator pointing at the first key of this track.
	key_iterator begin() { return m_keys.begin(); }
	/// Returns a const iterator pointing at the first key of this track.
	key_const_iterator begin() const { return m_keys.begin(); }
	/// Returns an iterator pointing at one past the last key of this track.
	key_iterator end() { return m_keys.end(); }
	/// Returns a const iterator pointing at one past the last key of this track.
	key_const_iterator end() const { return m_keys.end(); }

	//  Internal functions -------------------------------------------

protected:
	virtual key_type* _createKey(const time_type& time) const;

	//  Internal data members ----------------------------------------

	key_map_type m_keys;
};

// Constructors and destructor -------------------------------------------------

template <typename TimeT>
FKeyTrackT<TimeT>::FKeyTrackT()
{
}

template <typename TimeT>
FKeyTrackT<TimeT>::FKeyTrackT(const FKeyTrackT<TimeT>& other)
{
	for (auto it = other.m_keys.begin(); it != other.m_keys.end(); ++it)
		m_keys.insert(key_map_type::value_type(it->first, it->second->clone()));
}

template <typename TimeT>
FKeyTrackT<TimeT>::~FKeyTrackT()
{
	for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
		delete it->second;
}

// Public commands -------------------------------------------------------------

template <typename TimeT>
typename FKeyTrackT<TimeT>::key_type*
	FKeyTrackT<TimeT>::insertKey(const time_type& time)
{
	F_ASSERT(!hasKey(time));
	key_type* pKey = _createKey(time);

	m_keys.insert(key_map_type::value_type(time, pKey));
	return pKey;
}

template <typename TimeT>
typename FKeyTrackT<TimeT>::key_type* 
	FKeyTrackT<TimeT>::insertKey(key_type* pKey)
{
	F_ASSERT(pKey);
	F_ASSERT(!hasKey(pKey->time()));

	m_keys.insert(key_map_type::value_type(pKey->time(), pKey));
	return pKey;
}

template <typename TimeT>
typename FKeyTrackT<TimeT>::key_type*
	FKeyTrackT<TimeT>::takeKey(const time_type& time)
{
	key_const_iterator it = m_keys.find(time);
	if (it == m_keys.end())
		return NULL;

	key_type* pKey = it->second;
	m_keys.erase(it);
	return pKey;
}

template <typename TimeT>
bool FKeyTrackT<TimeT>::removeKey(const time_type& time)
{
	key_const_iterator it = m_keys.find(time);
	if (it == m_keys.end())
		return false;

	delete it->second;
	m_keys.erase(it);

	return true;
}

template <typename TimeT>
bool FKeyTrackT<TimeT>::removeKey(key_type* pKey)
{
	key_const_iterator it = m_keys.find(pKey->time());
	if (it == m_keys.end())
		return false;

	F_ASSERT(it->second == pKey);
	delete it->second;
	m_keys.erase(it);

	return true;
}

template <typename TimeT>
void FKeyTrackT<TimeT>::serialize(FArchive& ar)
{
	if (ar.isWriting())
	{
		ar << m_keys.size();
		for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
			it->second->serialize(ar);
	}
	else
	{
		F_ASSERT(m_keys.empty());
		key_map_type::size_type n; ar >> n;
		for (key_map_type::size_type i = 0; i < n; ++i)
		{
			key_type* pKey = _createKey(time_type());
			pKey->serialize(ar);
			m_keys.insert(key_map_type::value_type(pKey->time(), pKey));
		}
	}
}

// Public queries --------------------------------------------------------------

template <typename TimeT>
inline typename FKeyTrackT<TimeT>::track_iterator*
	FKeyTrackT<TimeT>::createIterator()
{
	return new track_iterator(&m_keys);
}

template <typename TimeT>
inline bool FKeyTrackT<TimeT>::hasKey(const time_type& time) const
{
	key_const_iterator it = m_keys.find(time);
	return it != m_keys.end();
}

template <typename TimeT>
inline typename FKeyTrackT<TimeT>::key_type* 
	FKeyTrackT<TimeT>::keyAt(const time_type& time) const
{
	key_const_iterator it = m_keys.find(time);
	return (it == m_keys.end()) ? NULL : it->second;
}

template <typename TimeT>
inline typename FKeyTrackT<TimeT>::key_type*
	FKeyTrackT<TimeT>::keyBefore(const time_type& time) const
{
	key_const_iterator it = m_keys.lower_bound(time);
	return (it == m_keys.begin()) ? NULL : (--it)->second;
}

template <typename TimeT>
inline typename FKeyTrackT<TimeT>::key_type*
	FKeyTrackT<TimeT>::keyAfter(const time_type& time) const
{
	key_const_iterator it = m_keys.upper_bound(time);
	return (it == m_keys.end()) ? NULL : it->second;
}

template <typename TimeT>
inline typename FKeyTrackT<TimeT>::key_range_type
	FKeyTrackT<TimeT>::keyRange(const time_type& time) const
{
	key_const_iterator it = m_keys.upper_bound(time);
	key_type* pKeyAfter = (it == m_keys.end()) ? NULL : it->second;
	key_type* pKeyBefore = (it == m_keys.begin()) ? NULL : (--it)->second;
	return key_range_type(pKeyBefore, pKeyAfter);
}

template <typename TimeT>
inline FKeyTrackT<TimeT>* FKeyTrackT<TimeT>::clone() const
{
	return new FKeyTrackT<TimeT>(*this);
}

#ifdef FLOW_DEBUG
template <typename TimeT>
void FKeyTrackT<TimeT>::dump(std::wostream& stream) const
{
	stream << "\n--- FKeyTrackT<TimeT> ---";
	stream << "\n     Keys:    " << m_keys.size();

	size_t i = 0, n = 8;
	for (auto it = m_keys.begin(); it != m_keys.end() && i < n; ++it, ++i)
	{
		stream << "\n     Key #" << i << ": ";
		it->second->dump(stream);
	}

	stream << std::endl;
}
#endif

// Internal functions ----------------------------------------------------------
	
template <typename TimeT>
typename FKeyTrackT<TimeT>::key_type*
	FKeyTrackT<TimeT>::_createKey(const time_type& time) const
{
	return new key_type(time);
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_KEYTRACKT_H