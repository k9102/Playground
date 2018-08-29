#include "gtest/gtest.h"
#include "../ConsoleApplication4/typelist.h"
#include <type_traits>
using namespace std;
TEST(TestCaseName, TestName) {

	typedef MakeTypelist<int, char, double, short>::Result myType;
	TypeAt<myType, 1>::Result n; 
	
	bool val = std::is_same_v<char, decltype(n)>;

	EXPECT_EQ(val,true) << "test printing";


	int idx = IndexOf<myType, double>::value;
	EXPECT_EQ(idx, 2);
}




class MyTestCase : public testing::TestWithParam<int> {};

TEST_P(MyTestCase, MyTest)
{
  std::cout << "Example Test Param: " << GetParam() << std::endl;
}

INSTANTIATE_TEST_CASE_P(MyGroup, MyTestCase, testing::Range(0, 10),
                        testing::PrintToStringParamName());