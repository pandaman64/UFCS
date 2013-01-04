#ifndef PANLIB_ALGORITHM_HEADER
#define PANLIB_ALGORITHM_HEADER

#include <algorithm>
#include <cstddef>

#include "boost/range/algorithm.hpp"
#include "boost/range/numeric.hpp"
#include "make_ufcs_wrapper.h"

#define UFCS_WRAPPER(name) MAKE_UFCS_WRAPPER(name##_impl,name)

namespace panlib{
namespace algorithm{
	//map
	struct map_impl{
		template<typename T,typename F>
		typename std::remove_reference<T>::type operator ()(T && seq,F &&f){
			typename std::remove_reference<T>::type ret(seq.size());
			boost::transform(seq,begin(ret),f);
			return ret;
		}
	};
	UFCS_WRAPPER(map);
	
	//reduce
	struct reduce_impl{
		template<typename Seq,typename F,typename T>
		typename std::remove_reference<T>::type operator ()(Seq &&seq,F &&f,T &&obj = T()){
			return boost::accumulate(seq,obj,f);
		}
	};
	UFCS_WRAPPER(reduce);

	//filter
	struct filter_impl{
		template<typename Seq,typename T>
		typename std::remove_reference<Seq>::type operator ()(Seq &&seq,T &&t){
			typename std::remove_reference<Seq>::type ret;
			for(auto &it : seq){
				ret.push_back(it);
			}
			return ret;
		}
	};
	UFCS_WRAPPER(filter);

	//skip
	struct skip_impl{
		template<typename Seq>
		typename std::remove_reference<Seq>::type operator ()(Seq &&seq,std::size_t n){
			using std::begin;
			using std::end;

			auto it = begin(seq),_e = end(seq);
			for(;n-- && it != _e;++it);
			typename std::remove_reference<Seq>::type ret(std::distance(it,_e));
			std::copy(it,_e,begin(ret));
		}
	};
	UFCS_WRAPPER(skip);
} //namespace algorithm
} //namespace panlib
#endif