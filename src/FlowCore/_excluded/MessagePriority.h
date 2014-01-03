// -----------------------------------------------------------------------------
//  File        MessagePriority.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MESSAGEPRIORITY_H
#define FLOWCORE_MESSAGEPRIORITY_H

#include "FlowCore/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FMessagePriority
// -----------------------------------------------------------------------------

struct FLOWCORE_EXPORT FMessagePriority
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Low,
		Normal,
		High,
		Critical
	};

	F_DECLARE_ENUM(FLOWCORE_EXPORT, FMessagePriority, Normal);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_MESSAGEPRIORITY_H