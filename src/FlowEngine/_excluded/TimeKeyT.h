// -----------------------------------------------------------------------------
//  File        TimeKeyT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_TIMEKEYT_H
#define FLOWENGINE_TIMEKEYT_H

#include "FlowEngine/Library.h"
#include "FlowCore/Archive.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FTimeKeyT
// -----------------------------------------------------------------------------

template <typename TimeT>
class FTimeKeyT
{
	//  Public types -------------------------------------------------

public:
	typedef TimeT time_type;

	//  Constructors and destructor ----------------------------------

	/// Creates a key with the given absolute time.
	FTimeKeyT(const time_type& time)
		: m_time(time) { }

protected:
	/// Protected default constructor.
	FTimeKeyT() { }
	/// Protected copy constructor. Use clone() to create a copy of this.
	FTimeKeyT(const FTimeKeyT<TimeT>& other) : m_time(other.m_time) { }
	/// Protected assignment operator. Use clone() to create a copy of this.
	FTimeKeyT<TimeT>& operator=(const FTimeKeyT<TimeT>& other);

	//  Public commands ----------------------------------------------

public:
	/// Sets the absolute time of the key.
	void setTime(const time_type& time) { m_time = time; }

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the absolute time of the key.
	const time_type& time() const { return m_time; }

	/// Returns a clone of the key.
	virtual FTimeKeyT<TimeT>* clone() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Internal data members ----------------------------------------

protected:
	time_type m_time;
};

// Public members --------------------------------------------------------------

template <typename TimeT>
void FTimeKeyT<TimeT>::serialize(FArchive& ar)
{
	if (ar.isWriting())
	{
		ar << m_time;
	}
	else // isReading
	{
		ar >> m_time;
	}
}

template <typename TimeT>
FTimeKeyT<TimeT>* FTimeKeyT<TimeT>::clone() const
{
	return new FTimeKeyT<TimeT>(*this);
}

#ifdef FLOW_DEBUG
template <typename TimeT>
void FTimeKeyT<TimeT>::dump(std::wostream& stream) const
{
	stream << "T: " << m_time << " (a FTimeKeyT<TimeT>)";
}
#endif

// Related non-member functions ------------------------------------------------

template <typename TimeT>
inline FArchive& operator<<(FArchive& ar, const FTimeKeyT<TimeT>& key)
{
	key.serialize(ar);
	return ar;
}

template <typename TimeT>
inline FArchive& operator>>(FArchive& ar, FTimeKeyT<TimeT>& key)
{
	key.serialize(ar);
	return ar;
}
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_TIMEKEYT_H