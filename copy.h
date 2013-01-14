#ifndef PANLIB_COPY_HEADER
#define PANLIB_COPY_HEADER

#include <type_traits>

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

} //namespace algorithm
} //namespace panlib

#endif
