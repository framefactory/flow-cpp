// -----------------------------------------------------------------------------
//  File        MouseEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/24 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_MOUSEEVENT_H
#define FLOWUI_MOUSEEVENT_H

#include "FlowUI/Library.h"
#include "FlowUI/UIEvent.h"
#include "FlowUI/MouseButton.h"

#include "FlowCore/Vector2T.h"

// -----------------------------------------------------------------------------
//  Class FMouseEvent
// -----------------------------------------------------------------------------

/// Holds information about the state of the mouse.
class FLOWUI_EXPORT FMouseEvent : public FUIEvent
{
	F_DECLARE_SERIALIZABLE(FMouseEvent);

	//  Constructors and destructor --------------------------------------------

public:
	/// Creates a mouse event from the given state of the mouse.
	FMouseEvent(FUIEventType type, FTime time, FModifierKeys modifiers,
		const FVector2f& widgetSize, const FVector2f& mousePos,
		FMouseButtons buttonState, FMouseButton buttonChange);

	//  Public commands --------------------------------------------------------
	
	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries ---------------------------------------------------------

	/// Returns the button that caused the state.
	FMouseButton button() const { return m_button; }
	/// Returns the buttons that are currently pressed.
	FMouseButtons buttons() const { return m_buttons; }
	
	/// Returns the position of the mouse relative to the window that sent the state.
	const FVector2f& position() const { return m_position; }

	/// Returns true if a mouse button has been pressed.
	bool buttonPressed() const { return type() == FUIEventType::MouseButtonPress; }
	/// Returns true if a mouse button has been released.
	bool buttonReleased() const { return type() == FUIEventType::MouseButtoRelease; }
	/// Returns true if a mouse button has been double clicked.
	bool doubleClick() const { return type() == FUIEventType::MouseDoubleClick; }
	/// Returns true if the mouse has moved.
	bool mouseMoved() const { return type() == FUIEventType::MouseMove; }

	//  Internal data members --------------------------------------------------

private:
	FVector2f m_position;
	FMouseButton m_button;
	FMouseButtons m_buttons;
};
	
// ----------------------------------------------------------------------------------------------------

#endif // FLOWUI_MOUSEEVENT_H
