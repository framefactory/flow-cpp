// -----------------------------------------------------------------------------
//  File        ViewType.cpp
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/08/06 $
// -----------------------------------------------------------------------------

#include "Tilator/ViewType.h"
#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FViewType
// -----------------------------------------------------------------------------

const char* FViewType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(OrthographicFront);
		F_ENUM_NAME(OrthographicBack);
		F_ENUM_NAME(OrthographicLeft);
		F_ENUM_NAME(OrthographicRight);
		F_ENUM_NAME(OrthographicTop);
		F_ENUM_NAME(OrthographicBottom);
		F_ENUM_NAME(OrthographicOblique);
		F_ENUM_NAME(OrthographicSpecial);

	default:
		return NULL;
	}
}

const char* FViewType::proxyType() const
{
	switch (_state)
	{
		F_ENUM_CASE(OrthographicFront, "web-image25d-front");
		F_ENUM_CASE(OrthographicBack, "web-image25d-back");
		F_ENUM_CASE(OrthographicLeft, "web-image25d-left");
		F_ENUM_CASE(OrthographicRight, "web-image25d-right");
		F_ENUM_CASE(OrthographicTop, "web-image25d-top");
		F_ENUM_CASE(OrthographicBottom, "web-image25d-bottom");
		F_ENUM_CASE(OrthographicOblique, "web-image25d-oblique");
		F_ENUM_CASE(OrthographicSpecial, "web-image25d-special");

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FViewType);

// -----------------------------------------------------------------------------