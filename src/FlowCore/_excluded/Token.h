// -----------------------------------------------------------------------------
//  File        Token.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TOKEN_H
#define FLOWCORE_TOKEN_H

#include "FlowCore/Library.h"
#include "FlowCore/String.h"

struct FTokenEntry;

// -----------------------------------------------------------------------------
//  Class FToken
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FToken
{
	//  Constructors and destructor ----------------------------------

public:
	FToken();
	explicit FToken(const wstring_t& text);
	FToken(const FToken& other);
	~FToken();

	//  Operators ----------------------------------------------------

	FToken& operator=(const FToken& other);
	operator wstring_t() const;

	bool operator==(const FToken& rhs) const;
	bool operator!=(const FToken& rhs) const;
	bool operator<(const FToken& rhs) const;
	bool operator>(const FToken& rhs) const;

	bool operator==(const wstring_t& rhs) const;
	bool operator!=(const wstring_t& rhs) const;
	bool operator<(const wstring_t& rhs) const;
	bool operator>(const wstring_t& rhs) const;

	bool operator==(const wchar_t* rhs) const;
	bool operator!=(const wchar_t* rhs) const;
	bool operator<(const wchar_t* rhs) const;
	bool operator>(const wchar_t* rhs) const;

	//  Public commands ----------------------------------------------

public:
	void setText(const wstring_t& text);

	//  Public queries -----------------------------------------------

	const wstring_t& text() const;

	//  Internal data members ----------------------------------------

private:
	FTokenEntry* m_pEntry;
};

// Inline members --------------------------------------------------------------

inline FToken::FToken()
	: m_pEntry(NULL)
{
}

inline bool FToken::operator==(const FToken& rhs) const
{
	return m_pEntry == rhs.m_pEntry;
}

inline bool FToken::operator!=(const FToken& rhs) const
{
	return m_pEntry != rhs.m_pEntry;
}

inline bool FToken::operator<(const FToken& rhs) const
{
	return text() < rhs.text();
}

inline bool FToken::operator>(const FToken& rhs) const
{
	return text() > rhs.text();
}

inline bool FToken::operator==(const wstring_t& rhs) const
{
	return text() == rhs;
}

inline bool FToken::operator!=(const wstring_t& rhs) const
{
	return text() != rhs;
}

inline bool FToken::operator<(const wstring_t& rhs) const
{
	return text() < rhs;
}

inline bool FToken::operator>(const wstring_t& rhs) const
{
	return text() > rhs;
}

inline bool FToken::operator==(const wchar_t* rhs) const
{
	return text() == wstring_t(rhs);
}

inline bool FToken::operator!=(const wchar_t* rhs) const
{
	return text() != wstring_t(rhs);
}

inline bool FToken::operator<(const wchar_t* rhs) const
{
	return text() < wstring_t(rhs);
}

inline bool FToken::operator>(const wchar_t* rhs) const
{
	return text() > wstring_t(rhs);
}

// -----------------------------------------------------------------------------


#endif // FLOWCORE_TOKEN_H