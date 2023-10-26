#pragma once
#include <QtCore/qobject.h>
#include <QtCore/qglobal.h>

#ifdef WIN32

#ifdef ACORE_LIB
#define ACORE_EXPORT __declspec(dllexport)
#else
#define ACORE_EXPORT __declspec(dllimport)
#endif

#else

#define ACORE_EXPORT

#endif
