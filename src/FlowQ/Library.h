// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowQ
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// ------------------------------------------------------------------------

#ifndef FLOWQ_LIBRARY_H
#define FLOWQ_LIBRARY_H

#include "FlowCore/Setup.h"

#ifndef FLOWQ_DYNAMIC
#  define FLOWQ_EXPORT
#elif defined(FLOWQ_LIB)
#  define FLOWQ_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWQ_EXPORT F_DECLARE_IMPORT
#endif

// ------------------------------------------------------------------------

#endif // FLOWQ_LIBRARY_H



