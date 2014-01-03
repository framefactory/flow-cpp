// -----------------------------------------------------------------------------
//  File        UnitTest.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_UNITTEST_H
#define FLOWCORE_UNITTEST_H

#include "FlowCore/Library.h"

#include <QObject>
#include <QString>

// -----------------------------------------------------------------------------
//  Class FUnitTest
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FUnitTest : public QObject
{
	Q_OBJECT;

protected:
	struct init_t {
		init_t(FUnitTest* pTest, const QString& className, const QString& title);
	};

public:
	virtual void setup();
	virtual void shutdown();

protected:
	void check(bool expression, const QString& expressionText);

	template<typename LT, typename RT>
	void compare(const LT& left, const RT& right, const QString& leftText, const QString& rightText);

};

// Template members ------------------------------------------------------------

template<typename LT, typename RT>
void FUnitTest::compare(const LT& left,
						 const RT& right,
						 const QString& leftText,
						 const QString& rightText)
{
	check(left == right, leftText + " == " + rightText);
}

// Macros ----------------------------------------------------------------------

#define F_DECLARE_TEST private: static FUnitTest::init_t s_init;

#define F_IMPLEMENT_TEST(class, title) FUnitTest::init_t class::s_init(new class(), #class, title);

#define F_CHECK(expression) check(expression, #expression)
#define F_CHECK_MESSAGE(expression, message) check(expression, message)
#define F_COMPARE(left, right) compare(left, right, #left, #right)

// -----------------------------------------------------------------------------

#endif // FLOWCORE_UNITTEST_H