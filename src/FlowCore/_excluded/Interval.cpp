// -----------------------------------------------------------------------------
//  File        Interval.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.27 $
// -----------------------------------------------------------------------------

#include "FlowCore/Interval.h"
#include "FlowCore/Archive.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FInterval
// -----------------------------------------------------------------------------

FArchive& operator<<(FArchive& ar, const FInterval& interval)
{
	ar << interval.start() << interval.end();
	return ar;
}

FArchive& operator>>(FArchive& ar, FInterval& interval)
{
	FTime start, end;
	ar >> start >> end;
	interval.setStart(start);
	interval.setEnd(end);
	return ar;
}

std::wostream& operator<<(std::wostream& stream, FInterval interval)
{
	stream << L"[" << interval.start() << ", " << interval.end() << "]";
	return stream;
}

// -----------------------------------------------------------------------------