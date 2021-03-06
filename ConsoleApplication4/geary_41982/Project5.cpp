


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


#define NEW_THREAD true

class NotificationCenter
{
public:
	using HANDLER = function<void(void*)>;
	using PARAM = tuple<int, bool, HANDLER>;

	void Register(string event, HANDLER func, int priority, bool is_thread = false)
	{
		auto& vec = event_handler[event];
			
	    vec.push_back(make_tuple(priority, is_thread,func));
		sort(begin(vec), end(vec), [](PARAM& l, PARAM& r) { return get<0>(l) > get<0>(r); });
	}
	
	void Notify(string event,void *param)
	{
		for (auto [pri,is_thread,handler] : event_handler[event])
		{
			if (is_thread)
			{
				thread Thr(handler,param);
				Thr.detach();
			}
			else
			{
				handler(param);
			}
		}
	}
private:
	map< string, vector<PARAM>> event_handler;


};

mutex m;
void foo(void* p, string name)
{
	{
	lock_guard<mutex> mu(m);
	cout << name << " : " << this_thread::get_id() << endl;
	}
	this_thread::sleep_for(3s);

	lock_guard<mutex> mu(m);
	cout << name << " end" << endl;
}
int main()
{
	NotificationCenter nc;
	// Register 의 3번째 인자는 우선순위, 4번째 인자는 스레드사용여부 입니다.
	// 우선순위 1일 제일 낮고, 3일 제일 높다가 가정합니다.
	// NEW_THREAD 지정시 해당 함수는 새로운 스레드로 동작해야 합니다.
	nc.Register("TEST_EVENT", bind(&foo, _1, "one"s), 1);
	nc.Register("TEST_EVENT", bind(&foo, _1, "two"s), 2, NEW_THREAD);
	nc.Register("TEST_EVENT", bind(&foo, _1, "three"s), 3);
	nc.Notify("TEST_EVENT", (void*)0); // 등록된 순서가 아닌 우선순위가
									   // 높은 순서로 실행되게 해주세요
									   // NEW_THREAD 옵션을 가진 경우. 새로운
									   // 스레드로 해당 함수를 동작되게 해주세요.
	getchar();
}
