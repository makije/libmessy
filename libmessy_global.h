#ifndef LIBMESSY_GLOBAL_H
#define LIBMESSY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBMESSY_LIBRARY)
#  define LIBMESSYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBMESSYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBMESSY_GLOBAL_H
