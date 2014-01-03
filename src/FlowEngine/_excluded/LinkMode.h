// -----------------------------------------------------------------------------
//  File        LinkMode.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.13 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_LINKMODE_H
#define FLOWENGINE_LINKMODE_H

#include "FlowEngine/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FLinkMode
// -----------------------------------------------------------------------------

struct FLOWENGINE_EXPORT FLinkMode
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Unlinkable,
		Input,
		Output
	};

	bool isUnlinkable() const { return _state == Unlinkable; }
	bool isInput() const { return _state == Input; }
	bool isOutput() const { return _state == Output; }

	F_DECLARE_ENUM(FLOWENGINE_EXPORT, FLinkMode, Unlinkable);
};

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_LINKMODE_H