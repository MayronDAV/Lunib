#pragma once


// std
#include <iostream>
#include <format>



namespace Lunib
{
	enum class LogType
	{
		TRACE = 0,
		INFO,
		WARN,
		ERROR,
		FATAL
	};

	inline std::string LogTypeToString(LogType p_type)
	{
		switch (p_type)
		{
			case LogType::TRACE:    return "TRACE";
			case LogType::INFO:     return "INFO ";
			case LogType::WARN:     return "WARN ";
			case LogType::ERROR:    return "ERROR";
			case LogType::FATAL:    return "FATAL";
			default:                return "NONE ";
		}
	}


} // Lunib


#ifndef LUNIB_DISABLE_LOG
	#define _YUNIB_LOGGER2(type, fmt)                                                      \
	{                                                                                     \
		std::cout << "[" << Lunib::LogTypeToString(type) << "]: " << fmt << "\n";      	  \
	}

	#define _YUNIB_LOGGER3(type, fmt, ...)                                                 \
	{                                                                                     \
		std::string _messg = std::format(fmt, __VA_ARGS__);                               \
		std::cout << "[" << Lunib::LogTypeToString(type) << "]: " << _messg << "\n";      \
	}

	#define _LOGGER_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define _LOGGER_GET_MACRO(...) EXPAND_MACRO(_LOGGER_GET_MACRO_NAME(__VA_ARGS__, _YUNIB_LOGGER3, _YUNIB_LOGGER2))
	#define _YUNIB_LOGGER(type, ...) EXPAND_MACRO(_LOGGER_GET_MACRO(__VA_ARGS__)(type, __VA_ARGS__))

	#define LTRACE(...)			_YUNIB_LOGGER(Lunib::LogType::TRACE, __VA_ARGS__);
	#define LINFO(...)	      	_YUNIB_LOGGER(Lunib::LogType::INFO, __VA_ARGS__);
	#define LWARN(...)			_YUNIB_LOGGER(Lunib::LogType::WARN, __VA_ARGS__);
	#define LERROR(...)			_YUNIB_LOGGER(Lunib::LogType::ERROR, __VA_ARGS__);
	#define LFATAL(...)		    _YUNIB_LOGGER(Lunib::LogType::FATAL, __VA_ARGS__);
#else
	#define LTRACE(...)
	#define LINFO(...)
	#define LWARN(...)
	#define LERROR(...)
	#define LFATAL(...)
#endif

