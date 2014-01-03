// -----------------------------------------------------------------------------
//  File        TestDataArray.cpp
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/13 $
// -----------------------------------------------------------------------------

#include "FlowTest/Application.h"
#include "FlowEngine/DataArray.h"

#include <boost/test/unit_test.hpp>


static void evaluateVerbose()
{

}

static void testCounter()
{
	FDataArray da1(FValueType::Float, 2, 2);

	BOOST_CHECK(da1.hasChanged() == true);
	BOOST_CHECK(da1.hasChanged(0) == true);
	BOOST_CHECK(da1.hasChanged(1) == true);

	da1.clearChanged();

	BOOST_CHECK(da1.fireCount() == 0);
	BOOST_CHECK(da1.fireCount(1) == 0);

	da1.fire(3);
	BOOST_CHECK(da1.fireCount() == 6);
	BOOST_CHECK(da1.fireCount(1) == 3);

	da1.fire(1, 7);
	BOOST_CHECK(da1.fireCount() == 13);
	BOOST_CHECK(da1.fireCount(0) == 3);
	BOOST_CHECK(da1.fireCount(1) == 10);

	BOOST_CHECK(da1.hasChanged() == false);
	BOOST_CHECK(da1.hasChanged(0) == false);
	BOOST_CHECK(da1.hasChanged(1) == false);

	da1.setChanged(0);
	BOOST_CHECK(da1.hasChanged() == true);
	BOOST_CHECK(da1.hasChanged(0) == true);

	FDataArray da2(da1);

	BOOST_CHECK(da2.hasChanged() == true);
	BOOST_CHECK(da2.hasChanged(0) == true);
	BOOST_CHECK(da2.hasChanged(1) == false);

	FDataArray da3(FValueType::String, 2, 2);
	da3.clearChanged();
	da3.convertFrom(da2);

	BOOST_CHECK(da3.hasChanged() == true);
	BOOST_CHECK(da3.hasChanged(0) == true);
	BOOST_CHECK(da3.hasChanged(1) == true);

	BOOST_CHECK(da3.fireCount() == 13);
	BOOST_CHECK(da3.fireCount(0) == 3);
	BOOST_CHECK(da3.fireCount(1) == 10);
}

#define _F_TEST_VALUE_CONSTRUCTOR(valueType, rawType, testVal) \
{ \
	rawType v = testVal; FDataArray da(testVal); \
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
	FDataArray da1(pv, 2, 3, false); \
	FDataArray da2(pv, 2, 3, true); \
	FDataArray da3(pv, 1, 6, false); \
	FDataArray da4(pv, 6, 1, false); \
	FDataArray da5(pv, 1, 1, false); \
	FDataArray da6(da1); \
	FDataArray da7 = da1; \
	FDataArray da8(da2); \
	FDataArray da9 = da2; \
	BOOST_CHECK(da1.type() == FValueType::valueType); \
	BOOST_CHECK(pv[2] == da1.as<rawType>(0, 2)); \
	BOOST_CHECK(pv[4] == da2.as<rawType>(1, 1)); \
	BOOST_CHECK(pv[3] == da3.as<rawType>(0, 3)); \
	BOOST_CHECK(pv[4] == da4.as<rawType>(4, 0)); \
	BOOST_CHECK(pv[0] == da5.as<rawType>(0, 0)); \
	for (FDataArray::size_type c = 0; c < 2; ++c) \
	for (FDataArray::size_type i = 0; i < 3; ++i) { \
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
	FDataArray da1(pv, 2, 3, false); \
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
	for (FDataArray::size_type c = 0; c < 100; c += 2) { \
	BOOST_CHECK(da1.as<rawType>(c, 0) == v1); \
	BOOST_CHECK(da1.as<rawType>(c, 1) == v2); \
	BOOST_CHECK(da1.as<rawType>(c, 2) == v3); \
	BOOST_CHECK(da1.as<rawType>(c+1, 0) == v4); \
	BOOST_CHECK(da1.as<rawType>(c+1, 1) == v5); \
	BOOST_CHECK(da1.as<rawType>(c+1, 2) == v6); } \
	da1.setChannelCount(4, true); \
	FDataArray da2(FValueType::##valueType, 6, 7); \
	BOOST_CHECK(da2.channelCount() == 6); \
	BOOST_CHECK(da2.dimensionCount() == 7); \
	da2.setDimensionCount(3); \
	BOOST_CHECK(da2.channelCount() == 6); \
	BOOST_CHECK(da2.dimensionCount() == 3); \
	da2.convertFrom(da1); \
	for (FDataArray::size_type c = 0; c < 6; c += 2) { \
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
	FDataArray da(pd, 3, 2, false);
	BOOST_CHECK(da.to<float>(0, 1) == (float)pd[1]);
	BOOST_CHECK(da.to<bool>(2, 0) == true);
	BOOST_CHECK(da.to<bool>(2, 1) == false);
	BOOST_CHECK(da.to<int8_t>(1, 0) == 2);
	BOOST_CHECK(da.to<int64_t>(2, 0) == 4);
	BOOST_CHECK(da.to<string_t>(0, 0) == "0");
	BOOST_CHECK(da.to<wstring_t>(1, 1) == L"3.34567");

	FDataArray db(FValueType::WString, 6, 1);
	db.set<double>(0.0);
	for (uint32_t i = 1; i < 6; ++i)
		db.set<double>(12 + i, 0, pd[i]);

	for (uint32_t i = 0; i < 6; ++i)
	{
		BOOST_CHECK((db.to<string_t>(6 + i, 0)
			== auto_convert<string_t, double>(pd[i])));
	}
}

BOOST_AUTO_TEST_CASE(testDataArray)
{
	testCounter();
	testConstruction();
	testConversion();
}