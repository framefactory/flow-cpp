#ifndef FLOWUI_LIBRARY_H
#define FLOWUI_LIBRARY_H

//#include "FlowCore/Setup.h"

#ifndef FLOWUI_DYNAMIC
#  define FLOWUI_EXPORT
#elif defined(FLOWUI_LIB)
#  define FLOWUI_EXPORT F_DECLARE_EXPORT
#else
#  define FLOWUI_EXPORT F_DECLARE_IMPORT
#endif

#endif // FLOWUI_LIBRARY_H