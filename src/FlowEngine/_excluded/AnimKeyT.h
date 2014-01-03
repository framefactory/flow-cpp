// -----------------------------------------------------------------------------
//  File        AnimKeyT.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_ANIMKEYT_H
#define FLOWENGINE_ANIMKEYT_H

#include "FlowEngine/Library.h"
#include "FlowEngine/ValueKeyT.h"
#include "FlowEngine/InterpolationMode.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FAnimKeyT
// -----------------------------------------------------------------------------

template <typename TimeT, typename ValueT>
class FAnimKeyT : public FValueKeyT<TimeT, ValueT>
{
	//  Public types -------------------------------------------------

public:
	typedef TimeT time_type;
	typedef ValueT value_type;

	//  Constructors and destructor ----------------------------------

	/// Creates a key with the given absolute time.
	FAnimKeyT(const time_type& time);
	/// Creates a new key frame from the given time and value.
	/// The interpolation defaults to Hold.
	FAnimKeyT(const time_type& time, const value_type& val);
	/// Creates a new key frame with handle data.
	/// The interpolation defaults to Bezier.
	FAnimKeyT(const time_type& time, const time_type& lhTime, const time_type& rhTime,
		const value_type& keyVal, const value_type& lhVal, const value_type& rhVal);

protected:
	/// Protected default constructor.
	FAnimKeyT() { }
	/// Protected copy constructor. Use clone() to create a copy of this.
	FAnimKeyT(const FAnimKeyT<TimeT, ValueT>& other);
	/// Protected assignment operator. Use clone() to create a copy of this.
	FAnimKeyT<TimeT, ValueT>& operator=(const FAnimKeyT<TimeT, ValueT>& other);

	//  Public commands ----------------------------------------------

public:
	/// Sets the absolute time of the left handle.
	virtual void setLeftHandleTime(const time_type& lhTime);
	/// Sets the absolute time of the right handle.
	virtual void setRightHandleTime(const time_type& rhTime);

	/// Sets the absolute value of the left handle.
	virtual void setLeftHandleValue(const value_type& lhVal);
	/// Sets the absolute value of the right handle.
	virtual void setRightHandleValue(const value_type& rhVal);

	/// Sets the interpolation scheme for the interval starting at this key.
	virtual void setInterpolationMode(FInterpolationMode mode);

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the absolute time of the left handle.
	time_type leftHandleTime() const;
	/// Returns the absolute time of the right handle.
	time_type rightHandleTime() const;

	/// Returns the absolute value of the left handle.
	value_type leftHandleValue() const;
	/// Returns the absolute value of the right handle.
	value_type rightHandleValue() const;

	/// Returns the interpolation scheme for the interval starting at this key.
	FInterpolationMode interpolationMode() const;

	/// Returns a clone of the key.
	virtual FAnimKeyT<TimeT, ValueT>* clone() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

//  Internal data members --------------------------------------------

private:
	time_type m_lhRelTime;
	time_type m_rhRelTime;

	value_type m_lhRelValue;
	value_type m_rhRelValue;

	FInterpolationMode m_interpolationMode;
};

// Public members --------------------------------------------------------------

template <typename TimeT, typename ValueT>
inline FAnimKeyT<TimeT, ValueT>::FAnimKeyT(const time_type& time)
	: FValueKeyT<TimeT, ValueT>(time),
	m_interpolationMode(FInterpolationMode::Invalid)
{
}

template <typename TimeT, typename ValueT>
inline FAnimKeyT<TimeT, ValueT>::FAnimKeyT(const time_type& time, const value_type& val)
	: FValueKeyT<TimeT, ValueT>(time, val),
	  m_interpolationMode(FInterpolationType::Hold)
{
}

template <typename TimeT, typename ValueT>
inline FAnimKeyT<TimeT, ValueT>::FAnimKeyT(
	const time_type& keyTime, const time_type& lhTime, const time_type& rhTime,
	const value_type& keyVal, const value_type& lhVal, const value_type& rhVal)
	: FValueKeyT<TimeT, ValueT>(keyTime, keyVal),
	  m_lhRelTime(keyTime - lhTime),
	  m_rhRelTime(keyTime - rhTime),
	  m_lhRelValue(keyVal - lhVal),
	  m_rhRelValue(keyVal - rhVal),
	  m_interpolationMode(FInterpolationMode::Bezier)
{
}

template <typename TimeT, typename ValueT>
inline FAnimKeyT<TimeT, ValueT>::FAnimKeyT(const FAnimKeyT<TimeT, ValueT>& other)
	: FValueKeyT<TimeT, ValueT>(other),
	  m_lhRelTime(other.m_lhRelTime),
	  m_rhRelTime(other.m_rhRelTime),
	  m_lhRelValue(other.m_lhRelValue),
	  m_rhRelValue(other.m_rhRelValue),
	  m_interpolationMode(other.m_interpolationMode)
{
}

template <typename TimeT, typename ValueT>
inline void FAnimKeyT<TimeT, ValueT>::setLeftHandleTime(const time_type& lhTime)
{
	m_lhRelTime = lhTime - time();
}

template <typename TimeT, typename ValueT>
inline void FAnimKeyT<TimeT, ValueT>::setRightHandleTime(const time_type& rhTime)
{
	m_rhRelTime = rhTime - time();
}

template <typename TimeT, typename ValueT>
inline void FAnimKeyT<TimeT, ValueT>::setLeftHandleValue(const value_type& lhVal)
{
	m_lhRelValue = lhVal - value();
}

template <typename TimeT, typename ValueT>
inline void FAnimKeyT<TimeT, ValueT>::setRightHandleValue(const value_type& rhVal)
{
	m_rhRelValue = rhVal - value();
}

template <typename TimeT, typename ValueT>
inline void FAnimKeyT<TimeT, ValueT>::setInterpolationMode(FInterpolationMode mode)
{
	m_interpolationMode = mode;
}

template <typename TimeT, typename ValueT>
inline typename FAnimKeyT<TimeT, ValueT>::time_type
	FAnimKeyT<TimeT, ValueT>::leftHandleTime() const
{
	return time() + m_lhRelTime;
}

template <typename TimeT, typename ValueT>
inline typename FAnimKeyT<TimeT, ValueT>::time_type
	FAnimKeyT<TimeT, ValueT>::rightHandleTime() const
{
	return time() + m_rhRelTime;
}

template <typename TimeT, typename ValueT>
inline typename FAnimKeyT<TimeT, ValueT>::value_type 
	FAnimKeyT<TimeT, ValueT>::leftHandleValue() const
{
	return value() + m_lhRelValue;
}

template <typename TimeT, typename ValueT>
inline typename FAnimKeyT<TimeT, ValueT>::value_type 
	FAnimKeyT<TimeT, ValueT>::rightHandleValue() const
{
	return value() + m_rhRelValue;
}

template <typename TimeT, typename ValueT>
inline FInterpolationMode FAnimKeyT<TimeT, ValueT>::interpolationMode() const
{
	return m_interpolationMode;
}

template <typename TimeT, typename ValueT>
void FAnimKeyT<TimeT, ValueT>::serialize(FArchive& ar)
{
	// call base class implementation
	FValueKeyT<TimeT, ValueT>::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_lhRelTime;
		ar << m_rhRelTime;
		ar << m_lhRelValue;
		ar << m_rhRelValue;
		ar << m_interpolationMode;
	}
	else // isReading
	{
		ar >> m_lhRelTime;
		ar >> m_rhRelTime;
		ar >> m_lhRelValue;
		ar >> m_rhRelValue;
		ar >> m_interpolationMode;
	}
}

template <typename TimeT, typename ValueT>
FAnimKeyT<TimeT, ValueT>* FAnimKeyT<TimeT, ValueT>::clone() const
{
	return new FAnimKeyT<TimeT, ValueT>(*this);
}

#ifdef FLOW_DEBUG
template <typename TimeT, typename ValueT>
void FAnimKeyT<TimeT, ValueT>::dump(std::wostream& stream) const
{
	stream << L"T: " << m_time << L", V: " << m_value
		<< ", IP: " << m_interpolationMode << L" (a FAnimKeyT<TimeT, ValueT>)";
}
#endif

// Related non-member functions ------------------------------------------------

template <typename TimeT, typename ValueT>
inline FArchive& operator<<(FArchive& ar, const FAnimKeyT<TimeT, ValueT>& key)
{
	key.serialize(ar);
	return ar;
}

template <typename TimeT, typename ValueT>
inline FArchive& operator>>(FArchive& ar, FAnimKeyT<TimeT, ValueT>& key)
{
	key.serialize(ar);
	return ar;
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_ANIMKEYT_H