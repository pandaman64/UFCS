#include "ufcs.h"
#include "map.h"

#include <iostream>
#include <initializer_list>
#include <vector>
#include <iterator>
#include <algorithm>

struct map_impl{
	template<typename T,typename F>
	typename std::remove_reference<T>::type operator ()(T && seq,F &&f){
		using std::begin;
		using std::end;
		typename std::remove_reference<T>::type ret(seq.size());
		std::transform(begin(seq),end(seq),begin(ret),f);
		return ret;
	}
};
MAKE_UFCS_WRAPPER(map_impl,map);

struct print_impl{
	template<typename T>
	void operator ()(T &&seq){
		for(auto &it : seq){
			std::cout << it << std::endl;
		}
	}
};
MAKE_UFCS_WRAPPER(print_impl,print);

int main(){
	auto l = {1,2,3,4,5,6};
	std::vector<int> v(l.begin(),l.end());
	
	for(auto it : panlib::algorithm::map(v,[](int i){ std::cout << "hoge"; return i*5; })){
		std::cout << it << std::endl;
	}
	for(auto &it : std::vector<double>(v.begin(),v.end())){
		std::cout << it << std::endl;
	}

	//ｶｯｸｲｲ...
	v->*map([](int i){ return i*2; })->*print();
	
	//普通にも呼び出せる
	print(v);
	print(map(v,[](int i){ return -i; }));
	
	//混ぜてもOK
	map(v,[](int i){ return i * i; })->*print();
	return 0;
}
