// -----------------------------------------------------------------------------
//  File        UnitTests.h
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#ifndef FLOWTEST_UNITTESTS_H
#define FLOWTEST_UNITTESTS_H

#include "FlowTest/Application.h"
#include "FlowCore/Log.h"

#ifdef F_TEST
#undef F_TEST
#endif

#define F_TEST(name, v1, v2) if (v1 == v2) F_TRACE << name << " \tPASSED\n"; \
	else F_TRACE << name << "\tFAILED: v1 = " << v1 << ", v2 = " << v2 << "\n";

void testString();
void testDateTime();
void testObject();
void testVector();
void testMatrix();
void testValueArray();

#endif // FLOWTEST_UNITTESTS_H