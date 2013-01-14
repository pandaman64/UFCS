#ifndef PANLIB_RANGE_VALUE_TYPE_HEADER
#define PANLIB_RANGE_VALUE_TYPE_HEADER

#include <type_traits>

namespace panlib{
namespace range{

	template<typename Range>
	struct range_value_type{
		typedef typename std::remove_reference<decltype(std::declval<Range>().front())>::type type;
	};

} //namespace range
} //namespace panlib

#endif
