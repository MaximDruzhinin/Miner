#ifndef DRAW_GLOBAL_H
#define DRAW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DRAW_LIBRARY)
#  define DRAW_EXPORT Q_DECL_EXPORT
#else
#  define DRAW_EXPORT Q_DECL_IMPORT
#endif


#endif // DRAW_GLOBAL_H
