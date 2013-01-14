#ifndef PANLIB_MAP_HEADER
#define PANLIB_MAP_HEADER

#include <utility>
#include "make_ufcs_wrapper.h"

namespace panlib{
namespace algorithm{

template<typename Range,typename F>
struct Map{
private:
	Range range;
	F func;

public:
	Map(Range r,F f) : range(r),func(f){
	}

	void pop_front(){
		range.pop_front();
	}

	auto front()
	->decltype(func(range.front())){
		return func(range.front());
	}

	bool empty() const{
		return range.empty();
	}
};

struct map_invoker{
	template<typename Range,typename F>
	Map<Range,F> operator ()(Range &&seq,F &&f){
		return { std::forward<Range>(seq),std::forward<F>(f) };
	}
};

MAKE_UFCS_WRAPPER(map_invoker,map);

} //namespace algorithm
} //namespace panlib

#endif
