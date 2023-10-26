#pragma once
#include "../awidget/inc/awidget.h"

#ifdef WIN32

#ifdef AGUI_LIB
#define AGUI_EXPORT __declspec(dllexport)
#else
#define AGUI_EXPORT __declspec(dllimport)
#endif

#else

#define AGUI_EXPORT

#endif
