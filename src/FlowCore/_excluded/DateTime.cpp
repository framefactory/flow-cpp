// -----------------------------------------------------------------------------
//  File        DateTime.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/18 $
// -----------------------------------------------------------------------------

#include "FlowCore/DateTime.h"
#include <sstream>

// -----------------------------------------------------------------------------
//  Class FDateTime
// -----------------------------------------------------------------------------

FDateTime FDateTime::now()
{
	return FDateTime(FDate::now(), FTime::now());
}

// Constructors and destructor -------------------------------------------------

FDateTime::FDateTime()
: m_time(0.0)
{
}

FDateTime::FDateTime(const FDate& date, const FTime& time)
: m_date(date),
  m_time(time)
{
}

FDateTime::FDateTime(int day, int month, int year,
                     int hour, int minute, int second)
: m_date(day, month, year),
  m_time(hour, minute, second)
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

// -----------------------------------------------------------------------------

std::wostream& operator<<(std::wostream& stream, const FDateTime& dateTime)
{
	std::wostringstream oss;
	oss << dateTime.date() << " " << dateTime.time();
	stream << oss.str();
	return stream;
}
// -----------------------------------------------------------------------------