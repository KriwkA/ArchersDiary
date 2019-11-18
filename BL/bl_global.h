#pragma once
#include <QtCore/qglobal.h>

#if defined(BL_LIBRARY)
#  define BL_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define BL_SHARED_EXPORT Q_DECL_IMPORT
#endif

