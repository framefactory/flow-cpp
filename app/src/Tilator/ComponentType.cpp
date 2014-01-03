// -----------------------------------------------------------------------------
//  File        ComponentType.cpp
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/08/06 $
// -----------------------------------------------------------------------------

#include "Tilator/ComponentType.h"
#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FComponentType
// -----------------------------------------------------------------------------

const char* FComponentType::name() const
{
	switch (_state)
	{
		F_ENUM_CASE(Diffuse, "diffuse");
		F_ENUM_CASE(Zone, "zone");
		F_ENUM_CASE(Normal, "normal");
		F_ENUM_CASE(Occlusion, "occlusion");
		F_ENUM_CASE(Depth, "depth");
		F_ENUM_CASE(Alpha, "alpha");
		F_ENUM_CASE(DepthAlpha, "depthAlpha");

	default:
		return NULL;
	}
}

const char* FComponentType::shortName() const
{
	switch (_state)
	{
		F_ENUM_CASE(Diffuse, "dif");
		F_ENUM_CASE(Zone, "zon");
		F_ENUM_CASE(Normal, "nrm");
		F_ENUM_CASE(Occlusion, "occ");
		F_ENUM_CASE(Depth, "dpt");
		F_ENUM_CASE(Alpha, "alp");
		F_ENUM_CASE(DepthAlpha, "dda");

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FComponentType);

// -----------------------------------------------------------------------------