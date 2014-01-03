// -----------------------------------------------------------------------------
//  File        Resource.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_RESOURCE_H
#define FLOWGRAPHICS_RESOURCE_H

#include "FlowGraphics/Library.h"

// -----------------------------------------------------------------------------
//  Class FResource
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FResource
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FResource();
	/// Copy constructor.
	FResource(const FResource& other);
	/// Virtual destructor.
	virtual ~FResource();

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

};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_RESOURCE_H