// -----------------------------------------------------------------------------
//  File        LinkMode.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/12/13 $
// -----------------------------------------------------------------------------

#include "FlowEngine/LinkMode.h"
#include "FlowCore/Archive.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FLinkMode
// -----------------------------------------------------------------------------

const char* FLinkMode::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Unlinkable);
		F_ENUM_NAME(Input);
		F_ENUM_NAME(Output);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FLinkMode);

// -----------------------------------------------------------------------------