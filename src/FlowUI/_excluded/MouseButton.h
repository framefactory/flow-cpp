// -----------------------------------------------------------------------------
//  File        MouseButton.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.24 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_MOUSEBUTTON_H
#define FLOWUI_MOUSEBUTTON_H

#include "FlowUI/Library.h"
#include "FlowCore/FlagsT.h"

#include <ostream>

class FArchive;


// -----------------------------------------------------------------------------
//  Class FMouseButton
// -----------------------------------------------------------------------------

class FLOWUI_EXPORT FMouseButton
{
	//  Public enumerations ------------------------------------------

public:
	enum state_t
	{
		Left,
		Mid,
		Right
	};

	//  Constructors and destructor ----------------------------------

	FMouseButton() : m_state(Left) { }
	FMouseButton(state_t state) : m_state(state) { }

	//  Public methods -----------------------------------------------

	operator state_t() const { return m_state; }

	bool operator==(FMouseButton rhs) const { return m_state == rhs.m_state; }
	bool operator!=(FMouseButton rhs) const { return m_state != rhs.m_state; }

	bool operator==(state_t state) const { return m_state == state; }
	bool operator!=(state_t state) const { return m_state != state; }

	/// Returns the name of the current state.
	const char* name() const;
	
	//  Internal data members ----------------------------------------

private:
	state_t m_state;
};

/// Writes the current state to the given archive.
FLOWUI_EXPORT FArchive& operator<<(FArchive& ar, FMouseButton obj);

/// Reads the current state from the given archive.
FLOWUI_EXPORT FArchive& operator>>(FArchive& ar, FMouseButton& obj);

/// Writes the name of the current state to the given stream.
template <typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, FMouseButton obj)
{
	stream << obj.name();
	return stream;
}

F_DECLARE_FLAGS(FMouseButtons, FMouseButton);
	
// -----------------------------------------------------------------------------

#endif // FLOWUI_MOUSEBUTTON_H