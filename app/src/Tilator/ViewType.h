// -----------------------------------------------------------------------------
//  File        ViewType.h
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/08/06 $
// -----------------------------------------------------------------------------

#ifndef TILATOR_VIEWTYPE_H
#define TILATOR_VIEWTYPE_H

#include "Tilator/Application.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FViewType
// -----------------------------------------------------------------------------

struct FViewType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		OrthographicFront,
		OrthographicBack,
		OrthographicLeft,
		OrthographicRight,
		OrthographicTop,
		OrthographicBottom,
		OrthographicOblique,
		OrthographicSpecial
	};

	const char* proxyType() const;

	F_DECLARE_ENUM(, FViewType, OrthographicFront);
};
	
// -----------------------------------------------------------------------------

#endif // TILATOR_VIEWTYPE_H