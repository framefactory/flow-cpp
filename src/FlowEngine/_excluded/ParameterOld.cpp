// -----------------------------------------------------------------------------
//  File        Parameter.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.10 $
// -----------------------------------------------------------------------------

#include "FlowEngine/Parameter.h"
#include "FlowEngine/Node.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <ostream>

/*
// -----------------------------------------------------------------------------
//  Class FParameter
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FParameter, FMessageTarget, 1);

// Constructors and destructor -------------------------------------------------

FParameter::FParameter(
	FLinkMode linkMode,
	FParameterTemplate* pTemplate,
	FNode* pParentNode,
	const FUniqueId& id)

	: FMessageTarget(id, pTemplate->name()),
	  m_pTemplate(pTemplate),
	  m_pData(NULL),
	  m_pParentParam(NULL),
	  m_pParentNode(pParentNode),
	  m_childIndex(0),
	  m_isDataOwner(0),
	  m_isTemplateOwner(0),
	  m_isInputLinkArray(0),
	  m_hasLinkedChildren(0),
	  m_isDimensionChild(0),
	  m_isValid(0)
{
	m_inLink.m_pLink = NULL;

	if (!m_pTemplate->dataType().isInvalid()
		&& !linkMode.isInput() || )

	if (m_pTemplate->keepLocalData())
	{
		m_pData = pTemplate->createDefaultData();
		m_isDataOwner = 1;
	}
}

FParameter::FParameter(
	FParameterTemplate* pTemplate,
	FParameter* pParentParameter,
	const FUniqueId& id)
	
	: FMessageTarget(id, pTemplate->name()),
	m_pTemplate(pTemplate),
	m_pData(NULL),
	m_pParentParam(pParentParameter),
	m_pParentNode(NULL),
	m_childIndex(0),
	m_isDataOwner(1),
	m_isTemplateOwner(0),
	m_isInputLinkArray(0),
	m_hasLinkedChildren(0),
	m_isDimensionChild(0),
	m_isValid(0)
{
	m_inLink.m_pLink = NULL;

	if (m_pTemplate->keepLocalData())
		m_pData = pTemplate->createDefaultData();

	m_pParentParam->m_children.push_back(this);
}

FParameter::FParameter(
	const FUniqueId& id,
	FParameter* pMaster)
	
	: FMessageTarget(id, pMaster),
	  m_pTemplate(pMaster->m_pTemplate),
	  m_pParentNode(pMaster->m_pParentNode)
{
	F_ASSERT(false);
	// TODO: Implement instance constructor
}

FParameter::FParameter(
	size_type childIndex,
	FParameter* pParentParameter,
	const FUniqueId& id)

	: FMessageTarget(id),
	m_pTemplate(pParentParameter->m_pTemplate),
	m_pData(NULL),
	m_pParentParam(pParentParameter),
	m_pParentNode(NULL),
	m_childIndex(childIndex),
	m_isDataOwner(1),
	m_isTemplateOwner(0),
	m_isInputLinkArray(0),
	m_hasLinkedChildren(0),
	m_isDimensionChild(1),
	m_isValid(0)
{
	m_inLink.m_pLink = NULL;

	if (m_pTemplate->hasDimensionNames())
		setName(m_pTemplate->dimensionName(childIndex));

	m_pParentParam->m_children.push_back(this);
}

FParameter::~FParameter()
{
	unlinkAll(true);

	for (size_t i = 0, n = m_children.size(); i < n; ++i)
		delete m_children[i];

	if (m_pParentParam)
	{
		m_pParentParam->m_children.erase(
			m_pParentParam->m_children.begin() + m_childIndex);
	}

	if (m_isDataOwner && m_pData)
		F_SAFE_DELETE(m_pData);
}

// Public commands -------------------------------------------------------------

void FParameter::invalidate()
{
	if (m_isDataOwner)
		m_pData->resetChanged();

	for (size_t i = 0, n = m_children.size(); i < n; i++)
			m_children[i]->invalidate();

	m_isValid = false;
}

void FParameter::linkFrom(FParameter* pSource)
{
	F_ASSERT(pSource);
	F_ASSERT(canLinkFrom(pSource));
	F_ASSERT(m_inLink.m_pLink == NULL || isEvent());

	if (m_inLink.m_pLink == NULL)
	{
		// add the first and only linked parameter
		F_ASSERT(!m_isInputLinkArray);
		F_ASSERT(m_isDataOwner || m_pData == NULL);

		m_inLink.m_pLink = pSource;
	}
	else
	{
		if (m_isInputLinkArray)
		{
			// we already have an array, just add the linked parameter
			m_inLink.m_pLinkVec->push_back(pSource);
		}
		else
		{
			// we're adding the second link, so create an array
			FParameter* pParam = m_inLink.m_pLink;
			m_inLink.m_pLinkVec = new vector_type(1, pParam);
			m_inLink.m_pLinkVec->push_back(pSource);
			m_isInputLinkArray = TRUE;
		}
	}

	// add this as outgoing link to source parameter
	pSource->m_outLinks.push_back(this);

	// retrieve the data object of the linked parameter
	FDataArray* pSourceData = pSource->data();

	if (!m_pTemplate->isEvent())
	{
		// assign new data object if available (delete old local data if any)
		if (m_pData)
		{
			F_ASSERT(m_isDataOwner && m_pTemplate->keepLocalData());
			delete m_pData;
		}

		m_pData = pSourceData;
		m_isDataOwner = false;

		// forward propagation of new data source
		for (size_t i = 0, n = m_outLinks.size(); i < n; i++)
			m_outLinks[i]->propagateDataSource(m_pData);
	}

	// set the hasLinkedChildren flag for all parents
	FParameter* pParam = this;
	while (pParam = pParam->m_pParentParam)
		pParam->m_hasLinkedChildren = 1;

	if (pSourceData)
		propagateDataSpace(pSourceData);
}

void FParameter::unlinkFrom(FParameter* pSource)
{
	F_ASSERT(pSource);
	F_ASSERT(isLinkedFrom(pSource));
	F_ASSERT(m_pTemplate->isEvent() || !m_isDataOwner);

	/// remove the linked parameter from this
	_removeInLink(pSource);
	/// remove this from the output links of the linked parameter
	pSource->_removeOutLink(this);

	if (m_inLink.m_pLink == NULL && !m_isDataOwner)
	{
		if (m_pTemplate->keepLocalData())
		{
			m_pData = m_pTemplate->createDefaultData(m_pData);
			m_isDataOwner = 1;
		}
		else
		{
			m_pData = NULL;
		}

		rootParameter()->updateLinkedChildrenFlag();
	}

	propagateDataSpace(m_pData);
}

void FParameter::unlinkAll(bool duringDestruction)
{
	while(!m_outLinks.empty())
		m_outLinks.back()->unlinkFrom(this);

	if (m_inLink.m_pLink == NULL)
		return;

	if (!m_isInputLinkArray)
	{
		m_inLink.m_pLink->_removeOutLink(this);
		m_inLink.m_pLink = NULL;
	}
	else
	{
		vector_type& inLinks = *m_inLink.m_pLinkVec;
		for (size_t i = 0, n = inLinks.size(); i < n; ++i)
			inLinks[i]->_removeOutLink(this);

		delete m_inLink.m_pLinkVec;
		m_inLink.m_pLinkVec = NULL;
	}

	if (!duringDestruction && !m_isDataOwner)
	{
		if (m_pTemplate->keepLocalData())
		{
			m_pData = m_pTemplate->createDefaultData(m_pData);
			m_isDataOwner = 1;
		}
		else
		{
			m_pData = NULL;
		}
	}

	rootParameter()->updateLinkedChildrenFlag();
	propagateDataSpace(m_pData);
}

void FParameter::setChannelCount(size_type count)
{
	F_ASSERT(count > 0);
	F_ASSERT(isDataOwner() && m_pData);

	m_pData->setChannelCount(count);
	propagateDataSpace(m_pData);
}

void FParameter::setChannelCapacity(size_type capacity)
{
	F_ASSERT(capacity > 0);
	F_ASSERT(isDataOwner() && m_pData);

	m_pData->setChannelCapacity(capacity);
	propagateDataSpace(m_pData);
}

void FParameter::setDimensionCount(size_type count)
{
	F_ASSERT(count > 0);
	F_ASSERT(isDataOwner() && m_pData);
	F_ASSERT(m_pTemplate->hasDynamicDimensions());

	m_pData->setDimensionCount(count);
	propagateDataSpace(m_pData);
}

void FParameter::setDimensionCapacity(size_type capacity)
{
	F_ASSERT(count > 0);
	F_ASSERT(isDataOwner() && m_pData);
	F_ASSERT(m_pTemplate->hasDynamicDimensions());

	m_pData->setDimensionCapacity(capacity);
	propagateDataSpace(m_pData);
}

void FParameter::serialize(FArchive& ar)
{
	// call base class implementation
	FMessageTarget::serialize(ar);

	if (ar.isReading())
	{
	}
	else // isWriting
	{
	}
}

// Public queries --------------------------------------------------------------

bool FParameter::canLinkFrom(FParameter* pSource) const
{
	// 1. only single linkable and multi linkable parameters can have input links
	// 2. for single linkable parameters, neither this parameter nor
	//    any of its children may be linked, and no linked parents
	// 4. data type must be compatible, number of dimensions be equal
	// 5. self-linkage not allowed
	// 6. can't link more than once between the same parameters

	if (isOutput() || isUnlinkable() || pSource == this
			|| isLinkedFrom(pSource) || !hasCompatibleData(pSource))
		return false;

	if (isEvent())
		return true;

	if ( hasInputLinks() || m_hasLinkedChildren || hasLinkedParents())
		return false;

	return true;
}

bool FParameter::isLinkedFrom(FParameter* pSource) const
{
	if (m_inLink.m_pLink == NULL)
		return false;

	if (!m_isInputLinkArray)
		return m_inLink.m_pLink == pSource;

	vector_type& inLinks = *m_inLink.m_pLinkVec;
	for (size_t i = 0, n = inLinks.size(); i < n; ++i)
		if (inLinks[i] == pSource)
			return true;

	return false;
}

wstring_t FParameter::toString() const
{
	return FMessageTarget::toString();
}

// Overrides -------------------------------------------------------------------

void FParameter::onMakeUnique()
{
	F_ASSERT(false);
}

bool FParameter::onProcessMessage(FMessage* pMessage)
{
	return false;
}

// Protected members -----------------------------------------------------------

void FParameter::propagateDataSource(FDataArray* pNewDataSource)
{
	// do not propagate if the parameter owns the data
	// or both data objects are equal, i.e. nothing changes
	if (m_isDataOwner || (pNewDataSource == m_pData))
		return;

	m_pData = pNewDataSource;

	// propagate recursively to all directly linked downstream parameters
	for (size_t i = 0, n = m_outLinks.size(); i < n; i++)
		m_outLinks[i]->propagateDataSource(pNewDataSource);
}

bool FParameter::updateLinkedChildrenFlag()
{
	// result for this parameter
	bool result = false;

	// also check all children, they all need to update their flag, and adjust the result
	for (size_t i = 0, n = m_children.size(); i < n && !result; ++i)
		result = m_children[i]->updateLinkedChildrenFlag() || result;

	m_hasLinkedChildren = result;
	return result;
}

void FParameter::adaptChannelCount(FDataArray* pSourceData)
{
	F_ASSERT(isInput());
	FParameter* pParam = this;
	vector_type* pChildren = NULL;

	if (m_hasDimensionChildren)
	{
		pChildren = &m_children;
	}
	else if (m_isDimensionChild)
	{
		pParam = m_pParentParam;
		pChildren = &m_pParentParam->m_children;
	}
	else if (!m_isDataOwner)
	{
		if (m_pParentNode && pParam->m_pData)
			m_pParentNode->_setChannelCapacity(pParam->m_pData->channelCapacity(), this);

		for (size_t i = 0, n = m_outLinks.size(); i < n; ++i)
			m_outLinks[i]->_adaptChannelCapacity();
		return;
	}

	// find maximum count of all in-links of parent and all dummy children
	FDataArray::size_type capacity = 0;

	if (!isEvent())
	{
		if (pParam->m_pData)
			capacity = pParam->m_pData->channelCapacity();
	}
	else
	{
		for (size_t i = 0, n = inputLinkCount(); i < n; ++i)
		{
			FParameter* pSource = inputLink(i);
			if (pSource->data())
				capacity = fMax(capacity, pSource->data()->channelCapacity());
		}
	}

	if (pChildren) // pChildern is not null only if we are in a dummy relationship
	{
		for (size_t i = 0, n = pChildren->size(); i < n; ++i)
		{
			FParameter* pChild = (*pChildren)[i];
			F_ASSERT(pChild->m_pData);
			if (!pChild->isEvent())
				capacity = fMax(capacity, pChild->m_pData->channelCapacity());
			else
			{
				for (size_t i = 0, n = pChild->inputLinkCount(); i < n; ++i)
				{
					FParameter* pSource = pChild->inputLink(i);
					F_ASSERT(pSource->m_pData);
					capacity = fMax(capacity, pSource->m_pData->channelCapacity());
				}
			}
		}
	}

	capacity = fMin(capacity, m_pTemplate->channelLimit());

	// set count and propagate to out links
	if (pParam->m_pData && pParam->m_isDataOwner)
		pParam->m_pData->setChannelCapacity(capacity, true);

	if (m_pParentNode)
		m_pParentNode->_setChannelCapacity(capacity, this);

	for (size_t i = 0, n = pParam->m_outLinks.size(); i < n; ++i)
		pParam->m_outLinks[i]->_adaptChannelCapacity();

	if (pChildren)
	{
		for (size_t i = 0, n = pChildren->size(); i < n; i++)
		{
			FParameter* pChild = (*pChildren)[i];
			pChild->m_pData->setChannelCapacity(capacity, true);

			for (size_t i = 0, n = pChild->m_outLinks.size(); i < n; i++)
				pChild->m_outLinks[i]->_adaptChannelCapacity();
		}
	}
}

// Internal functions ----------------------------------------------------------

void FParameter::_validate()
{
	if (m_pTemplate->isOutput())
	{
		if (m_pParentNode)
			m_pParentNode->validate();

		// if this is a dimension child, get updated value(s) from parent
		if (m_isDimensionChild)
		{
			F_ASSERT(m_pData && m_isDataOwner && m_pTemplate->keepLocalData());
			const FDataArray* pParentData = m_pParentParam->data();

			for (size_type c = 0, n = pParentData->channelCount(); c < n; c++)
			{
				if (pParentData->hasChanged(c))
				{
					m_pData->convertFrom(pParentData, c, c, m_childIndex, 0);
					m_pData->setChanged(c);
				}				
			}
		}

		// for an output, we're done
		return;
	}

	// if we are linked...
	if (m_inLink.m_pLink)
	{
		// only one link
		if (!m_isInputLinkArray)
		{
			// validate the only linked parameter
			m_inLink.m_pLink->validate();
		}
		else // multiple links
		{
			// first validate all linked parameters
			vector_type& inLinks = *m_inLink.m_pLinkVec;
			for (size_t i = 0, n = inLinks.size(); i < n; i++)
				inLinks[i]->validate();

			// then add the fire counts and update the data from the channel
			// with maximum counts > 0
			for (size_type c = 0, n = m_pData->channelCount(); c < n; ++c)
			{
				size_t maxCount = 0;
				FDataArray* pSourceDataWithMaxCount = NULL;
				for (size_t i = 0, n = inLinks.size(); i < n; ++i)
				{
					FDataArray* pSourceData = inLinks[i]->data();
					if (pSourceData)
					{
						size_type count = pSourceData->fireCount(c);
						if (count > 0)
						{
							if (m_pData && m_isDataOwner)
								m_pData->fire(c, count); // add the fire count
							if (count > maxCount)
							{
								maxCount = count;
								pSourceDataWithMaxCount = pSourceData;
							}
						}
					}
				}

				if (pSourceDataWithMaxCount)
				{
					if (m_pData && m_isDataOwner)
					{
						m_pData->convertFrom(pSourceDataWithMaxCount,
							c, c, 1, 1, 1, 0, 0, m_pData->dimensionCount());
					}
					else
					{
						m_pData = pSourceDataWithMaxCount;
					}

					m_pData->setChanged(c);
				}
			} // end for
		} // end if single/multi link
	} // end if linked

	// validate all children
	if (m_hasLinkedChildren)
	{
		F_ASSERT(!m_isDimensionChild);

		for (size_t i = 0, n = m_children.size(); i < n; i++)
			m_children[i]->validate();
		return;
	}

	// if this is a linked dimension child and has changed values,
	// we need to update the value at the corresponding index of the parent
	if (m_isDimensionChild)
	{
		FDataArray* pParentData = m_pParentParam->data();
		F_ASSERT(pParentData);
		F_ASSERT(m_pData);
		F_ASSERT((size_type)m_childIndex < pParentData->dimensionCount());
		F_ASSERT(m_pData->channelCount() == pParentData->channelCount());

		if (hasInputLinks())
		{
			F_ASSERT(m_pParentParam->isEvent()
				|| !m_pParentParam->hasInputLinks());

			for (size_type c = 0, n = pParentData->channelCount(); c < n; c++)
			{
				if (m_pData->hasChanged(c))
				{
					pParentData->convertFrom(m_pData, c, c, 0, m_childIndex);
					pParentData->setChanged(c);
				}
			}
		}
		else if (m_outLinks.size() > 0) // check if parent has changed values and update
		{
			for (size_type c = 0, n = pParentData->channelCount(); c < n; c++)
			{
				if (pParentData->hasChanged(c))
				{
					m_pData->convertFrom(pParentData, c, c, m_childIndex, 0);
					m_pData->setChanged(c);
				}
			}
		}
	}
}



void FParameter::_removeInLink(FParameter* pSource)
{
	if (!m_isInputLinkArray)
	{
		m_inLink.m_pLink = NULL;
	}
	else
	{
		F_ASSERT(isEvent());
		vector_type& inLinks = *m_inLink.m_pLinkVec;
		for (size_t i = 0, n = inLinks.size(); i < n; ++i)
		{
			if (inLinks[i] == pSource)
			{
				inLinks.erase(inLinks.begin() + i);
				if (inLinks.size() == 1)
				{
					FParameter* pParam = inLinks.front();
					delete m_inLink.m_pLinkVec;
					m_inLink.m_pLink = pParam;
					m_isInputLinkArray = FALSE;
				}

				break;
			}
		}
	}
}

void FParameter::_removeOutLink(FParameter* pSource)
{
	for (size_t i = 0, n = m_outLinks.size(); i < n; ++i)
	{
		if (m_outLinks[i] == pSource)
		{
			m_outLinks.erase(m_outLinks.begin() + i);
			break;
		}
	}
}





void FParameter::_adaptChannelCount()
{
	F_ASSERT(isInput());
	FParameter* pParam = this;
	vector_type* pChildren = NULL;

	if (m_hasDimensionChildren)
	{
		pChildren = &m_children;
	}
	else if (m_isDimensionChild)
	{
		pParam = m_pParentParam;
		pChildren = &m_pParentParam->m_children;
	}
	else if (!m_isDataOwner)
	{
		if (m_pParentNode && pParam->m_pData)
			m_pParentNode->_setChannelCount(pParam->m_pData->channelCount(), this);

		for (size_t i = 0, n = m_outLinks.size(); i < n; i++)
			m_outLinks[i]->_adaptChannelCount();
		return;
	}

	// find maximum count of all in-links of parent and all dummy children
	FDataArray::size_type count = 0;

	if (!isEvent())
	{
		if (pParam->m_pData)
			count = pParam->m_pData->channelCount();
	}
	else
	{
		for (size_t i = 0, n = pParam->m_inLink.m_pLinkVec->size(); i < n; i++)
		{
			FParameter* pSource = (*(pParam->m_inLink.m_pLinkVec))[i];
			if (pSource->data())
				count = fMax(count, pSource->data()->channelCount());
		}
	}

	if (pChildren) // pChildern is not null only if we are in a dummy relationship
	{
		for (size_t i = 0, n = pChildren->size(); i < n; i++)
		{
			FParameter* pChild = (*pChildren)[i];
			assert(pChild->m_pData);
			if (!pChild->isEvent())
				count = fMax(count, pChild->m_pData->channelCount());
			else
			{
				for (size_t i = 0, n = pChild->inputLinkCount(); i < n; i++)
				{
					FParameter* pSource = pChild->inputLink(i);
					assert(pSource->m_pData);
					count = fMax(count, pSource->m_pData->channelCount());
				}
			}
		}
	}

	count = fMin(count, m_pTemplate->channelLimit());

	// set count and propagate to out links
	if (pParam->m_pData && pParam->m_isDataOwner)
		pParam->m_pData->setChannelCount(count, true);

	if (m_pParentNode)
		m_pParentNode->_setChannelCount(count, this);

	for (size_t i = 0, n = pParam->m_outLinks.size(); i < n; i++)
		pParam->m_outLinks[i]->_adaptChannelCount();

	if (pChildren)
	{
		for (size_t i = 0, n = pChildren->size(); i < n; i++)
		{
			FParameter* pChild = (*pChildren)[i];
			pChild->m_pData->setChannelCount(count, true);
			for (size_t i = 0, n = pChild->m_outLinks.size(); i < n; i++)
				pChild->m_outLinks[i]->_adaptChannelCount();
		}
	}
}

bool FParameter::_hasCompatibleData(FParameter* pSource) const
{
	// data is compatible if  1) types are equal or both value types (i.e. compatible)
	//                        2) both are or are not events
	//                        3) both have the same dimensions OR one has dimension 0,
	//                           meaning that it can adapt to the number of dimensions of
	//                           the other parameter

	// TODO! Compare object types, must be equal

	const FParameterTemplate* pSourceTempl = pSource->getTemplate();
	FValueType type = m_pTemplate->dataType();
	FValueType sourceType = pSourceTempl->dataType();

	if (type == sourceType || type.isString() || type.isInvalid())
	{
		if (type.isObject() && sourceType.isObject()
			&& (m_pTemplate->objectType() != pSourceTempl->objectType()))
		{
			return false;
		}

		if ((m_pTemplate->isEvent() == pSourceTempl->isEvent())
			&& (m_pTemplate->hasDynamicDimensions() && pSourceTempl->hasDynamicDimensions()
			|| (m_pTemplate->dimensionCount() == pSourceTempl->dimensionCount())))
		{
			return true;
		}
	}

	return false;
}

bool FParameter::_hasLinkedParents() const
{
	return (m_pParentParam &&
		(m_pParentParam->hasInputLinks() || m_pParentParam->_hasLinkedParents()));
}
*/
// -----------------------------------------------------------------------------