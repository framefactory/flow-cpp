// -----------------------------------------------------------------------------
//  File        KeyboardEvent.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_KEYBOARDEVENT_H
#define FLOWUI_KEYBOARDEVENT_H

#include "FlowUI/Library.h"
#include "FlowUI/UIEvent.h"

// -----------------------------------------------------------------------------
//  Class FKeyboardEvent
// -----------------------------------------------------------------------------

/// Event representing a state change of the keyboard.
class FLOWUI_EXPORT FKeyboardEvent : public FUIEvent
{
	F_DECLARE_SERIALIZABLE(FKeyboardEvent);

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a keyboard event from the given keyboard state.
	FKeyboardEvent(FUIEventType type, FTime time, FModifierKeys modifiers,
			       const FVector2f& widgetSize, int key, std::wstring& text);

	//  Public commands ----------------------------------------------

	/// Serialization.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the code of the key that was pressed or released.
	int key() const { return m_key; }
	/// Returns the text that the pressed key combination generates.
	const std::wstring& text() const { return m_text; }

	/// Returns true if a key was pressed.
	bool keyPressed() const { return type() == FUIEventType::KeyPress; }
	/// Returns true if a key was released.
	bool keyReleased() const { return type() == FUIEventType::KeyRelease; }

	//  Internal data members ----------------------------------------

private:
	int m_key;
	std::wstring m_text;
};
	
// ----------------------------------------------------------------------------------------------------

#endif // FLOWUI_KEYBOARDEVENT_H
