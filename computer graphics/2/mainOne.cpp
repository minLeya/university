#include <GL/glut.h> 
#include <stdlib.h> 
#include <math.h> 
#include <windows.h> 

#define PI 3.1459 

GLfloat R = 640.0 / 480; //Форматное соотношение 
GLfloat w = 40;  //Ширина мирового окна 
GLfloat h; //Высота мирового окна 
GLfloat l, r, b, t; //Параметры мирового окна 
GLint i, j, k;
GLfloat jj{ 1.3 };
bool replay{ 0 };


void init(void)
{
	h = w / R; l = -w / 2; r = w / 2; b = -h / 2; t = h / 2; //Расчет пара-метров мирового окна 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H)
{
	if (R > W / H) glViewport(0, 0, W, W / R);
	else glViewport(0, 0, H * R, H);
}

void fig0(void)
{
	glColor3f(0.4, 0.3, 1.0); //голубая окр
	glBegin(GL_POLYGON);
	int  x = 5;
	for (int a = 0; a <= 360; a += 1)
	{
		glVertex2f(x * cos(a) - 10, x * sin(a));
	}
	glEnd();
}

void fig1(void)
{
	glColor3f(1.0, 0.4, 1.0); //розовая окр
	glBegin(GL_POLYGON);
	int  x = 5;
	for (int a = 0; a <= 360; a += 1)
	{
		glVertex2f(x * cos(a) + 10, x * sin(a));
	}
	glEnd();
}

void scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	if (replay) {
		glScalef(jj, jj, 0.0);
	}
	else {
		glScalef(1.0, 1.0, 0.0);
	}
	fig0();

	glPopMatrix();


	glPushMatrix();
	if (replay) {
		glScalef(1.0, 1.0, 0.0);
	}
	else {
		glScalef(jj, jj, 0.0);
	}
	fig1();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();

	if (replay) replay = 0;
	else replay = 1;

	Sleep(500);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("1 задание");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}
