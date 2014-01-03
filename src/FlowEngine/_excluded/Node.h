// -----------------------------------------------------------------------------
//  File        Node.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.24 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_NODE_H
#define FLOWENGINE_NODE_H

#include "FlowEngine/Library.h"
#include "FlowEngine/DataArray.h"

#include "FlowCore/CompositeObject.h"
#include "FlowCore/Archive.h"

#include <iostream>

// -----------------------------------------------------------------------------
//  Class FNode
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FNode : public FCompositeObject
{
	F_DECLARE_SERIALIZABLE_CUSTOM_DC(FNode);
	friend class FParameter;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a new node that becomes a child of the given parent node.
	FNode(FNode* pParent = NULL);
	/// Virtual destructor.
	virtual ~FNode();

	//  Public commands ----------------------------------------------

		void validate();

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

	//  Internal functions -------------------------------------------

private:
	void _setChannelCapacity(FDataArray::size_type capacity, FParameter* pParam);
	void _setChannelCount(FDataArray::size_type count, FParameter* pParam);

	//  Internal data members ----------------------------------------

private:
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_NODE_H