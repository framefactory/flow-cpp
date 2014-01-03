// -----------------------------------------------------------------------------
//  File        Token.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.30 $
// -----------------------------------------------------------------------------

#include "FlowCore/Token.h"
#include "FlowCore/TokenRegistry.h"
#include "FlowCore/MemoryTracer.h"


// -----------------------------------------------------------------------------
//  Class FToken
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FToken::FToken(const wstring_t& text)
{
	m_pEntry = FTokenRegistry::instance()->add(text);
}

FToken::FToken(const FToken& other)
{
	m_pEntry = other.m_pEntry;
	FTokenRegistry::instance()->addRef(other.m_pEntry);
}

FToken::~FToken()
{
	if (m_pEntry)
		FTokenRegistry::instance()->removeRef(m_pEntry);
}

// Operators -------------------------------------------------------------------

FToken& FToken::operator=(const FToken& other)
{
	if (&other == this)
		return *this;

	if (other.m_pEntry == m_pEntry)
		return *this;

	if (m_pEntry)
		FTokenRegistry::instance()->removeRef(m_pEntry);
	
	m_pEntry = other.m_pEntry;
	FTokenRegistry::instance()->addRef(m_pEntry);

	return *this;
}

FToken::operator wstring_t() const
{
	return FTokenRegistry::instance()->text(m_pEntry);
}

// Public commands -------------------------------------------------------------

void FToken::setText(const wstring_t& text)
{
	if (m_pEntry)
		FTokenRegistry::instance()->removeRef(m_pEntry);

	m_pEntry = FTokenRegistry::instance()->add(text);
}

// Public queries --------------------------------------------------------------

const wstring_t& FToken::text() const
{
	return FTokenRegistry::instance()->text(m_pEntry);
}

// -----------------------------------------------------------------------------