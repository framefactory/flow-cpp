// -----------------------------------------------------------------------------
//  File        ParameterGroup.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/16 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_PARAMETERGROUP_H
#define FLOWENGINE_PARAMETERGROUP_H

#include "FlowEngine/Library.h"
#include "FlowEngine/Parameter.h"


// -----------------------------------------------------------------------------
//  Class FParameterGroup
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FParameterGroup : public FParameter
{
	F_DECLARE_SERIALIZABLE(FParameterGroup);

	//  Constructors and destructor ----------------------------------

public:
	/// Virtual destructor.
	virtual ~FParameterGroup();

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

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:

};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_PARAMETERGROUP_H