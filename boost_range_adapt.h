#ifndef BOOST_RANGE_ADAPT_HEADER
#define BOOST_RANGE_ADAPT_HEADER

#include "boost/range/algorithm.hpp"
#include "boost/preprocessor.hpp"

#include "function_wrapper.h"
#include "make_ufcs_wrapper.h"

#define BOOST_RANGE_ALGO_WRAP(...) BOOST_PP_REPEAT(BOOST_PP_TUPLE_SIZE((__VA_ARGS__)),BOOST_RANGE_ALGO_WRAP_FUNC,(__VA_ARGS__))
#define BOOST_RANGE_ALGO_WRAP_FUNC(z,n,t) BOOST_RANGE_ALGO_WRAP_IMPL(BOOST_PP_TUPLE_ELEM(n,t))
#define BOOST_RANGE_ALGO_WRAP_IMPL(name) FUNCTION_WRAPPER(boost::name,BOOST_PP_CAT(name,_impl));MAKE_UFCS_WRAPPER(BOOST_PP_CAT(name,_impl),name);

namespace panlib{
namespace algorithm{
	BOOST_RANGE_ALGO_WRAP(\
		adjacent_find,\
		binary_search,\
		count,\
		count_if,\
		equal,\
		equal_range,\
		for_each,\
		find,\
		find_end,\
		find_first_of,\
		find_if,\
		lexicographical_compare,\
		lower_bound,\
		max_element,\
		min_element,\
		mismatch,\
		search,\
		search_n,\
		upper_bound\
	)

}
}

#endif
