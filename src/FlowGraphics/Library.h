// ------------------------------------------------------------------------
//  File        Library.h
//  Project     FlowGraphics
// ------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// ------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_LIBRARY_H
#define FLOWGRAPHICS_LIBRARY_H

#include "FlowCore/Setup.h"

#ifndef FLOWGRAPHICS_DYNAMIC
#  define FLOWGRAPHICS_EXPORT
#elif defined(FLOWGRAPHICS_LIB)
#  define FLOWGRAPHICS_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWGRAPHICS_EXPORT F_DECLARE_IMPORT
#endif

#endif // FLOWGRAPHICS_LIBRARY_H