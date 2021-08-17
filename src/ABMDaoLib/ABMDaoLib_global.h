#ifndef ABMDAOLIB_GLOBAL_H
#define ABMDAOLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ABMDAOLIB_LIBRARY)
#  define ABMDAOLIB_EXPORT Q_DECL_EXPORT
#else
#  define ABMDAOLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // ABMDAOLIB_GLOBAL_H
