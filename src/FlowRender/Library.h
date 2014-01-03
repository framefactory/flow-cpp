// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowRender
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// ------------------------------------------------------------------------

#ifndef FLOWRENDER_LIBRARY_H
#define FLOWRENDER_LIBRARY_H

#include "FlowCore/Setup.h"

#ifndef FLOWRENDER_DYNAMIC
#  define FLOWRENDER_EXPORT
#elif defined(FLOWRENDER_LIB)
#  define FLOWRENDER_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWRENDER_EXPORT F_DECLARE_IMPORT
#endif

// ------------------------------------------------------------------------

#endif // FLOWRENDER_LIBRARY_H



