// -----------------------------------------------------------------------------
//  File        MouseEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/24 $
// -----------------------------------------------------------------------------

#include "FlowUI/MouseEvent.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FMouseEvent
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FMouseEvent, FUIEvent, 1);

// Constructors and destructor -------------------------------------------------

FMouseEvent::FMouseEvent(FUIEventType type,
	                     FTime time,
	                     FModifierKeys modifiers,
						 const FVector2f& widgetSize,
						 const FVector2f& mousePos,
						 FMouseButtons buttonState,
						 FMouseButton buttonChange)
: FUIEvent(type, time, modifiers, widgetSize),
  m_position(mousePos),
  m_buttons(buttonState),
  m_button(buttonChange)
{
	F_ASSERT(type.isMouseEvent());
}

// Public commands -------------------------------------------------------------

void FMouseEvent::serialize(FArchive& ar)
{
	FUIEvent::serialize(ar);

	if (ar.isReading())
	{
		ar >> m_position;
		ar >> m_buttons;
		ar >> m_button;
	}
	else // isWriting
	{
		ar << m_position;
		ar << m_buttons;
		ar << m_button;
	}
}

// -----------------------------------------------------------------------------