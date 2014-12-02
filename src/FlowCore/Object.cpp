// -----------------------------------------------------------------------------
//  File        Object.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/06 $
// -----------------------------------------------------------------------------

#include "FlowCore/Object.h"
#include "FlowCore/TypeInfo.h"
#include "FlowCore/TypeRegistry.h"

// -----------------------------------------------------------------------------
//  Class FObject
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

const FTypeInfo FObject::typeInfo("FObject", sizeof(FObject), 0, NULL, NULL);

const FTypeInfo* FObject::staticType() {
	return &FObject::typeInfo;
}

// Public commands -------------------------------------------------------------

void FObject::serialize(FArchive&)
{
	// do nothing
}

// Public queries --------------------------------------------------------------

const FTypeInfo* FObject::dynamicType() const {
	return &FObject::typeInfo;
}

bool FObject::isKindOf(const FTypeInfo* pClass) const {
	return dynamicType()->isDerivedFrom(pClass);
}

QString FObject::toString() const
{
	return dynamicType()->typeName();
}

#ifdef FLOW_DEBUG
QString FObject::dump() const
{
	return QString("\n\n*** %1 (a FObject) ***").arg(dynamicType()->typeName());
}
#endif

// -----------------------------------------------------------------------------
