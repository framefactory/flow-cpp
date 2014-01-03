// -----------------------------------------------------------------------------
//  File        TestObject.h
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/Object.h"
#include "FlowCore/Archive.h"
#include "FlowCore/String.h"
#include "FlowCore/Math.h"

#include <boost/test/unit_test.hpp>

#include <fstream>

// -----------------------------------------------------------------------------
//  Class FSerializableTestObject
// -----------------------------------------------------------------------------

class  FSerializableTestObject : public FObject
{
	F_DECLARE_SERIALIZABLE_CUSTOM_DC(FSerializableTestObject);

public:
	FSerializableTestObject();
	virtual ~FSerializableTestObject() { }

	virtual void serialize(FArchive& ar);

	bool         m_valBool;
	int8_t       m_valInt8;
	uint8_t      m_valUInt8;
	int16_t      m_valInt16;
	uint16_t     m_valUInt16;
	int32_t      m_valInt32;
	uint32_t     m_valUInt32;
	int64_t      m_valInt64;
	uint64_t     m_valUInt64;
	float        m_valFloat;
	double       m_valDouble;
	string_t     m_valString;
	wstring_t    m_valWString;

	FSerializableTestObject* m_pTestObject1;
	FSerializableTestObject* m_pTestObject2;
};

F_IMPLEMENT_SERIALIZABLE(FSerializableTestObject, FObject, 1);

FSerializableTestObject::FSerializableTestObject()
{
	m_valBool = true;
	m_valInt8 = 0x12;
	m_valUInt8 = 0xF2;
	m_valInt16 = 0x1234;
	m_valUInt16 = 0xF234;
	m_valInt32 = 0x71234567;
	m_valUInt32 = 0xF1234567;
	m_valInt64 = 0x7000000001234567;
	m_valUInt64 = 0xF000000001234567;
	m_valFloat = (float)FMath::pi;
	m_valDouble = FMath::e;
	m_valString = "This is an ANSI string.";
	m_valWString = L"This is a unicode string.";

	m_pTestObject1 = NULL;
	m_pTestObject2 = NULL;
}

void FSerializableTestObject::serialize(FArchive& ar)
{
	if (ar.isWriting())
	{
		ar << m_pTestObject1 << m_pTestObject2;
		ar << m_valString << m_valWString;
		ar << m_valBool;
		ar << m_valInt8 << m_valUInt8 << m_valInt16 << m_valUInt16;
		ar << m_valInt32 << m_valUInt32 << m_valInt64 << m_valUInt64;
		ar << m_valFloat << m_valDouble;
	}
	else // is reading
	{
		ar >> m_pTestObject1 >> m_pTestObject2;
		ar >> m_valString >> m_valWString;
		ar >> m_valBool;
		ar >> m_valInt8 >> m_valUInt8 >> m_valInt16 >> m_valUInt16;
		ar >> m_valInt32 >> m_valUInt32 >> m_valInt64 >> m_valUInt64;
		ar >> m_valFloat >> m_valDouble;
	}
}



// -----------------------------------------------------------------------------

void compare(FSerializableTestObject* pObj1, FSerializableTestObject* pObj2)
{
	BOOST_CHECK_EQUAL(pObj1->m_valBool, pObj2->m_valBool);
	BOOST_CHECK_EQUAL(pObj1->m_valInt8, pObj2->m_valInt8);
	BOOST_CHECK_EQUAL(pObj1->m_valUInt8, pObj2->m_valUInt8);
	BOOST_CHECK_EQUAL(pObj1->m_valInt16, pObj2->m_valInt16);
	BOOST_CHECK_EQUAL(pObj1->m_valUInt16, pObj2->m_valUInt16);
	BOOST_CHECK_EQUAL(pObj1->m_valInt32, pObj2->m_valInt32);
	BOOST_CHECK_EQUAL(pObj1->m_valUInt32, pObj2->m_valUInt32);
	BOOST_CHECK_EQUAL(pObj1->m_valInt64, pObj2->m_valInt64);
	BOOST_CHECK_EQUAL(pObj1->m_valUInt64, pObj2->m_valUInt64);
	BOOST_CHECK_EQUAL(pObj1->m_valFloat, pObj2->m_valFloat);
	BOOST_CHECK_EQUAL(pObj1->m_valDouble, pObj2->m_valDouble);
	BOOST_CHECK(pObj1->m_valString == pObj2->m_valString);
	BOOST_CHECK(pObj1->m_valWString == pObj2->m_valWString);
}

BOOST_AUTO_TEST_CASE(testObject)
{
	FSerializableTestObject* m_pTest1 = new FSerializableTestObject();
	FSerializableTestObject* m_pTest2 = new FSerializableTestObject();
	
	// cyclic dependency in object graph
	m_pTest1->m_pTestObject1 = m_pTest2;
	m_pTest2->m_pTestObject1 = m_pTest1;

	{
		std::fstream fileStream("test.dat", std::ios_base::out);
		FArchive ar(&fileStream, FArchive::Write, true);
		ar << m_pTest1;
		fileStream.close();
	}

	FSerializableTestObject* m_pTest3 = NULL;

	{
		std::fstream fileStream("test.dat", std::ios_base::in);
		FArchive ar(&fileStream, FArchive::Read, true);
		ar >> m_pTest3;
		fileStream.close();
	}

	compare(m_pTest1, m_pTest3);
	compare(m_pTest1->m_pTestObject1, m_pTest3->m_pTestObject1);

	F_SAFE_DELETE(m_pTest1->m_pTestObject1);
	F_SAFE_DELETE(m_pTest1);
	F_SAFE_DELETE(m_pTest3->m_pTestObject1);
	F_SAFE_DELETE(m_pTest3);
}

