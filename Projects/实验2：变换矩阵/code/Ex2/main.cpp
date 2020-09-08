// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "glut/glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;

template<typename T>
T min(const T& a, const T& b) {
	if (a < b) return a;
	else return b;
}

//a��ƽ������ʾ���ĺ���߳���b��ƽ������ʾ��������߳���c�Ǵ�ֱ����ʾ���ı߳�
//��������һ����������ʾ��ƽ���غϣ�λ����ʾ�����ڲ����ĳ����塣����λ��Ϊ��ʾ�����롣
void Draw_Cube(float A, float B, float H)
{
	float a = A / 2;
	float b = B / 2;
	float h = H;
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(-a, -b, 0);
	glVertex3f(-a, b, 0);
	glVertex3f(a, b, 0);
	glVertex3f(a, -b, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-a, -b, -h);
	glVertex3f(-a, b, -h);
	glVertex3f(a, b, -h);
	glVertex3f(a, -b, -h);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-a, -b, -h);
	glVertex3f(-a, -b, 0);
	glVertex3f(a, -b, 0);
	glVertex3f(a, -b, -h);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-a, b, -h);
	glVertex3f(-a, b, 0);
	glVertex3f(a, b, 0);
	glVertex3f(a, b, -h);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-a, -b, -h);
	glVertex3f(-a, -b, 0);
	glVertex3f(-a, b, 0);
	glVertex3f(-a, b, -h);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(a, -b, -h);
	glVertex3f(a, -b, 0);
	glVertex3f(a, b, 0);
	glVertex3f(a, b, -h);
	glEnd();
}

//��������ĳߴ���Ϊ���������ȵ�λ�á��ߴ����ݱ�������õ�
//����һ��������ƽ������ʾ����λ����ʾ�����ڲ��������ӡ�����λ��Ϊ��ʾ�����롣
void drawTable(float A, float B, float H) {
	float a = A / 2;
	float b = B / 2;
	float h = H;
	Draw_Cube(A, B, H);

	glPushMatrix();
	glTranslatef(-a / 2, -b / 2, -h);
	Draw_Cube(a / 2, b / 2, min(A, B)); //���Ƴ�����
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-a / 2, b / 2, -h);
	Draw_Cube(a / 2, b / 2, min(A, B));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(a / 2, b / 2, -h);
	Draw_Cube(a / 2, b / 2, min(A, B));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(a / 2, -b / 2, -h);
	Draw_Cube(a / 2, b / 2, min(A, B));
	glPopMatrix();
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //���ߵķ�ʽ��ʾ����ͱ���
	glLoadIdentity();						      // Reset The Current Modelview Matrix

	glPushMatrix();
	glTranslatef(-4.5f, 0.0f, -8.0f);		// Place the triangle Left
	glTranslatef(0.0f, fTranslate, 0.0f);   // Translate in Y direction
	drawTable(2, 2, 0.5);					// Draw table					
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -8.0f);		// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);		    // Rotate around Y axis
	drawTable(2, 2, 0.5);					// Draw table
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5f, 0.0f, -8.0f);
	glScalef(fScale, fScale, fScale);
	drawTable(2, 2, 0.5);
	glPopMatrix();

	fTranslate += 0.001f;
	fRotate += 0.1f;
	fScale -= 0.001f;

	if (fTranslate > 0.5f) fTranslate = 0.0f;
	if (fScale < 0.5f) fScale = 1.0f;
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	if (height == 0)									// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(1280, 640);
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}