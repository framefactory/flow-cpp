// -----------------------------------------------------------------------------
//  File        String.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_STRING_H
#define FLOWCORE_STRING_H

#include "FlowCore/Library.h"

#include <string>
#include <vector>
#include <iosfwd>


typedef std::string string_t;
typedef std::wstring wstring_t;

typedef std::vector<string_t> string_vector_t;
typedef std::vector<wstring_t> wstring_vector_t;

// -----------------------------------------------------------------------------
//  Class FString
// -----------------------------------------------------------------------------

/// Class providing static methods for string manipulation.
class FLOWCORE_EXPORT FString
{
	//  Public enums -------------------------------------------------

public:
	enum SplitBehaviour
	{
		KeepEmptyParts,
		SkipEmptyParts
	};

	//  Public static methods ----------------------------------------

	/// Extracts a float value from the given ANSI string.
	static float toFloat(const std::string& str, bool* ok = 0);
	/// Extracts a float value from the given unicode string.
	static float toFloat(const std::wstring& str, bool* ok = 0);
	
	/// Extracts a double value from the given ANSI string.
	static double toDouble(const std::string& str, bool* ok = 0);
	/// Extracts a double value from the given unicode string.
	static double toDouble(const std::wstring& str, bool* ok = 0);
	
	/// Extracts an int32_t value from the given ANSI string.
	static int32_t toInt32(const std::string& str, bool* ok = 0);
	/// Extracts an int32_t value from the given unicode string.
	static int32_t toInt32(const std::wstring& str, bool* ok = 0);
	
	/// Extracts an uint32_t value from the given ANSI string.
	static uint32_t toUInt32(const std::string& str, bool* ok = 0);
	/// Extracts an uint32_t value from the given unicode string.
	static uint32_t toUInt32(const std::wstring& str, bool* ok = 0);
	
	/// Extracts an int64_t value from the given ANSI string.
	static int64_t toInt64(const std::string& str, bool* ok = 0);
	/// Extracts an int64_t value from the given unicode string.
	static int64_t toInt64(const std::wstring& str, bool* ok = 0);
	
	/// Extracts an uint64_t value from the given ANSI string.
	static uint64_t toUInt64(const std::string& str, bool* ok = 0);
	/// Extracts an uint64_t value from the given unicode string.
	static uint64_t toUInt64(const std::wstring& str, bool* ok = 0);

	/// Splits the given string using the separator chars in sep.
	static size_t split(const std::string& str, const std::string& sep,
		SplitBehaviour behaviour, OUT std::vector<std::string>& tokens);
	/// Splits the given unicode string using the separator chars in sep.
	static size_t split(const std::wstring& str, const std::wstring& sep,
		SplitBehaviour behaviour, OUT std::vector<std::wstring>& tokens);

	/// Converts the characters of the given string to upper case.
	static std::string toUpper(const std::string& str);
	/// Converts the characters of the given string to upper case.
	static std::wstring toUpper(const std::wstring& str);

	/// Converts the characters of the given string to lower case.
	static std::string toLower(const std::string& str);
	/// Converts the characters of the given string to lower case.
	static std::wstring toLower(const std::wstring& str);

	/// Converts the given ansi string to unicode.
	static std::wstring toUtf(const std::string& str, bool* ok = 0);
	/// Converts the given ansi string to unicode.
	static std::wstring toUtf(const char* str, bool* ok = 0);
	/// Converts the given ansi string to unicode.
	static std::wstring toUtf(const std::ostringstream& stream, bool* ok = 0);
	/// Converts the given ansi string to unicode.
	static std::wstring toUtf(const std::wostringstream& stream, bool* ok = 0);
	/// No-op overload.
	static std::wstring toUtf(const std::wstring& str, bool* ok = 0);

	/// Converts the given unicode string to ansi.
	static std::string fromUtf(const std::wstring& str, bool* ok = 0);

	
	//  Private static members ---------------------------------------
	
private:
	static void _setLocale();
	static bool s_localeIsSet;
};

// -----------------------------------------------------------------------------

#endif // FLOWCORE_STRING_H