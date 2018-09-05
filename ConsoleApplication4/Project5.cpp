

#include <iostream>
#include <algorithm> // sort 
#include <json/json.h>
#include <sstream>

#include "typelist.h"

using namespace std;


int main_a()
{
	xtuple<int> t1; // ok
					// xtuple<int, char> t2; // error. xtuple에는 타입을 하나만 보낼수 있습니다.
	xtuple<Typelist<int, Typelist<char, NullType>>> t2; // ok.. TypeList를 사용하면
														// 타입을 몇개 라도 보낼수 있습니다.
	return true;
}


int main_b()
{
	// myType : TypeList<int, TypeList<char, TypeList<double, NullType>>
	typedef MakeTypelist<int, char, double>::Result myType;
	cout << typeid(myType).name() << endl;
	return true;
}


int main_c()
{
	typedef MakeTypelist<int, char, double>::Result myType;
	cout << Length<myType>::value << endl; //3
	return true;
}
int main_d()
{
	typedef MakeTypelist<int, char, double>::Result myType;
	// myType 끝에 short를 추가한 타입을 만듭니다.
	typedef Append<myType, short>::Result myType2;
	cout << typeid(myType2).name() << endl;
	// myType2 2개를 결합한 타입을 만듭니다.
	typedef Append<myType2, myType2>::Result myType3;
	cout << Length<myType3>::value << endl; // 8
	return true;
}

int main_e()
{

	typedef MakeTypelist<int, char, double, short>::Result myType;
	// (1) TypeAt : N번째 타입이 무슨 타입인지 알아내는 템플릿 입니다.
	TypeAt<myType, 1>::Result n; // n은 char 타입이어야 합니다.
	cout << typeid(n).name() << endl;
								 // (2) IndexOf : 특정 타입이 몇번째 있는지 찾아 내는 템플릿입니다.
	
	cout << IndexOf<myType, double>::value << endl; // 2가 나와야 합니다.
													// (3) Erase : 특정 타입을 제거한 새로운 TypeList 만들기
											//최초 발견된것 하나만 제거
	typedef Erase<myType, char>::Result myType2;
	cout << typeid(myType2).name() << endl; // int, double, short 의 TypeList입니다.
										// (4) Replace : 특정 타입을 다른 타입으로 교체한 TypeList 만들기
	typedef Replace<myType, char, float>::Result myType3;
	cout << typeid(myType3).name() << endl; // int, float, double, short
	return true;
}

#include <tuple>

template<size_t...N>
struct Seq
{
};

template<size_t...N> struct GenSeqHelper;

template<size_t n,size_t...N> 
struct GenSeqHelper<n,N...>:GenSeqHelper<n-1,n-1,N...>
{
};

template<size_t...N> 
struct GenSeqHelper<0,N...>
{
	using  type = Seq<N...>;
};

template<size_t N>
struct GenSeq :GenSeqHelper<N>
{
};

template<typename TP> auto make_seq(const TP &tp)
{
	constexpr size_t N = tuple_size_v<TP>;
	return GenSeq<N>::type();
}


template<typename TP, size_t...N> void printp(TP &tp)
{
	printp_imp(tp, make_seq(tp));
}

template<typename TP, size_t...N> void printp_imp(TP &tp, Seq<N...>)
{
	int seq[] = { get<N>(tp)... };

	for (auto&i : seq)
		cout << i << endl;
}


int main()
{

	tuple<int, int, int,int,int> t{ 11,22,33,44,55 };

	printp(t);

	return true;
}