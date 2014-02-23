// -----------------------------------------------------------------------------
//  File        AttributeRole.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2014/02/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/AttributeRole.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FAttributeRole
// -----------------------------------------------------------------------------

const char* FAttributeRole::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Undefined);
		F_ENUM_NAME(Position);
		F_ENUM_NAME(Normal);
		F_ENUM_NAME(Tangent);
		F_ENUM_NAME(Bitangent);
		F_ENUM_NAME(TexCoords);
		F_ENUM_NAME(Color);
		F_ENUM_NAME(Weight);
		F_ENUM_NAME(Custom);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FAttributeRole);

// -----------------------------------------------------------------------------