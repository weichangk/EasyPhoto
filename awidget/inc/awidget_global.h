#pragma once
#include <QtWidgets/qwidget.h>
#include <QtCore/qglobal.h>

#ifdef WIN32

#ifdef AWIDGET_LIB
#define AWIDGET_EXPORT __declspec(dllexport)
#else
#define AWIDGET_EXPORT __declspec(dllimport)
#endif

#else

#define AWIDGET_EXPORT

#endif
