// -----------------------------------------------------------------------------
//  File        Event.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#include "FlowUI/UIEvent.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FUIEvent
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FUIEvent, FObject);

// Constructors and destructor -------------------------------------------------

FUIEvent::FUIEvent(FUIEventType type,
	               FTime time,
	               FModifierKeys modifiers,
				   const FVector2f& widgetSize)
: m_eventType(type),
  m_eventTime(time),
  m_modifierKeys(modifiers),
  m_widgetSize(widgetSize)
{
}

FUIEvent::~FUIEvent()
{
}

// Public commands -------------------------------------------------------------

void FUIEvent::serialize(FArchive& ar)
{
	FObject::serialize(ar);

	if (ar.isReading())
	{
		ar >> m_eventType;
		ar >> m_eventTime;
		ar >> m_modifierKeys;
		ar >> m_widgetSize;
	}
	else // isWriting
	{
		ar << m_eventType;
		ar << m_eventTime;
		ar << m_modifierKeys;
		ar << m_widgetSize;
	}
}

// Public queries --------------------------------------------------------------


// -----------------------------------------------------------------------------