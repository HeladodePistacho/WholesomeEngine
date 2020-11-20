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

		OutputDebugString(out.str().c_str());

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

enum class ENGINE_STATUS
{
	FAIL,
	SUCCESS,
	FINISHED
};

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#endif // !_GLOBALS_H_



