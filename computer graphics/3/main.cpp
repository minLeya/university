#include "GL/glut.h"
#include <gl\glut.h>
#include <math.h>
#include <cmath>
GLfloat angle = 0, scal=1.0, super = 0;
GLfloat scale_last{ 1.0 }, scale_next{ 1.0 };
GLboolean flag_scale_up{ false }, flag_scale_down{ false };

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myDisplay()
{
	glPushMatrix(); //Сохраняем VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(3, 2, 1, 0, 0, 0, 0, 1, 0); // VM=Fwe
	GLfloat myLightPosition[] = { 3.0, 3.0, 3.0, 1.0 }; // Источник све-та в CKw
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*Позиция ис-точника света будет преобразована в CKe*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPushMatrix(); //Сохраняем VM=Fwe или преобразованную в результате движения по окружности наблюдателя.
	glScalef(scale_next, scale_next, 1.0);//Сохранение масштабности сохранённой и не изменённой VM = Fwe.
	//Масштабирование по Х и У VM=Fwe по нажатию кнопок мыши.
	if (flag_scale_up)
	{
		scale_last = scale_next;
		scale_next += 0.1;
		glScalef(scale_next / scale_last, scale_next / scale_last, 1.0);
		flag_scale_up = false;
	}
	else if (flag_scale_down)
	{
		scale_last = scale_next;
		scale_next -= 0.1;
		glScalef(scale_next / scale_last, scale_next / scale_last, 1.0);
		flag_scale_down = false;
	}

	glRotatef(angle, 0, 0, 1); // VM=Fwe*R*R*R
	glutSolidOctahedron();//?? how to scale
	glPopMatrix(); // Восстанавливаем VM=Fwe
	glDisable(GL_LIGHTING); ////Выключаем освещение для рисования линий и прочего в цвете.
	//Рисуем координатные оси разного цвета в CKe.
	glBegin(GL_LINES);
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}
void myIdle()
{
	angle += super;
	if (angle > 360.0) angle = 0;
	glutPostRedisplay();
}

void KeyboardEvent(unsigned char key, int a, int b) {
	switch (key)
	{
	case 'x':
		super = 0.05;
		break;

	case 'y':
		super = -0.05;
		break;
	}

}

void MouseClickEvents(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && (scale_next + 0.1) <= 1.6)
	{
		flag_scale_up = true;
		flag_scale_down = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP && (scale_next - 0.1) >= 0.4)
	{
		flag_scale_down = true;
		flag_scale_up = false;
	}
}

void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("my window");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(KeyboardEvent);
	glutMouseFunc(MouseClickEvents);
	init();
	glutMainLoop();
}
