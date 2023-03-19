#include <GL/glut.h>
#include <cmath>
#include <math.h>
#include <stdlib.h>


GLfloat angle = 0, addAngle = 0;
GLfloat angle2 = 0, addAngle2 = 0;
int even1 = 0, even2 = 0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display()
{
	glPushMatrix(); //Сохраняем VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //вместе с очисткой буфера цвета предусмотреть очистку буфера глубины
	glEnable(GL_DEPTH_TEST); //включение режима удаления невидимых (проверка глубины)
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0); // VM=Fwe // позиция наблюдателя

	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 }; // Источник света в CKw
	GLfloat myDiffuse[] = { 0.75164, 0.60648, 0.22648, 1 }; //рассеивание
	GLfloat myShininess[] = { 51.2 }; //блеск
	GLfloat myAmbient[] = { 0.24725, 0.1995, 0.0745, 1 }; //фоновое
	GLfloat mySpecular[] = { 0.628281, 0.555802, 0.366065, 1 }; //зеркальность
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
	glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);

	glPushMatrix();
	glRotatef(angle2, 0, 1, 0); // вращаем источник света

	// Направление к источнику света в CKe
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(1, 2, 2);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glEnable(GL_LIGHTING); // Включение расчета освещенности
	glEnable(GL_LIGHT0); // включаем этот конкретный источник
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	// грань 0 (основание)
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(-2, 0, -1);
	glVertex3f(2, 0, -1);
	glVertex3f(2, 0, 1);
	glVertex3f(-2, 0, 1);
	glEnd();

	// грань 1 (правая стенка)
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(2, 0, 1);
	glVertex3f(2, 0, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glEnd();

	// грань 2 (левая стенка)
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2, 0, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-2, 0, -1);
	glEnd();

	// грань 3 (верхушка)
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glEnd();

	// грань 4 (передняя стенка)
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2, 0, 1);
	glVertex3f(2, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();

	// грань 5 (задняя стенка)
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(2, 0, -1);
	glVertex3f(-2, 0, -1);



	glEnd();

	glPopMatrix();
	glDisable(GL_LIGHTING); //Выключаем освещение

	glBegin(GL_LINES); //Рисуем координатные оси
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
	glEnd();

	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}

void Idle()
{
	angle += addAngle; if (angle > 360.0) angle = 0;
	angle2 += addAngle2; if (angle2 > 360.0) angle2 = 0;
	glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'o') {
		if (even1 % 2 == 0) addAngle = 0.5;
		else addAngle = 0;
		even1++;
	}
	else if (key == 'l') {
		if (even2 % 2 == 0) addAngle2 = 0.5;
		else addAngle2 = 0;
		even2++;
	}

	if (key == 'f') {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else if (key == 'b') {
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //устанавливая режим дисплея в функции main( ), предусмотрено использование буфера глубины
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Лаба 4, Задание 2");
	glutDisplayFunc(Display);

	glutKeyboardFunc(keys);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	init();
	glutMainLoop();
}
