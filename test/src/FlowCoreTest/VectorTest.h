// -----------------------------------------------------------------------------
//  File        VectorTest.h
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORETEST_VECTORTEST_H
#define FLOWCORETEST_VECTORTEST_H

#include "FlowCore/UnitTest.h"

// -----------------------------------------------------------------------------
//  Class FVectorTest
// -----------------------------------------------------------------------------

class FVectorTest : public FUnitTest
{
	Q_OBJECT;
	F_DECLARE_TEST;

	//  Public commands ----------------------------------------------

public:
	virtual void setup();
	virtual void shutdown();

public slots:
	void testVector();

};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORETEST_VECTORTEST_H