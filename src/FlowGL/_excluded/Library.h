// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowGL
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// ------------------------------------------------------------------------

#ifndef FLOWGL_LIBRARY_H
#define FLOWGL_LIBRARY_H

#include "FlowCore/Setup.h"

#ifndef FLOWGL_DYNAMIC
#  define FLOWGL_EXPORT
#elif defined(FLOWGL_LIB)
#  define FLOWGL_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWGL_EXPORT F_DECLARE_IMPORT
#endif

// -----------------------------------------------------------------------------

#endif // FLOWGL_LIBRARY_H