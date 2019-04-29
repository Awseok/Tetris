#include <iostream>
using namespace std;

class Block
{
public:
	double x1, y1, x2, y2, width, height, red, blue, green;

	virtual void turn() {};
};

class StraightStick : public Block
{
public:
	StraightStick()
	{
		x1 = -0.05;
		y1 = 1;
		x2 = 0.05;
		y2 = 0.8;
		width = abs(x2 - x1);
		height = abs(y2 - y1);
	}

	virtual void turn()
	{
		x1 = -height;
		y1 = 1 - width / 2;
		x2 = height;
		y2 = 1;
		width = abs(x2 - x1);
		height = abs(y2 - y1);
	}
};

int main()
{
	StraightStick st = StraightStick();
	cout << "(" << st.x1 << ", " << st.y1 << ")" << "(" << st.x2 << ", " << st.y2 << ")" << endl;
	st.turn();
	cout << "(" << st.x1 << ", " << st.y1 << ")" << "(" << st.x2 << ", " << st.y2 << ")" << endl;
	st.turn();
	cout << "(" << st.x1 << ", " << st.y1 << ")" << "(" << st.x2 << ", " << st.y2 << ")" << endl;
	st.turn();
	cout << "(" << st.x1 << ", " << st.y1 << ")" << "(" << st.x2 << ", " << st.y2 << ")" << endl;
	st.turn();
	cout << "(" << st.x1 << ", " << st.y1 << ")" << "(" << st.x2 << ", " << st.y2 << ")" << endl;

	getchar();
	return 0;
}