#pragma once
#include "../agui/inc/abasewidget.h"

#ifdef WIN32

#ifdef IMAGEKIT_LIB
#define IMAGEKIT_EXPORT __declspec(dllexport)
#else
#define IMAGEKIT_EXPORT __declspec(dllimport)
#endif

#else

#define IMAGEKIT_EXPORT

#endif
