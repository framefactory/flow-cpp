// -----------------------------------------------------------------------------
//  File        Parameter.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.10 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_PARAMETER_H
#define FLOWENGINE_PARAMETER_H

#include "FlowEngine/Library.h"
#include "FlowEngine/DataArray.h"
#include "FlowEngine/LinkMode.h"
#include "FlowEngine/ParameterTemplate.h"

#include "FlowCore/MessageTarget.h"

#include <vector>
#include <iosfwd>

class FNode;
/*
// -----------------------------------------------------------------------------
//  Class FParameter
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FParameter : public FMessageTarget
{
	F_DECLARE_SERIALIZABLE(FParameter);

	//  Public types -------------------------------------------------

public:
	typedef FDataArray::size_type size_type;
	typedef std::vector<FParameter*> vector_type;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a root parameter from the given template.
	FParameter(FLinkMode linkMode, FParameterTemplate* pTemplate,
		FNode* pParentNode, const FUniqueId& id);
	/// Creates a child parameter from the given template.
	FParameter(FParameterTemplate* pTemplate,
		FParameter* pParentParameter, const FUniqueId& id);
	/// Creates an instance of the given master parameter.
	FParameter(const FUniqueId& id, FParameter* pMaster);

protected:
	/// Creates a dimension child parameter.
	FParameter(size_type childIndex, FParameter* pParentParameter,
		const FUniqueId& id);

public:
	/// Virtual destructor.
	virtual ~FParameter();

	//  Public commands ----------------------------------------------

	/// Validates the parameter. Validates all input links
	/// and marks this parameter as valid.
	void validate();
	/// Clears the validation flag.
	void invalidate();

	/// Links the given source parameter as an input of this parameter.
	/// Calling this function is only valid if canLinkFrom() returns true.
	void linkFrom(FParameter* pSource);
	/// Unlinks the given source parameter from this parameter.
	void unlinkFrom(FParameter* pSource);
	/// Removes all currently linked parameters.
	void unlinkAll(bool duringDestruction = false);

	/// Changes the number of actual data channels.
	void setChannelCount(size_type count);
	/// Changes the number of allocated data channels.
	void setChannelCapacity(size_type capacity);
	/// Changes the number of actual data dimensions.
	void setDimensionCount(size_type count);
	/// Changes the number of allocated data dimensions.
	void setDimensionCapacity(size_type capacity);

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns true if this parameter has been validated.
	bool isValid() const { return m_isValid; }
	/// Returns true if this parameter is not linkable.
	bool isUnlinkable() const { return m_linkMode.isUnlinkable(); }
	/// Returns true if this parameter is input linkable.
	bool isInput() const { return m_linkMode.isInput(); }
	/// Returns true if this parameter is output linkable.
	bool isOutput() const { return m_linkMode.isOutput(); }
	/// Returns true if this parameter has event behavior.
	bool isEvent() const { return m_pTemplate->isEvent(); }
	/// Returns true if this parameter currently owns its data.
	bool isDataOwner() const { return m_isDataOwner; }
	/// Returns true if this parameter's data persists if unlinked.
	bool isDataPersistent() const { return m_isDataPersistent; }

	/// Returns the number of actual channels of this parameter's data.
	/// Returns 0 if the parameter doesn't own any data.
	size_type channelCount() const;
	/// Returns the number of allocated channels of this parameter's data.
	/// Returns 0 if the parameter doesn't own any data.
	size_type channelCapacity() const;
	/// Returns the number of actual dimensions of this parameter's data.
	/// Returns 0 if the parameter doesn't own any data.
	size_type dimensionCount() const;
	/// Returns the number of allocated dimensions of this parameter's data.
	/// Returns 0 if the parameter doesn't own any data.
	size_type dimensionCapacity() const;

	/// Returns true if it's possible to add the given source parameter
	/// as an input link of this parameter.
	bool canLinkFrom(FParameter* pSource) const;
	/// Returns true if the given source parameter is currently linked to this.
	bool isLinkedFrom(FParameter* pSource) const;

	/// Returns true if this parameter has input links.
	bool hasInputLinks() const { return m_inLink.m_pLink != NULL; }
	/// Returns the number of input links.
	size_t inputLinkCount() const;
	/// Returns the linked parameter at the given index.
	FParameter* inputLink(size_t index) const;

	/// Returns true if this parameter has output links.
	bool hasOutputLinks() const { return !m_outLinks.empty(); }
	/// Returns the number of output links.
	size_t outputLinkCount() const { return m_outLinks.size(); }
	/// Returns the linked parameter at the given index.
	FParameter* outputLink(size_t index) const;

	/// Returns the parent parameter.
	FParameter* parentParameter() const { return m_pParentParam; }
	/// Returns the root parameter of this.
	FParameter* rootParameter() const;
	/// Returns true if this parameter has no parent parameter.
	bool isRootParameter() const { return !m_pParentParam; }
	/// Returns the number of child parameters.
	size_t childParameterCount() const { return m_children.size(); }
	/// Returns the parameter child at the given index.
	FParameter* childParameterAt(size_t index) const;

	/// Returns the data carried by this parameter.
	FDataArray* data() const { return m_pData; }

	/// Returns the template this parameter is created from.
	const FParameterTemplate* getTemplate() const { return m_pTemplate; }
	
	/// Returns the parent node that owns this parameter.
	FNode* parentNode() const { return m_pParentNode; }

	/// Returns a text representation of the value of this parameter.
	std::wstring toString() const;

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Protected methods --------------------------------------------

protected:
	/// Called by upstream parameters if their data object has changed.
	void propagateDataSource(FDataArray* pNewData);
	/// Called by upstream parameters if their data space, i.e.
	/// dimensions and channels have changed.
	void propagateDataSpace(FDataArray* pData);

	/// Recursively sets or clears the hasLinkedChildren flag.
	bool updateLinkedChildrenFlag();
	/// Returns true if the data types of this and the given parameter
	/// are compatible.
 	bool hasCompatibleData(FParameter* pSource) const;
	/// Returns true if this parameter has parents with input links.
	bool hasLinkedParents() const;

	//  Overrides ----------------------------------------------------

protected:
	virtual void onMakeUnique();
	virtual bool onProcessMessage(FMessage* pMessage);

	//  Internal types -----------------------------------------------

private:
	typedef std::vector<FParameter*> vector_type;

	union inLink_t
	{
		FParameter* m_pLink;
		vector_type* m_pLinkVec;
	};

	//  Internal functions -------------------------------------------
	
	void _validate();

	void _removeInLink(FParameter* pSource);
	void _removeOutLink(FParameter* pSource);


	//  Internal data members ----------------------------------------

	FParameterTemplate* m_pTemplate;
	FDataArray* m_pData;
	FLinkMode m_linkMode;

	inLink_t m_inLink;
	vector_type m_outLinks;

	FParameter* m_pParentParam;
	vector_type m_children;

	FNode* m_pParentNode;

	uint32_t m_childIndex			: 16;
	uint32_t m_isDataOwner			:  1;
	uint32_t m_isDataPersistent		:  1;
	uint32_t m_isTemplateOwner		:  1;
	uint32_t m_isInputLinkArray		:  1;
	uint32_t m_hasLinkedChildren	:  1;
	uint32_t m_hasDimensionChildren	:  1;
	uint32_t m_isDimensionChild		:  1;
	uint32_t m_isValid				:  1;
};

// Inline members --------------------------------------------------------------

inline void FParameter::validate()
{
	if (m_isValid)
		return;

	_validate();
	m_isValid = true;
}

inline FParameter::size_type FParameter::channelCount() const
{
	return m_pData ? m_pData->channelCount() : 0;
}

inline FParameter::size_type FParameter::channelCapacity() const
{
	return m_pData ? m_pData->channelCapacity() : 0;
}

inline size_t FParameter::inputLinkCount() const
{
	return m_isInputLinkArray ?
		m_inLink.m_pLinkVec->size() : (m_inLink.m_pLink != NULL);
}

inline FParameter* FParameter::inputLink(size_t index) const
{
	F_ASSERT(m_inLink.m_pLink != NULL);

	if (m_isInputLinkArray)
	{
		F_ASSERT(index < m_inLink.m_pLinkVec->size());
		return (*m_inLink.m_pLinkVec)[index];
	}

	F_ASSERT(index == 0);
	return m_inLink.m_pLink;
}

inline FParameter* FParameter::outputLink(size_t index) const
{
	F_ASSERT(index < m_outLinks.size());
	return m_outLinks[index];
}

inline FParameter* FParameter::rootParameter() const
{
	FParameter* pParam = const_cast<FParameter*>(this);
	while (pParam->parentParameter())
		pParam = pParam->parentParameter();
	return pParam;
}

inline FParameter* FParameter::childParameterAt(size_t index) const
{
	F_ASSERT(index < m_children.size());
	return m_children[index];
}

// -----------------------------------------------------------------------------
*/

#endif // FLOWENGINE_PARAMETER_H