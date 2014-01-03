// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowEngine
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// ------------------------------------------------------------------------

#ifndef FLOWENGINE_LIBRARY_H
#define FLOWENGINE_LIBRARY_H

#include "FlowCore/Setup.h"

#ifndef FLOWENGINE_DYNAMIC
#  define FLOWENGINE_EXPORT
#elif defined(FLOWENGINE_LIB)
#  define FLOWENGINE_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWENGINE_EXPORT F_DECLARE_IMPORT
#endif

// -----------------------------------------------------------------------------

#endif // FLOWENGINE_LIBRARY_H