// -----------------------------------------------------------------------------
//  File        ParameterGroup.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/16 $
// -----------------------------------------------------------------------------

#include "FlowEngine/ParameterGroup.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>


// -----------------------------------------------------------------------------
//  Class FParameterGroup
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FParameterGroup, FParameter, 1);

// Constructors and destructor -------------------------------------------------

FParameterGroup::~FParameterGroup()
{
}

// Public commands -------------------------------------------------------------

void FParameterGroup::serialize(FArchive& ar)
{
	FParameter::serialize(ar);

	if (ar.isWriting())
	{
	}
	else // is reading
	{
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FParameterGroup::dump(std::wostream& stream) const
{
	FParameter::dump(stream);
	stream << "\n--- FParameterGroup ---";
}
#endif

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------