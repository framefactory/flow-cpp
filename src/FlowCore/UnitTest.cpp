// -----------------------------------------------------------------------------
//  File        UnitTest.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#include "FlowCore/UnitTest.h"
#include "FlowCore/TestManager.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FUnitTest
// -----------------------------------------------------------------------------

// Inner Class init_t ----------------------------------------------------------

FUnitTest::init_t::init_t(FUnitTest* pTest,
						  const QString& className,
						  const QString& title)
{
	FTestManager::instance()->registerTest(pTest, className, title);
}

// Constructors and destructor -------------------------------------------------

// Protected commands ----------------------------------------------------------

void FUnitTest::setup()
{
}

void FUnitTest::shutdown()
{
}

void FUnitTest::check(bool expression, const QString& expressionText)
{
	FTestManager::instance()->reportTest(expression, expressionText);
}

// -----------------------------------------------------------------------------