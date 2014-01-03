// -----------------------------------------------------------------------------
//  File        FString.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#include "FlowCore/String.h"

#include <boost/algorithm/string.hpp>
#include <boost/system/system_error.hpp>
#include <boost/locale.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <sstream>
#include <ostream>
#include <locale>

// -----------------------------------------------------------------------------
//  Class FString
// -----------------------------------------------------------------------------

// Helper functions ------------------------------------------------------------

template <typename T, typename C>
static inline T fParse(const std::basic_string<C>& str, bool* ok)
{
	T result = T(0);

	try {
		result = boost::lexical_cast<T>(str);
		if (ok) *ok = true;
	}
	catch (boost::bad_lexical_cast &) {
		if (ok) *ok = false;
	}

	return result;
}

template <typename C>
static inline size_t fSplit(const std::basic_string<C>& str,
	const std::basic_string<C>& sep,
	FString::SplitBehaviour behaviour,
	OUT std::vector<std::basic_string<C>>& tokens)
{
	typedef boost::tokenizer<boost::char_separator<C>,
		typename std::basic_string<C>::const_iterator, std::basic_string<C>> tokenizer;

	boost::empty_token_policy policy = (behaviour == FString::KeepEmptyParts
		? boost::keep_empty_tokens : boost::drop_empty_tokens);

	boost::char_separator<C> charSep(sep.c_str(), 0, policy);
	tokenizer tok(str, charSep);

	tokens.clear();
	for (typename tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
		tokens.push_back(*it);

	return tokens.size();
}

template <typename C>
static inline std::basic_string<C> fToUpper(conststd::basic_string<C>& str)
{
	std::basic_string<C> result(str);
	boost::algorithm::to_upper(result);
	return result;
}

template <typename C>
static inline std::basic_string<C> fToLower(const std::basic_string<C>& str)
{
	std::basic_string<C> result(str);
	boost::algorithm::to_lower(result);
	return result;
}

// Public static members -------------------------------------------------------

float FString::toFloat(const std::string& str, bool* ok /* = 0 */)
{
	return fParse<float>(str, ok);
}

float FString::toFloat(const std::wstring& str, bool* ok /* = 0 */)
{
	return fParse<float>(str, ok);
}

double FString::toDouble(const std::string& str, bool* ok /* = 0 */)
{
	return fParse<double>(str, ok);
}

double FString::toDouble(const std::wstring& str, bool* ok /* = 0 */)
{
	return fParse<double>(str, ok);
}

int32_t FString::toInt32(const std::string& str, bool* ok /* = 0 */)
{
	return fParse<int32_t>(str, ok);
}

int32_t FString::toInt32(const std::wstring& str, bool* ok /* = 0 */)
{
	return fParse<int32_t>(str, ok);
}

uint32_t FString::toUInt32(const std::string& str, bool* ok /* = 0 */)
{
	return fParse<uint32_t>(str, ok);
}

uint32_t FString::toUInt32(const std::wstring& str, bool* ok /* = 0 */)
{
	return fParse<uint32_t>(str, ok);
}

int64_t FString::toInt64(const std::string& str, bool* ok /* = 0 */)
{
	return fParse<int64_t>(str, ok);
}

int64_t FString::toInt64(const std::wstring& str, bool* ok /* = 0 */)
{
	return fParse<int64_t>(str, ok);
}

uint64_t FString::toUInt64(const std::string& str, bool* ok /* = 0 */)
{
	return fParse<uint64_t>(str, ok);
}

uint64_t FString::toUInt64(const std::wstring& str, bool* ok /* = 0 */)
{
	return fParse<uint64_t>(str, ok);
}

size_t FString::split(const std::string& str, const std::string& sep,
	SplitBehaviour behaviour, OUT std::vector<std::string>& tokens)
{
	return fSplit(str, sep, behaviour, tokens);
}

size_t FString::split(const std::wstring& str, const std::wstring& sep,
	SplitBehaviour behaviour, OUT std::vector<std::wstring>& tokens)
{
	return fSplit(str, sep, behaviour, tokens);
}

std::string FString::toUpper(const std::string& str)
{
	return fToUpper(str);
}

std::wstring FString::toUpper(conststd::wstring& str)
{
	return fToUpper(str);
}

std::string FString::toLower(const std::string& str)
{
	return fToLower(str);
}

std::wstring FString::toLower(conststd::wstring& str)
{
	return fToLower(str);
}

std::wstring FString::toUtf(const std::string& str, bool* ok /* = 0 */)
{
	_setLocale();

	try {
		std::wstring result
			= boost::locale::conv::to_utf<wchar_t>(str, std::locale());
		if (ok) *ok = true;
		return result;
	}
	catch (std::bad_cast &) {
		if (ok) *ok = false;
		return std::wstring();
	}
}

std::wstring FString::toUtf(const char* str, bool* ok /* = 0 */)
{
	std::string s(str);
	return toUtf(s);
}

std::wstring FString::toUtf(const std::ostringstream& stream, bool* ok /* = 0 */)
{
	return FString::toUtf(stream.str(), ok);
}

std::wstring FString::toUtf(const std::wostringstream& stream, bool* ok /* = 0 */)
{
	if (ok) *ok = true;
	return stream.str();
}

std::wstring FString::toUtf(const std::wstring& str, bool* ok /* = 0 */)
{
	if (ok) *ok = true;
	return str;
}

std::string FString::fromUtf(const std::wstring& str, bool* ok /* = 0 */)
{
	_setLocale();

	try {
		std::string result 
			= boost::locale::conv::from_utf(str, std::locale());
		if (ok) *ok = true;
		return result;
	}
	catch (std::bad_cast &) {
		if (ok) *ok = false;
		return std::string();
	}
}

// Private static members ------------------------------------------------------

bool FString::s_localeIsSet = false;

void FString::_setLocale()
{
	if (!s_localeIsSet)
	{
		s_localeIsSet = true;
		std::locale loc(boost::locale::generator().generate(""));
		std::locale::global(loc);
	}
}

// -----------------------------------------------------------------------------