// -----------------------------------------------------------------------------
//  File        DateTime.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_DATETIME_H
#define FLOWCORE_DATETIME_H

#include "FlowCore/Library.h"
#include "FlowCore/Date.h"
#include "FlowCore/Time.h"

#include <ostream>

// -----------------------------------------------------------------------------
//  Class FDateTime
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FDateTime
{
	//  Static members -----------------------------------------------

public:
	/// Returns the current local date and time.
	static FDateTime now();

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a date/time object with date and time set to zero.
	FDateTime();
	/// Creates a date/time object from the given date and time.
	FDateTime(const FDate& date, const FTime& time);
	/// Creates a date/time object from the given data.
	FDateTime(int day, int month, int year, int hour, int minute, int second);

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	const FDate& date() const { return m_date; }
	const FTime& time() const { return m_time; }

	int day() const { return m_date.day(); }
	int month() const { return m_date.month(); }
	int year() const { return m_date.year(); }

	int hour() const { return m_time.hour(); }
	int minute() const { return m_time.minute(); }
	int second() const { return m_time.second(); }

	//  Internal data members ----------------------------------------

private:
	FDate m_date;
	FTime m_time;
};

// -----------------------------------------------------------------------------

/// Formats a date/time according to the current locale and
/// outputs it to the given stream.
std::wostream& operator<<(std::wostream& stream, const FDateTime& dateTime);

// -----------------------------------------------------------------------------

#endif // FLOWCORE_DATETIME_H