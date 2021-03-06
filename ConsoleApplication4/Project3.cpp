



#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

struct People
{
	string name;
	int age;
	People(string n, int a) : name(n), age(a) {}
	void Dump() const { cout << name << "(" << age << ")" << endl; }
};


template<typename T> void show(T v)
{
	for (auto &i : v)
	{
		i->Dump();
	}
}

int main()
{
	vector<shared_ptr<People>> v;
	// ("kim", 10), ("lee", 15), ("park", 5), ("jung", 20), ("choi", 12) 를 v에 넣어주세요.
		// 이름순으로 정렬해서 출력해 보세요
		// 나이순으로 정렬해서 출력해 보세요.
	v.emplace_back(make_shared<People>("kim", 10));
	v.emplace_back(make_shared<People>("lee", 15));
	v.emplace_back(make_shared<People>("park", 5));
	v.emplace_back(make_shared<People>("jung", 20));
	v.emplace_back(make_shared<People>("choi", 12));

	sort(begin(v), end(v), [](auto& l, auto &r) { return l->name < r->name; });

	show(v);


	cout << "--------------------------"s << endl;
	sort(begin(v), end(v), [](auto& l, auto &r) { return l->age < r->age; });

	show(v);
}
