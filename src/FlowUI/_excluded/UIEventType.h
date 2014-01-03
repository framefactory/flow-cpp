// -----------------------------------------------------------------------------
//  File        UIEventType.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_UIEVENTTYPE_H
#define FLOWUI_UIEVENTTYPE_H

#include "FlowUI/Library.h"
#include <ostream>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FUIEventType
// -----------------------------------------------------------------------------

class FLOWUI_EXPORT FUIEventType
{
	//  Public enumerations ------------------------------------------

public:
	enum state_t
	{
		Undefined					= 0x00000000,
		Keyboard					= 0x00010000,
		KeyPress					= 0x00010001,
		KeyRelease					= 0x00010002,
		Mouse						= 0x00020000,
		MouseButtonPress			= 0x00020001,
		MouseButtoRelease			= 0x00020002,
		MouseDoubleClick			= 0x00020004,
		MouseMove					= 0x00020008,
		Touch						= 0x00040000,
		TouchBegin					= 0x00040001,
		TouchMove					= 0x00040002,
		TouchEnd					= 0x00040004,
		TouchCancel					= 0x00040008,
		Speech                      = 0x00080000,
		Tracking                    = 0x00100000
	};

	//  Constructors and destructor ----------------------------------

	FUIEventType() : m_state(Undefined) { }
	FUIEventType(state_t state) : m_state(state) { }

	//  Public methods -----------------------------------------------

	operator state_t() const { return m_state; }

	bool operator==(FUIEventType rhs) const { return m_state == rhs.m_state; }
	bool operator!=(FUIEventType rhs) const { return m_state != rhs.m_state; }

	bool operator==(state_t state) const { return m_state == state; }
	bool operator!=(state_t state) const { return m_state != state; }

	/// Returns true if this is a keyboard event type.
	bool isKeyboardEvent() const { return (m_state & Keyboard) > 0; }
	/// Returns true if this is a mouse event type.
	bool isMouseEvent() const { return (m_state & Mouse) > 0; }
	/// Returns true if this is a touch event type.
	bool isTouchEvent() const { return (m_state & Touch) > 0; }

	/// Returns the name of the current state.
	const char* name() const;

	//  Internal data members ----------------------------------------

private:
	state_t m_state;
};

/// Writes the current state to the given archive.
FLOWUI_EXPORT FArchive& operator<<(FArchive& ar, FUIEventType obj);

/// Reads the current state from the given archive.
FLOWUI_EXPORT FArchive& operator>>(FArchive& ar, FUIEventType& obj);

/// Writes the name of the current state to the given stream.
template <typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, FUIEventType obj)
{
	stream << obj.name();
	return stream;
}
	
// -----------------------------------------------------------------------------

#endif // FLOWUI_UIEVENTTYPE_H


