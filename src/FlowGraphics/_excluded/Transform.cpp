// -----------------------------------------------------------------------------
//  File        Transform.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/Transform.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FTransform
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FTransform::FTransform()
{
	m_vertexTransform.setIdentity();
	m_normalTransform.setIdentity();
}

// Internal functions ----------------------------------------------------------

void FTransform::calculateNormalTransform()
{
	m_vertexTransform.extractRotation(m_normalTransform);
	m_normalTransform.invert();
	m_normalTransform.transpose();
}

// -----------------------------------------------------------------------------