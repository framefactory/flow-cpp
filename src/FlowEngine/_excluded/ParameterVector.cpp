// -----------------------------------------------------------------------------
//  File        ParameterVector.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/16 $
// -----------------------------------------------------------------------------

#include "FlowEngine/ParameterVector.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>


// -----------------------------------------------------------------------------
//  Class FParameterVector
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FParameterVector, FParameter, 1);

// Constructors and destructor -------------------------------------------------

FParameterVector::~FParameterVector()
{
}

// Public commands -------------------------------------------------------------

void FParameterVector::serialize(FArchive& ar)
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
void FParameterVector::dump(std::wostream& stream) const
{
	FParameter::dump(stream);
	stream << "\n--- FParameterVector ---";
}
#endif

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------