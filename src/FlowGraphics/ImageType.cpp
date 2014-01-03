// -----------------------------------------------------------------------------
//  File        ImageType.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/ImageType.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FImageType
// -----------------------------------------------------------------------------

const char* FImageType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Unknown		);
		F_ENUM_NAME(Bitmap		);
		F_ENUM_NAME(UInt16		);
		F_ENUM_NAME(Int16		);
		F_ENUM_NAME(UInt32		);
		F_ENUM_NAME(Int32		);
		F_ENUM_NAME(Float		);
		F_ENUM_NAME(Double		);
		F_ENUM_NAME(Complex		);
		F_ENUM_NAME(RGB_UInt16	);
		F_ENUM_NAME(RGBA_UInt16	);
		F_ENUM_NAME(RGB_Float	);
		F_ENUM_NAME(RGBA_Float	);
		F_ENUM_NAME(Indexed_1	);
		F_ENUM_NAME(Indexed_4	);
		F_ENUM_NAME(Indexed_8	);
		F_ENUM_NAME(Special_16  );
		F_ENUM_NAME(RGB			);
		F_ENUM_NAME(RGBA		);

	default:
		return NULL;
	}
}

int FImageType::bitsPerPixel() const
{
	switch (_state)
	{
		case Unknown		: return 0;
		case Bitmap			: return 24;
		case UInt16			: return 16;
		case Int16			: return 16;
		case UInt32			: return 32;
		case Int32			: return 32;
		case Float			: return 32;
		case Double			: return 64;
		case Complex		: return 128;
		case RGB_UInt16		: return 16;
		case RGBA_UInt16	: return 16;
		case RGB_Float		: return 32;
		case RGBA_Float		: return 32;
		case Indexed_1		: return 1;
		case Indexed_4		: return 4;
		case Indexed_8		: return 8;
		case Special_16		: return 16;
		case RGB			: return 24;
		case RGBA			: return 32;

	default:
		return 0;
	}
}

F_IMPLEMENT_ENUM(FImageType);

// -----------------------------------------------------------------------------