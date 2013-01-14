#ifndef PANLIB_COPY_HEADER
#define PANLIB_COPY_HEADER

#include <type_traits>
#include <utility>

#include "ufcs.h"
#include "make_ufcs_wrapper.h"

namespace panlib{
namespace algorithm{

template<typename Range>
struct Copy{
private:
	Range range;

public:
	typedef typename std::remove_reference<decltype(range.front())>::type value_type;
	
	Copy(Range r) : range(r){}

	void pop_back(){
		range.pop_back();
	}

	value_type front(){
		return range.front();
	}

	bool empty() const{
		return range.empty();
	}
};

struct copy_algorithm{
	template<typename Range>
	Copy<Range> operator ()(Range &&range){
		return { std::forward<Range>(range) };
	}
};
MAKE_UFCS_WRAPPER(copy_algorithm,copy);

} //namespace algorithm
} //namespace panlib

#endif
