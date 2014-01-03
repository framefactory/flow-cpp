// -----------------------------------------------------------------------------
//  File        TestTypes.cpp
//  Project     FlowTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/03 $
// -----------------------------------------------------------------------------

#include "FlowCore/UniqueId.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <iostream>

#include <boost/test/unit_test.hpp>

using namespace boost::uuids;

BOOST_AUTO_TEST_CASE(testUniqueId)
{
	// Construction

	FUniqueId id1("{8935A5A0-43E6-40D0-ACF1-A4B9D297500D}");
	FUniqueId id2(L"8935A5A0-43E6-40D0-ACF1-A4B9D297500D");
	FUniqueId id3(string_t("8935A5A0-43E6-40D0-ACF1-A4B9D297500D"));
	FUniqueId id4(wstring_t(L"{8935A5A0-43E6-40D0-ACF1-A4B9D297500D}"));

	BOOST_CHECK(id1 == id2);
	BOOST_CHECK(id2 == id3);
	BOOST_CHECK(id3 == id4);

	FUniqueId id0;
	BOOST_CHECK(id0.isNull());
	BOOST_CHECK(!id1.isNull());

	FUniqueId rnd1 = FUniqueId::createRandom();
	FUniqueId rnd2 = FUniqueId::createRandom();
	FUniqueId rnd3(FUniqueId::createRandom());
	FUniqueId rnd4(FUniqueId::createRandom());
	BOOST_CHECK(rnd1 != rnd2);
	BOOST_CHECK(rnd2 != rnd3);
	BOOST_CHECK(rnd3 != rnd4);

	FUniqueId rnd5(rnd2);
	FUniqueId rnd6 = rnd3;
	BOOST_CHECK(rnd5 == rnd2);
	BOOST_CHECK(rnd6 == rnd3);
	BOOST_CHECK(rnd5.toString() == rnd2.toString());
	BOOST_CHECK(rnd6.toString() == rnd3.toString());

	// toString()

	std::wstring idText(L"8935A5A0-43E6-40D0-ACF1-A4B9D297500D");
	idText = FString::toLower(idText);

	BOOST_CHECK(id1.toString() == idText);
	BOOST_CHECK(id2.toString() == idText);
	BOOST_CHECK(id3.toString() == idText);
	BOOST_CHECK(id4.toString() == idText);

	// Data access

	string_generator gen;
	uuid u1 = gen(idText);

	uint8_t* pV1 = (uint8_t*)&id1[0];
	uint8_t* pV2 = u1.begin();

	for (size_t i = 0; i < 16; ++i)
		BOOST_CHECK(pV1[i] == pV2[i]);

	// Comparison operators

	FUniqueId id5("00000000-0000-0000-0000-000000000001");
	FUniqueId id6("00000000-0000-0000-0000-000100000000");
	FUniqueId id7("00000000-0000-0001-0000-000000000000");
	FUniqueId id8("00000001-0000-0000-0000-000000000000");

	BOOST_CHECK(id5 < id6);
	BOOST_CHECK(id6 < id7);
	BOOST_CHECK(id7 < id8);

	BOOST_CHECK(id6 > id5);
	BOOST_CHECK(id7 > id6);
	BOOST_CHECK(id8 > id7);

	BOOST_CHECK(id5 <= id6);
	BOOST_CHECK(id6 <= id7);
	BOOST_CHECK(id7 <= id8);

	BOOST_CHECK(id6 >= id5);
	BOOST_CHECK(id7 >= id6);
	BOOST_CHECK(id8 >= id7);

	BOOST_CHECK(id8 == id8);
	BOOST_CHECK(id8 != id7);

	// Hash code

	BOOST_CHECK(id5.hashCode() == id7.hashCode());
	BOOST_CHECK(id5.hashCode() != id6.hashCode());
	BOOST_CHECK(rnd1.hashCode() != rnd2.hashCode());
}
