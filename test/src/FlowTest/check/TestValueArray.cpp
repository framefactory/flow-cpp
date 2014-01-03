// -----------------------------------------------------------------------------
//  File        TestValueArray.h
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#include "FlowTest/Application.h"
#include "FlowCore/ValueArray.h"
#include "FlowCore/Vector3T.h"

#include <boost/test/unit_test.hpp>

#ifdef FLOW_DEBUG
void evaluateVerbose()
{
	F_TRACE << "\nCreate a scalar float VA\n";
	FValueArray vaFloat(5.13f);
	F_TRACE << vaFloat.to<float>();

	F_TRACE << "\nCreate a double vector VA\n";
	FVector3d vecDouble(1.11, 2.22, 3.33);
	FValueArray vaDouble(vecDouble.ptr(), 1, 3, false);
	F_TRACE << vaDouble;

	F_TRACE << "\nCreate a scalar boolean VA\n";
	FValueArray vaBool(false);
	F_TRACE << vaBool;

	F_TRACE << "\nCreate an int16_t vector VA\n";
	int16_t int16Arr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	FValueArray vaInt16(int16Arr, 2, 4, false);
	F_TRACE << vaInt16;

	F_TRACE << "\nCreate a string vector VA\n";
	FValueArray vaString(FValueType::String, 1, 3);
	vaString.set(0, 0, string_t("Hello"));
	vaString.set(0, 1, string_t(" there, "));
	vaString.set(0, 2, string_t("world"));
	F_TRACE << vaString;

	F_TRACE << "\nCreating a referenced double vector VA\n";
	double dblArr[15];
	for (size_t i = 0; i < 15; ++i)
		dblArr[i] = double(i) * 1.01;
	FValueArray vaRefDouble(dblArr, 3, 5, true);
	F_TRACE << vaRefDouble;

	F_TRACE << "\nConvert the ref double vec to a ref int64 vec\n";
	int64_t int64Arr[15];
	FValueArray vaRefInt64(int64Arr, 3, 5, true);
	vaRefInt64.convertFrom(vaRefDouble);
	F_TRACE << vaRefInt64;

	F_TRACE << "\nConvert the ref double vec to vectors\n";
	FVector3d vecDouble1(vaRefDouble.ptr<double>(0, 0));
	FVector3d vecDouble2(vaRefDouble.ptr<double>(1, 1));
	FVector3d vecDouble3(vaRefDouble.ptr<double>(2, 2));
	F_TRACE << vecDouble1 << std::endl << vecDouble2 << std::endl << vecDouble3 << std::endl;
}
#endif

#define _F_TEST_VALUE_CONSTRUCTOR(valueType, rawType, testVal) \
{ \
	rawType v = testVal; FValueArray da(testVal); \
	BOOST_CHECK(da.type() == FValueType::valueType); \
	BOOST_CHECK(v == da.as<rawType>()); \
	BOOST_CHECK(v == da.as<rawType>(0, 0)); \
	BOOST_CHECK(v == *da.ptr<rawType>()); \
	BOOST_CHECK(v == *da.ptr<rawType>(0, 0)); \
	BOOST_CHECK(v == da.to<rawType>(0, 0)); \
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
	BOOST_CHECK(da1.type() == FValueType::valueType); \
	BOOST_CHECK(pv[2] == da1.as<rawType>(0, 2)); \
	BOOST_CHECK(pv[4] == da2.as<rawType>(1, 1)); \
	BOOST_CHECK(pv[3] == da3.as<rawType>(0, 3)); \
	BOOST_CHECK(pv[4] == da4.as<rawType>(4, 0)); \
	BOOST_CHECK(pv[0] == da5.as<rawType>(0, 0)); \
	for (FValueArray::size_type c = 0; c < 2; ++c) \
	for (FValueArray::size_type i = 0; i < 3; ++i) { \
	BOOST_CHECK(da6.as<rawType>(c, i) == da1.as<rawType>(c, i)); \
	BOOST_CHECK(da7.as<rawType>(c, i) == da6.as<rawType>(c, i)); \
	BOOST_CHECK(da8.as<rawType>(c, i) == da7.as<rawType>(c, i)); \
	BOOST_CHECK(da9.as<rawType>(c, i) == da8.as<rawType>(c, i)); \
	BOOST_CHECK(da9.as<rawType>(c, i) == da2.as<rawType>(c, i)); } \
}

static void testConstruction()
{
	_F_TEST_VALUE_CONSTRUCTOR(Float, float, 2.2f);
	_F_TEST_VALUE_CONSTRUCTOR(Double, double, 2.1234);
	_F_TEST_VALUE_CONSTRUCTOR(Bool, bool, true);
	_F_TEST_VALUE_CONSTRUCTOR(Int32, int32_t, 589342331);
	_F_TEST_VALUE_CONSTRUCTOR(String, string_t, string_t("Hello World"));
	_F_TEST_VALUE_CONSTRUCTOR(WString, wstring_t, wstring_t(L"This is a wide string"));

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
	_F_TEST_PTR_CONSTRUCTOR(String, string_t, "abc", "def", "ghi", "jkl", "mno", "pqr");
	_F_TEST_PTR_CONSTRUCTOR(WString, wstring_t, L"abc", L"def", L"ghi", L"jkl", L"mno", L"pqr");
	_F_TEST_PTR_CONSTRUCTOR(Object, FObject*, (FObject*)0x11, (FObject*)0x22, (FObject*)0x33, (FObject*)0x44, (FObject*)0x55, (FObject*)0x66);
}

#define _F_TEST_CONVERSION(valueType, rawType, v1, v2, v3, v4, v5, v6) \
{ \
	rawType pv[] = { v1, v2, v3, v4, v5, v6 }; \
	FValueArray da1(pv, 2, 3, false); \
	BOOST_CHECK(da1.channelCount() == 2); \
	BOOST_CHECK(da1.dimensionCount() == 3); \
	BOOST_CHECK(da1.as<rawType>(0, 0) == v1); \
	BOOST_CHECK(da1.as<rawType>(0, 1) == v2); \
	BOOST_CHECK(da1.as<rawType>(0, 2) == v3); \
	BOOST_CHECK(da1.as<rawType>(1, 0) == v4); \
	BOOST_CHECK(da1.as<rawType>(1, 1) == v5); \
	BOOST_CHECK(da1.as<rawType>(1, 2) == v6); \
	da1.setChannelCount(100, true); \
	BOOST_CHECK(da1.channelCount() == 100); \
	BOOST_CHECK(da1.dimensionCount() == 3); \
	for (FValueArray::size_type c = 0; c < 100; c += 2) { \
	BOOST_CHECK(da1.as<rawType>(c, 0) == v1); \
	BOOST_CHECK(da1.as<rawType>(c, 1) == v2); \
	BOOST_CHECK(da1.as<rawType>(c, 2) == v3); \
	BOOST_CHECK(da1.as<rawType>(c+1, 0) == v4); \
	BOOST_CHECK(da1.as<rawType>(c+1, 1) == v5); \
	BOOST_CHECK(da1.as<rawType>(c+1, 2) == v6); } \
	da1.setChannelCount(4, true); \
	FValueArray da2(FValueType::##valueType, 6, 7); \
	BOOST_CHECK(da2.channelCount() == 6); \
	BOOST_CHECK(da2.dimensionCount() == 7); \
	da2.setDimensionCount(3); \
	BOOST_CHECK(da2.channelCount() == 6); \
	BOOST_CHECK(da2.dimensionCount() == 3); \
	da2.convertFrom(da1); \
	for (FValueArray::size_type c = 0; c < 6; c += 2) { \
	BOOST_CHECK(da2.as<rawType>(c, 0) == v1); \
	BOOST_CHECK(da2.as<rawType>(c, 1) == v2); \
	BOOST_CHECK(da2.as<rawType>(c, 2) == v3); \
	BOOST_CHECK(da2.as<rawType>(c+1, 0) == v4); \
	BOOST_CHECK(da2.as<rawType>(c+1, 1) == v5); \
	BOOST_CHECK(da2.as<rawType>(c+1, 2) == v6); } \
}

static void testConversion()
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
	_F_TEST_CONVERSION(String, string_t, "abc", "def", "ghi", "jkl", "mno", "pqr");
	_F_TEST_CONVERSION(WString, wstring_t, L"abc", L"def", L"ghi", L"jkl", L"mno", L"pqr");
	_F_TEST_CONVERSION(Object, FObject*, (FObject*)0x11, (FObject*)0x22, (FObject*)0x33, (FObject*)0x44, (FObject*)0x55, (FObject*)0x66);

	// individual conversion tests
	double pd[] = { 0.0, 1.12345, 2.23456, 3.34567, 4.99999, 0.0 };
	FValueArray da(pd, 3, 2, false);
	BOOST_CHECK(da.to<float>(0, 1) == (float)pd[1]);
	BOOST_CHECK(da.to<bool>(2, 0) == true);
	BOOST_CHECK(da.to<bool>(2, 1) == false);
	BOOST_CHECK(da.to<int8_t>(1, 0) == 2);
	BOOST_CHECK(da.to<int64_t>(2, 0) == 4);
	BOOST_CHECK(da.to<string_t>(0, 0) == "0");
	BOOST_CHECK(da.to<wstring_t>(1, 1) == L"3.34567");

	FValueArray db(FValueType::WString, 6, 1);
	db.set<double>(0.0);
	for (FValueArray::size_type i = 1; i < 6; ++i)
		db.set<double>(12 + i, 0, pd[i]);

	for (FValueArray::size_type i = 0; i < 6; ++i)
	{
		BOOST_CHECK((db.to<string_t>(6 + i, 0)
			== auto_convert<string_t, double>(pd[i])));
	}
}

BOOST_AUTO_TEST_CASE(testValueArray)
{
#ifdef FLOW_DEBUG
	//evaluateVerbose();
#endif

	testConstruction();
	testConversion();
}
