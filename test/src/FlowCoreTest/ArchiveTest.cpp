// -----------------------------------------------------------------------------
//  File        ArchiveTest.cpp
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#include "FlowCoreTest/ArchiveTest.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <QFile>

// -----------------------------------------------------------------------------
//  Class FMySerializableObject
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FMySerializableObject, FObject, 1);

FMySerializableObject::FMySerializableObject()
	: m_pTestObject1(NULL),
	  m_pTestObject2(NULL),
	  m_valBool(false),
	  m_valInt8(0),
	  m_valUInt8(0),
	  m_valInt16(0),
	  m_valUInt16(0),
	  m_valInt32(0),
	  m_valUInt32(0),
	  m_valInt64(0),
	  m_valUInt64(0),
	  m_valFloat(0),
	  m_valDouble(0),
	  m_valPChar(""),
	  m_valQString("")
{
}

FMySerializableObject::FMySerializableObject(int)
{
	m_pTestObject1 = NULL;
    m_pTestObject2 = NULL;
	m_valBool = true;
	m_valInt8 = -56;
	m_valUInt8 = 254;
	m_valInt16 = -32000;
	m_valUInt16 = 65000;
	m_valInt32 = -2147480000;
	m_valUInt32 = 4294960000;
	m_valInt64 = -(int64_t(2147480000) << 32);
	m_valUInt64 = uint64_t(4294960000) << 32;
	m_valFloat = 3.14159265;
	m_valDouble = 0.1234567890123456789;
	m_valPChar = "This is a char sequence";
	m_valQString = "This is a unicode QString";
}

void FMySerializableObject::serialize(FArchive& ar)
{
	if (ar.isWriting())
	{
		ar << m_pTestObject1 << m_pTestObject2;
		ar << m_valQString;
		ar << m_valPChar;
		ar << m_valDouble << m_valFloat;
		ar << m_valInt8 << m_valInt16 << m_valInt32 << m_valInt64;
		ar << m_valUInt8 << m_valUInt16 << m_valUInt32 << m_valUInt64;
		ar << m_valBool;
	}
	else // is reading
	{
		ar >> m_pTestObject1 >> m_pTestObject2;
		ar >> m_valQString;
		ar >> m_valPChar;
		ar >> m_valDouble >> m_valFloat;
		ar >> m_valInt8 >> m_valInt16 >> m_valInt32 >> m_valInt64;
		ar >> m_valUInt8 >> m_valUInt16 >> m_valUInt32 >> m_valUInt64;
		ar >> m_valBool;
	}
}

// -----------------------------------------------------------------------------
//  Class FArchiveTest
// -----------------------------------------------------------------------------

F_IMPLEMENT_TEST(FArchiveTest, "Class FArchive");

// Initialization --------------------------------------------------------------

void FArchiveTest::setup()
{

}

void FArchiveTest::shutdown()
{

}

// Tests -----------------------------------------------------------------------

void FArchiveTest::compareObjects(FMySerializableObject* pObj1, FMySerializableObject* pObj2)
{
	F_COMPARE(pObj1->m_valBool, pObj2->m_valBool);
	F_COMPARE(pObj1->m_valInt8, pObj2->m_valInt8);
	F_COMPARE(pObj1->m_valUInt8, pObj2->m_valUInt8);
	F_COMPARE(pObj1->m_valInt16, pObj2->m_valInt16);
	F_COMPARE(pObj1->m_valUInt16, pObj2->m_valUInt16);
	F_COMPARE(pObj1->m_valInt32, pObj2->m_valInt32);
	F_COMPARE(pObj1->m_valUInt32, pObj2->m_valUInt32);
	F_COMPARE(pObj1->m_valInt64, pObj2->m_valInt64);
	F_COMPARE(pObj1->m_valUInt64, pObj2->m_valUInt64);
	F_COMPARE(pObj1->m_valFloat, pObj2->m_valFloat);
	F_COMPARE(pObj1->m_valDouble, pObj2->m_valDouble);
	F_COMPARE(pObj1->m_valQString, pObj2->m_valQString);
	F_CHECK(strcmp(pObj1->m_valPChar, pObj2->m_valPChar) == 0);
}

void FArchiveTest::test1()
{
	FMySerializableObject* pObj1 = new FMySerializableObject(1);
	
	QFile outFile("test.far");
	outFile.open(QFile::WriteOnly);

	FArchive outArchive(&outFile, false);
	outArchive << pObj1;
	outFile.close();

	FMySerializableObject* pObj2;

	QFile inFile("test.far");
	inFile.open(QFile::ReadOnly);

	FArchive inArchive(&inFile, false);
	inArchive >> pObj2;
	inFile.close();

	// compare object members
	compareObjects(pObj1, pObj2);

	// cleanup
	F_SAFE_DELETE(pObj1);
	F_SAFE_DELETE(pObj2);
}

void FArchiveTest::test2()
{
	FMySerializableObject* pTest1 = new FMySerializableObject(1);
	FMySerializableObject* pTest2 = new FMySerializableObject(1);

	// cyclic dependency in object graph
	pTest1->m_pTestObject1 = pTest2;
	pTest2->m_pTestObject1 = pTest1;

	QFile outFile("test.far");
	outFile.open(QFile::WriteOnly);

	FArchive outArchive(&outFile);
	outArchive << pTest1;
	outFile.close();

	FMySerializableObject* pTest3 = NULL;

	QFile inFile("test.far");
	inFile.open(QFile::ReadOnly);

	FArchive inArchive(&inFile);
	inArchive >> pTest3;
	inFile.close();
	
	compareObjects(pTest1, pTest3);
	compareObjects(pTest1->m_pTestObject1, pTest3->m_pTestObject1);
	F_COMPARE(pTest1->m_pTestObject2, pTest3->m_pTestObject2);

	// cleanup
	F_SAFE_DELETE(pTest1->m_pTestObject1);
	F_SAFE_DELETE(pTest1);
	F_SAFE_DELETE(pTest3->m_pTestObject1);
	F_SAFE_DELETE(pTest3);

}

// -----------------------------------------------------------------------------