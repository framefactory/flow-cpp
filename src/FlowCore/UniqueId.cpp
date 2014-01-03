// -----------------------------------------------------------------------------
//  File        UniqueId.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/03 $
// -----------------------------------------------------------------------------

#include "FlowCore/UniqueId.h"
#include "FlowCore/Archive.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <sstream>

using namespace boost::uuids;

static inline const uuid& _toUuid(const FUniqueId& id) {
	return *reinterpret_cast<const uuid*>(&id);
}

static basic_random_generator<boost::mt19937> _rndGen;

// -----------------------------------------------------------------------------
//  Class FUniqueId
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

FUniqueId FUniqueId::createRandom()
{
	uuid u(_rndGen());
	uint32_t* pUuid = (uint32_t*)&u;

	FUniqueId id;
	id.m_data[0] = *pUuid++;
	id.m_data[1] = *pUuid++;
	id.m_data[2] = *pUuid++;
	id.m_data[3] = *pUuid;
	return id;
}

FUniqueId FUniqueId::fromName(const QString& name, const FUniqueId& nameSpace)
{
	name_generator gen(_toUuid(nameSpace));
	uuid u = gen(name.toStdWString());
	uint32_t* pUuid = (uint32_t*)&u;

	FUniqueId id;
	id.m_data[0] = *pUuid++;
	id.m_data[1] = *pUuid++;
	id.m_data[2] = *pUuid++;
	id.m_data[3] = *pUuid;
	return id;
}

// Constructors ----------------------------------------------------------------

FUniqueId::FUniqueId(const QString& str)
{
	string_generator gen;
	uuid u = gen(str.toStdWString());
	uint32_t* pUuid = (uint32_t*)&u;

	m_data[0] = *pUuid++;
	m_data[1] = *pUuid++;
	m_data[2] = *pUuid++;
	m_data[3] = *pUuid;
}

// Public queries --------------------------------------------------------------

QString FUniqueId::toString() const
{
	std::wostringstream oss;
	oss << _toUuid(*this);
	return QString::fromStdWString(oss.str());
}

// Operators -------------------------------------------------------------------

FArchive& operator<<(FArchive& ar, const FUniqueId& obj)
{
	ar << obj[0] << obj[1] << obj[2] << obj[3];
	return ar;
}

FArchive& operator>>(FArchive& ar, FUniqueId& obj)
{
	ar >> obj[0] >> obj[1] >> obj[2] >> obj[3];
	return ar;
}

// -----------------------------------------------------------------------------