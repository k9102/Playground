
#include <type_traits>

using namespace std;


#if 1
template<typename T> typename enable_if<is_integral<T>::value,T>::type Sum(T a, T b)
{
	return a + b;
}

#else
using namespace std;
template<typename T> T Sum(T a, T b)
{
	static_assert(is_integral<T>::value == true, "type is not integral");
	return a + b;
}
#endif
int main()
{
	int n1 = 5, n2 = 10;
	short s1 = 5, s2 = 10;
	double d1 = 3.4, d2 = 1.2;
	Sum(n1, n2); // ok
	Sum(s1, s2); // ok
	Sum(d1, d2); // error가 나와야 합니다.
}