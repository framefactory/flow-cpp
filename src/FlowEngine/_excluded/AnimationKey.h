// -----------------------------------------------------------------------------
//  File        AnimationKey.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_ANIMATIONKEY_H
#define FLOWENGINE_ANIMATIONKEY_H

#include "FlowEngine/Library.h"
#include "FlowEngine/ValueKey.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FAnimationKey
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FAnimationKey : public FValueKey
{
	F_DECLARE_SERIALIZABLE(FAnimationKey);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates an animation key with the given time and value.
	FAnimationKey(FTime time, const FValueArray& val,
		FInterpolationMode mode = FInterpolationMode::Linear);
	/// Creates an animation key with the given time and values.
	FAnimationKey(FTime keyTime, FTime lhTime, FTime rhTime,
		const FValueArray& keyValue, const FValueArray& lhValue,
		const FValueArray& rhValue,
		FInterpolationMode mode = FInterpolationMode::Bezier);


	//  Public commands ----------------------------------------------

	/// Sets the absolute time of the left handle.
	void setLeftHandleTime(FTime time);
	/// Sets the absolute time of the right handle.
	void setRightHandleTime(FTime time);
	/// Sets the absolute value of the left handle.
	void setLeftHandleValue(const FValueArray& val);
	/// Sets the absolute value of the right handle.
	void setRightHandleValue(const FValueArray& val);
	/// Sets the interpolation mode between this and the next key.
	void setInterpolationMode(FInterpolationMode mode);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the absolute time of the left handle.
	FTime leftHandleTime() const { return m_leftHandleTime; }
	/// Returns the absolute time of the right handle.
	FTime rightHandleTime() const { return m_rightHandleTime; }
	/// Returns the absolute value of the left handle.
	const FValueArray& leftHandleValue() const { return m_leftHandleValue; }
	/// Returns the absolute value of the right handle.
	const FValueArray& rightHandleValue() const { return m_rightHandleValue; }
	/// Returns the interpolation mode between this and the next key.
	virtual FInterpolationMode interpolationMode() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Internal data members ----------------------------------------

private:
	FTime m_keyTime;
	FTime m_leftHandleTime;
	FTime m_rightHandleTime;

	FValueArray m_keyValue;
	FValueArray m_leftHandleValue;
	FValueArray m_rightHandleValue;

	FInterpolationMode m_interpolationMode;
};

// Inline members --------------------------------------------------------------

inline void FAnimationKey::setLeftHandleTime(FTime time)
{
	m_leftHandleTime = time;
}

inline void FAnimationKey::setRightHandleTime(FTime time)
{
	m_rightHandleTime = time;
}

inline void FAnimationKey::setLeftHandleValue(const FValueArray& val)
{
	m_leftHandleValue = val;
}

inline void FAnimationKey::setRightHandleValue(const FValueArray& val)
{
	m_rightHandleValue = val;
}

inline void FAnimationKey::setInterpolationMode(FInterpolationMode mode)
{
	m_interpolationMode = mode;
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_ANIMATIONKEY_H
