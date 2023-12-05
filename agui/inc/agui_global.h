/*
 * @Author: weick
 * @Date: 2023-12-05 22:52:15
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:52:15
 */

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
