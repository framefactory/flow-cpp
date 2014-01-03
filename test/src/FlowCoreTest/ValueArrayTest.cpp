// -----------------------------------------------------------------------------
//  File        ValueArrayTest.cpp
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#include "FlowCoreTest/ValueArrayTest.h"

#include "FlowCore/ValueArray.h"
#include "FlowCore/Vector3T.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FValueArrayTest
// -----------------------------------------------------------------------------

F_IMPLEMENT_TEST(FValueArrayTest, "Class FValueArray");

// Initialization --------------------------------------------------------------

void FValueArrayTest::setup()
{
}

void FValueArrayTest::shutdown()
{
}

// Tests -----------------------------------------------------------------------

void FValueArrayTest::evaluateVerbose()
{
	F_TRACE << "\nCreate a scalar float VA\n";
	FValueArray vaFloat(5.13f);
	F_TRACE << vaFloat.to<float>();

	F_TRACE << "\nCreate a double vector VA\n";
	FVector3d vecDouble(1.11, 2.22, 3.33);
	FValueArray vaDouble(vecDouble.ptr(), 1, 3, false);
	F_TRACE << vaDouble.dump();

	F_TRACE << "\nCreate a scalar boolean VA\n";
	FValueArray vaBool(false);
	F_TRACE << vaBool.dump();

	F_TRACE << "\nCreate an int16_t vector VA\n";
	int16_t int16Arr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	FValueArray vaInt16(int16Arr, 2, 4, false);
	F_TRACE << vaInt16.dump();

	F_TRACE << "\nCreate a string vector VA\n";
	FValueArray vaString(FValueType::String, 1, 3);
	vaString.set<QString>(0, 0, "Hello");
	vaString.set<QString>(0, 1, " there, ");
	vaString.set<QString>(0, 2, "world");
	F_TRACE << vaString.dump();

	F_TRACE << "\nCreating a referenced double vector VA\n";
	double dblArr[15];
	for (size_t i = 0; i < 15; ++i)
		dblArr[i] = double(i) * 1.01;
	FValueArray vaRefDouble(dblArr, 3, 5, true);
	F_TRACE << vaRefDouble.dump();

	F_TRACE << "\nConvert the ref double vec to a ref int64 vec\n";
	int64_t int64Arr[15];
	FValueArray vaRefInt64(int64Arr, 3, 5, true);
	vaRefInt64.convertFrom(vaRefDouble);
	F_TRACE << vaRefInt64.dump();

	F_TRACE << "\nConvert the ref double vec to vectors\n";
	FVector3d vecDouble1(vaRefDouble.ptr<double>(0, 0));
	FVector3d vecDouble2(vaRefDouble.ptr<double>(1, 1));
	FVector3d vecDouble3(vaRefDouble.ptr<double>(2, 2));
	F_TRACE << vecDouble1.toString() << "\n"
		<< vecDouble2.toString() << "\n"
		<< vecDouble3.toString() << "\n";
}

#define _F_TEST_VALUE_CONSTRUCTOR(valueType, rawType, testVal) \
{ \
	rawType v = testVal; FValueArray da(testVal); \
	F_CHECK(da.type() == FValueType::valueType); \
	F_CHECK(v == da.as<rawType>()); \
	F_CHECK(v == da.as<rawType>(0, 0)); \
	F_CHECK(v == *da.ptr<rawType>()); \
	F_CHECK(v == *da.ptr<rawType>(0, 0)); \
	F_CHECK(v == da.to<rawType>(0, 0)); \
}

#define _F_TEST_PTR_CONSTRUCTOR(valueType, rawType, v1, v2, v3, v4, v5, v6) \
{ \
	rawType pv[] = { v1, v2, v3, v4, v5, v6 }; \
	FValueArray da1(pv, 2, 3, false); \
	FValueArray da2(pv, 2, 3, true); \
	FValueArray da3(pv, 1, 6, false); \
	FValueArray da4(pv, 6, 1, false); \
	FValueArray da5(pv, 1, 1, false); \
	FValueArray da6(da1); \
	FValueArray da7 = da1; \
	FValueArray da8(da2); \
	FValueArray da9 = da2; \
	F_CHECK(da1.type() == FValueType::valueType); \
	F_CHECK(pv[2] == da1.as<rawType>(0, 2)); \
	F_CHECK(pv[4] == da2.as<rawType>(1, 1)); \
	F_CHECK(pv[3] == da3.as<rawType>(0, 3)); \
	F_CHECK(pv[4] == da4.as<rawType>(4, 0)); \
	F_CHECK(pv[0] == da5.as<rawType>(0, 0)); \
	for (FValueArray::size_type c = 0; c < 2; ++c) \
	for (FValueArray::size_type i = 0; i < 3; ++i) { \
	F_CHECK(da6.as<rawType>(c, i) == da1.as<rawType>(c, i)); \
	F_CHECK(da7.as<rawType>(c, i) == da6.as<rawType>(c, i)); \
	F_CHECK(da8.as<rawType>(c, i) == da7.as<rawType>(c, i)); \
	F_CHECK(da9.as<rawType>(c, i) == da8.as<rawType>(c, i)); \
	F_CHECK(da9.as<rawType>(c, i) == da2.as<rawType>(c, i)); } \
}

void FValueArrayTest::testConstruction()
{
	_F_TEST_VALUE_CONSTRUCTOR(Float, float, 2.2f);
	_F_TEST_VALUE_CONSTRUCTOR(Double, double, 2.1234);
	_F_TEST_VALUE_CONSTRUCTOR(Bool, bool, true);
	_F_TEST_VALUE_CONSTRUCTOR(Int32, int32_t, 589342331);
	_F_TEST_VALUE_CONSTRUCTOR(String, QString, QString("Hello World"));

	_F_TEST_PTR_CONSTRUCTOR(Float, float, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
	_F_TEST_PTR_CONSTRUCTOR(Double, double, 1.11, 2.22, 3.33, 4.44, 5.55, 6.66);
	_F_TEST_PTR_CONSTRUCTOR(Bool, bool, false, false, true, true, false, true);
	_F_TEST_PTR_CONSTRUCTOR(Int8, int8_t, -11, -22, -33, -44, -55, -66);
	_F_TEST_PTR_CONSTRUCTOR(UInt8, uint8_t, 11, 22, 33, 44, 55, 66);
	_F_TEST_PTR_CONSTRUCTOR(Int16, int16_t, -1111, -2222, -3333, -4444, -5555, -6666);
	_F_TEST_PTR_CONSTRUCTOR(UInt16, uint16_t, 1111, 2222, 3333, 4444, 5555, 6666);
	_F_TEST_PTR_CONSTRUCTOR(Int32, int32_t, -1010, -2020, -3030, -4040, -5050, -6060);
	_F_TEST_PTR_CONSTRUCTOR(UInt32, uint32_t, 1010, 2020, 3030, 4040, 5050, 6060);
	_F_TEST_PTR_CONSTRUCTOR(Int64, int64_t, -10101, -20202, -30303, -40404, -50505, -60606);
	_F_TEST_PTR_CONSTRUCTOR(UInt64, uint64_t, 10101, 20202, 30303, 40404, 50505, 60606);
	_F_TEST_PTR_CONSTRUCTOR(String, QString, QString("abc"), QString("def"), QString("ghi"), QString("jkl"), QString("mno"), QString("pqr"));
	_F_TEST_PTR_CONSTRUCTOR(Object, FObject*, (FObject*)0x11, (FObject*)0x22, (FObject*)0x33, (FObject*)0x44, (FObject*)0x55, (FObject*)0x66);
}

#define _F_TEST_CONVERSION(valueType, rawType, v1, v2, v3, v4, v5, v6) \
{ \
	rawType pv[] = { v1, v2, v3, v4, v5, v6 }; \
	FValueArray da1(pv, 2, 3, false); \
	F_CHECK(da1.channelCount() == 2); \
	F_CHECK(da1.dimensionCount() == 3); \
	F_CHECK(da1.as<rawType>(0, 0) == v1); \
	F_CHECK(da1.as<rawType>(0, 1) == v2); \
	F_CHECK(da1.as<rawType>(0, 2) == v3); \
	F_CHECK(da1.as<rawType>(1, 0) == v4); \
	F_CHECK(da1.as<rawType>(1, 1) == v5); \
	F_CHECK(da1.as<rawType>(1, 2) == v6); \
	da1.setChannelCount(100, true); \
	F_CHECK(da1.channelCount() == 100); \
	F_CHECK(da1.dimensionCount() == 3); \
	for (FValueArray::size_type c = 0; c < 100; c += 2) { \
	F_CHECK(da1.as<rawType>(c, 0) == v1); \
	F_CHECK(da1.as<rawType>(c, 1) == v2); \
	F_CHECK(da1.as<rawType>(c, 2) == v3); \
	F_CHECK(da1.as<rawType>(c+1, 0) == v4); \
	F_CHECK(da1.as<rawType>(c+1, 1) == v5); \
	F_CHECK(da1.as<rawType>(c+1, 2) == v6); } \
	da1.setChannelCount(4, true); \
	FValueArray da2(FValueType::##valueType, 6, 7); \
	F_CHECK(da2.channelCount() == 6); \
	F_CHECK(da2.dimensionCount() == 7); \
	da2.setDimensionCount(3); \
	F_CHECK(da2.channelCount() == 6); \
	F_CHECK(da2.dimensionCount() == 3); \
	da2.convertFrom(da1); \
	for (FValueArray::size_type c = 0; c < 6; c += 2) { \
	F_CHECK(da2.as<rawType>(c, 0) == v1); \
	F_CHECK(da2.as<rawType>(c, 1) == v2); \
	F_CHECK(da2.as<rawType>(c, 2) == v3); \
	F_CHECK(da2.as<rawType>(c+1, 0) == v4); \
	F_CHECK(da2.as<rawType>(c+1, 1) == v5); \
	F_CHECK(da2.as<rawType>(c+1, 2) == v6); } \
}

void FValueArrayTest::testConversion()
{
	_F_TEST_CONVERSION(Float, float, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
	_F_TEST_CONVERSION(Double, double, 1.11, 2.22, 3.33, 4.44, 5.55, 6.66);
	_F_TEST_CONVERSION(Bool, bool, false, false, true, true, false, true);
	_F_TEST_CONVERSION(Int8, int8_t, -11, -22, -33, -44, -55, -66);
	_F_TEST_CONVERSION(UInt8, uint8_t, 11, 22, 33, 44, 55, 66);
	_F_TEST_CONVERSION(Int16, int16_t, -1111, -2222, -3333, -4444, -5555, -6666);
	_F_TEST_CONVERSION(UInt16, uint16_t, 1111, 2222, 3333, 4444, 5555, 6666);
	_F_TEST_CONVERSION(Int32, int32_t, -1010, -2020, -3030, -4040, -5050, -6060);
	_F_TEST_CONVERSION(UInt32, uint32_t, 1010, 2020, 3030, 4040, 5050, 6060);
	_F_TEST_CONVERSION(Int64, int64_t, -10101, -20202, -30303, -40404, -50505, -60606);
	_F_TEST_CONVERSION(UInt64, uint64_t, 10101, 20202, 30303, 40404, 50505, 60606);
	_F_TEST_CONVERSION(String, QString, "abc", "def", "ghi", "jkl", "mno", "pqr");
	_F_TEST_CONVERSION(Object, FObject*, (FObject*)0x11, (FObject*)0x22, (FObject*)0x33, (FObject*)0x44, (FObject*)0x55, (FObject*)0x66);

	// individual conversion tests
	double pd[] = { 0.0, 1.12345, 2.23456, 3.34567, 4.99999, 0.0 };
	FValueArray da(pd, 3, 2, false);
	F_CHECK(da.to<float>(0, 1) == (float)pd[1]);
	F_CHECK(da.to<bool>(2, 0) == true);
	F_CHECK(da.to<bool>(2, 1) == false);
	F_CHECK(da.to<int8_t>(1, 0) == 2);
	F_CHECK(da.to<int64_t>(2, 0) == 4);
	F_CHECK(da.to<QString>(0, 0) == "0");
	F_CHECK(da.to<QString>(1, 1) == "3.34567");

	FValueArray db(FValueType::String, 6, 1);
	db.set<double>(0.0);
	for (FValueArray::size_type i = 1; i < 6; ++i)
		db.set<double>(12 + i, 0, pd[i]);

	for (FValueArray::size_type i = 0; i < 6; ++i)
	{
		F_CHECK((db.to<QString>(6 + i, 0)
			== auto_convert<QString, double>(pd[i])));
	}
}

// -----------------------------------------------------------------------------