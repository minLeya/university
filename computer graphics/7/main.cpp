#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

int count = 0;
float* X;
float* Y;
const float M_PI = 3.14159265f;
int X11, Y11, dY, dX, X22, Y22, a;


void init()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}

void draw()
{
	GLfloat A = 100, B = 50, X = 0, Y = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(10, 10, 600, 400);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-100.0, 0.0); glVertex2f(100.0, 0.0);
	glVertex2f(0.0, 100.0); glVertex2f(0.0, -100.0);
	glEnd();

	// x = –ay 

	a = 1;
	Y11 = -60; Y22 = 60;
	X11 = (-1) * a * Y11; X22 = (-1) * a * Y22;
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	dX = X22 - X11;
	dY = Y22 - Y11;
	glVertex2f(X11, Y11);
	while (Y11 < Y22)
	{
		Y11 = Y11 + 1;
		X11 = X11 + dY / dX;
		glVertex2f(X11, Y11);
	}
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Лаба 7");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}
