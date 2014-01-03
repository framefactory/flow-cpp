// -----------------------------------------------------------------------------
//  File        TransformTRS.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/TransformTRS.h"

// -----------------------------------------------------------------------------
//  Class FTransformTRS
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FTransformTRS::FTransformTRS()
: m_translation(0.0f, 0.0f, 0.0f),
  m_rotation(0.0f, 0.0f, 0.0f),
  m_scaling(1.0f, 1.0f, 1.0f),
  m_uniformScaling(1.0f),
  m_rotationCenter(0.0f, 0.0f, 0.0f),
  m_scalingCenter(0.0f, 0.0f, 0.0f),
  m_allFlags(0)
{
}

FTransformTRS::~FTransformTRS()
{
}

// Public commands -------------------------------------------------------------

void FTransformTRS::setTranslation(const FVector3f& translation)
{
	if (translation != m_translation)
	{
		m_translation = translation;
		m_translationChanged = true;
		m_translationSet = !translation.allZero();
	}
}

void FTransformTRS::setRotation(const FVector3f& rotation)
{
	if (rotation != m_rotation)
	{
		m_rotation = rotation;
		m_rotationChanged = true;
		m_rotationSet = !rotation.allZero();
	}
}

void FTransformTRS::setScaling(const FVector3f& scaling)
{
	if (scaling != m_scaling)
	{
		m_scaling = scaling;
		m_scalingChanged = true;
		m_scalingSet = !scaling.allOne() && m_uniformScaling != 1.0f;
	}
}

void FTransformTRS::setUniformScaling(float uniformScaling)
{
	if (uniformScaling != m_uniformScaling)
	{
		m_uniformScaling = uniformScaling;
		m_scalingChanged = true;
		m_scalingSet = !m_scaling.allOne() && uniformScaling != 1.0f;
	}
}

void FTransformTRS::setRotationOrder(FRotationOrder rotationOrder)
{
	if (rotationOrder != m_rotationOrder)
	{
		m_rotationOrder = rotationOrder;
		m_rotationChanged = m_rotationChanged || m_rotationSet;
	}
}

void FTransformTRS::setRotationCenter(const FVector3f& rotationCenter)
{
	if (rotationCenter != m_rotationCenter)
	{
		m_rotationCenter = rotationCenter;
		m_rotationChanged = m_rotationChanged || m_rotationSet;
	}
}

void FTransformTRS::setScalingCenter(const FVector3f& scalingCenter)
{
	if (scalingCenter != m_scalingCenter)
	{
		m_scalingCenter = scalingCenter;
		m_scalingChanged = m_scalingChanged || m_scalingSet;
	}
}

// Overrides -------------------------------------------------------------------

void FTransformTRS::onUpdate()
{
	FMatrix4f& vt = vertexTransform();
	vt.setIdentity();
	float* m = vt.ptr();

	if (m_rotationChanged && m_rotationSet)
	{
		float rx = FMath::deg2rad(m_rotation.x);
		m_sin.x = sinf(rx);
		m_cos.x = cosf(rx);

		float ry = FMath::deg2rad(m_rotation.y);
		m_sin.y = sinf(ry);
		m_cos.y = cosf(ry);

		float rz = FMath::deg2rad(m_rotation.z);
		m_sin.z = sinf(rz);
		m_cos.z = cosf(rz);
	}

	switch(m_rotationOrder)
	{
	case FRotationOrder::XYZ:

		break;
	case FRotationOrder::XZY:
		break;
	case FRotationOrder::YXZ:
		break;
	case FRotationOrder::YZX:
		break;
	case FRotationOrder::ZXY:
		break;
	case FRotationOrder::ZYX:
		break;
	}

	if (m_translationSet)
	{
		m[3] = m_translation.x;
		m[7] = m_translation.y;
		m[11] = m_translation.z;
	}
}

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------