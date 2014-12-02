// -----------------------------------------------------------------------------
//  File        UniqueId.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 2 $
//  $Date: 2013/12/23 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_UNIQUEID_H
#define FLOWCORE_UNIQUEID_H

#include "FlowCore/Library.h"
#include <QString>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FUniqueId
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FUniqueId
{
	//  Static members -----------------------------------------------
	
public:
	/// Creates a random unique id.
	static FUniqueId createRandom();

	/// Creates a unique id from a given name and name space.
	static FUniqueId fromName(const QString& name, const FUniqueId& nameSpace);

	//  Constructors -------------------------------------------------

	/// Default constructor. Creates a null id, all components are set to zero.
	FUniqueId();
	/// Creates a custom id using the given components.
	FUniqueId(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3);
	/// Creates a unique id by parsing the given GUID string.
	FUniqueId(const QString& str);

	//  Public queries -----------------------------------------------

	/// Access to one of the four 32-bit components of the id.
	uint32_t& operator[](size_t index) { return m_data[index]; }
	/// Const access to one of the four 32-bit components of the id.
	const uint32_t& operator[](size_t index) const { return m_data[index]; }

	/// Returns true if the unique id is null,
	/// i.e. all components are equal to zero.
	bool isNull() const;
	/// Returns a permutation of the id.
	FUniqueId permute() const;
	/// Returns an exclusive or of the the given pattern with this.
	FUniqueId exclusiveOr(const FUniqueId& pattern) const;
	/// Returns a text representation of the unique id in GUID format.
	QString toString() const;
	/// Returns a hash code for this id.
	size_t hashCode() const;

	//  Operators ----------------------------------------------------

	/// Returns true if the two ids are equal.
	FLOWCORE_EXPORT friend bool operator==(const FUniqueId& lhs, const FUniqueId& rhs);
	/// Returns true if the two ids are not equal.
	FLOWCORE_EXPORT friend bool operator!=(const FUniqueId& lhs, const FUniqueId& rhs);
	/// Returns true if the first id is smaller than the second id.
	FLOWCORE_EXPORT friend bool operator<(const FUniqueId& lhs, const FUniqueId& rhs);
	/// Returns true if the first id is greater than the second id.
	FLOWCORE_EXPORT friend bool operator>(const FUniqueId& lhs, const FUniqueId& rhs);
	/// Returns true if the first id is smaller or equal than the second id.
	FLOWCORE_EXPORT friend bool operator<=(const FUniqueId& lhs, const FUniqueId& rhs);
	/// Returns true if the first id is greater or equal than the second id.
	FLOWCORE_EXPORT friend bool operator>=(const FUniqueId& lhs, const FUniqueId& rhs);

	/// Serialization: write operator.
	FLOWCORE_EXPORT friend FArchive& operator<<(FArchive& ar, const FUniqueId& obj);
	/// Serialization: read operator.
	FLOWCORE_EXPORT friend FArchive& operator>>(FArchive& ar, FUniqueId& obj);

	//  Internal data members ----------------------------------------

private:
	uint32_t m_data[4];
};

// Inline members --------------------------------------------------------------

inline FUniqueId::FUniqueId()
{
	m_data[0] = 0;
	m_data[1] = 0;
	m_data[2] = 0;
	m_data[3] = 0;
}

inline FUniqueId::FUniqueId(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
	m_data[0] = v0;
	m_data[1] = v1;
	m_data[2] = v2;
	m_data[3] = v3;
}

inline bool FUniqueId::isNull() const
{
	return m_data[0] == 0 && m_data[1] == 0 && m_data[2] == 0 && m_data[3] == 0;
}

inline FUniqueId FUniqueId::permute() const
{
	return FUniqueId(m_data[0] + 95601553,
					 m_data[1] + 1007753,
					 m_data[2] + 6907,
					 m_data[3] + 409483);
}

inline FUniqueId FUniqueId::exclusiveOr(const FUniqueId& pattern) const
{
	return FUniqueId(m_data[0] ^ pattern.m_data[0],
		             m_data[1] ^ pattern.m_data[1],
				     m_data[2] ^ pattern.m_data[2],
				     m_data[3] ^ pattern.m_data[3]);
}

inline size_t FUniqueId::hashCode() const
{
	if (sizeof(size_t) == 4)
		return m_data[0] ^ m_data[1] ^ m_data[2] ^ m_data[3];
	else
		return *((size_t*)m_data) ^ *((size_t*)(m_data + 2));
}

inline bool operator==(const FUniqueId& lhs, const FUniqueId& rhs)
{
	return lhs.m_data[0] == rhs.m_data[0]
		&& lhs.m_data[1] == rhs.m_data[1]
		&& lhs.m_data[2] == rhs.m_data[2]
		&& lhs.m_data[3] == rhs.m_data[3];
}

inline bool operator!=(const FUniqueId& lhs, const FUniqueId& rhs)
{
	return lhs.m_data[0] != rhs.m_data[0]
		|| lhs.m_data[1] != rhs.m_data[1]
		|| lhs.m_data[2] != rhs.m_data[2]
		|| lhs.m_data[3] != rhs.m_data[3];
}

inline bool operator<(const FUniqueId& lhs, const FUniqueId& rhs)
{
	return lhs.m_data[0] < rhs.m_data[0]
	|| (lhs.m_data[0] == rhs.m_data[0]
	&& (lhs.m_data[1] < rhs.m_data[1]
	|| (lhs.m_data[1] == rhs.m_data[1]
	&& (lhs.m_data[2] < rhs.m_data[2]
	|| (lhs.m_data[2] == rhs.m_data[2] && lhs.m_data[3] < rhs.m_data[3])))));
}

inline bool operator>(const FUniqueId& lhs, const FUniqueId& rhs)
{
	return lhs.m_data[0] > rhs.m_data[0]
	|| (lhs.m_data[0] == rhs.m_data[0]
	&& (lhs.m_data[1] > rhs.m_data[1]
	|| (lhs.m_data[1] == rhs.m_data[1]
	&& (lhs.m_data[2] > rhs.m_data[2]
	|| (lhs.m_data[2] == rhs.m_data[2] && lhs.m_data[3] > rhs.m_data[3])))));
}

inline bool operator<=(const FUniqueId& lhs, const FUniqueId& rhs)
{
	return lhs.m_data[0] < rhs.m_data[0]
	|| (lhs.m_data[0] == rhs.m_data[0]
	&& (lhs.m_data[1] < rhs.m_data[1]
	|| (lhs.m_data[1] == rhs.m_data[1]
	&& (lhs.m_data[2] < rhs.m_data[2]
	|| (lhs.m_data[2] == rhs.m_data[2] && lhs.m_data[3] <= rhs.m_data[3])))));
}

inline bool operator>=(const FUniqueId& lhs, const FUniqueId& rhs)
{
	return lhs.m_data[0] > rhs.m_data[0]
	|| (lhs.m_data[0] == rhs.m_data[0]
	&& (lhs.m_data[1] > rhs.m_data[1]
	|| (lhs.m_data[1] == rhs.m_data[1]
	&& (lhs.m_data[2] > rhs.m_data[2]
	|| (lhs.m_data[2] == rhs.m_data[2] && lhs.m_data[3] >= rhs.m_data[3])))));
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_UNIQUEID_H
