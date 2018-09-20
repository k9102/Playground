#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>

using namespace std;

using INPUT = tuple<int, int, int>;
using HIT = pair<int,int>;
vector<INPUT> space;

void Populate(vector<INPUT> &space)
{

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(i==j) continue;
            for(int k=0;k<9;k++)
            {
                if(j==k) continue;
                if(i==k) continue;
                space.emplace_back(i+1,j+1,k+1);
            }
        }
    }
}

pair<int, int> Hit(INPUT f, INPUT s)
{
    int strike = 0;
    int ball = 0;
    array<int, 3> fa, fb;

    tie(fa[0], fa[1], fa[2]) = f;
    tie(fb[0], fb[1], fb[2]) = s;

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

    return {strike,ball};
}

int main()
{

    srand (time(NULL));

    Populate(space);

    while (true)
    {
        int sel = rand() % space.size();
        auto &[f, s, t] = space[sel];
        cout << f << " " << s << " " << t << endl;

        INPUT user_input{f,s,t};

        int strike, ball;
        cin >> strike >> ball;

        HIT user_hit{strike,ball};

        space.erase(remove_if(begin(space),end(space),[&user_input,&user_hit](auto set)
        {
            return user_hit!=Hit(user_input,set);
        }),end(space));

        assert(space.size()!=0);
        cout << space.size() << endl;
        if(space.size()==1)
        {
            auto [a,b,c] = space[0];
            cout << "bingo => " << a <<" "<< b << " "<<c << endl;
            return 0;
        }
    }

    return 0;
}