// -----------------------------------------------------------------------------
//  File        TransformTRS.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_TRANSFORMTRS_H
#define FLOWGRAPHICS_TRANSFORMTRS_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/Transform.h"
#include "FlowGraphics/RotationOrder.h"

// -----------------------------------------------------------------------------
//  Class FTransformTRS
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FTransformTRS : public FTransform
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FTransformTRS();
	/// Virtual destructor.
	virtual ~FTransformTRS();

	//  Public commands ----------------------------------------------

public:
	void setTranslation(const FVector3f& translation);
	void setRotation(const FVector3f& rotation);
	void setScaling(const FVector3f& scaling);
	void setUniformScaling(float uniformScaling);
	void setRotationOrder(FRotationOrder rotationOrder);
	void setRotationCenter(const FVector3f& rotationCenter);
	void setScalingCenter(const FVector3f& scalingCenter);

	//  Public queries -----------------------------------------------

	const FVector3f& translation() const { return m_translation; }
	const FVector3f& rotation() const { return m_rotation; }
	const FVector3f& scaling() const { return m_scaling; }
	float uniformScaling() const { return m_uniformScaling; }
	FRotationOrder rotationOrder() const { return m_rotationOrder; }
	const FVector3f& rotationCenter() const { return m_rotationCenter; }
	const FVector3f& scalingCenter() const { return m_scalingCenter; }

	//  Overrides ----------------------------------------------------

protected:
	virtual void onUpdate();

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	FVector3f m_translation;
	FVector3f m_rotation;
	FVector3f m_scaling;
	float m_uniformScaling;
	FRotationOrder m_rotationOrder;
	FVector3f m_rotationCenter;
	FVector3f m_scalingCenter;

	FVector3f m_sin;
	FVector3f m_cos;

	union
	{
		struct
		{
			uint32_t m_translationChanged		: 1;
			uint32_t m_rotationChanged			: 1;
			uint32_t m_scalingChanged			: 1;
			uint32_t m_translationSet			: 1;
			uint32_t m_rotationSet				: 1;
			uint32_t m_scalingSet				: 1;
			uint32_t m_rotationCenterSet		: 1;
			uint32_t m_scalingCenterSet			: 1;
		};

		uint32_t m_allFlags;
	};
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_TRANSFORMTRS_H