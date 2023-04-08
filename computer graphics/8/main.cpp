#include <gl\glut.h>
#include <math.h>

GLfloat rotate = 0;
GLfloat lightRotate = 0;
GLfloat k = 0.05;


bool rotation = false;
bool light = false;


void f1()
{
	// Верхняя грань
	glBegin(GL_POLYGON);
	glNormal3f(0.4, 0.4, 0.4);
	glVertex3f(-0.1, 1, -0.3);
	glVertex3f(0.7, 1, -0.3);
	glVertex3f(0.4, 0.9, 0);
	glVertex3f(-0.4, 0.9, 0);
	glEnd();

	// боковая правая верхняя
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 1, -0.3);
	glVertex3f(0.5, 0.7, -0.3);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0.4, 0.9, 0);
	glEnd();


	// горизонтальная правая верхняя
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(0.7, 0.7, -0.3);
	glVertex3f(1.8, 0.7, -0.3);
	glVertex3f(1.3, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glEnd();

	// самая боковая правая
	glBegin(GL_POLYGON);
	glNormal3f(0.577, 0.577, 0.577);
	glVertex3f(1.8, 0.7, -0.3);
	glVertex3f(1.6, -0.2, -0.3);
	glVertex3f(1.2, 0.2, 0);
	glVertex3f(1.3, 0.6, 0);
	glEnd();

	// горизонтальная правая нижняя
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(1.6, -0.2, -0.3);
	glVertex3f(1.2, 0.2, 0);
	glVertex3f(0.4, 0.2, 0);
	glVertex3f(0.7, -0.2, -0.3);
	glEnd();

	// боковая правая нижняя
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(0.4, 0.2, 0);
	glVertex3f(0.7, -0.2, -0.3);
	glVertex3f(0.7, -0.5, -0.3);
	glVertex3f(0.4, -0.4, 0);
	glEnd();

	// Нижняя грань
	glBegin(GL_POLYGON);
	glNormal3f(0.577, 0.577, 0.577);
	glVertex3f(-0.7, -0.5, -0.3);
	glVertex3f(0.7, -0.5, -0.3);
	glVertex3f(0.4, -0.4, 0);
	glVertex3f(-0.4, -0.4, 0);
	glEnd();

	// боковая левая нижняя
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.4, 0.2, 0);
	glVertex3f(-0.7, -0.2, -0.3);
	glVertex3f(-0.7, -0.5, -0.3);
	glVertex3f(-0.4, -0.4, 0);
	glEnd();

	// горизонтальная левая нижняя!!
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(-1.3, -0.2, -0.3);
	glVertex3f(-1.2, 0.2, 0);
	glVertex3f(-0.4, 0.2, 0);
	glVertex3f(-0.7, -0.2, -0.3);
	glEnd();

	// самая боковая левая!!
	glBegin(GL_POLYGON);
	glNormal3f(-0.577, 0.577, 0.577);
	glVertex3f(-1.4, 0.7, -0.3);
	glVertex3f(-1.6, -0.2, -0.3);
	glVertex3f(-1.2, 0.2, 0);
	glVertex3f(-1.1, 0.6, 0);
	glEnd();

	// горизонтальная левая верхняя
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(-0.7, 0.7, -0.3);
	glVertex3f(-1.4, 0.7, -0.3);
	glVertex3f(-1.1, 0.6, 0);
	glVertex3f(-0.4, 0.6, 0);
	glEnd();


	// боковая левая верхняя
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.7, 1, -0.3);
	glVertex3f(-0.7, 0.7, -0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(-0.4, 0.9, 0);
	glEnd();
}

void f2() //золото
{
	// вертикальная пластина
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(-0.4, 0.9, 0);
	glVertex3f(0.4, 0.9, 0);
	glVertex3f(0.4, -0.4, 0);
	glVertex3f(-0.4, -0.4, 0);
	glEnd();


	// вертикальная пластина левая
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(-1.1, 0.6, 0);
	glVertex3f(-1.2, 0.2, 0);
	glVertex3f(0.4, 0.2, 0);
	glVertex3f(0.4, 0.6, 0);
	glEnd();

	// вертикальная пластина правая
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(-0.4, 0.2, 0);
	glVertex3f(1.2, 0.2, 0);
	glVertex3f(1.3, 0.6, 0);
	glEnd();
}

void f3()
{
	// вертикальная пластина
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(-0.7, 1, -0.3);
	glVertex3f(0.7, 1, -0.3);
	glVertex3f(0.7, -0.5, -0.3);
	glVertex3f(-0.7, -0.5, -0.3);
	glEnd();

	// вертикальная пластина левая
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(-1.4, 0.7, -0.3);
	glVertex3f(-1.6, -0.2, -0.3);
	glVertex3f(-0.7, -0.2, -0.3);
	glVertex3f(-0.7, 0.7, -0.3);
	glEnd();

	// вертикальная пластина правая
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(1.8, 0.7, -0.3);
	glVertex3f(1.6, -0.2, -0.3);
	glVertex3f(0.7, -0.2, -0.3);
	glVertex3f(0.7, 0.7, -0.3);
	glEnd();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void myDisplay()
{
	glPushMatrix(); //Сохраняем VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(1, 0, 5, 0, 0, 0, 0, 1, 0); // VM=Fwe


	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 };

	
	// начальное положение источника света Зачищаем буферы цвета и глубины
	glPushMatrix();
	glRotatef(lightRotate, 0, 1, 0); // вращаем источник света
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glPopMatrix();
	glEnable(GL_LIGHTING); // Включение расчета освещенности
	glEnable(GL_LIGHT0); // включаем этот конкретный источник


	glPushMatrix(); //Сохраняем VM=Fwe
	glRotatef(rotate, 0, 1, 0); // VM=Fwe*R*R*R
	glColor4f(1.0, 0.0, 0.0, 0.25);
	f1();//зад и стенки
	f3(); 
	
	
	f2();
	glPopMatrix(); // Восстанавливаем VM=Fwe

	glDisable(GL_LIGHTING); //Выключаем освещение
	glPopMatrix();

	glutSwapBuffers();
}
void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}
void myIdle()
{
	if (rotation)
	{
		rotate += k;
	}
	if (light)
	{
		lightRotate += k;
	}
	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y)
{
	if (key == 'o') { rotation = !rotation; }
	if (key == 'l') { light= !light; }
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("логотип");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(MyKeyboard);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
