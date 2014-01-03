// -----------------------------------------------------------------------------
//  File        UnicodeTraits.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_UNICODETRAITS_H
#define FLOWCORE_UNICODETRAITS_H

#include "FlowCore/Library.h"
#include "FlowCore/RangeT.h"

#include <map>
#include <unordered_map>
#include <string>

// -----------------------------------------------------------------------------
//  Class FUnicodeTraits
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FUnicodeTraits
{
public:
	typedef FRangeT<uint32_t> range_type;

	static range_type codeBlockRange(const char* blockName);
	static range_type codeBlockRange(uint32_t blockIndex);
	static const char* codeBlockName(uint32_t blockIndex);
	static uint32_t codeBlockCount() { return s_blockCount; }

private:
	FUnicodeTraits() { }

	struct blockEntry_t
	{
		uint32_t begin;
		uint32_t end;
		const char* name;
	};

	static const uint32_t s_blockCount = 220;
	static const blockEntry_t s_blockTable[];

	typedef std::unordered_map<std::string, uint32_t> nameIndexMap_t;
	static nameIndexMap_t s_nameIndexMap;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_UNICODETRAITS_H
