#ifndef GLOBAL_GLOBAL_H
#define GLOBAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CORE_LIBRARY)
#  define CORE_EXPORT Q_DECL_EXPORT
#else
#  define CORE_EXPORT Q_DECL_IMPORT
#endif




#endif // GLOBAL_GLOBAL_H
