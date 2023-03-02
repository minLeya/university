#include <GL/glut.h>


void init();
void draw();

void main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3 задание");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

void init() 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0,0.0, 1.0);
}

void draw() 
{
	GLfloat r = 1.0, g = 0.5, b = 0.0;
	GLint x = 0, y = 0, w = 20, h = 20;
	glClear(GL_COLOR_BUFFER_BIT);
	for (x = 0; x <= 600; x += w)
	{
		for (y = 0; y <= 600; y += h)
		{
			glViewport(x, y, w, h);
			glColor3f(r, g, b);
			if (r < 1.0)
			{
				r += 0.2;
			}
			else
			{
				r=0;
			}

			if (g < 1.0)
			{
				g += 0.2;
			}
			else
			{
				g = 0;
			}

			if (b < 1.0)
			{
				b += 0.2;
			}
			else
			{
				b = 0;
			}

			glBegin(GL_POLYGON);
				glVertex2f(0.5, 0.25);
				glVertex2f(0.75, 0.5);
				glVertex2f(0.5, 0.75);
				glVertex2f(0.25, 0.5);
			glEnd();
		}
	}

	glFlush();
}
