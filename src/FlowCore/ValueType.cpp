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