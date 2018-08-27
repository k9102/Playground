#include <iostream>
using namespace std;

int count_percent(const char *fmt)
{
	int cnt = 0;
	while (1)
	{
		int res = strncmp(fmt, "%d", 2);
		if (res != 0)
		{
			break;
		}
		cnt++;
		fmt += 2;
	}

	return cnt;
}

template<typename...Types>
void cpp_print(const char *fmt, Types...args)
{
	if (count_percent(fmt) == sizeof...(args))
	{
		printf(fmt, args...);
	}
	else
	{
		throw "argument mismatch";
	}
}

int main()
{
	printf("%d\n", 1, 2, 3); // 인자가 너무 많습니다.
	printf("%d%d\n", 1); // 인자가 부족 합니다.
						 // cpp_print를 만들어 보세요
	try
	{
		cpp_print("%d\n", 1, 2, 3); // 예외가 나오게 하세요
		cpp_print("%d%d\n", 1); // 예외가 나오게 하세요
	}
	catch (...)
	{
		cout << "예외 발생" << endl;
	}
}