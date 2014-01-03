// -----------------------------------------------------------------------------
//  File        Date.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_DATE_H
#define FLOWCORE_DATE_H

#include "FlowCore/Library.h"
#include <ostream>

// -----------------------------------------------------------------------------
//  Class FDate
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FDate
{
	//  Static members -----------------------------------------------
	
public:
	static FDate now();

	//  Constructors and destructor ----------------------------------

	FDate();
	FDate(int year, int month, int day);

	//  Public commands ----------------------------------------------

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);

	//  Public queries -----------------------------------------------

	int year() const;
	int month() const;
	int day() const;

	//  Operators ----------------------------------------------------

	/// Formats a date according to the current locale and outputs it to the given stream.
	friend std::wostream& operator<<(std::wostream& stream, const FDate& date);

	//  Internal data members ----------------------------------------

private:
	int m_year;
	int m_month;
	int m_day;
};

// -----------------------------------------------------------------------------

#endif // FLOWCORE_DATE_H