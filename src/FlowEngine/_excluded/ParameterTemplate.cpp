// -----------------------------------------------------------------------------
//  File        ParameterTemplate.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.10 $
// -----------------------------------------------------------------------------

#include "FlowEngine/ParameterTemplate.h"

#include "FlowCore/Archive.h"
#include "FlowCore/TypeRegistry.h"
#include "FlowCore/MemoryTracer.h"

#include <ostream>
#include <sstream>

// -----------------------------------------------------------------------------
//  Class FParameterTemplate
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FParameterTemplate, FNamedObject, 1);

// Constructors and destructor -------------------------------------------------

FParameterTemplate::FParameterTemplate(
	const wstring_t& name, FValueType valueType,
	size_type channelCount, size_type dimensionCount, bool isEvent)
: FNamedObject(name),
  m_defaultValues(valueType, 1, dimensionCount),
  m_channelCount(channelCount),
  m_dimensionCount(dimensionCount),
  m_pObjectType(NULL),
  m_isEvent(isEvent)
{

}

FParameterTemplate::~FParameterTemplate()
{
}

// Public commands -------------------------------------------------------------

void FParameterTemplate::setDimensionNames(const wstring_vector_t& names)
{
	F_ASSERT(names.size() == m_dimensionCount);
	m_dimensionNames = names;
}

void FParameterTemplate::setObjectType(const FTypeInfo* pObjectType)
{
	m_pObjectType = pObjectType;
}

void FParameterTemplate::serialize(FArchive& ar)
{
	FNamedObject::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_defaultValues;
		ar << m_dimensionCount;
		ar << m_channelCount;
		ar << m_pObjectType;
		ar << m_dimensionNames;
		ar << m_isEvent;
	}
	else // is reading
	{
		ar >> m_defaultValues;
		ar >> m_dimensionCount;
		ar >> m_channelCount;
		ar >> m_pObjectType;
		ar >> m_dimensionNames;
		ar >> m_isEvent;
	}
}

// Public queries --------------------------------------------------------------

FDataArray* FParameterTemplate::createDefaultData(
	const FDataArray* pLinkedData /* = NULL */) const
{
	FDataArray* pData
		= new FDataArray(m_defaultValues.type(), m_channelCount, m_dimensionCount);

	if (!pData->isEmpty())
	{
		if (pLinkedData)
			pData->convertFrom(*pLinkedData);
		else
			pData->convertFromValueArray(m_defaultValues);
	}

	return pData;
}

wstring_t FParameterTemplate::toString() const
{
	std::wostringstream stream;
	stream << name() << L": " << _typeDescription();
	return stream.str();
}

#ifdef FLOW_DEBUG
void FParameterTemplate::dump(std::wostream& stream) const
{
	FNamedObject::dump(stream);
	stream << "\n--- FParameterTemplate ---";
	stream << "\n     Data type:          " << _typeDescription();
}
#endif

// Internal functions ----------------------------------------------------------

wstring_t FParameterTemplate::_typeDescription() const
{
	std::wostringstream stream;
	stream << m_defaultValues.typeName();
	if (dataType().isObject() && m_pObjectType)
		stream << " (" << m_pObjectType->typeName() << ")";
	stream << " [" << m_channelCount << "c, " << m_dimensionCount << "d";
	stream << (isEvent() ? " | Event]" : "]");
	return stream.str();
}
// -----------------------------------------------------------------------------