// -----------------------------------------------------------------------------
//  File        ValueArrayTest.h
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORETEST_VALUEARRAYTEST_H
#define FLOWCORETEST_VALUEARRAYTEST_H

#include "FlowCore/UnitTest.h"

// -----------------------------------------------------------------------------
//  Class FValueArrayTest
// -----------------------------------------------------------------------------

class FValueArrayTest : public FUnitTest
{
	Q_OBJECT;
	F_DECLARE_TEST;

public:
	virtual void setup();
	virtual void shutdown();

	public slots:
		void evaluateVerbose();
		void testConstruction();
		void testConversion();
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORETEST_VALUEARRAYTEST_H