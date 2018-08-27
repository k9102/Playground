
#include <iostream>
using namespace std;

template<typename T> class has_virtual_function
{
	class nested :public T
	{
		virtual void nested_f() {};
	};
public:
	static constexpr bool value = sizeof(T) == sizeof(nested);

};

template<typename T> void foo(T& c)
{
	if (has_virtual_function<T>::value)
		cout << "T has virtual function" << endl;
	else
		cout << "T has not virtual function" << endl;
}


class nv_class
{
};

class v_class
{
	virtual void f() {};
};

int main()
{
	v_class vc;
	nv_class nvc;
	foo(vc);
	foo(nvc);
}