// -----------------------------------------------------------------------------
//  File        TouchEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_TOUCHEVENT_H
#define FLOWUI_TOUCHEVENT_H

#include "FlowUI/Library.h"
#include "FlowUI/UIEvent.h"

// -----------------------------------------------------------------------------
//  Class FTouchEvent
// -----------------------------------------------------------------------------

class FLOWUI_EXPORT FTouchEvent : public FUIEvent
{
	F_DECLARE_SERIALIZABLE(FTouchEvent);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a touch event from the given touch state.
	FTouchEvent(FUIEventType type, FTime time, FModifierKeys modifiers,
		const FVector2f& widgetSize);
	/// Virtual destructor.
	virtual ~FTouchEvent();

	//  Public commands ----------------------------------------------

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------



	//  Internal data members ----------------------------------------

private:

};
	
// -----------------------------------------------------------------------------

#endif // FLOWUI_TOUCHEVENT_H