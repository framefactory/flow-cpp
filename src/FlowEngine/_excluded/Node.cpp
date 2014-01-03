// -----------------------------------------------------------------------------
//  File        Node.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.24 $
// -----------------------------------------------------------------------------

#include "FlowEngine/Node.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FNode
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FNode, FCompositeObject, 1);

// Constructors and destructor -------------------------------------------------

FNode::FNode(FNode* pParent /* = NULL */)
	: FCompositeObject(pParent)
{
}

FNode::~FNode()
{
}

// Public commands -------------------------------------------------------------

void FNode::serialize(FArchive& ar)
{
	if (ar.isWriting())
	{
	}
	else // is reading
	{
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FNode::dump(std::wostream& stream) const
{
	FCompositeObject::dump(stream);
	stream << "\n--- FNode ---";
}
#endif

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------
