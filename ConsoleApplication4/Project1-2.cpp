#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <array>
#include <cassert>
#include <algorithm>
#include <memory>
using namespace std;


typedef tuple<int, int, int> INPUT;
typedef tuple<int, int> RESULT;

class IGameStrategy
{
public:
	virtual INPUT GetInput(vector<pair<INPUT, RESULT>> hist) = 0;
};

class GameRandomStrategy:public IGameStrategy
{
public:
	virtual INPUT GetInput(vector<pair<INPUT, RESULT>> hist) override
	{
		INPUT i;
		int x = 0, y = 0, z = 0;
		do {
			x = rand() % 9 + 1;
			y = rand() % 9 + 1;
			z = rand() % 9 + 1;
		} while (x == y || y == z || x == z);
		return { x,y,z };
	}
};

class GameAiStrategy :public IGameStrategy
{
private:
	vector<int> GetRandom(size_t n)
	{
		vector<int> ran;
		assert(n < 10);

		int nums = 0;
		while (nums < n)
		{
			int r;
			r = rand() % n;
			bool isexist = any_of(begin(ran), end(ran), [r](auto n) {return r == n; });
			if (!isexist)
				ran.push_back(r);
			else
				continue;
			nums++;
		}

		return ran;
	}
public:
	virtual INPUT GetInput(vector<pair<INPUT, RESULT>> hist) override
	{
		enum { UNKNOWN, STRIKE, BALL };
		array<int, 9> old_status = { UNKNOWN };
		array<int, 9> status = { UNKNOWN };

		do
		{
			old_status = status;
			for (auto[input, result] : hist)
			{
				auto[strike, ball] = result;
				array<int, 3> l; tie(l[0], l[1], l[2]) = input;
				for (auto& v : l) { v = v - 1; };

				assert(strike + ball == 3); /* basic assumption*/
				assert(strike != 3);  /*Guessing is already completed*/

									  /*1.known(#3)*/
				if (strike == 0)
				{
					for (auto i : l) status[i] = BALL;
					continue;
				}

				int unknown_cnt = 0;
				int unknown_pos;
				for (auto i : l)
				{
					if (status[i] == UNKNOWN)
					{
						unknown_pos = i;
						unknown_cnt++;
					}
					else
					{
						if (status[i] == STRIKE) strike--;
					}
				}
				/*2. known(#2)*/
				if (unknown_cnt == 1)
				{
					status[unknown_pos] = strike == 0 ? BALL : STRIKE;
				}
			}
		} while (old_status != status);  /*loop until the status is not changed*/

		vector<int> ran;
		vector<int> known;
		for (auto i = 0; i < status.size(); i++) { if (status[i] == STRIKE) known.push_back(i); }

		if (size(known) == 3) return { known[0] + 1,known[1] + 1,known[2] + 1 };

		for (auto i = 0; i < status.size(); i++) { if (status[i] == BALL) known.push_back(i); }

		auto n = size(known) > 2 ? 2 : size(known);
		vector<int> known_ran = GetRandom(n);
		for (auto i = 0; i < n; i++)
		{
			ran.push_back(known[known_ran[i]]);
		}

		vector<int> unknown;
		for (auto i = 0; i < status.size(); i++) { if (status[i] == UNKNOWN) unknown.push_back(i); }

		n = 3 - n;
		vector<int> unknown_ran = GetRandom(size(unknown));
		for (auto i = 0; i < n; i++)
		{
			ran.push_back(unknown[unknown_ran[i]]);
		}

		return { ran[0] + 1,ran[1] + 1,ran[2] + 1 };
	}
};

class BaseBallGame
{
	unique_ptr<IGameStrategy> strategy_;
	vector<pair<INPUT, RESULT> > v;
public:
	BaseBallGame() { srand((unsigned)time(0)); }
	void SetStrategy(IGameStrategy *strategy) { v.clear(); strategy_.reset(strategy); }
	void run()
	{
		while (1)
		{
			//-----------------------------------------------
			// 이전의 결과가 담긴 vector v를 참고 해서
			// 사용자가 생각한 숫자를 예측해 냅니다.
			// 현재 구현은 무조건 랜덤 입니다.
			auto [x,y,z] = strategy_->GetInput(v);
			//--------------------------------------
			cout << "당신이 생각한 숫자는 " << x
			<< ", " << y << ", " << z << " 입니까 ?" << endl;
			int strike = 0, ball = 0;
			cout << "strike 갯수 : ";
			cin >> strike;
			if (strike == 3)
			{
				cout << "성공 !" << endl;
				break;
			}
			cout << "ball 갯수 : ";
			cin >> ball;
			//--------------------------------------
			// 입력된 결과(strike, ball)을 기록해 두었다가
			// 다음수를 예측할때 사용합니다.
			v.push_back(make_pair(INPUT(x, y, z), RESULT(strike, ball)));
			dump();
		}
	}
	// 필요하신 분을 위해 참고용으로 만든 함수입니다.
	void dump()
	{
		printf("-------------------------------\n");
		printf("입력값 s b\n");
		for (auto& p : v) // p는 pair<INPUT, RESULT> 입니다.
		{
			printf(" %d %d %d : %d %d\n",
				get<0>(p.first), get<1>(p.first), get<2>(p.first),
				get<0>(p.second), get<1>(p.second));
		}
		printf("-------------------------------\n");
	}
};

int main(void)
{
		BaseBallGame bbg;
		bbg.SetStrategy(new GameAiStrategy);
		bbg.run();

		bbg.SetStrategy(new GameRandomStrategy);
		bbg.run();
}
