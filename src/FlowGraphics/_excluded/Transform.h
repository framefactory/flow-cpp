// -----------------------------------------------------------------------------
//  File        Transform.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_TRANSFORM_H
#define FLOWGRAPHICS_TRANSFORM_H

#include "FlowGraphics/Library.h"

#include "FlowCore/Vector3T.h"
#include "FlowCore/Vector4T.h"
#include "FlowCore/Matrix4T.h"

// -----------------------------------------------------------------------------
//  Class FTransform
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FTransform
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FTransform();
	/// Virtual destructor.
	virtual ~FTransform() { }

	//  Public commands ----------------------------------------------

public:
	// Updates the transform
	void update();

	//  Public queries -----------------------------------------------

	const FMatrix4f& vertexTransform() const { return m_vertexTransform; }
	const FMatrix3f& normalTransform() const { return m_normalTransform; }

	//  Overridables -------------------------------------------------

protected:
	virtual void onUpdate() = 0;

	//  Protected members --------------------------------------------

	void calculateNormalTransform();

	FMatrix4f& vertexTransform() { return m_vertexTransform; }
	FMatrix3f& normalTransform() { return m_normalTransform; }

	//  Internal data members ----------------------------------------

private:
	FMatrix4f m_vertexTransform;
	FMatrix3f m_normalTransform;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_TRANSFORM_H