// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowCore
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// ------------------------------------------------------------------------

#ifndef FLOWCORE_LIBRARY_H
#define FLOWCORE_LIBRARY_H

#include "FlowCore/Setup.h"

#ifndef FLOWCORE_DYNAMIC
#  define FLOWCORE_EXPORT
#elif defined(FLOWCORE_LIB)
#  define FLOWCORE_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWCORE_EXPORT F_DECLARE_IMPORT
#endif

// ------------------------------------------------------------------------

#endif // FLOWCORE_LIBRARY_H



