// -----------------------------------------------------------------------------
//  File        GLBuffer.h
//  Project     FlowGL
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/04 $
// -----------------------------------------------------------------------------

#ifndef FLOWGL_GLBUFFER_H
#define FLOWGL_GLBUFFER_H

#include "FlowGL/Library.h"
#include "FlowGL/GLObject.h"

// -----------------------------------------------------------------------------
//  Class FGLBuffer
// -----------------------------------------------------------------------------

class FLOWGL_EXPORT FGLBuffer
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FGLBuffer();
	/// Virtual destructor.
	virtual ~FGLBuffer();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	FGLObject m_obj;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGL_GLBUFFER_H