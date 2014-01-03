// -----------------------------------------------------------------------------
//  File        ObjectTest.h
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORETEST_OBJECTTEST_H
#define FLOWCORETEST_OBJECTTEST_H

#include "FlowCore/UnitTest.h"

// -----------------------------------------------------------------------------
//  Class FObjectTest
// -----------------------------------------------------------------------------

class FObjectTest : public FUnitTest
{
	Q_OBJECT;
	F_DECLARE_TEST;

	//  Public commands ----------------------------------------------

public:
	virtual void setup();
	virtual void shutdown();

public slots:
	void test1();
	void test2();

	//  Internal data members ----------------------------------------

private:

};
	
// -----------------------------------------------------------------------------


#endif // FLOWCORETEST_OBJECTTEST_H