

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



struct NullType {};
template <class T, class U> struct Typelist
{
	typedef T Head;
	typedef U Tail;
};

Typelist<int, NullType> t1; // 한개의 타입을 보관합니다.
Typelist<int, Typelist<double, NullType>> t2; // 2개의 타입을 보관합니다.
Typelist<int, Typelist<double, Typelist<char, NullType>>> t3; // 3개의 타입 보관


template<typename T> class xtuple // xtuple은 인자가 하나밖에 없습니다.
{
};

int main_a()
{
	xtuple<int> t1; // ok
					// xtuple<int, char> t2; // error. xtuple에는 타입을 하나만 보낼수 있습니다.
	xtuple<Typelist<int, Typelist<char, NullType>>> t2; // ok.. TypeList를 사용하면
														// 타입을 몇개 라도 보낼수 있습니다.
	return true;
}


template < typename T1 = NullType, typename T2 = NullType, typename T3 = NullType,
	typename T4 = NullType, typename T5 = NullType, typename T6 = NullType,
	typename T7 = NullType, typename T8 = NullType, typename T9 = NullType,
	typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
	typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
	typename T16 = NullType, typename T17 = NullType, typename T18 = NullType >
	struct MakeTypelist
{
private:
	typedef typename MakeTypelist<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
		T14, T15, T16, T17, T18 >::Result TailResult;
public:
	typedef Typelist<T1, TailResult> Result;
};

template<> struct MakeTypelist<>
{
	typedef NullType Result;
};

int main_b()
{
	// myType : TypeList<int, TypeList<char, TypeList<double, NullType>>
	typedef MakeTypelist<int, char, double>::Result myType;
	cout << typeid(myType).name() << endl;
	return true;
}



template <class TList> struct Length;
template <> struct Length<NullType>
{
	enum { value = 0 };
};
template <class T, class U> struct Length< Typelist<T, U> >
{
	enum { value = 1 + Length<U>::value };
};
int main_c()
{
	typedef MakeTypelist<int, char, double>::Result myType;
	cout << Length<myType>::value << endl; //3
	return true;
}


template <class TList, class T> struct Append;
template <> struct Append<NullType, NullType>
{
	typedef NullType Result;
};
template <class T> struct Append<NullType, T>
{
	typedef Typelist<T, NullType> Result;
};
template <class Head, class Tail>
struct Append<NullType, Typelist<Head, Tail> >
{
	typedef Typelist<Head, Tail> Result;
};
template <class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>, T>
{
	typedef Typelist<Head,
		typename Append<Tail, T>::Result>
		Result;
};


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

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T,size_t N /*position*/> struct TypeAt;
template<typename H,typename T> struct TypeAt<Typelist<H, T>, 0>
{
	using Result = H;
};
template<typename H, typename T,size_t N> struct TypeAt<Typelist<H, T>, N>
{
	using Result = typename TypeAt<T,N-1>::Result;
};



template<typename T, typename ST /*search type*/> struct IndexOf;
template<typename T, typename ST> struct IndexOf<Typelist<ST, T>, ST>
{
	static constexpr int value = 0;
};
template<typename H, typename T, typename ST> struct IndexOf<Typelist<H, T>, ST>
{
	static constexpr int value = 1+ IndexOf<T, ST>::value;
};



template<typename T, typename ET /*erase type*/> struct Erase;
template<typename T, typename ET> struct Erase<Typelist<ET, T>, ET>
{
	using Result = T;
};
template<typename H, typename T, typename ET> struct Erase<Typelist<H, T>, ET>
{
	using Result = Typelist<H, typename Erase<T,ET>::Result>;
};



template<typename T, typename ST /* search type */,typename RT /*replace type*/> struct Replace;
template<typename T, typename ST, typename RT> struct Replace<Typelist<ST, T>, ST,RT>
{
	using Result = Typelist<RT, T>;
};
template<typename H, typename T,typename ST, typename RT> struct Replace<Typelist<H, T>, ST,RT>
{
	using Result = Typelist<H, typename Replace<T,ST,RT>::Result>;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
int main()
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
}