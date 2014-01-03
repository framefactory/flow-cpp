// -----------------------------------------------------------------------------
//  File        TestAnimation.cpp
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/08 $
// -----------------------------------------------------------------------------

#include "FlowTest/Application.h"

#include "FlowEngine/AnimationTrack.h"
#include "FlowEngine/AnimationKey.h"
#include "FlowEngine/ValueKey.h"
#include "FlowEngine/DataArray.h"

#include <boost/test/unit_test.hpp>

#ifdef FLOW_DEBUG
static void evaluateVerbose()
{
	FDataArray data(FValueType::Double, 3, 1);
	FAnimationTrack track(&data, FTrackType::Interpolate);

	FAnimationKey* pKey;

	pKey = new FAnimationKey(FTime(40.0), FTime(35.0), FTime(45.0),
		FValueArray(400.0), FValueArray(400.0), FValueArray(400.0),
		FInterpolationMode::Linear);

	track.insertKey(pKey);

	pKey = new FAnimationKey(FTime(20.0), FValueArray(200.0),
		FInterpolationMode::Linear);

	track.insertKey(pKey);

	pKey = new FAnimationKey(FTime(30.0), FTime(25.0), FTime(35.0),
		FValueArray(300.0), FValueArray(300.0), FValueArray(300.0),
		FInterpolationMode::Bezier);

	track.insertKey(pKey);

	pKey = new FAnimationKey(FTime(10.0), FValueArray(100.0),
		FInterpolationMode::Hold);

	track.insertKey(pKey);

	track.dump(F_PRINT);

	FValueArray time(FValueType::Double, 3, 1);

	F_PRINT << "\nTIME EVALUATION #1\n";

	time.as<double>(0, 0) = 10.0;
	time.as<double>(1, 0) = 15.0;
	time.as<double>(2, 0) = 20.0;

	time.dump(F_PRINT);
	track.setTime(&time);
	data.dump(F_PRINT);

	F_PRINT << "\nTIME EVALUATION #2\n";

	time.as<double>(0, 0) = 8.0;
	time.as<double>(1, 0) = 25.0;
	time.as<double>(2, 0) = 35.0;

	track.advanceTime(&time);
	time.dump(F_PRINT);
	data.dump(F_PRINT);

	F_PRINT << "\nTIME EVALUATION #3\n";

	time.as<double>(0, 0) = 12.5;
	time.as<double>(1, 0) = 35.0;
	time.as<double>(2, 0) = 45.0;

	track.advanceTime(&time);
	time.dump(F_PRINT);
	data.dump(F_PRINT);

	F_PRINT << "\nTIME EVALUATION #4 (Bezier)\n";

	time.as<double>(0, 0) = 32.0;
	time.as<double>(1, 0) = 35.0;
	time.as<double>(2, 0) = 38.0;

	track.advanceTime(&time);
	time.dump(F_PRINT);
	data.dump(F_PRINT);
}
#endif

BOOST_AUTO_TEST_CASE(testAnimation)
{
#ifdef FLOW_DEBUG
	//evaluateVerbose();
#endif
}