// -----------------------------------------------------------------------------
//  File        TestManager.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TESTMANAGER_H
#define FLOWCORE_TESTMANAGER_H

#include "FlowCore/Library.h"
#include "FlowCore/SingletonT.h"

#include <QString>
#include <vector>

class FUnitTest;

// -----------------------------------------------------------------------------
//  Class FTestManager
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FTestManager : public FSingletonAutoT<FTestManager>
{
	friend class FSingletonAutoT<FTestManager>;
	friend class FUnitTest;

private:
	struct unitTest_t
	{
		unitTest_t(FUnitTest* aTest, const QString& aClassName, const QString& aTitle)
			: pTest(aTest), className(aClassName), title(aTitle) { }

		FUnitTest* pTest;
		QString className;
		QString title;
	};

	struct result_t
	{
		result_t(unitTest_t* aTest, bool aResult, const QString& anExpression)
			: pTest(aTest), result(aResult), expression(anExpression) { }

		unitTest_t* pTest;
		bool result;
		QString expression;

	};

	//  Constructors and destructor ----------------------------------

protected:
	FTestManager();
	virtual ~FTestManager();

	//  Public commands ----------------------------------------------

public:
	int run();

protected:
	void registerTest(FUnitTest* pTest, const QString& className, const QString& title);
	void reportTest(bool result, const QString& expression);

	//  Internal functions -------------------------------------------

private:
	bool _runUnitTest(unitTest_t* pTest);
	void _clearResults();

	//  Internal data members ----------------------------------------

private:
	typedef std::vector<unitTest_t*> testVec_t;
	testVec_t m_unitTests;

	typedef std::vector<result_t*> resultVec_t;
	resultVec_t m_results;

	uint32_t m_passed;
	uint32_t m_failed;

	unitTest_t* m_pCurrentTest;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_TESTMANAGER_H