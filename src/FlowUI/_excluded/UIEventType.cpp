// -----------------------------------------------------------------------------
//  File        UIEventType.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#include "FlowUI/UIEventType.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FUIEventType
// -----------------------------------------------------------------------------

const char* FUIEventType::name() const
{
	switch (m_state)
	{
		F_ENUM_NAME(Undefined			);
		F_ENUM_NAME(Keyboard			);
		F_ENUM_NAME(KeyPress			);
		F_ENUM_NAME(KeyRelease			);
		F_ENUM_NAME(Mouse				);
		F_ENUM_NAME(MouseButtonPress	);
		F_ENUM_NAME(MouseButtoRelease	);
		F_ENUM_NAME(MouseDoubleClick	);
		F_ENUM_NAME(MouseMove			);
		F_ENUM_NAME(Touch				);
		F_ENUM_NAME(TouchBegin			);
		F_ENUM_NAME(TouchMove			);
		F_ENUM_NAME(TouchEnd			);
		F_ENUM_NAME(TouchCancel			);

	default:
		F_ASSERT(false); return "UNKNOWN";
	}
}

FArchive& operator<<(FArchive& ar, FUIEventType obj)
{
	ar << (uint32_t)obj;
	return ar;
}

FArchive& operator>>(FArchive& ar, FUIEventType& obj)
{
	uint32_t val;
	ar >> val;
	obj = (FUIEventType::state_t)val;
	return ar;
}

// -----------------------------------------------------------------------------
