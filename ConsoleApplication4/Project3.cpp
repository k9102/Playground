#include <string>
#include <iostream>

using namespace std;
#define DBGOUT(line)   cout << line << endl;
using namespace std;
class People
{
	string name;
	string addr;
	int age;
public:
	People(string n, string add, int a) : name(n), addr(add), age(a) {}
	// 복사 생성자, 대입연산자, Move 생성자, Move 대입연산자를 만드세요..
	// 실행 여부를 확인하기 위해 logging 해주세요
	People(const People &p) : name(p.name), addr(p.addr), age(p.age) { DBGOUT(__FUNCSIG__); }
	People(People &&p) : name(move(p.name)), addr(move(p.addr)), age(move(p.age)) { DBGOUT(__FUNCSIG__); }
	People &operator=(const People &p) { 
		DBGOUT(__FUNCSIG__);
		name = p.name;
		addr = p.addr;
		age = p.age;
	}
	People &operator=(People &&p) {
		DBGOUT(__FUNCSIG__);
		name = move(p.name);
		addr = move(p.addr);
		age = move(p.age);
	}
};
int main()
{
	People p1{ "홍길동", "서울", 20 };
	People p2 = p1; // copy
	People p3 = move(p1); // move
}