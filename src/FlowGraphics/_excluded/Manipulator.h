// -----------------------------------------------------------------------------
//  File        Manipulator.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_MANIPULATOR_H
#define FLOWGRAPHICS_MANIPULATOR_H

#include "FlowGraphics/Library.h"
#include "FlowCore/Object.h"

// -----------------------------------------------------------------------------
//  Class FManipulator
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FManipulator : public FObject
{
	//F_DECLARE_ABSTRACT_(FManipulator);

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FManipulator();
	/// Virtual destructor.
	virtual ~FManipulator();

	//  Public commands ----------------------------------------------

public:
	//bool activate(const FUIEvent* pUIEvent);




	//  Public queries -----------------------------------------------

	//  Overridables -------------------------------------------------

protected:
	//virtual bool onActivate(FManipulatorEvent* pManipEvent) = 0;
	//virtual void onUpdate(FManipulatorEvent* pManipEvent) = 0;
	//virtual void onDeactivate(FManipulatorEvent* pManipEvent) = 0;

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_MANIPULATOR_H