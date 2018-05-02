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

#include <gsl/gsl>


void show(gsl::span<int> s)
{
	for (const auto &i : s)
	{
		cout << i << "\n";
	}
}
#include <chrono>
#include <ctime>
int main()
{
	int data[10] = { 1,2,3,4,5,6,7,8,9,0 };
	show(data);

	vector<int> v(10);

	copy(begin(v),end(v),data);
}
