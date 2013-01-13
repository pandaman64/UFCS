#ifndef PANLIB_MAP_HEADER
#define PANLIB_MAP_HEADER

#include <type_traits>
#include <iterator>
#include "make_ufcs_wrapper.h"

namespace panlib{
namespace algorithm{

template<typename Seq,typename F>
struct MapIterator{
	typedef typename std::remove_reference<Seq>::type sequence_type;
	typedef typename sequence_type::iterator undering_iterator;
	typedef MapIterator<Seq,F> this_type;

	MapIterator(undering_iterator it,F f) : iterator(it),func(f){
	}

	auto operator ++()
	->decltype(++std::declval<undering_iterator>()){
		return ++iterator;
	}
	auto operator ++(int)
	->decltype(std::declval<undering_iterator>()++){
		return iterator--;
	}
	auto operator --()
	->decltype(--std::declval<undering_iterator>()){
		return --iterator;
	}
	auto operator --(int)
	->decltype(std::declval<undering_iterator>()--){
		return iterator--;
	}

	auto operator *() const
	->decltype(std::declval<F>()(*std::declval<undering_iterator>())){
		return func(*iterator);
	}

	friend bool operator ==(this_type const& lhs,this_type const& rhs){
		return lhs.iterator == rhs.iterator;
	}
	friend bool operator !=(this_type const& lhs,this_type const& rhs){
		return lhs.iterator != rhs.iterator;
	}
	
private:
	undering_iterator iterator;
	F func;
};

template<typename Seq,typename F>
struct Map{
	typedef MapIterator<Seq,F> iterator;

	Map(Seq seq,F f) : sequence(seq),func(f){
	}

	iterator begin(){
		using std::begin;
		return { begin(sequence),func };
	}
	iterator end(){
		using std::end;
		return { end(sequence),func };
	}

private:
	mutable Seq sequence;
	mutable F func;
};

struct map_invoker{
	template<typename Seq,typename F>
	Map<Seq,F> operator ()(Seq &&seq,F &&f){
		return { std::forward<Seq>(seq),std::forward<F>(f) };
	}
};

MAKE_UFCS_WRAPPER(map_invoker,map);

} //namespace algorithm
} //namespace panlib

#endif
