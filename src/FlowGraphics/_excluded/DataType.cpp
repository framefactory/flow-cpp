// -----------------------------------------------------------------------------
//  File        DataType.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/DataType.h"
#include "FlowCore/Archive.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FDataType
// -----------------------------------------------------------------------------

size_t FDataType::size() const
{
	switch (_state)
	{
	case Float:   return 4;
	case Float2:  return 8;
	case Float3:  return 12;
	case Float4:  return 16;
	case Double:  return 8;
	case Double2: return 16;
	case Double3: return 24;
	case Double4: return 32;
	case UByte:   return 1;
	case UByte2:  return 2;
	case UByte3:  return 3;
	case UByte4:  return 4;
	case UShort:  return 2;
	case UInt:    return 4;

	default:
		return 0;
	}
}

size_t FDataType::components() const
{
	switch (_state)
	{
	case Float:   return 1;
	case Float2:  return 2;
	case Float3:  return 3;
	case Float4:  return 4;
	case Double:  return 1;
	case Double2: return 2;
	case Double3: return 3;
	case Double4: return 4;
	case UByte:   return 1;
	case UByte2:  return 2;
	case UByte3:  return 3;
	case UByte4:  return 4;
	case UShort:  return 1;
	case UInt:    return 1;

	default:
		return 0;
	}
}

const char* FDataType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Float);
		F_ENUM_NAME(Float2);
		F_ENUM_NAME(Float3);
		F_ENUM_NAME(Float4);
		F_ENUM_NAME(Double);
		F_ENUM_NAME(Double2);
		F_ENUM_NAME(Double3);
		F_ENUM_NAME(Double4);
		F_ENUM_NAME(UByte);
		F_ENUM_NAME(UByte2);
		F_ENUM_NAME(UByte3);
		F_ENUM_NAME(UByte4);
		F_ENUM_NAME(UShort);
		F_ENUM_NAME(UInt);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FDataType);

// -----------------------------------------------------------------------------