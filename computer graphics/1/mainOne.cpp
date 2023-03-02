#include <GL/glut.h>
#include <cmath>
#include <math.h>


void init();
void draw();

void main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("2 задание");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

void init() 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void draw() 
{
	GLfloat pi = 3.14159, x, y, t, a = 0.7;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glViewport(10, 10, 580, 580);
	//абсцисса и ордината
	glBegin(GL_LINES);
		glVertex2f(-1.0, 0.0); glVertex2f(1.0, 0.0); //абсцисса
		glVertex2f(0.0, -1.0); glVertex2f(0.0, 1.0); //ордината
	glEnd();
	
	// converting degrees to radians
	//x = xDegrees * 3.14159 / 180;
	//sin(x); //x - radians
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (t = 0; t <=360*pi/180; t += pi/180)
	{
		x = sin(a * t);
		y = cos(a * t);
		glVertex2f(x, y);
	}
	glEnd();
	
	glFlush();
}
