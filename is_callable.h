#ifndef PANLIB_IS_CALLABLE_HEADER
#define PANLIB_IS_CALLABLE_HEADER

#include <type_traits>

namespace panlib{ namespace detail{
	template<typename T,typename ...Args,typename R = decltype(T()(std::declval<Args>()...))>
	std::true_type check_callable(int);
	template<typename ...Args>
	std::false_type check_callable(long);
} //namespace detail

	template<typename ...Args>
	struct is_callable : decltype(detail::check_callable<Args...>(0)){
	};
} //namespace panlib



#endif
