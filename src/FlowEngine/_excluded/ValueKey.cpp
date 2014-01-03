// -----------------------------------------------------------------------------
//  File        ValueKey.cpp
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/08 $
// -----------------------------------------------------------------------------

#include "FlowEngine/ValueKey.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FValueKey
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FValueKey, FObject, 1);

// Constructors and destructor -------------------------------------------------

FValueKey::FValueKey(FTime time)
	: m_time(time)
{
}

FValueKey::FValueKey(FTime time, const FValueArray& val)
	: m_time(time),
	  m_value(val)
{
}

FValueKey::~FValueKey()
{
}

// Public commands -------------------------------------------------------------

void FValueKey::serialize(FArchive& ar)
{
	FObject::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_time;
		ar << m_value;
	}
	else // is reading
	{
		ar >> m_time;
		ar >> m_value;
	}
}

// Public queries --------------------------------------------------------------

FInterpolationMode FValueKey::interpolationMode() const
{
	return FInterpolationMode::Invalid;
}

#ifdef FLOW_DEBUG
void FValueKey::dump(std::wostream& stream) const
{
	FObject::dump(stream);
	stream << "\n--- FValueKey ---";
	stream << "\n     Time:  " << m_time;
	stream << "\n     Value: " << m_value;
}
#endif

// -----------------------------------------------------------------------------