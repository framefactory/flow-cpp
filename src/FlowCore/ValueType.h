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

	template <> static FValueType fromType<float>()        { return Float; }
	template <> static FValueType fromType<double>()       { return Double; }
	template <> static FValueType fromType<bool>()         { return Bool; }
	template <> static FValueType fromType<qint8>()       { return Int8; }
	template <> static FValueType fromType<quint8>()      { return UInt8; }
	template <> static FValueType fromType<int16_t>()      { return Int16; }
	template <> static FValueType fromType<uint16_t>()     { return UInt16; }
	template <> static FValueType fromType<qint32>()      { return Int32; }
	template <> static FValueType fromType<quint32>()     { return UInt32; }
	template <> static FValueType fromType<qint64>()      { return Int64; }
	template <> static FValueType fromType<quint64>()     { return UInt64; }
	template <> static FValueType fromType<QString>()      { return String; }
	template <> static FValueType fromType<FObject*>()     { return Object; }

	F_DECLARE_ENUM(FLOWCORE_EXPORT, FValueType, Invalid);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_VALUETYPE_H