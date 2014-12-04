// -----------------------------------------------------------------------------
//  File        ValueType.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/12/07 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_VALUETYPE_H
#define FLOWCORE_VALUETYPE_H

#include "FlowCore/Library.h"
#include <QString>

class FObject;
class FArchive;

// -----------------------------------------------------------------------------
//  Class FValueType
// -----------------------------------------------------------------------------

struct FLOWCORE_EXPORT FValueType
{
	typedef quint8 value_type;

	enum enum_type : value_type
	{
		Invalid,
		Float,
		Double,
		Bool,
		Int8,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		String,
		Object
	};

	size_t byteCount() const;

	bool isInvalid() const { return _state == Invalid; }
	bool isNumber() const { return _state > Invalid && _state < String; }
	bool isString() const { return _state == String; }
	bool isObject() const { return _state == Object; }

	template <typename T>
	static FValueType fromType()
	{
		F_ASSERT(false);
		return Invalid;
	}

	F_DECLARE_ENUM(FLOWCORE_EXPORT, FValueType, Invalid);
};

// Template members ------------------------------------------------------------

template <>
inline FValueType FValueType::fromType<float>()
{
    return FValueType::Float;
}

template <>
inline FValueType FValueType::fromType<double>()
{
    return FValueType::Double;
}

template <>
inline FValueType FValueType::fromType<bool>()
{
    return FValueType::Bool;
}

template <>
inline FValueType FValueType::fromType<qint8>()
{
    return FValueType::Int8;
}

template <>
inline FValueType FValueType::fromType<quint8>()
{
    return FValueType::UInt8;
}

template <>
inline FValueType FValueType::fromType<int16_t>()
{
    return FValueType::Int16;
}

template <>
inline FValueType FValueType::fromType<uint16_t>()
{
    return FValueType::UInt16;
}

template <>
inline FValueType FValueType::fromType<qint32>()
{
    return Int32;
}

template <>
inline FValueType FValueType::fromType<quint32>()
{
    return FValueType::UInt32;
}

template <>
inline FValueType FValueType::fromType<qint64>()
{
    return FValueType::Int64;
}

template <>
inline FValueType FValueType::fromType<quint64>()
{
    return FValueType::UInt64;
}

template <>
inline FValueType FValueType::fromType<QString>()
{
    return FValueType::String;
}

template <>
inline FValueType FValueType::fromType<FObject*>()
{
    return FValueType::Object;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_VALUETYPE_H
