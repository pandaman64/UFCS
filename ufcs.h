#ifndef UFCS_HEADER
#define UFCS_HEADER

#include <tuple>
#include <utility>
#include <cstddef>
#include <type_traits>

#include "is_callable.h"

template<std::size_t...>
struct index_tuple{};

template<std::size_t N,typename Indices>
struct make_index_tuple_impl;
template<std::size_t N,std::size_t ...Indices>
struct make_index_tuple_impl<N,index_tuple<Indices...>>{
	typedef index_tuple<N,Indices...> type;
};

template<std::size_t Beg,std::size_t End>
struct make_index_tuple{
	typedef typename make_index_tuple_impl<Beg,typename make_index_tuple<Beg + 1,End>::type>::type type;
};
template<std::size_t End>
struct make_index_tuple<End,End>{
	typedef index_tuple<End> type;
};

namespace panlib{
namespace ufcs{
namespace detail{
	template<typename F,typename ...Args>
	struct arguments_holder{
		arguments_holder(Args ...args) : arguments(args...){}
		std::tuple<Args...> arguments;
	};
	template<typename F,typename Seq,typename ...Args,std::size_t ...Indices>
	auto call_impl(F &&f,Seq &&seq,std::tuple<Args...> &&args,index_tuple<Indices...>)
	->decltype(f(std::forward<Seq>(seq),std::forward<Args>(std::get<Indices>(args))...)){
		return f(std::forward<Seq>(seq),std::forward<Args>(std::get<Indices>(args))...);
	}

	template<typename Seq,typename F,typename ...Args,typename std::enable_if<sizeof...(Args)>::type* = nullptr>
	auto operator ->*(Seq &&seq,arguments_holder<F,Args...> &&holder)
	->decltype(call_impl(F(),std::forward<Seq>(seq),std::forward<std::tuple<Args...>>(holder.arguments),typename make_index_tuple<0,sizeof...(Args) - 1>::type())){
		return call_impl(F(),std::forward<Seq>(seq),std::forward<std::tuple<Args...>>(holder.arguments),typename make_index_tuple<0,sizeof...(Args) - 1>::type());
	}
	template<typename Seq,typename F,typename ...Args,typename std::enable_if<!sizeof...(Args)>::type* = nullptr>
	auto operator ->*(Seq &&seq,arguments_holder<F,Args...> &&holder)
	->decltype(call_impl(F(),std::forward<Seq>(seq),std::forward<std::tuple<Args...>>(holder.arguments),index_tuple<>())){
		return call_impl(F(),std::forward<Seq>(seq),std::forward<std::tuple<Args...>>(holder.arguments),index_tuple<>());
	}
}
template<typename T>
struct wrapper{
	template<typename ...Args,typename std::enable_if<!is_callable<T,Args...>{}>::type* = nullptr>
	detail::arguments_holder<T,Args...> operator ()(Args&& ...args) const{
		return { std::forward<Args>(args)... };
	}
	template<typename ...Args,typename std::enable_if<is_callable<T,Args...>{}>::type* = nullptr>
	auto operator ()(Args&& ...args) const
	-> decltype(T()(std::forward<Args>(args)...)){
		return T()(std::forward<Args>(args)...);
	}
};
} //namespace ufcs
} //namespace panlib

#endif