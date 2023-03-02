#include <GL/glut.h>


void init();
void draw();

void main(int argc, char** argv) //Главная функция
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //само окно (прога с названием «1задание» и тд)
	glutInitWindowPosition(50, 50); //где находится на экране
	glutCreateWindow("1 задание");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

void init() //Функция инициализации
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, 2.0,0.0, 1.0); - установка мирового окна, которое будет отображаться в viewport
}

void draw() //Функция рисования
{
	//ломаная
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.7, 0.0); glVertex2f(-0.4, 0.2);
	glVertex2f(-0.1, 0.0); glVertex2f(0.2, 0.2);
	glVertex2f(-0.4, 0.4); glVertex2f(0.0, 0.7);
	glEnd();


	//квадрат
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	//треугольник
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.8, -0.9, 0.0);
	glVertex3f(-0.4, -0.9, 0.0);
	glVertex3f(-0.6, -0.3, 0.0);
	glEnd();

	glFlush();
}
