#include "GL/glut.h"
#include <cmath>
#include <math.h>
#include <stdlib.h>

GLfloat R = 640.0 / 480; //Форматное соотношение
GLfloat w = 40, h; //Ширина и Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f = 0.0;
GLfloat angle = 0;
void init(void) //Расчет параметров мирового окна
{
	h = w / R; l = -w / 2; r = w / 2; b = -h / 2; t = h / 2;
	glClearColor(1.0, 1.0, 1.0, 0.0);
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
void showAxis(void)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, t);
	glVertex2f(0, 0);
	glVertex2f(r, 0);
	glEnd();
}
void fig0(void) //фиг.1 движущийся пу
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glVertex2f(5.0, 1.0);
	glVertex2f(5.0, -1.0);
	glEnd();

}
void drawCircle(float x, float y, float r, int amountSegments) //фиг.0 (окружность)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);
		float dx = r * cosf(angle);
		float dy = r * sinf(angle);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}
void scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawCircle(0, 0, 5, 100);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0); //смещение по осям x0 и y0
	glRotatef(f, 0.0, 0.0, 1.0); //поворот
	glTranslatef(-10.0, 0.0, 0.0); //смещение по осям x0 и y0
	glScalef(1.0, -1.0, 1.0);
	fig0();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
void timer(int value)
{
	f += 90;
	if (f >= 360) { f = 0; }
	glutPostRedisplay();
	glutTimerFunc(500, timer, 0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //два буфера для более плавного движения
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Задание 2");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutTimerFunc(500, timer, 0);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
	return 0;
}

