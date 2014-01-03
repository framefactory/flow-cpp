// -----------------------------------------------------------------------------
//  File        ChannelType.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/ChannelType.h"
#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FChannelType
// -----------------------------------------------------------------------------

const char* FChannelType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Position);
		F_ENUM_NAME(Normal);
		F_ENUM_NAME(Tangent);
		F_ENUM_NAME(Bitangent);
		F_ENUM_NAME(TexCoord);
		F_ENUM_NAME(Color);
		F_ENUM_NAME(Custom);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FChannelType);

// -----------------------------------------------------------------------------