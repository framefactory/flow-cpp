// -----------------------------------------------------------------------------
//  File        KeyboardEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/24 $
// -----------------------------------------------------------------------------

#include "FlowUI/KeyboardEvent.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FKeyboardEvent
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FKeyboardEvent, FUIEvent, 1);

// Constructors and destructor -------------------------------------------------

FKeyboardEvent::FKeyboardEvent(FUIEventType type,
	                           FTime time,
							   FModifierKeys modifiers,
							   const FVector2f& widgetSize,
							   int key,
							   std::wstring& text)
: FUIEvent(type, time, modifiers, widgetSize),
  m_key(key),
  m_text(text)
{
	F_ASSERT(type.isKeyboardEvent());
}

// Public commands -------------------------------------------------------------

void FKeyboardEvent::serialize(FArchive& ar)
{
	FUIEvent::serialize(ar);

	if (ar.isReading())
	{
		ar >> m_key;
		ar >> m_text;
	}
	else // isWriting
	{
		ar << m_key;
		ar << m_text;
	}
}

// Public queries --------------------------------------------------------------


// -----------------------------------------------------------------------------