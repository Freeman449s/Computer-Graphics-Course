// glutEx1.cpp : �������̨Ӧ�ó������ڵ㡣
//
//ע��FPS������Ӧ��

//��ʾ�б�һϵ��Ԥ�������Դ��Ժ���õĺ���
//����������þ��и��ߵ����ܡ����磬һϵ��CTM����ĵ��ã�����Ϊ��ʾ�б�󽫽�����������
//һ����ʾ�б�����������ɾ��ǰ�����ٱ��޸�
#include <stdlib.h>
#include "glut.h"
#include <stdio.h>
#include <string.h>

#include "stanford_bunny.h"

float eye[] = { 0, 8, 12 };
float center[] = { 0, 0, 0 };
float fDistance = 0.2f;
float fRotate = 0;
bool bAnim = false; //Anim:animation ��������ת��ģʽ

bool bDrawList = false;
GLint listIndex = 0;

int iBunnyNum = 1;

void DrawTable()
{
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(16, 2, 16);
	//��(0,0,0)λ�û��Ʊ߳�x��������
	//ʹ��glScale�ı�߳������Ƴ�����
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, -7, 6);
	glScalef(2, 12, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, -7, -6);
	glScalef(2, 12, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -7, -6);
	glScalef(2, 12, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -7, 6);
	glScalef(2, 12, 2);
	glutSolidCube(1.0);
	glPopMatrix();
}

//���ƶ�����ӣ�xΪ�������ӵĸ���
//���ӵ�λ���ǹ̶��ģ��������Ҳ���˿�ʼ���л���
void drawMultiBunny(int num) {
	int i = 1;
	double x = 6;
	double z = 6;
	glMatrixMode(GL_MODELVIEW);
	while (i <= num) {
		glPushMatrix();
		glTranslated(x, 2, z);
		glScaled(3, 3, 3);
		DrawBunny();
		if (i % 4 == 0) {
			x = 6;
			z -= 4;
		}
		else {
			x -= 4;
		}
		i++;
		glPopMatrix();
	}
}

GLint GenList(int bunnyNum)
{
	//typedef int GLint
	//����ʹ��glNewList(GLuint listName,GLenum mode)ֱ�Ӵ����б���listName�����Ѿ���ռ��
	//��listName��ռ�õ�����µ���glNewList��ɾ��ԭ�����б�
	//GLuint glGenlists(GLsize range)����range��������δ��ռ�õ��б�ռ䣬�����׸��б������
	//ע�⣺��Щ��ʾ�б��������unsigned int�͵ģ��������ͨ������range������������ʾ�б�
	GLint lid = glGenLists(1);
	//��ʼ�б�����
	//GL_COMPILE:ֻ���룻GL_COMPILE_AND_EXECUTE:���������ִ��һ��
	glNewList(lid, GL_COMPILE);
	
	drawMultiBunny(bunnyNum);
	DrawTable();

	//�����б�����
	glEndList();
	return lid;
}

void drawScene_list() {
	glCallList(listIndex);
}

void DrawScene()
{
	drawMultiBunny(iBunnyNum);
	DrawTable();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45, whRatio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }

	case 'a':
	{
		eye[0] += fDistance;
		center[0] += fDistance;
		break;
	}
	case 'd':
	{
		eye[0] -= fDistance;
		center[0] -= fDistance;
		break;
	}
	case 'w':
	{
		eye[1] -= fDistance;
		center[1] -= fDistance;
		break;
	}
	case 's':
	{
		eye[1] += fDistance;
		center[1] += fDistance;
		break;
	}
	case 'z':
	{
		eye[2] *= 0.95;
		break;
	}
	case 'c':
	{
		eye[2] *= 1.05;
		break;
	}
	case 'l':
	{
		bDrawList = !bDrawList;	// �л���ʾ�б�ͷ���ʾ�б���Ʒ�ʽ
		break;
	}
	case ' ':
	{
		bAnim = !bAnim;
		break;
	}
	case 'i': {
		if (iBunnyNum < 16) {
			iBunnyNum++;
			//void glDeleteLists(GLuint list,GLsizei range)ɾ����list��ʼ����range���б�
			//����һ��Χ����ĳһ������û�ж�Ӧ��ĳ����ʾ�б���������������
			glDeleteLists(listIndex, 1);
			listIndex = GenList(iBunnyNum);
		}
		break;
	}
	case 'k': {
		if (iBunnyNum > 1) {
			iBunnyNum--;
			glDeleteLists(listIndex, 1);
			listIndex = GenList(iBunnyNum);
		}
		break;
	}
	default: break;
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy(mode, "display list");
	else
		strcpy(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  // ѡ��ͶӰ����
	glPushMatrix();               // ����ԭ����
	glLoadIdentity();             // װ�뵥λ����
	glOrtho(0, 480, 0, 480, -1, 1);    // λ����ͶӰ
	glMatrixMode(GL_MODELVIEW);   // ѡ��Modelview����
	glPushMatrix();               // ����ԭ����
	glLoadIdentity();             // װ�뵥λ����
	glRasterPos2f(10, 10);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // ѡ��ͶӰ����
	glPopMatrix();                // ����Ϊԭ�������
	glMatrixMode(GL_MODELVIEW);   // ѡ��Modelview����
	glPopMatrix();                // ����Ϊԭ�������
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5, 0, 1);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0, 5, 50)��Y������

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_pos[] = { 10, 10, 10, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);

	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glScalef(0.4, 0.4, 0.4);
	if (!bDrawList)
		DrawScene();						// old way
	else
		drawScene_list();                   // new way

	getFPS();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Exercise 4");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	listIndex = GenList(iBunnyNum);

	glutMainLoop();
	return 0;
}