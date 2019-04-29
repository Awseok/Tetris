#include <iostream>
#include <math.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <time.h>
#define windowSizeW 450
#define windowSizeH 850
#define PI 3.141592
#define NomalXLeft -1
#define NomalXRight 1
#define NomalYUp 1
#define NomalYBottom -1
using namespace std;

void MyDisplay();
void downBlock();
void MyKeyboard(int key, int X, int Y);
void rand_col();

float rand_red, rand_blue, rand_green;
char *crn_block;
GLdouble Delta, Delta_x;

class turn_arr
{
public:
	double arr[4];

	turn_arr()
	{
		arr[0] = cos(PI / 2);
		arr[1] = -sin(PI /2);
		arr[2] = sin(PI / 2);
		arr[3] = cos(PI / 2);
	}

	double roundX(double x, double y)
	{
		return arr[0] * x + arr[1] * y;
	}
	double roundY(double x, double y)
	{
		return arr[2] * x + arr[3] * y;
	}
};

class Block
{
public:
	double x1, y1, width, height, red, blue, green;

	void turn() {
		turn_arr roundArr = turn_arr();
		x1 = roundArr.roundX(x1, y1); // roundArr.arr[0] * x1 + roundArr.arr[1] * y1;
		y1 = roundArr.roundY(x1, y1); // roundArr.arr[2] * x1 + roundArr.arr[3] * y1;
	};
};

Block *block_pointer;

class StraightStick : public Block
{
public:
	double x2, y2, i = 0;

	StraightStick()
	{
		x1 = 0.05;
		y1 = 1;
		x2 = 0.05;
		y2 = 0;
		width = abs(x2 - x1);
		height = abs(y2 - y1);
	}

	void turn()
	{ 
		turn_arr roundArr = turn_arr();
		x1 = roundArr.roundX(x1, y1); // roundArr.arr[0] * x1 + roundArr.arr[1] * y1;
		y1 = roundArr.roundY(x1, y1); // roundArr.arr[2] * x1 + roundArr.arr[3] * y1;
		x2 = roundArr.roundX(x2, y2); // roundArr.arr[0] * x2 + roundArr.arr[1] * y2;
		y2 = roundArr.roundY(x2, y2); // roundArr.arr[2] * x2 + roundArr.arr[3] * y2;
	}
};

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowSizeW, windowSizeH);
	glutInitWindowPosition(600, 150);
	glutCreateWindow("Tetris");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutSpecialFunc(MyKeyboard);
	glutIdleFunc(downBlock);
	glutMainLoop();

	return 0;
}

void MyDisplay()
{
	srand(unsigned(time(NULL)));
	glClear(GL_COLOR_BUFFER_BIT);

	StraightStick st = StraightStick();
	block_pointer = &st;
	glBegin(GL_POLYGON);
	glColor3f(rand_red, rand_blue, rand_green);
	glVertex2d(block_pointer->x1 + Delta_x, block_pointer->y1 + Delta);
	glVertex2d(- block_pointer->x1 + Delta_x, block_pointer->y1 + Delta);
	glVertex2d(- block_pointer->x1 + Delta_x, block_pointer->y1 - 0.2 + Delta);
	glVertex2d(block_pointer->x1 + Delta_x, block_pointer->y1 - 0.2 + Delta);
	glEnd();

	//glBegin(GL_POLYGON);
	//glColor3f(rand_red, rand_blue, rand_green);
	//glVertex2d(0.05 + Delta_x,1 + Delta);
	//glVertex2d(-0.05 + Delta_x, 1 + Delta);
	//glVertex2d(-0.05 + Delta_x, 0.8 + Delta);
	//glVertex2d(0.05 + Delta_x, 0.8 + Delta);
	//glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex2d(NomalXLeft, NomalYUp);
	glVertex2d(NomalXLeft, NomalYUp - 1.6);
	glVertex2d(NomalXLeft + 0.05, NomalYUp - 1.6);
	glVertex2d(NomalXLeft + 0.05, NomalYUp);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(NomalXLeft, NomalYUp - 1.6);
	glVertex2d(NomalXLeft, NomalYBottom);
	glVertex2d(NomalXRight, NomalYBottom);
	glVertex2d(NomalXRight, NomalYUp - 1.6);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(NomalXRight, NomalYUp - 1.6);
	glVertex2d(NomalXRight - 0.05, NomalYUp - 1.6);
	glVertex2d(NomalXRight - 0.05, NomalYUp);
	glVertex2d(NomalXRight, NomalYUp);
	glEnd();
	glutSwapBuffers();
}

void downBlock()
{
	if (Delta > -1.4)
	{
		Sleep(700);
		Delta -= 0.1;
	}
	//else
	//	rand_col();
	glutPostRedisplay();
}

//void rand_col()
//{
//	rand_red = (float)((rand() % 10) * 0.1);
//	rand_blue = (float)((rand() % 10) * 0.1);
//	rand_green = (float)((rand() % 10) * 0.1);
//}

void MyKeyboard(int key, int X, int Y)
{
	if (Delta > -1.4)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			if(Delta_x > -0.85)
				Delta_x -= 0.1;
			break;
		case GLUT_KEY_RIGHT:
			if(Delta_x < 0.85)
				Delta_x += 0.1;
			break;
		case GLUT_KEY_DOWN:
			Delta -= 0.1;
			break;
		case GLUT_KEY_UP:
			block_pointer->turn();
			break;
		}
	}
}