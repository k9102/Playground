#pragma warning(suppress : 4996)
#include <iostream>
#include <algorithm>
#include <array>


using namespace std;
int main()
{
	int x[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int y[10] = { 0 };

	copy_if(begin(x), end(x), rbegin(y), [](auto n) { return n % 2 == 0; });
	for (auto n : y)
		cout << n << endl;
}
// 출력 결과 : 0, 0, 0, 0, 0, 10, 8, 6, 4, 2
