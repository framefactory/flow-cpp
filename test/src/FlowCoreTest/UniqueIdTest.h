// -----------------------------------------------------------------------------
//  File        UniqueIdTest.h
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORETEST_UNIQUEIDTEST_H
#define FLOWCORETEST_UNIQUEIDTEST_H

#include "FlowCore/UnitTest.h"
#include <QString>

// -----------------------------------------------------------------------------
//  Class FUniqueIdTest
// -----------------------------------------------------------------------------

class  FUniqueIdTest : public FUnitTest
{
	Q_OBJECT;
	F_DECLARE_TEST;

public:
	virtual void setup();
	virtual void shutdown();

public slots:
	void test();
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORETEST_UNIQUEIDTEST_H