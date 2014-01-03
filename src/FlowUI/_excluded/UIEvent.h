// -----------------------------------------------------------------------------
//  File        UIEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_UIEVENT_H
#define FLOWUI_UIEVENT_H

#include "FlowUI/Library.h"
#include "FlowUI/UIEventType.h"
#include "FlowUI/ModifierKeys.h"

#include "FlowCore/Vector2T.h"
#include "FlowCore/Time.h"
#include "FlowCore/Object.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FUIEvent
// -----------------------------------------------------------------------------

/// Abstract base type for a user interface event.
class FLOWUI_EXPORT FUIEvent : public FObject
{
	F_DECLARE_ABSTRACT_SERIALIZABLE(FUIEvent);

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FUIEvent(FUIEventType type, FTime time,
		FModifierKeys modifiers, const FVector2f& widgetSize);
	/// Virtual destructor.
	virtual ~FUIEvent();

	//  Public commands ----------------------------------------------

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// The type of the UI event.
	FUIEventType type() const { return m_eventType; }
	/// The time when the event occurred.
	FTime time() const { return m_eventTime; }
	
	/// Convenience function, returns true if this is a keyboard event.
	bool isKeyboardEvent() const { return m_eventType.isKeyboardEvent(); }
	/// Convenience function, returns true if this is a mouse event.
	bool isMouseEvent() const { return m_eventType.isMouseEvent(); }
	/// Convenience function, returns true if this is a touch event.
	bool isTouchEvent() const { return m_eventType.isTouchEvent(); }

	/// Returns the modifier keys active at the time the event occurred.
	FModifierKeys modifierKeys() const { return m_modifierKeys; }

	/// Returns true if the shift modifier key was pressed.
	bool shiftPressed() const { return m_modifierKeys.test(FModifierKey::Shift); }
	/// Returns true if the control modifier key was pressed.
	bool controlPressed() const { return m_modifierKeys.test(FModifierKey::Control); }
	/// Returns true if the alt modifier key was pressed.
	bool altPressed() const { return m_modifierKeys.test(FModifierKey::Alt); }
	/// Returns true if a key on the keypad was pressed.
	bool keypadPressed() const { return m_modifierKeys.test(FModifierKey::Keypad); }

	/// Returns the size of the widget that created the event, in pixels.
	const FVector2f& widgetSize() const { return m_widgetSize; }

	//  Internal data members ----------------------------------------

private:
	FUIEventType m_eventType;
	FTime m_eventTime;
	FModifierKeys m_modifierKeys;
	FVector2f m_widgetSize;
};

// -----------------------------------------------------------------------------

#endif // FLOWUI_EVENT_H