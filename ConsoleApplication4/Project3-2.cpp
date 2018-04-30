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

template<typename T,template<typename> class C> class Queue
{
public:
	Queue(C<T> *data): data_(data) {};
	void Push(T v) { 
		data_->push_back(v);
	}
	T Pop() { 
		T  v = data_->front();
		data_->pop_front();
		return v;
	}
private:
	C<T> *data_;

};
int main()
{
	list<int> l;
	Queue<int,list> q(&l);
	q.Push(10);
	q.Push(20);
	cout << q.Pop() << endl; // 10
	cout << q.Pop() << endl; // 20
}