// -----------------------------------------------------------------------------
//  File        VectorTest.cpp
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#include "FlowCoreTest/VectorTest.h"

#include "FlowCore/Vector2T.h"
#include "FlowCore/Vector3T.h"
#include "FlowCore/Vector4T.h"
#include "FlowCore/FastVec.h"

// -----------------------------------------------------------------------------
//  Class FVectorTest
// -----------------------------------------------------------------------------

F_IMPLEMENT_TEST(FVectorTest, "Class FVector");

// Initialization --------------------------------------------------------------

void FVectorTest::setup()
{
}

void FVectorTest::shutdown()
{
}

// Tests -----------------------------------------------------------------------

void FVectorTest::testVector()
{
	FVector4f v3(-1.0f, -2.0f, -3.0f, -4.0f);
	FVector4f v2 = -v3;
	FVector4f v1; v1.set(3.5f, 5.5f, 7.5f, 9.5f);
	float s = 10.0f;

	FVector4f cSum(4.5f, 7.5f, 10.5f, 13.5f);
	FVector4f cDif(2.5f, 3.5f, 4.5f, 5.5f);
	FVector4f t;

	FFastVec4f fv3(v3);
	FFastVec4f fv2 = -fv3;
	FFastVec4f fv1; fv1.set(v1);
	FFastVec4f ft;

	t = v1 + v2; ft = fv1 + fv2;
	F_CHECK_MESSAGE(t == cSum, "Addition v1 + v2");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Addition v1 + v2, Fast version");
	t = v1; t += v2; ft = fv1; ft += fv2;
	F_CHECK_MESSAGE(t == cSum, "Addition v1 += v2");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Addition v1 += v2, Fast version");
	t = v1 + s; ft = fv1 + s;
	F_CHECK_MESSAGE(t == FVector4f(13.5f, 15.5f, 17.5f, 19.5f), "Addition v1 + s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Addition v1 + s, Fast version");
	t = v1; t += s; ft = fv1; ft += s;
	F_CHECK_MESSAGE(t == FVector4f(13.5f, 15.5f, 17.5f, 19.5f), "Addition v1 += s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Addition v1 += s, Fast version");

	t = v1 - v2; ft = fv1 - fv2;
	F_CHECK_MESSAGE(t == cDif, "Subtraction v1 - v2");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Subtraction v1 - v2, Fast version");
	t = v1; t -= v2; ft = fv1; ft -= fv2;
	F_CHECK_MESSAGE(t == cDif, "Subtraction v1 -= v2");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Subtraction v1 -= v2, Fast version");
	t = v2 - s; ft = fv2 - s;
	F_CHECK_MESSAGE(t == FVector4f(-9.0f, -8.0f, -7.0f, -6.0f), "Subtraction v2 - s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Subtraction v2 - s, Fast version");
	t = v2; t -= s; ft = fv2; ft -= s;
	F_CHECK_MESSAGE(t == FVector4f(-9.0f, -8.0f, -7.0f, -6.0f), "Subtraction v2 -= s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Subtraction v2 -= s, Fast version");

	t = v1 * s; ft = fv1 * s;
	F_CHECK_MESSAGE(t == FVector4f(35.0f, 55.0f, 75.0f, 95.0f), "Multiplication v1 * s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Multiplication v1 * s, Fast version");
	t = v1; t *= s; ft = fv1; ft *=s;
	F_CHECK_MESSAGE(t == FVector4f(35.0f, 55.0f, 75.0f, 95.0f), "Multiplication v1 *= s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Multiplication v1 *= s, Fast version");

	t = v1 / s; ft = fv1 / s;
	F_CHECK_MESSAGE(t == FVector4f(.35f, .55f, .75f, .95f), "Division v1 / s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Division v1 / s, Fast version");
	t = v1; t /= s; ft = fv1; ft /= s;
	F_CHECK_MESSAGE(t == FVector4f(.35f, .55f, .75f, .95f), "Division v1 /= s");
	F_CHECK_MESSAGE(t == FVector4f(ft), "Division v1 /= s, Fast version");

	float t1 = v1 * v2; float ft1 = fv1 * fv2;
	F_CHECK_MESSAGE(t1 == 75.0f, "Dot product v1 * v2");
	F_CHECK_MESSAGE(t1 == ft1, "Dot product v1 * v2, Fast version");
	t1 = v2 * v1; ft1 = fv2 * fv1;
	F_CHECK_MESSAGE(t1 == 75.0f, "Dot product v2 * v1");
	F_CHECK_MESSAGE(t1 == ft1, "Dot product v2 * v1, Fast version");
	t1 = v1.dot(v2); ft1 = fv1.dot(fv2);
	F_CHECK_MESSAGE(t1 == 75.0f, "Dot product v1.dot(v2)");
	F_CHECK_MESSAGE(t1 == ft1, "Dot product v1.dot(v2), Fast version");
	t1 = fDot(v2, v1); ft1 = fDot(fv2, fv1);
	F_CHECK_MESSAGE(t1 == 75.0f, "Dot product fDot(v2, v1)");
	F_CHECK_MESSAGE(t1 == ft1, "Dot product fDot(v2, v1), Fast version");
}

// -----------------------------------------------------------------------------