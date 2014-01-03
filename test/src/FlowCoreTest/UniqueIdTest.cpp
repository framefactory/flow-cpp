// -----------------------------------------------------------------------------
//  File        UniqueIdTest.cpp
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#include "FlowCoreTest/UniqueIdTest.h"
#include "FlowCore/UniqueId.h"
#include "FlowCore/MemoryTracer.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace boost::uuids;

// -----------------------------------------------------------------------------
//  Class FUniqueIdTest
// -----------------------------------------------------------------------------

F_IMPLEMENT_TEST(FUniqueIdTest, "Class FUniqueId");

// Initialization --------------------------------------------------------------

void FUniqueIdTest::setup()
{
}

void FUniqueIdTest::shutdown()
{
}

// Tests -----------------------------------------------------------------------

void FUniqueIdTest::test()
{
	// Construction

	FUniqueId id1("{8935A5A0-43E6-40D0-ACF1-A4B9D297500D}");
	FUniqueId id2("8935A5A0-43E6-40D0-ACF1-A4B9D297500D");

	F_CHECK(id1 == id2);

	FUniqueId id0;
	F_CHECK(id0.isNull());
	F_CHECK(!id1.isNull());

	FUniqueId rnd1 = FUniqueId::createRandom();
	FUniqueId rnd2 = FUniqueId::createRandom();
	FUniqueId rnd3(FUniqueId::createRandom());
	FUniqueId rnd4(FUniqueId::createRandom());
	F_CHECK(rnd1 != rnd2);
	F_CHECK(rnd2 != rnd3);
	F_CHECK(rnd3 != rnd4);

	FUniqueId rnd5(rnd2);
	FUniqueId rnd6 = rnd3;
	F_CHECK(rnd5 == rnd2);
	F_CHECK(rnd6 == rnd3);
	F_CHECK(rnd5.toString() == rnd2.toString());
	F_CHECK(rnd6.toString() == rnd3.toString());

	// toString()

	QString idText("8935A5A0-43E6-40D0-ACF1-A4B9D297500D");
	idText = idText.toLower();

	F_CHECK(id1.toString() == idText);
	F_CHECK(id2.toString() == idText);

	// Data access

	string_generator gen;
	uuid u1 = gen(idText.toStdWString());

	uint8_t* pV1 = (uint8_t*)&id1[0];
	uint8_t* pV2 = u1.begin();

	for (size_t i = 0; i < 16; ++i)
		F_CHECK(pV1[i] == pV2[i]);

	// Comparison operators

	FUniqueId id5("00000000-0000-0000-0000-000000000001");
	FUniqueId id6("00000000-0000-0000-0000-000100000000");
	FUniqueId id7("00000000-0000-0001-0000-000000000000");
	FUniqueId id8("00000001-0000-0000-0000-000000000000");

	F_CHECK(id5 < id6);
	F_CHECK(id6 < id7);
	F_CHECK(id7 < id8);

	F_CHECK(id6 > id5);
	F_CHECK(id7 > id6);
	F_CHECK(id8 > id7);

	F_CHECK(id5 <= id6);
	F_CHECK(id6 <= id7);
	F_CHECK(id7 <= id8);

	F_CHECK(id6 >= id5);
	F_CHECK(id7 >= id6);
	F_CHECK(id8 >= id7);

	F_CHECK(id8 == id8);
	F_CHECK(id8 != id7);

	// Hash code

	F_CHECK(id5.hashCode() == id7.hashCode());
	F_CHECK(id5.hashCode() != id6.hashCode());
	F_CHECK(rnd1.hashCode() != rnd2.hashCode());

}

// -----------------------------------------------------------------------------