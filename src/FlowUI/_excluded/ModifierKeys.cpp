// -----------------------------------------------------------------------------
//  File        ModifierKeys.cpp
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.22 $
// -----------------------------------------------------------------------------

#include "FlowUI/ModifierKeys.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FModifierKey
// -----------------------------------------------------------------------------

const char* FModifierKey::name() const
{
	switch (m_state)
	{
		F_ENUM_NAME(None	);
		F_ENUM_NAME(Shift	);
		F_ENUM_NAME(Control	);
		F_ENUM_NAME(Alt		);
		F_ENUM_NAME(Keypad	);

	default:
		F_ASSERT(false); return "UNKNOWN";
	}
}

FArchive& operator<<(FArchive& ar, FModifierKey obj)
{
	ar << (uint8_t)obj;
	return ar;
}

FArchive& operator>>(FArchive& ar, FModifierKey& obj)
{
	uint8_t val;
	ar >> val;
	obj = (FModifierKey::state_t)val;
	return ar;
}

// -----------------------------------------------------------------------------