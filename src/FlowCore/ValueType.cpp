// -----------------------------------------------------------------------------
//  File        ValueType.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.07 $
// -----------------------------------------------------------------------------

#include "FlowCore/ValueType.h"
#include "FlowCore/Archive.h"

// -----------------------------------------------------------------------------
//  Class FValueType
// -----------------------------------------------------------------------------

size_t FValueType::byteCount() const
{
	switch (_state)
	{
	case Invalid: return 0;
	case Float: return sizeof(float);
	case Double: return sizeof(double);
	case Bool: return sizeof(bool);
	case Int8: return sizeof(qint8);
	case UInt8: return sizeof(quint8);
	case Int16: return sizeof(int16_t);
	case UInt16: return sizeof(uint16_t);
	case Int32: return sizeof(qint32);
	case UInt32: return sizeof(quint32);
	case Int64: return sizeof(qint64);
	case UInt64: return sizeof(quint64);
	case String: return 0;
	case Object: return 0;

	default:
        return 0;
	}
}

const char* FValueType::name() const
{
	switch (_state)
	{
		F_ENUM_NAME(Invalid);
		F_ENUM_NAME(Float);
		F_ENUM_NAME(Double);
		F_ENUM_NAME(Bool);
		F_ENUM_NAME(Int8);
		F_ENUM_NAME(UInt8);
		F_ENUM_NAME(Int16);
		F_ENUM_NAME(UInt16);
		F_ENUM_NAME(Int32);
		F_ENUM_NAME(UInt32);
		F_ENUM_NAME(Int64);
		F_ENUM_NAME(UInt64);
		F_ENUM_NAME(String);
		F_ENUM_NAME(Object);

	default:
		return NULL;
	}
}

F_IMPLEMENT_ENUM(FValueType);

// -----------------------------------------------------------------------------
