#ifndef PANLIB_IMMEDIATE_COPY_HEADER
#define PANLIB_IMMEDIATE_COPY_HEADER

#include <utility>
#include <list>
#include <type_traits>

#include "ufcs.h"
#include "make_ufcs_wrapper.h"

#include "range_value_type.h"

namespace panlib{
namespace algorithm{

	template<typename Range,typename Container = std::vector<typename range::range_value_type<Range>::type>>
	struct ImmediateCopy{
	private:
		typedef typename range::range_value_type<Range>::type value_type;
		typedef typename Container::iterator iterator_type;
		Container container;
		typename range::choose_iterator_range<iterator_type>::type range;

	public:
		ImmediateCopy(Range r) : range(iterator_type(),iterator_type()){
			while(!r.empty()){
				container.push_back(r.front());
				r.pop_front();
			}
			range = range::all(container);
		}

		void pop_front(){
			range.pop_front();
		}

		value_type front(){
			return range.front();
		}

		bool empty() const{
			return range.empty();
		}
	};

	struct immediate_copy_algorithm{
		template<typename Range>
		ImmediateCopy<typename std::remove_reference<Range>::type> operator ()(Range &&range){
			return { std::forward<Range>(range) };
		}
	};
	MAKE_UFCS_WRAPPER(immediate_copy_algorithm,immediate_copy);

} //namespace algorithm
} //namespace panlib

#endif
