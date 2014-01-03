// -----------------------------------------------------------------------------
//  File        PrecompiledHeader.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_PRECOMPILEDHEADER_H
#define FLOWCORE_PRECOMPILEDHEADER_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <locale>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
#  pragma warning(disable: 4996)
#endif

#include <boost/algorithm/string.hpp>
#include <boost/system/system_error.hpp>
#include <boost/locale.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
#  pragma warning(enable: 4996)
#  include <Windows.h>
#endif

#include "FlowCore/Library.h"


#endif // FLOWCORE_PRECOMPILEDHEADER_H