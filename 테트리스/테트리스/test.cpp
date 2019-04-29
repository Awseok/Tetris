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
#define stick_width 0.050000F
#define stick_height 0.200000F
#pragma warning(disable:4244)
using namespace std;

void MyDisplay();
void downBlock();
void MyKeyboard(int key, int X, int Y);
bool block_check();
void create_block();
//bool boundCheck();

bool turn_val;
bool block_box[40][17];
float rand_red, rand_blue, rand_green;
char *crn_block;
GLfloat Delta, Delta_x;

class Block
{
public:
	float x1, y1, x2, y2, width, height, red, blue, green;

	virtual void turn() {};
};

Block *block_pointer;

class StraightStick : public Block
{
public:
	StraightStick()
	{
		x1 = -stick_width;
		y1 = NomalYUp;
		x2 = stick_width;
		y2 = NomalYUp - stick_height;
		width = abs(x2 - x1);
		height = abs(y2 - y1);
	}

	virtual void turn()
	{
		x1 = -height;
		y1 = NomalYUp - width / 2;
		x2 = height;
		y2 = NomalYUp;
		width = abs(x2 - x1);
		height = abs(y2 - y1);
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
	for (int i = 0; i < 40; i++)
		block_box[i][16] = true;
	glutDisplayFunc(MyDisplay);
	glutSpecialFunc(MyKeyboard);
	glutIdleFunc(downBlock);
	glutMainLoop();

	return 0;
}

StraightStick st = StraightStick();

void MyDisplay()
{
	srand(unsigned(time(NULL)));
	glClear(GL_COLOR_BUFFER_BIT);


	block_pointer = &st;
	if (turn_val)
	{
		block_pointer->turn();
		turn_val = false;
	}
	glBegin(GL_POLYGON);
	glColor3f(rand_red, rand_blue, rand_green);
	glVertex2d(block_pointer->x1 + Delta_x, block_pointer->y1 + Delta);
	glVertex2d(block_pointer->x2 + Delta_x, block_pointer->y1 + Delta);
	glVertex2d(block_pointer->x2 + Delta_x, block_pointer->y2 + Delta);
	glVertex2d(block_pointer->x1 + Delta_x, block_pointer->y2 + Delta);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex2d(NomalXLeft, NomalYUp);
	glVertex2d(NomalXLeft, NomalYUp - 1.6);
	glVertex2d(NomalXLeft + stick_width, NomalYUp - 1.6);
	glVertex2d(NomalXLeft + stick_width, NomalYUp);
	glEnd();

	//glBegin(GL_POLYGON);
	//glVertex2d(NomalXLeft, NomalYUp - 1.6);
	//glVertex2d(NomalXLeft, NomalYBottom);
	//glVertex2d(NomalXRight, NomalYBottom);
	//glVertex2d(NomalXRight, NomalYUp - 1.6);
	//glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(NomalXRight, NomalYUp - 1.6);
	glVertex2d(NomalXRight - 0.05, NomalYUp - 1.6);
	glVertex2d(NomalXRight - 0.05, NomalYUp);
	glVertex2d(NomalXRight, NomalYUp);
	glEnd();
	glutSwapBuffers();
}


bool block_check()
{
	int x, y, x2, y2, i, j, temp = 0;

	x = ((block_pointer->x1 + Delta_x) * 100)/5 + 19; // 19는 배열의 중간 인덱스

	if (10 - (int)((block_pointer->y1 + Delta) * 100) % 10 > 0)
	{
		if (block_pointer->y1 + Delta > 0)
			y = 10 - (int)((block_pointer->y1 + Delta) * 10 + 0.01);
		else 
			y = 10 - (int)((block_pointer->y1 + Delta) * 10 - 0.01);
	}
	else
		y = 10 - (int)((block_pointer->y1 + Delta) * 10);

	x2 = ((block_pointer->x2 + Delta_x) * 100)/5 + 19;

	if (10 - (int)((block_pointer->y2 + Delta) * 100) % 10 > 0)
	{
		if (block_pointer->y2 + Delta > 0)
			y2 = 10 - (int)((block_pointer->y2 + Delta) * 10 + 0.01);
		else
			y2 = 10 - (int)((block_pointer->y2 + Delta) * 10 - 0.01);
	}
	else
		y2 = 10 - (int)((block_pointer->y2 + Delta) * 10);
	
	if (y > y2)
	{
		temp = y;
		y = y2;
		y2 = temp;
	}
	for (i = x; i < x2; i++)
		for (j = y; j < y2; j++)
			if (block_box[i][j])
				return false;

	return true;
}

void block_store()
{
	int x, y, x2, y2, i, j, temp = 0;

	x = (block_pointer->x1 + Delta_x) * 10 + 8;
	y = (block_pointer->y1 + Delta) * 10 + 8;
	x2 = (block_pointer->x2 + Delta_x) * 10 + 8;
	y2 = (block_pointer->y2 + Delta) * 10 + 8;
	y < y2 ? 0 : temp = y, y = y2, y2 = temp;
	for (i = x; i < x2; i++)
		for (j = y; j < y2; j++)
			block_box[i][j] = true;
				
}

void downBlock()
{
	if (block_check())
	{
		Sleep(500);
		Delta -= 0.100000f;
	}

	//else
	//{
	//	block_store();
	//	create_block();
	//}
	glutPostRedisplay();
}

//bool boundCheck()
//{
//	if (block_pointer->x1 + Delta_x < - 0.95 || block_pointer->x2 + Delta_x > 0.95)
//		return false;
//	if (block_pointer->y1 + Delta < - 0.65 || block_pointer->y2 + Delta < - 0.6)
//		return false;
//	else
//		return true;
//}

void create_block()
{
	StraightStick st = StraightStick();
}

void MyKeyboard(int key, int X, int Y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (Delta_x > -0.85)
			Delta_x -= 0.100000f;
		break;
	case GLUT_KEY_RIGHT:
		if (Delta_x < 0.85)
			Delta_x += 0.100000f;
		break;
	case GLUT_KEY_DOWN:
		if(Delta > - 1.6)
			Delta -= 0.100000f;
		break;
	case GLUT_KEY_UP:
		turn_val = true;
		break;
	}
}