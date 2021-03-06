



#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;


int main(int argc,char *argv[])
{
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	
	string buf;
	vector<vector<string>> v;
	unordered_map<string, string> lookup;

	while (getline(in, buf)) 
	{
		istringstream ss(buf);
		string f, s, t;
		ss >> f >> s >> t;
		if (f == "define") lookup[s] = t;
		else if(s == "=")
		{
			out << f << s << lookup[t] << endl;
		}
	}
}
