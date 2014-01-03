// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowKinect
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// ------------------------------------------------------------------------

#ifndef FLOWKINECT_LIBRARY_H
#define FLOWKINECT_LIBRARY_H

#include "FlowCore/Setup.h"

#define FLOWKINECT_DYNAMIC

#ifndef FLOWKINECT_DYNAMIC
#  define FLOWKINECT_EXPORT
#elif defined(FLOWKINECT_LIB)
#  define FLOWKINECT_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWKINECT_EXPORT F_DECLARE_IMPORT
#endif

// ------------------------------------------------------------------------

#endif // FLOWKINECT_LIBRARY_H



