// -----------------------------------------------------------------------------
//  File        AnimationTrack.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#include "FlowEngine/AnimationTrack.h"
#include "FlowEngine/AnimTrackT.h"
#include "FlowEngine/DataArray.h"

#include "FlowCore/String.h"
#include "FlowCore/AutoConvert.h"
#include "FlowCore/MemoryTracer.h"


typedef FKeyTrackT<FTime> keyTrack_t;
typedef FAnimTrackT<FTime, double> animTrack_t;
typedef FValueTrackT<FTime, bool> valueTrackBool_t;
typedef FValueTrackT<FTime, int32_t> valueTrackInt_t;
typedef FValueTrackT<FTime, double> valueTrackDouble_t;
typedef FValueTrackT<FTime, wstring_t> valueTrackString_t;
typedef animTrack_t::key_type animKey_t;

// -----------------------------------------------------------------------------
//  Class FAnimationTrack
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FAnimationTrack, FInstance, 1);

// Constructors and destructor -------------------------------------------------

FAnimationTrack::FAnimationTrack(
	FTrackType trackType, const FUniqueId& id)
: FMessageTarget(id),
  m_trackType(trackType),
  m_pDataTarget(NULL)
{
	_createTrack();
}

FAnimationTrack::FAnimationTrack(
	FDataArray* pDataTarget, FTrackType trackType, const FUniqueId& id)
: FMessageTarget(id),
  m_trackType(trackType),
  m_pDataTarget(pDataTarget)
{
	_createTrack();
	_createIterators();
}

FAnimationTrack::FAnimationTrack(
	FAnimationTrack* pMaster, const FUniqueId& id)
: FMessageTarget(id, pMaster),
  m_pTrack(pMaster->m_pTrack),
  m_trackType(pMaster->m_trackType),
  m_pDataTarget(NULL)
{
}

FAnimationTrack::FAnimationTrack(
	FDataArray* pDataTarget, FAnimationTrack* pMaster, const FUniqueId& id)
: FMessageTarget(id, pMaster),
  m_pTrack(pMaster->m_pTrack),
  m_trackType(pMaster->m_trackType),
  m_pDataTarget(pDataTarget)
{
	_createIterators();
}

FAnimationTrack::~FAnimationTrack()
{
	for (size_t i = 0, n = m_iterators.size(); i < n; ++i)
		F_SAFE_DELETE(m_iterators[i]);

	if (!isReference())
		F_SAFE_DELETE(m_pTrack);
}

// Public commands -------------------------------------------------------------

void FAnimationTrack::setTime(FTime time)
{
	F_ASSERT(m_pDataTarget);
	if (!m_pDataTarget)
		return;

	m_iterators[0]->setTime(time);

	_evaluate();
}

void FAnimationTrack::advanceTime(FTime time)
{
	F_ASSERT(m_pDataTarget);
	if (!m_pDataTarget)
		return;

	int32_t count = m_iterators[0]->advanceTime(time);
	m_pDataTarget->fire(0, count);

	_evaluate();
}

void FAnimationTrack::setTime(const FValueArray* pTime)
{
	F_ASSERT(m_pDataTarget);
	if (!m_pDataTarget)
		return;

	for (int32_t i = 0, n = (int32_t)m_iterators.size(); i < n; ++i)
		m_iterators[i]->setTime(FTime(pTime->to<double>(i, 0)));

	_evaluate();
}

void FAnimationTrack::advanceTime(const FValueArray* pTime)
{
	F_ASSERT(m_pDataTarget);
	if (!m_pDataTarget)
		return;

	for (int32_t i = 0, n = (int32_t)m_iterators.size(); i < n; ++i)
	{
		int32_t count = m_iterators[i]->advanceTime(FTime(pTime->to<double>(i, 0)));
		m_pDataTarget->fire(i, count);
	}

	_evaluate();
}

bool FAnimationTrack::changeKey(const FValueKey* pKey, FTime offset)
{
	if (m_trackType == FTrackType::Trigger)
		return false;

	keyTrack_t::key_type* pChangedKey = m_pTrack->takeKey(pKey->time());
	if (!pChangedKey)
		return false;

	_setKeyValues(pKey, pChangedKey);
	pChangedKey->setTime(pKey->time() + offset);
	m_pTrack->insertKey(pChangedKey);

	_resetIterators();
	return true;
}

void FAnimationTrack::changeKeys(const key_vector_type& keys, FTime offset)
{
	keyTrack_t::key_vector_type changedKeys;
	changedKeys.reserve(keys.size());

	for (size_t i = 0, n = keys.size(); i < n; ++i)
	{
		keyTrack_t::key_type* pKey = m_pTrack->takeKey(keys[i]->time());
		if (pKey)
		{
			_setKeyValues(keys[i], pKey);
			pKey->setTime(keys[i]->time() + offset);
			changedKeys.push_back(pKey);
		}
	}

	for (size_t i = 0, n = keys.size(); i < n; ++i)
		m_pTrack->insertKey(changedKeys[i]);

	_resetIterators();
}

bool FAnimationTrack::moveKey(FTime time, FTime offset)
{
	keyTrack_t::key_type* pKey = m_pTrack->takeKey(time);
	if (!pKey)
		return false;

	pKey->setTime(time + offset);
	m_pTrack->insertKey(pKey);

	_resetIterators();
	return true;
}

void FAnimationTrack::moveKeys(const time_vector_type& times, FTime offset)
{
	keyTrack_t::key_vector_type keys;
	keys.reserve(times.size());

	for (size_t i = 0, n = times.size(); i < n; ++i)
	{
		keyTrack_t::key_type* pKey = m_pTrack->takeKey(times[i]);
		if (pKey)
		{
			pKey->setTime(times[i] + offset);
			keys.push_back(pKey);
		}
	}

	for (size_t i = 0, n = keys.size(); i < n; ++i)
		m_pTrack->insertKey(keys[i]);

	_resetIterators();
}

void FAnimationTrack::insertKey(const FValueKey* pKey)
{
	keyTrack_t::key_type* pNewKey;
	_createKey(&pNewKey, pKey->time());
	_setKeyValues(pKey, pNewKey);
	m_pTrack->insertKey(pNewKey);

	_resetIterators();
}

void FAnimationTrack::setDataTarget(FDataArray* pDataTarget)
{
	m_pDataTarget = pDataTarget;
	if (pDataTarget)
		_createIterators();
}

void FAnimationTrack::serialize(FArchive& ar)
{
	FInstance::serialize(ar);
	m_pTrack->serialize(ar);

	if (ar.isWriting())
	{
		ar << m_trackType;

		if (!isReference())
			m_pTrack->serialize(ar);
	}
	else // is reading
	{
		m_pDataTarget = NULL;
		ar >> m_trackType;

		if (isReference())
		{
			m_pTrack = dynamic_cast<FAnimationTrack*>(master())->m_pTrack;
		}
		else
		{
			_createTrack();
			m_pTrack->serialize(ar);
		}
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FAnimationTrack::dump(std::wostream& stream) const
{
	FInstance::dump(stream);
	stream << "\n--- FAnimationTrack ---";
	stream << "\n     Channels:    " << m_iterators.size();
	stream << "\n     Track type:  " << m_trackType;
	stream << "\n     Target type: " << m_pDataTarget->type();
	m_pTrack->dump(stream);
}
#endif

// Overrides -------------------------------------------------------------------

bool FAnimationTrack::onProcessMessage(FMessage* pMessage)
{
	return false;
}

void FAnimationTrack::onMakeUnique()
{
	m_pTrack = m_pTrack->clone();
	_createIterators();
}

/*
FAnimationTrack* FAnimationTrack::clone() const
{
	return new FAnimationTrack(*this);
}
*/

// Internal functions ----------------------------------------------------------

void FAnimationTrack::_createTrack()
{
	switch(m_trackType)
	{
	case FTrackType::Trigger:
		m_pTrack = new keyTrack_t();
		return;

	case FTrackType::Interpolate:
		m_pTrack = new animTrack_t();
		return;

	case FTrackType::Boolean:
		m_pTrack = new valueTrackBool_t();
		return;

	case FTrackType::Integer:
		m_pTrack = new valueTrackInt_t();
		return;

	case FTrackType::Double:
		m_pTrack = new valueTrackDouble_t();
		return;

	case FTrackType::String:
		m_pTrack = new valueTrackString_t();
		return;

	default:
		F_ASSERT(false);
		m_pTrack = NULL;
		return;
	}
}

void FAnimationTrack::_createIterators()
{
	size_t oldCount = m_iterators.size();
	size_t newCount = m_pDataTarget->channelCount();

	for (size_t i = 0; i < oldCount; ++i)
		F_SAFE_DELETE(m_iterators[i]);

	m_iterators.resize(newCount);

	for (size_t i = 0; i < newCount; ++i)
		m_iterators[i] = m_pTrack->createIterator();
}

void FAnimationTrack::_resetIterators()
{
	for (size_t i = 0, n = m_iterators.size(); i < n; ++i)
		m_iterators[i]->reset();
}

#define _F_EVALUATE_INTERP(valueType, rawType) \
	case FValueType::valueType: \
		for (uint32_t i = 0; i < n; ++i) m_pDataTarget->as<rawType>(i, 0) \
			= auto_convert<rawType, double>(static_cast<animTrack_t::track_iterator*>( \
				m_iterators[i])->evaluate()); break;

#define _F_EVALUATE_HOLD(valueType, rawType) \
		for (uint32_t i = 0; i < n; ++i) m_pDataTarget->as<rawType>(i, 0) \
			= static_cast<FValueTrackT<FTime, rawType>::track_iterator*>( \
				m_iterators[i])->evaluate();

void FAnimationTrack::_evaluate()
{
	F_ASSERT(m_pDataTarget);

	// don't need to evaluate values for a trigger track
	if (m_trackType == FTrackType::Trigger)
		return;

	size_t n = m_iterators.size();

	switch (m_trackType)
	{
	case FTrackType::Interpolate:
		{
			switch (m_pDataTarget->type())
			{
				_F_EVALUATE_INTERP(Float, float);
				_F_EVALUATE_INTERP(Double, double);
				_F_EVALUATE_INTERP(Bool, bool);
				_F_EVALUATE_INTERP(Int8, int8_t);
				_F_EVALUATE_INTERP(UInt8, uint8_t);
				_F_EVALUATE_INTERP(Int16, int16_t);
				_F_EVALUATE_INTERP(UInt16, uint16_t);
				_F_EVALUATE_INTERP(Int32, int32_t);
				_F_EVALUATE_INTERP(UInt32, uint32_t);
				_F_EVALUATE_INTERP(Int64, int64_t);
				_F_EVALUATE_INTERP(UInt64, uint64_t);
				_F_EVALUATE_INTERP(String, string_t);
				_F_EVALUATE_INTERP(WString, wstring_t);

			default:
				F_ASSERT(false);
				break;
			}
		}

		return;

	case FTrackType::Boolean:
		_F_EVALUATE_HOLD(Bool, bool);
		return;
	
	case FTrackType::Integer:
		_F_EVALUATE_HOLD(Int32, int32_t);
		return;
	
	case FTrackType::Double:
		_F_EVALUATE_HOLD(Double, double);
		return;
	
	case FTrackType::String:
		_F_EVALUATE_HOLD(WString, wstring_t);
		return;

	default:
		F_ASSERT(false);
		return;
	}
}

void FAnimationTrack::_createKey(keyTrack_t::key_type** ppKey, FTime time)
{
	F_ASSERT(ppKey);

	switch(m_trackType)
	{
	case FTrackType::Trigger:
		*ppKey = new keyTrack_t::key_type(time);
		return;

	case FTrackType::Interpolate:
		*ppKey = new animTrack_t::key_type(time);
		return;

	case FTrackType::Boolean:
		*ppKey = new valueTrackBool_t::key_type(time);
		return;

	case FTrackType::Integer:
		*ppKey = new valueTrackInt_t::key_type(time);
		return;

	case FTrackType::Double:
		*ppKey = new valueTrackDouble_t::key_type(time);
		return;

	case FTrackType::String:
		*ppKey = new valueTrackString_t::key_type(time);
		return;

	default:
		F_ASSERT(false);
		return;
	}
}

void FAnimationTrack::_setKeyValues(
	const FValueKey* pSrcKey, keyTrack_t::key_type* pDstKey)
{
	switch (m_trackType)
	{
	case FTrackType::Interpolate:
		{
			animTrack_t::key_type* pDstAK
				= static_cast<animTrack_t::key_type*>(pDstKey);
			pDstAK->setValue(pSrcKey->value().to<double>(0, 0));

			const FAnimationKey* pSrcAK = dynamic_cast<const FAnimationKey*>(pSrcKey);
			if (pSrcAK)
			{
				pDstAK->setLeftHandleTime(pSrcAK->leftHandleTime());
				pDstAK->setRightHandleTime(pSrcAK->rightHandleTime());
				pDstAK->setLeftHandleValue(pSrcAK->leftHandleValue().to<double>(0, 0));
				pDstAK->setRightHandleValue(pSrcAK->rightHandleValue().to<double>(0, 0));
				pDstAK->setInterpolationMode(pSrcAK->interpolationMode());
			}
		}
		break;

	case FTrackType::Boolean:
		{
			valueTrackBool_t::key_type* pDstVK
				= static_cast<valueTrackBool_t::key_type*>(pDstKey);
			pDstVK->setValue(pSrcKey->value().to<bool>(0, 0));
		}
		break;

	case FTrackType::Integer:
		{
			valueTrackInt_t::key_type* pDstVK
				= static_cast<valueTrackInt_t::key_type*>(pDstKey);
			pDstVK->setValue(pSrcKey->value().to<int32_t>(0, 0));
		}
		break;

	case FTrackType::Double:
		{
			valueTrackDouble_t::key_type* pDstVK
				= static_cast<valueTrackDouble_t::key_type*>(pDstKey);
			pDstVK->setValue(pSrcKey->value().to<double>(0, 0));
		}
		break;

	case FTrackType::String:
		{
			valueTrackString_t::key_type* pDstVK
				= static_cast<valueTrackString_t::key_type*>(pDstKey);
			pDstVK->setValue(pSrcKey->value().to<wstring_t>(0, 0));
		}
		break;

	default:
		F_ASSERT(false);
		break;
	}
}

// -----------------------------------------------------------------------------