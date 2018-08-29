#pragma once

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

template <class TList> struct Length;
template <> struct Length<NullType>
{
	enum { value = 0 };
};
template <class T, class U> struct Length< Typelist<T, U> >
{
	enum { value = 1 + Length<U>::value };
};



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



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, size_t N /*position*/> struct TypeAt;
template<typename H, typename T> struct TypeAt<Typelist<H, T>, 0>
{
	using Result = H;
};
template<typename H, typename T, size_t N> struct TypeAt<Typelist<H, T>, N>
{
	using Result = typename TypeAt<T, N - 1>::Result;
};



template<typename T, typename ST /*search type*/> struct IndexOf;
template<typename T, typename ST> struct IndexOf<Typelist<ST, T>, ST>
{
	static constexpr int value = 0;
};
template<typename H, typename T, typename ST> struct IndexOf<Typelist<H, T>, ST>
{
	static constexpr int value = 1 + IndexOf<T, ST>::value;
};



template<typename T, typename ET /*erase type*/> struct Erase;
template<typename T, typename ET> struct Erase<Typelist<ET, T>, ET>
{
	using Result = T;
};
template<typename H, typename T, typename ET> struct Erase<Typelist<H, T>, ET>
{
	using Result = Typelist<H, typename Erase<T, ET>::Result>;
};

template<typename T, typename ST /* search type */, typename RT /*replace type*/> struct Replace;
template<typename T, typename ST, typename RT> struct Replace<Typelist<ST, T>, ST, RT>
{
	using Result = Typelist<RT, T>;
};
template<typename H, typename T, typename ST, typename RT> struct Replace<Typelist<H, T>, ST, RT>
{
	using Result = Typelist<H, typename Replace<T, ST, RT>::Result>;
};