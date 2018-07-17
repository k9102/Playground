
#include <iostream>
#include <memory>
#include <utility>
#include <array>
template<typename Type> class Singleton
{
protected:
	Singleton() = default;
private:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	template<typename...ARGS> static Type& getInstance(ARGS&&...args)
	{
		static Type instance(std::forward<ARGS>(args)...);
		return instance;
	}
};

class Mouse : public Singleton<Mouse>
{
public:
	Mouse() {}
};

class Cursor : public Singleton<Cursor>
{
public:
	Cursor(int x, int y) 
	{
		std::cout << "test = " << x <<","<< y << std::endl;
	}
};
int main()
{
	Mouse& m = Mouse::getInstance();
	Cursor& c = Cursor::getInstance(1, 2);
}