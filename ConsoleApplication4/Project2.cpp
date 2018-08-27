
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
auto average( T& t)
{
	std::remove_reference_t<std::remove_cv_t<decltype(t[0])>> sum = 0;
	
	for_each(begin(t),end(t),[&sum](auto i)
	{
		sum += i;
	}
	);
	return sum;
}

int main()
{
	int x[10]{ 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	cout << average(x) << endl;
	cout << average(v) << endl;
}
