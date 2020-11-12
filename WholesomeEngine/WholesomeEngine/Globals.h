#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>

namespace DEBUG
{
	inline std::stringstream out;

	template<typename T, typename... Params>
	void LOG(std::string str, T arg)
	{
		if constexpr(std::is_null_pointer_v<T>)
			out << str << std::endl;
		else
			out << str.substr(0, str.find_first_of('%')) << arg << std::endl;

#if defined(_DEBUG)
		OutputDebugString(out.str().c_str());
#endif
		out.clear();
		out.str(std::string());
	}

	template<typename T, typename... Params>
	void LOG(std::string str, T arg, Params... args)
	{
		out << str.substr(0, str.find_first_of('%')) << arg;
		LOG(str.substr(str.find_first_of('%') + 1), args...);
	}
}

#endif // !_GLOBALS_H_



