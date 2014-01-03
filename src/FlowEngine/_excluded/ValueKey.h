// -----------------------------------------------------------------------------
//  File        ValueKey.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_VALUEKEY_H
#define FLOWENGINE_VALUEKEY_H

#include "FlowEngine/Library.h"
#include "FlowEngine/InterpolationMode.h"

#include "FlowCore/Object.h"
#include "FlowCore/Time.h"
#include "FlowCore/ValueArray.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FValueKey
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FValueKey : public FObject
{
	F_DECLARE_SERIALIZABLE(FValueKey);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a new key with the given time.
	FValueKey(FTime time);
	/// Creates a new key with the given time and value.
	FValueKey(FTime time, const FValueArray& val);

	/// Virtual destructor.
	virtual ~FValueKey();

	//  Public commands ----------------------------------------------

public:
	/// Sets the time of this key.
	void setTime(FTime time);
	/// Sets the value of this key.
	void setValue(const FValueArray& val);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the time of this key.
	FTime time() const { return m_time; }
	/// Returns the value of this key.
	const FValueArray& value() const { return m_value; }
	/// Returns the interpolation mode.
	virtual FInterpolationMode interpolationMode() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Internal data members ----------------------------------------

private:
	FTime m_time;
	FValueArray m_value;
};

// Inline members --------------------------------------------------------------

inline void FValueKey::setTime(FTime time)
{
	m_time = time;
}

inline void FValueKey::setValue(const FValueArray& val)
{
	m_value = val;
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_VALUEKEY_H