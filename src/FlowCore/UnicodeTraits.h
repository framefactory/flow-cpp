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

#include <QtGlobal>

#include <map>
#include <unordered_map>
#include <string>

// -----------------------------------------------------------------------------
//  Class FUnicodeTraits
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FUnicodeTraits
{
public:
	typedef FRangeT<quint32> range_type;

	static range_type codeBlockRange(const char* blockName);
	static range_type codeBlockRange(quint32 blockIndex);
	static const char* codeBlockName(quint32 blockIndex);
	static quint32 codeBlockCount();

private:
	FUnicodeTraits() { }
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_UNICODETRAITS_H
