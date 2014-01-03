// -----------------------------------------------------------------------------
//  File        FParameter.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/16 $
// -----------------------------------------------------------------------------

#include "FlowEngine/Parameter.h"
#include "FlowCore/MemoryTracer.h"

#include "FlowCore/Archive.h"
#include <ostream>


// -----------------------------------------------------------------------------
//  Class FParameter
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FParameter, FMessageTarget, 1);

// Constructors and destructor -------------------------------------------------

FParameter::~FParameter()
{
}

// Public commands -------------------------------------------------------------

void FParameter::serialize(FArchive& ar)
{
	FMessageTarget::serialize(ar);

	if (ar.isWriting())
	{
	}
	else // is reading
	{
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FParameter::dump(std::wostream& stream) const
{
	FMessageTarget::dump(stream);
	stream << "\n--- FParameter ---";
}
#endif

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------