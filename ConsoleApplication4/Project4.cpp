#include <iostream>
#include <string>

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
	~People() { DBGOUT(__FUNCSIG__); }
	People &operator=(const People &p) noexcept{
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

	void print() const
	{
		cout << "-----------" << endl;
		cout << name << endl; 
		cout << addr << endl;
		cout << age << endl;
	}
};

#define MAX 10

int main()
{
	// (3)번 과제에서 만든 People을 사용하세요.
	// 1. People을 힙에 10개 생성해 보세요..
	// People{"홍길동", "서울", 20} 으로 초기화 하세요..
	// 힌트) 메모리 할당과 생성자 호출을 분리 하세요
	// 2. 위에서 만드는 배열(버퍼)를 20개 키워 보세요..
	// A. 20개 버퍼를 새로 할당하고
	// B. 기존에 버퍼의 내용을 새로운 버퍼에 옮기세요.
	// move 생성자에 예외가 없다면 move 생성자로,
	// 예외가 있다면 복사 생성자로 옮기세요
	// C. 버퍼의 새로운 공간은 {"unknwon", "unknown", 0} 으로 초기화 하세요
	// 3. 새로운 버퍼의 새용을 출력하세요.
	// 4. 버퍼을 줄이지는 말고 버퍼 끝에 있는 3개 객체를 파괴(명시적 소멸자 호출)해보세요.


	People *p1 = (People *)operator new(sizeof(People) * 10);

	for (int i = 0; i < 10; i++)
	{
		new(p1 + i) People{ "홍길동", "서울", 20 };
	}

	People *p2 = (People *)operator new(sizeof(People) * 20);
	
	for (int i = 0; i < 10; i++)
	{
		new(p2 + i) People{ move_if_noexcept(p1[i]) };
	}

	for (int i = 10; i < 20; i++)
	{
		new(p2 + i) People{ "unknwon", "unknown", 0 };
	}

	for (int i = 0; i < 20; i++)
	{
		p2[i].print();
	}

	for (int i = 0; i < 3; i++)
	{
		p2[17+i].~People();
	}
}