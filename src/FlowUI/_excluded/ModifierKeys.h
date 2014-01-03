// -----------------------------------------------------------------------------
//  File        ModifierKeys.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.22 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_MODIFIERKEYS_H
#define FLOWUI_MODIFIERKEYS_H

#include "FlowUI/Library.h"
#include "FlowCore/FlagsT.h"
#include <ostream>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FModifierKey
// -----------------------------------------------------------------------------

class FLOWUI_EXPORT FModifierKey
{
	//  Public enumerations ------------------------------------------

public:
	enum state_t
	{
		None				= 0x00,
		Shift				= 0x01,
		Control				= 0x02,
		Alt					= 0x04,
		Keypad				= 0x08
	};

	//  Constructors and destructor ----------------------------------

	FModifierKey() : m_state(None) { }
	FModifierKey(state_t state) : m_state(state) { }

	//  Public methods -----------------------------------------------

	operator state_t() const { return m_state; }

	bool operator==(FModifierKey rhs) const { return m_state == rhs.m_state; }
	bool operator!=(FModifierKey rhs) const { return m_state != rhs.m_state; }

	bool operator==(state_t state) const { return m_state == state; }
	bool operator!=(state_t state) const { return m_state != state; }

	/// Returns the name of the current state.
	const char* name() const;
	
	//  Internal data members ----------------------------------------

private:
	state_t m_state;
};

/// Writes the current state to the given archive.
FLOWUI_EXPORT FArchive& operator<<(FArchive& ar, FModifierKey obj);

/// Reads the current state from the given archive.
FLOWUI_EXPORT FArchive& operator>>(FArchive& ar, FModifierKey& obj);

/// Writes the name of the current state to the given stream.
template <typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, FModifierKey obj)
{
	stream << obj.name();
	return stream;
}

F_DECLARE_FLAGS(FModifierKeys, FModifierKey);

// -----------------------------------------------------------------------------

#endif // FLOWUI_MODIFIERKEYS_H