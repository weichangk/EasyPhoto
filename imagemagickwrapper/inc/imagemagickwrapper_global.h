/*
 * @Author: weick
 * @Date: 2023-12-22 23:28:10
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-22 23:42:38
 */

#pragma once

#ifdef WIN32

#ifdef IMAGEMAGICKWRAPPER_LIB
#define IMAGEMAGICKWRAPPER_EXPORT __declspec(dllexport)
#else
#define IMAGEMAGICKWRAPPER_EXPORT __declspec(dllimport)
#endif

#else

#define IMAGEMAGICKWRAPPER_EXPORT

#endif
