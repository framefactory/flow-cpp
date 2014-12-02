// -----------------------------------------------------------------------------
//  File        TestManager.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#include "FlowCore/TestManager.h"
#include "FlowCore/UnitTest.h"
#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

#include <QMetaObject>
#include <QMetaMethod>

// -----------------------------------------------------------------------------
//  Class FTestManager
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FTestManager::FTestManager()
	: m_passed(0),
	  m_failed(0),
	  m_pCurrentTest(NULL)
{
}

FTestManager::~FTestManager()
{
	for (size_t i = 0; i < m_unitTests.size(); ++i) {
		delete m_unitTests[i];
	}
}

// Public commands -------------------------------------------------------------

int FTestManager::run()
{
	_clearResults();

	F_TRACE << "\n***** UNIT TESTS STARTED *****";

	bool success = true;
	for (size_t i = 0; i < m_unitTests.size(); ++i) {
		success = _runUnitTest(m_unitTests[i]) && success;
	}

	F_TRACE << "\n***** UNIT TESTS COMPLETED *****";
	F_TRACE << "\nPassed: " << m_passed << ", Failed: " << m_failed << "\n";

	_clearResults();
	return success ? 0 : 1;
}

void FTestManager::registerTest(FUnitTest* pTest,
								const QString& className,
								const QString& title)
{
	FTestManager::unitTest_t* pUnitTest = new unitTest_t(pTest, className, title);
	m_unitTests.push_back(pUnitTest);
}

void FTestManager::reportTest(bool result,
							  const QString& expression)
{
	result_t* pResult = new result_t(m_pCurrentTest, result, expression);
	m_results.push_back(pResult);

	if (result) {
		m_passed++;
		F_TRACE << "    PASSED: " << expression;
	}
	else {
		m_failed++;
		F_TRACE << "*** FAILED: " << expression;
	}
}

// Internal functions ----------------------------------------------------------

bool FTestManager::_runUnitTest(FTestManager::unitTest_t* pUnitTest)
{
	m_pCurrentTest = pUnitTest;
	const QMetaObject* pMeta = pUnitTest->pTest->metaObject();

	F_TRACE << "\nRUNNING TESTS FOR " << pUnitTest->className << " (" << pUnitTest->title << ")";
	pUnitTest->pTest->setup();

	quint32 failedOffset = m_failed;

	for (int i = pMeta->methodOffset(); i < pMeta->methodCount(); ++i) {
		QMetaMethod method = pMeta->method(i);
		method.invoke(pUnitTest->pTest);
	}

	pUnitTest->pTest->shutdown();
	return m_failed == failedOffset;
}

void FTestManager::_clearResults()
{
	for (size_t i = 0; i < m_results.size(); ++i) {
		delete m_results[i];
	}

	m_results.clear();

	m_passed = 0;
	m_failed = 0;
	m_pCurrentTest = NULL;
}

// -----------------------------------------------------------------------------