// -----------------------------------------------------------------------------
//  File        FParameter.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/16 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_FPARAMETER_H
#define FLOWENGINE_FPARAMETER_H

#include "FlowEngine/Library.h"
#include "FlowEngine/DataArray.h"

#include "FlowCore/MessageTarget.h"

#include <vector>

class FNode;

// -----------------------------------------------------------------------------
//  Class FParameter
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FParameter : public FMessageTarget
{
	F_DECLARE_SERIALIZABLE(FParameter);

	//  Public types -------------------------------------------------

public:
	typedef std::vector<FParameter*> vector_type;

	//  Constructors and destructor ----------------------------------

public:
	/// Virtual destructor.
	virtual ~FParameter();

	//  Public commands ----------------------------------------------

public:
	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:
	virtual bool onProcessMessage(FMessage* pMessage);
	virtual void onMakeUnique();

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	union inLink_t
	{
		FParameter* pParam;
		vector_type* pVector;
	};

	inLink_t m_inLinks;
	vector_type m_outLinks;

	FValueArray* m_pData;
	FNode* m_pParentNode;

	uint32_t m_isValid              :  1;
	uint32_t m_isEvent              :  1;
	uint32_t m_isInputLinkArray		:  1;
	uint32_t m_isDataOwner			:  1;
	uint32_t m_isDataPersistent		:  1;
	uint32_t m_isTemplateOwner		:  1;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_FPARAMETER_H