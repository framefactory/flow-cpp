// -----------------------------------------------------------------------------
//  File        Date.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#include "FlowCore/Date.h"

#include <boost/locale.hpp>
#include <boost/format.hpp>
#include <ctime>

// -----------------------------------------------------------------------------
//  Class FDate
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

FDate FDate::now()
{
	time_t rawTime = time(NULL);
	tm timeInfo;

#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
	localtime_s(&timeInfo, &rawTime);
#else
	tm* pTI = localtime(&rawTime);
	timeInfo = *pTI;
#endif
	
	FDate result;
	result.m_year = timeInfo.tm_year;
	result.m_month = timeInfo.tm_mon;
	result.m_day = timeInfo.tm_mday;
	return result;
}

// Constructors and destructor -------------------------------------------------

FDate::FDate()
: m_year(0),
  m_month(0),
  m_day(0)
{
}

FDate::FDate(int year, int month, int day)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

// Public commands -------------------------------------------------------------

void FDate::setYear(int year)
{
	m_year = year - 1900;
}

void FDate::setMonth(int month)
{
	m_month = month - 1;
}

void FDate::setDay(int day)
{
	m_day = day;
}

// Public queries --------------------------------------------------------------

int FDate::year() const
{
	return m_year + 1900;
}

int FDate::month() const
{
	return m_month + 1;
}

int FDate::day() const
{
	return m_day;
}

// -----------------------------------------------------------------------------

std::wostream& operator<<(std::wostream& stream, const FDate& date)
{
	tm timeInfo;
	memset(&timeInfo, 0, sizeof(timeInfo));
	timeInfo.tm_year = date.m_year;
	timeInfo.tm_mon = date.m_month;
	timeInfo.tm_mday = date.m_day;

	std::locale loc = stream.imbue(std::locale());
	time_t rawTime = mktime(&timeInfo);
	stream << boost::io::group(boost::locale::as::date, rawTime);
	stream.imbue(loc);
	return stream;
}

// -----------------------------------------------------------------------------
