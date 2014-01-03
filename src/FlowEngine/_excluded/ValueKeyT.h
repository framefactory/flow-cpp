// -----------------------------------------------------------------------------
//  File        ValueKeyT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_VALUEKEYT_H
#define FLOWENGINE_VALUEKEYT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/TimeKeyT.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FValueKeyT
// -----------------------------------------------------------------------------

template <typename TimeT, typename ValueT>
class FValueKeyT : public FTimeKeyT<TimeT>
{
	//  Public types -------------------------------------------------

public:
	typedef TimeT time_type;
	typedef ValueT value_type;

	//  Constructors and destructor ----------------------------------

	/// Creates a key with the given absolute time.
	FValueKeyT(const time_type& time)
		: FTimeKeyT<TimeT>(time) { }
	/// Creates a new key frame from the given time and value.
	FValueKeyT(const time_type& time, const value_type& val)
		: FTimeKeyT<TimeT>(time), m_value(val) { }
 
protected:
	/// Protected default constructor.
	FValueKeyT() { }
	/// Protected copy constructor. Use clone() to create a copy of this.
	FValueKeyT(const FValueKeyT<TimeT, ValueT>& other);
	/// Protected assignment operator. Use clone() to create a copy of this.
	FValueKeyT<TimeT, ValueT>& operator=(const FValueKeyT<TimeT, ValueT>& other);

	//  Public commands ----------------------------------------------

public:
	/// Sets the absolute value of the key.
	void setValue(const value_type& val) { m_value = val; }

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the absolute value of the key.
	const value_type& value() const { return m_value; }

	/// Returns a clone of the key.
	virtual FValueKeyT<TimeT, ValueT>* clone() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Internal data members ----------------------------------------

protected:
	value_type m_value;
};

// Public members --------------------------------------------------------------

template <typename TimeT, typename ValueT>
inline FValueKeyT<TimeT, ValueT>::FValueKeyT(const FValueKeyT<TimeT, ValueT>& other)
	: FTimeKeyT<TimeT>(other), m_value(other.m_value)
{
}

template <typename TimeT, typename ValueT>
void FValueKeyT<TimeT, ValueT>::serialize(FArchive& ar)
{
	// call base class implementation
	FTimeKeyT<TimeT>::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_value;
	}
	else // isReading
	{
		ar >> m_value;
	}
}

template <typename TimeT, typename ValueT>
FValueKeyT<TimeT, ValueT>* FValueKeyT<TimeT, ValueT>::clone() const
{
	return new FValueKeyT<TimeT, ValueT>(*this);
}

#ifdef FLOW_DEBUG
template <typename TimeT, typename ValueT>
void FValueKeyT<TimeT, ValueT>::dump(std::wostream& stream) const
{
	stream << L"T: " << m_time << L", V: " << m_value << L" (a FValueKeyT<TimeT, ValueT>)";
}
#endif

// Related non-member functions ------------------------------------------------

template <typename TimeT, typename ValueT>
inline FArchive& operator<<(FArchive& ar, const FValueKeyT<TimeT, ValueT>& key)
{
	key.serialize(ar);
	return ar;
}

template <typename TimeT, typename ValueT>
inline FArchive& operator>>(FArchive& ar, FValueKeyT<TimeT, ValueT>& key)
{
	key.serialize(ar);
	return ar;
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_VALUEKEYT_H