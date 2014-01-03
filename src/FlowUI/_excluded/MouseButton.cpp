// -----------------------------------------------------------------------------
//  File        MouseButton.cpp
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.24 $
// -----------------------------------------------------------------------------

#include "FlowUI/MouseButton.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FMouseButton
// -----------------------------------------------------------------------------

const char* FMouseButton::name() const
{
	switch (m_state)
	{
		F_ENUM_NAME(Left );
		F_ENUM_NAME(Mid  );
		F_ENUM_NAME(Right);

	default:
		F_ASSERT(false); return "UNKNOWN";
	}
}

FArchive& operator<<(FArchive& ar, FMouseButton obj)
{
	ar << (uint8_t)obj;
	return ar;
}

FArchive& operator>>(FArchive& ar, FMouseButton& obj)
{
	uint8_t val;
	ar >> val;
	obj = (FMouseButton::state_t)val;
	return ar;
}

// -----------------------------------------------------------------------------