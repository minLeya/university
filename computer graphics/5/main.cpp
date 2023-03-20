#include <GL/glut.h>
#include <cmath>
#include <Windows.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include <gl\glut.h>.
#include <C:\Users\Лейсан\Downloads\glaux.h>
#pragma comment(lib, "C:\\Users\\Лейсан\\Downloads\\GLAUX.LIB")
#pragma comment(lib, "legacy_stdio_definitions.lib")

int width, height;


GLfloat angle1 = 0, angle_plus = 0;
GLfloat angle2 = 0, angle_plus2 = 0;
int even1 = 0, even2 = 0;
GLuint list = 0;
GLuint list2 = 0;
GLuint texture[3] = {0, 1, 2};

GLvoid LoadGLTextures()
{
	// Загрузка картинок
	AUX_RGBImageRec* texture1 = auxDIBImageLoad(L"C:\\Users\\Лейсан\\Desktop\\учеба\\компьютерная графика\\5 лаба\\texture_2.bmp");

	AUX_RGBImageRec* texture2 = auxDIBImageLoad(L"C:\\Users\\Лейсан\\Desktop\\учеба\\компьютерная графика\\5 лаба\\texture_2.bmp");
	AUX_RGBImageRec* texture3 = auxDIBImageLoad(L"C:\\Users\\Лейсан\\Desktop\\учеба\\компьютерная графика\\5 лаба\\texture_2.bmp");

	// Создание текстуры
	glGenTextures(3, texture); //создается n идентификаторов текстур, которые будут записаны в массив texture

	glBindTexture(GL_TEXTURE_2D, texture[0]); // Перед началом определения свойств новой текстуры нужно сделать ее текущей при помощи команды
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Возвращает среднеарифметическое значение четырех элементов текстуры, расположенных в центре пикселя
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	/*текстура будет двухмерной (GL_TEXTURE_2D). Ноль задает уровень детализации, это обычно ноль. Три - число компонент цветовых данных,
	так как изображение сделано из трех цветовых компонент (красный, зеленный, синий). texture1- >sizeX - это ширина текстуры, автоматически.
	texture1->sizeY - высота текстуры. Ноль - это бордюр. Он обычно остается нулем.
	GL_RGB сообщает OpenGL, что данные изображения представлены в порядке следования красных, зеленных и голубых компонент цвета.
	GL_UNSIGNED_BYTE означает, что данные из которых состоит изображение имеют размер байта и все числа без знака, и в конце texture1->data сообщает OpenGL, где брать сами данные.
	В этом случае указатель на данные в записи texture1.*/
}

GLvoid LoadCallLists() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	list = glGenLists(1); //Генерация незадействованного индекса списка
	glNewList(list, GL_COMPILE); //Создание списка и накопление команд

	// грань 1 основание
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(-2, 0, -1);
	glVertex3f(2, 0, -1);
	glVertex3f(2, 0, 1);
	glVertex3f(-2, 0, 1);
	glEnd();



	// грань 3 (верхушка)
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glTexCoord2f(-1, -1); glVertex3f(-1, 1, 1);
	glTexCoord2f(1, -1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(-1, 1); glVertex3f(-1, 1, -1);
	glEnd();

	// грань 4 (передняя стенка)

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(-1, -1); glVertex3f(-2, 0, 1);
	glTexCoord2f(1, 1); glVertex3f(2, 0, 1);
	glTexCoord2f(0.5, 0.5); glVertex3f(1, 1, 1);
	glTexCoord2f(-0.5, -0.5); glVertex3f(-1, 1, 1);
	glEnd();

	// грань 5 (задняя стенка)
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glTexCoord2f(-0.5, -0.5); glVertex3f(-1, 1, -1);
	glTexCoord2f(0.5, 0.5); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(2, 0, -1);
	glTexCoord2f(-1, -1); glVertex3f(-2, 0, -1);
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

	glEndList(); //Завершение накопления команд в списке

	list2 = glGenLists(1);
	glNewList(list2, GL_COMPILE);

	glBegin(GL_LINES); //Рисуем координатные оси
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
	glEnd();

	glEndList();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	LoadGLTextures();

	LoadCallLists();
}

void Display()
{
	glPushMatrix(); //Сохраняем VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //вместе с очисткой буфера цвета предусмотреть очистку буфера глубины
	glEnable(GL_DEPTH_TEST); //включение режима удаления невидимых (проверка глубины)
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0); // VM=Fwe // позиция наблюдателя

	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 }; // Источник света в CKw
	GLfloat myDiffuse[] = { 0.50754, 0.50754, 0.50754, 1 };
	GLfloat myShininess[] = { 51.2 };
	GLfloat myAmbient[] = { 0.19225, 0.19225, 0.19225, 1 };
	GLfloat mySpecular[] = { 0.508273, 0.508273, 0.508273, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
	glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);

	glPushMatrix(); //Сохраняем VM=Fwe
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
	glPopMatrix(); // Восстанавливаем VM=Fwe

	glPushMatrix(); //Сохраняем VM=Fwe
	glRotatef(angle1, 0, 1, 0); // VM=Fwe*R

	glCallList(list); //Вызов списка накопленных ранее команд

	glPopMatrix(); // Восстанавливаем VM=Fwe
	glDisable(GL_LIGHTING); //Выключаем освещение

	glCallList(list2); //Вызов списка накопленных ранее команд

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
	angle1 += angle_plus; if (angle1 > 360.0) angle1 = 0;
	angle2 += angle_plus2; if (angle2 > 360.0) angle2 = 0;
	Sleep(2);
	glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'o') {
		if (even1 % 2 == 0) angle_plus = 0.5;
		else angle_plus = 0;
		even1++;
	}
	else if (key == 'l') {
		if (even2 % 2 == 0) angle_plus2 = 0.5;
		else angle_plus2 = 0;
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
void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); }
	else if (button == GLUT_RIGHT_BUTTON) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //устанавливая режим дисплея в функции main( ), предусмотрено использование буфера глубины
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Лаба 5");
	glutDisplayFunc(Display);
	glutMouseFunc(mouseButton);
	glutKeyboardFunc(keys);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	init();
	glutMainLoop();
}
