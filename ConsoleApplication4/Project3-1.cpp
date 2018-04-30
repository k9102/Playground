#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <array>
#include <cassert>
#include <algorithm>
#include <memory>
#include <string>
using namespace std;

#include <iostream>
#include <list>
using namespace std;

template<typename T> class Queue :private list<T>
{
public:
	void Push(T v) { 
		list<T>::push_back(v);
	}
	T Pop() { 
		T  v = list<T>::front();
		list<T>::pop_front();
		return v;
	}
};
int main()
{
	Queue<int> q;
	q.Push(10);
	q.Push(20);
	cout << q.Pop() << endl; // 10
	cout << q.Pop() << endl; // 20
}