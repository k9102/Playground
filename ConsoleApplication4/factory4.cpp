// Factory3.cpp => Factory5.cpp �� ����

#include <iostream>
#include <vector>
#include <map>
#include "Singleton.hpp"
using namespace std;

class Shape
{
public:
	virtual void Draw() { cout << "Draw Shape" << endl; }

	virtual Shape* Clone() = 0;
};

class Rect : public Shape
{
public:
	virtual void Draw() { cout << "Draw Rect" << endl; }

	static Shape* Create() { return new Rect; }

	virtual Shape* Clone() { return new Rect(*this); }
};

class Circle : public Shape
{
public:
	virtual void Draw() { cout << "Circle Rect" << endl; }

	static Shape* Create() { return new Circle; }

	virtual Shape* Clone() { return new Circle(*this); }
};



class ShapeFactory
{
	MAKE_SINGLETON(ShapeFactory)


		map<int, Shape*> protype_map;

public:
	void Register(int type, Shape* sample)
	{
		protype_map[type] = sample;
	}

	Shape* CreateShape(int type)
	{
		Shape* p = 0;
		auto ret = protype_map.find(type);
		if (ret == protype_map.end())
			return 0;

		p = protype_map[type]->Clone();

		return p;
	}
};



int main()
{
	ShapeFactory& factory = ShapeFactory::getInstance();

	// ���忡 ��ǰ�� ����Ѵ�.
	//        Ŭ���� ���
	//factory.Register( 1, &Rect::Create);
	//factory.Register( 2, &Circle::Create);

	Rect* r1 = new Rect;// ������ ũ�� 5
	Rect* r2 = new Rect;// �Ķ��� ũ�� 10

						// ���忡 ��ü ���
	factory.Register(1, r1);
	factory.Register(2, r2);

	//factory.ShowProduct();



	vector<Shape*> v;

	while (1)
	{
		int cmd;
		cin >> cmd;

		//
		if (cmd >= 1 && cmd <= 5)
		{
			Shape* p = factory.CreateShape(cmd);

			if (p != 0)
				v.push_back(p);
		}
		else if (cmd == 9)
		{
			for (auto p : v)
				p->Draw(); // ������
		}
	}
}
































//
