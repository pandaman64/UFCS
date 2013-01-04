#ifndef FUNCTION_WRAPPER_HEADER
#define FUNCTION_WRAPPER_HEADER

#include <utility>

#define FUNCTION_WRAPPER(func_name,wrapper_name) \
	struct wrapper_name{\
		template<typename ...Args>\
		auto operator ()(Args&& ...args)\
		->decltype(func_name(std::forward<Args>(args)...)){\
			return func_name(std::forward<Args>(args)...);\
		}\
	}

#endif
