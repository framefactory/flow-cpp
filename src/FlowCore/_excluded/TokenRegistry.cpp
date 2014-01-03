// -----------------------------------------------------------------------------
//  File        TokenRegistry.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.30 $
// -----------------------------------------------------------------------------

#include "FlowCore/TokenRegistry.h"
#include "FlowCore/MemoryTracer.h"

#include <boost/thread/locks.hpp>

// -----------------------------------------------------------------------------
//  Class FTokenRegistry
// -----------------------------------------------------------------------------

struct FTokenEntry
{
	FTokenEntry(const wstring_t& _text)
		: text(_text), refCount(1)
	{
	}

	wstring_t text;
	uint32_t refCount;
};

// Constructors and destructor -------------------------------------------------

FTokenRegistry::FTokenRegistry()
{
}

FTokenRegistry::~FTokenRegistry()
{
	for (auto it = m_tokens.begin(); it != m_tokens.end(); ++it)
		delete it->second;
}

// Protected members -----------------------------------------------------------

FTokenEntry* FTokenRegistry::add(const wstring_t& text)
{
	F_ASSERT(!text.empty());
	boost::lock_guard<boost::mutex> guard(m_mutex);

	auto it = m_tokens.find(text);
	if (it != m_tokens.end())
		return it->second;

	FTokenEntry* pEntry = new FTokenEntry(text);
	m_tokens.insert(tokenMap_t::value_type(text, pEntry));
	return pEntry;
}

void FTokenRegistry::addRef(FTokenEntry* pEntry)
{
	F_ASSERT(pEntry);
	boost::lock_guard<boost::mutex> guard(m_mutex);

	pEntry->refCount++;
}

void FTokenRegistry::removeRef(FTokenEntry* pEntry)
{
	F_ASSERT(pEntry);
	boost::lock_guard<boost::mutex> guard(m_mutex);

	pEntry->refCount--;
	if (!pEntry->refCount)
	{
		F_ASSERT(m_tokens.find(pEntry->text) != m_tokens.end());
		m_tokens.erase(pEntry->text);
		delete pEntry;
	}
}

const wstring_t& FTokenRegistry::text(const FTokenEntry* pEntry) const
{
	return pEntry->text;
}

// -----------------------------------------------------------------------------
