// -----------------------------------------------------------------------------
//  File        TouchEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#include "FlowUI/TouchEvent.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FTouchEvent
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FTouchEvent, FUIEvent, 1);

// Constructors and destructor -------------------------------------------------

FTouchEvent::FTouchEvent(FUIEventType type,
	                     FTime time,
						 FModifierKeys modifiers,
						 const FVector2f& widgetSize)
						 : FUIEvent(type, time, modifiers, widgetSize)
{
	F_ASSERT(type.isTouchEvent());
}

FTouchEvent::~FTouchEvent()
{
}

// Public commands -------------------------------------------------------------

void FTouchEvent::serialize(FArchive& ar)
{
	FUIEvent::serialize(ar);

	if (ar.isWriting())
	{
	}
	else // is reading
	{
	}
}

// -----------------------------------------------------------------------------