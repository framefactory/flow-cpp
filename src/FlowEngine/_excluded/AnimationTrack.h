// -----------------------------------------------------------------------------
//  File        AnimationTrack.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_ANIMATIONTRACK_H
#define FLOWENGINE_ANIMATIONTRACK_H

#include "FlowEngine/Library.h"
#include "FlowEngine/TrackType.h"
#include "FlowEngine/AnimationKey.h"
#include "FlowEngine/KeyTrackT.h"

#include "FlowCore/Time.h"
#include "FlowCore/ValueType.h"
#include "FlowCore/Archive.h"
#include "FlowCore/MessageTarget.h"

#include <ostream>
class FDataArray;

// -----------------------------------------------------------------------------
//  Class FAnimationTrack
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FAnimationTrack : public FMessageTarget
{
	F_DECLARE_SERIALIZABLE(FAnimationTrack);

	//  Public types -------------------------------------------------

public:
	typedef std::vector<FValueKey*> key_vector_type;
	typedef std::vector<FTime> time_vector_type;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates an animation track without a data target.
	FAnimationTrack(FTrackType trackType,
		const FUniqueId& id = FUniqueId());
	/// Creates an animation track writing to the given data target.
	FAnimationTrack(FDataArray* pDataTarget, FTrackType trackType,
		const FUniqueId& id = FUniqueId());
	/// Creates a reference to the given master without a data target.
	FAnimationTrack(FAnimationTrack* pMaster,
		const FUniqueId& id = FUniqueId());
	/// Creates a reference to the given master writing to the data target.
	FAnimationTrack(FDataArray* pDataTarget, FAnimationTrack* pMaster,
		const FUniqueId& id = FUniqueId());

	/// Virtual destructor.
	virtual ~FAnimationTrack();

	//  Public commands ----------------------------------------------

public:
	/// Sets the current time and evaluates the track at that time.
	void setTime(FTime time);
	/// Advances the current time and evaluates the track at that time.
	void advanceTime(FTime time);

	/// Evaluates the track once per channel.
	void setTime(const FValueArray* pTime);
	/// Evaluates the track once per channel.
	void advanceTime(const FValueArray* pTime);

	/// Changes the key at the given time. Returns true if a key was found.
	bool changeKey(const FValueKey* pKey, FTime offset);
	/// Changes the key at the given time. Returns true if a key was found.
	void changeKeys(const key_vector_type& keys, FTime offset);
	
	/// Moves a key to a different time.
	bool moveKey(FTime time, FTime offset);
	/// Moves a key to a different time.
	void moveKeys(const time_vector_type& times, FTime offset);

	/// Inserts the given key into the animation track.
	void insertKey(const FValueKey* pKey);
	/// Removes the key at the given time. Returns true if a key was found.
	bool removeKey(FTime time);

	/// Sets or changes the data target, i.e. the object where
	/// the animation data is written to.
	void setDataTarget(FDataArray* pDataTarget);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns true if the track has a key at the given time.
	bool hasKey(FTime time) const;
	/// Returns the key at the given position. The caller takes ownership.
	FValueKey* keyAt(FTime time) const;
	/// Returns the keys in the given interval. The caller takes ownership.
	key_vector_type keysBetween(FTime begin, FTime end) const;

	/// Returns the data target for this animation track.
	FDataArray* dataTarget() const { return m_pDataTarget; }
	/// Returns the type of the animation track.
	FTrackType trackType() const { return m_trackType; }

	/// The number of data elements in the data target.
	size_t evaluationCount() const { return m_iterators.size(); }

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overrides ----------------------------------------------------

protected:
	virtual bool onProcessMessage(FMessage* pMessage);
	virtual void onMakeUnique();
	//virtual FAnimationTrack* clone() const;

	//  Internal types -----------------------------------------------

private:
	typedef FKeyTrackT<FTime> keyTrack_t;
	typedef FKeyTrackIteratorT<FTime> keyTrackIter_t;
	typedef std::vector<keyTrackIter_t*> trackIterVec_t;

	//  Internal functions -------------------------------------------

	void _createTrack();
	void _createIterators();
	void _resetIterators();
	void _evaluate();
	void _createKey(keyTrack_t::key_type** ppKey, FTime time);
	void _setKeyValues(const FValueKey* pSrcKey, keyTrack_t::key_type* pDstKey);

	//  Internal data members ----------------------------------------

	keyTrack_t* m_pTrack;
	FTrackType m_trackType;
	FDataArray* m_pDataTarget;
	trackIterVec_t m_iterators; 
};

// Inline members --------------------------------------------------------------

inline bool FAnimationTrack::removeKey(FTime time)
{
	bool result = m_pTrack->removeKey(time);
	_resetIterators();
	return result;
}

inline bool FAnimationTrack::hasKey(FTime time) const
{
	return m_pTrack->hasKey(time);
}

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_ANIMATIONTRACK_H