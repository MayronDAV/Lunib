#pragma once

#if defined(LUNIB_WINDOWS)
	#ifdef LUNIB_EXPORT
		#define LUNIB_API __declspec(dllexport)
	#else
		#define LUNIB_API __declspec(dllimport)
	#endif
#elif defined(LUNIB_LINUX) || defined(LUNIB_APPLE)
    #ifdef LUNIB_EXPORT
        #define LUNIB_API __attribute__((visibility("default")))
    #else
        #define LUNIB_API
    #endif
#else
	#define LUNIB_API
	#error Currently only support windows, linux or macOS !
#endif

#define EXPAND_MACRO(x) x
#define STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

// std
#include <cassert>

#include "log.h"