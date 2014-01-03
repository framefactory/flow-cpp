// -----------------------------------------------------------------------------
//  File        TestDateTime.h
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#include "FlowTest/UnitTests.h"
#include "FlowCore/DateTime.h"

#include <iostream>


void testDateTime()
{
	F_TRACE << std::endl;
	F_TRACE << "UNIT TEST DATE AND TIME CLASSES\n";
	F_TRACE << "-------------------------------\n\n";

	FTime t1(0.0);
	FTime t2(12, 34, 48, 539, 1000);
	FTime t3(27, 13, 14, 27, 1000);
	FTime t4(5, 69, 69, 27, 25);
	FTime t5(FTime::now());

	F_TRACE << t1 << std::endl;
	F_TRACE << t2 << std::endl;
	F_TRACE << t2.timecode(1000) << std::endl;
	F_TRACE << t3.timecode(1000) << std::endl;
	F_TRACE << t4.timecode(25) << std::endl;
	F_TRACE << L"Current time: " << t5 << std::endl;

	FDate d1 = FDate::now();
	F_TRACE << "Current date: " << d1 << std::endl;

	FDateTime dt1 = FDateTime::now();
	F_TRACE << "Current date and time: " << dt1 << std::endl;
}
