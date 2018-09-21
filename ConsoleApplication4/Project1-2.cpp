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
	vector<INPUT> space_;

	void Populate(vector<INPUT> &space)
	{

		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				if (i == j) continue;
				for (int k = 0; k<9; k++)
				{
					if (j == k) continue;
					if (i == k) continue;
					space.emplace_back(i + 1, j + 1, k + 1);
				}
			}
		}
	}

	template<typename T,size_t...t>  auto Tuple2ArrayImpl(T tpl,index_sequence<t...>)
	{
		using type = typename tuple_element<0, T>::type;
		array<type, sizeof...(t)> ary = { get<t>(tpl)... };

		return ary;
	}

	template<typename...T> auto Tuple2Array(tuple<T...> tpl)
	{
		return Tuple2ArrayImpl(tpl, make_index_sequence<sizeof...(T)>());
	}

	RESULT Hit(INPUT f, INPUT s)
	{
		int strike = 0;
		int ball = 0;
#if true
		auto fa = Tuple2Array(f);
		auto fb = Tuple2Array(s);
#else
		array<int, 3> fa, fb;
		tie(fa[0], fa[1], fa[2]) = f;
		tie(fb[0], fb[1], fb[2]) = s;
#endif

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (fa[i] == fb[j])
				{
					if (i == j)
						strike++;
					else
						ball++;
				}
			}

		return { strike,ball };
	}

public:
	GameAiStrategy()
	{
		Populate(space_);
	}
	virtual INPUT GetInput(vector<pair<INPUT, RESULT>> hist)
	{
		if (0 != hist.size())
		{
			auto&[com_guess, user_answer] = hist.back();

			space_.erase(remove_if(begin(space_), end(space_), 
			[&com_guess, &user_answer, this](auto event)
			{
				return user_answer != Hit(com_guess, event);
			}), end(space_));
		}

		int sel = rand() % space_.size();

		return space_[sel];
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
