// -----------------------------------------------------------------------------
//  File        ArchiveTest.h
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORETEST_ARCHIVETEST_H
#define FLOWCORETEST_ARCHIVETEST_H

#include "FlowCore/UnitTest.h"
#include "FlowCore/Object.h"

class FArchive;

// -----------------------------------------------------------------------------
//  Class FMySerializableObject
// -----------------------------------------------------------------------------

class  FMySerializableObject : public FObject
{
	F_DECLARE_SERIALIZABLE_CUSTOM_DC(FMySerializableObject);

public:
	FMySerializableObject();
	FMySerializableObject(int);
	virtual ~FMySerializableObject() { }


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
	char*        m_valPChar;
	QString      m_valQString;

	FMySerializableObject* m_pTestObject1;
	FMySerializableObject* m_pTestObject2;
};
	
// -----------------------------------------------------------------------------
//  Class FArchiveTest
// -----------------------------------------------------------------------------

class FArchiveTest : public FUnitTest
{
	Q_OBJECT;
	F_DECLARE_TEST;

public:
	virtual void setup();
	virtual void shutdown();

public slots:
	void test1();
	void test2();

private:
	void compareObjects(FMySerializableObject* pObj1, FMySerializableObject* pObj2);
};

// -----------------------------------------------------------------------------

#endif // FLOWCORETEST_ARCHIVETEST_H