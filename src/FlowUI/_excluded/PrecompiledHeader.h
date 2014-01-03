// -----------------------------------------------------------------------------
//  File        PrecompiledHeader.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_PRECOMPILEDHEADER_H
#define FLOWUI_PRECOMPILEDHEADER_H

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

#include <boost/algorithm/string.hpp>
#include <boost/system/system_error.hpp>
#include <boost/locale.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
#  include <Windows.h>
#endif



#include "FlowCore/FlowCore.h"


#endif // FLOWUI_PRECOMPILEDHEADER_H