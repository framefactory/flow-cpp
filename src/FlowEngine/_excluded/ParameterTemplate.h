// -----------------------------------------------------------------------------
//  File        ParameterTemplate.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.10 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_PARAMETERTEMPLATE_H
#define FLOWENGINE_PARAMETERTEMPLATE_H

#include "FlowEngine/Library.h"
#include "FlowEngine/LinkMode.h"
#include "FlowEngine/DataArray.h"

#include "FlowCore/NamedObject.h"
#include "FlowCore/String.h"

#include <iosfwd>
class FArchive;
class FTypeInfo;

// -----------------------------------------------------------------------------
//  Class FParameterTemplate
// -----------------------------------------------------------------------------

F_DECLARE_SHARED_PTR(FParameterTemplate);

class FLOWENGINE_EXPORT FParameterTemplate : public FNamedObject
{
	F_DECLARE_SERIALIZABLE(FParameterTemplate);

	//  Public types -------------------------------------------------

public:
	typedef FDataArray::size_type size_type;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a template for a linkable parameter.
	FParameterTemplate(const wstring_t& name, FValueType valueType,
		size_type channelCount, size_type dimensionCount, bool isEvent);

	/// Virtual destructor.
	virtual ~FParameterTemplate();

	//  Public commands ----------------------------------------------

	/// Sets names for the parameter's dimensions.
	void setDimensionNames(const wstring_vector_t& names);
	/// Sets an object type.
	void setObjectType(const FTypeInfo* pObjectType);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Creates a data array for the parameter filled with default values.
	/// If a data array is specified, values of that array are used to create
	/// the defaults.
	FDataArray* createDefaultData(const FDataArray* pLinkedData = NULL) const;

	/// Returns true if the link type is single link.
	bool isEvent() const { return m_isEvent; }

	/// Returns the type of the parameter data.
	FValueType dataType() const { return m_defaultValues.type(); }
	/// Returns the type info for object data.
	const FTypeInfo* objectType() const { return m_pObjectType; }
	
	/// Returns the maximum number of channels of the parameter data.
	/// A count of zero indicates unlimited channels.
	FValueArray::size_type channelCount() const { return m_channelCount; }
	/// Returns the number of dimensions of the parameter data.
	/// A count of zero indicates dynamic dimensions.
	FValueArray::size_type dimensionCount() const { return m_dimensionCount; }
	/// Returns true if the parameter can change its dimension count dynamically.
	bool hasDynamicDimensions() const { return m_dimensionCount == 0; }
	/// Returns true if the parameter has names for individual dimensions.
	bool hasDimensionNames() const { return !m_dimensionNames.empty(); }
	/// Returns the name of the value with the given index.
	const wstring_t& dimensionName(size_t index) const;

	/// Returns a text representation of this parameter template.
	virtual wstring_t toString() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Internal functions -------------------------------------------

	/// Returns a text with type name, dimension and channel count, event state.
	wstring_t FParameterTemplate::_typeDescription() const;

	//  Internal data members ----------------------------------------

private:
	FValueArray m_defaultValues;
	FValueArray::size_type m_channelCount;
	FValueArray::size_type m_dimensionCount;
	const FTypeInfo* m_pObjectType;
	std::vector<wstring_t> m_dimensionNames;
	bool m_isEvent;
};

// Inline members --------------------------------------------------------------

const wstring_t& FParameterTemplate::dimensionName(size_t index) const
{
	F_ASSERT(index < m_dimensionCount);
	return m_dimensionNames[index];
}
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_PARAMETERTEMPLATE_H