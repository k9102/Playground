#include <thread>
#include <functional>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <algorithm>
#include <map>
#include <sstream>
#include <queue>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::placeholders;


#include <chrono>
#include <ctime>

/*primary template*/
template<typename...T> struct ktuple;
template<typename F, typename...T> struct ktuple<F, T...>:public ktuple<T...>
{
	F value;
	ktuple(F f, T...args) :value(f), ktuple<T...>(args...) {};
};

/*recursion end condition*/
template<> class ktuple<>
{
};

/*primary template*/
template<int N, typename T> struct ktuple_element;
template<int N, typename F, typename...T> struct ktuple_element<N, ktuple<F, T...>>
{
	/* tuple type*/
	using ttype = typename ktuple_element< N - 1, ktuple<T...>>::ttype;
	/* element type*/
	using etype = typename ktuple_element< N - 1, ktuple<T...>>::etype;
};

/*recursion end condition*/
template<typename F, typename...T> struct ktuple_element<0, ktuple<F, T...>>
{
	using ttype = ktuple<F, T...>;
	using etype = F;
};

template<int N, typename...Arg>  
typename ktuple_element<N, ktuple<Arg...>>::etype&  
get(ktuple<Arg...> &t)
{
	return static_cast<typename ktuple_element<N, ktuple<Arg...>>::ttype &>(t).value;
};

int main()
{
	ktuple<int, double, short> t(1, 1.1, 3);

	cout << get<2>(t) <<endl;

	get<2>(t) = 6;

	cout << get<2>(t) << endl;
}
