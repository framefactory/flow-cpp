// -----------------------------------------------------------------------------
//  File        AnimationKey.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#include "FlowEngine/AnimationKey.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FAnimationKey
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FAnimationKey, FValueKey, 1);

// Constructors and destructor -------------------------------------------------

FAnimationKey::FAnimationKey(FTime time, const FValueArray& val,
	FInterpolationMode mode /* = FInterpolationMode::Linear */)
	: FValueKey(time, val),
	  m_leftHandleTime(time),
	  m_rightHandleTime(time),
	  m_leftHandleValue(val),
	  m_rightHandleValue(val),
	  m_interpolationMode(mode)
{
}

FAnimationKey::FAnimationKey(FTime keyTime, FTime lhTime, FTime rhTime,
	const FValueArray& keyValue, const FValueArray& lhValue,
	const FValueArray& rhValue,
	FInterpolationMode mode /* = FInterpolationMode::Bezier */)
	: FValueKey(keyTime, keyValue),
	  m_leftHandleTime(lhTime),
	  m_rightHandleTime(rhTime),
	  m_leftHandleValue(lhValue),
	  m_rightHandleValue(rhValue),
	  m_interpolationMode(mode)
{
}

// Public commands -------------------------------------------------------------

void FAnimationKey::serialize(FArchive& ar)
{
	if (ar.isReading())
	{
		ar >> m_leftHandleTime;
		ar >> m_rightHandleTime;
		ar >> m_leftHandleValue;
		ar >> m_rightHandleValue;
		ar >> m_interpolationMode;
	}
	else // isWriting
	{
		ar << m_leftHandleTime;
		ar << m_rightHandleTime;
		ar << m_leftHandleValue;
		ar << m_rightHandleValue;
		ar << m_interpolationMode;
	}
}

// Public queries --------------------------------------------------------------

FInterpolationMode FAnimationKey::interpolationMode() const
{
	return m_interpolationMode;
}

#ifdef FLOW_DEBUG
void FAnimationKey::dump(std::wostream& stream) const
{
	FValueKey::dump(stream);
	stream << "\n--- FAnimationKey ---";
	stream << "\n     LH Time:  " << m_leftHandleTime;
	stream << "\n     LH Value: " << m_leftHandleValue;
	stream << "\n     RH Time:  " << m_rightHandleTime;
	stream << "\n     RH Value: " << m_rightHandleValue;
	stream << "\n     Interpol. " << m_interpolationMode;
}
#endif

// -----------------------------------------------------------------------------