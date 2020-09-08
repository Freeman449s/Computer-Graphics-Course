// glutEx1.cpp : 定义控制台应用程序的入口点。
//
//注意FPS函数的应用

//显示列表：一系列预存起来以待以后调用的函数
//相比立即调用具有更高的性能。例如，一系列CTM矩阵的调用，创建为显示列表后将仅保存结果矩阵。
//一旦显示列表被建立，则在删除前不能再被修改
#include <stdlib.h>
#include "glut.h"
#include <stdio.h>
#include <string.h>

#include "stanford_bunny.h"

float eye[] = { 0, 8, 12 };
float center[] = { 0, 0, 0 };
float fDistance = 0.2f;
float fRotate = 0;
bool bAnim = false; //Anim:animation 动画（旋转）模式

bool bDrawList = false;
GLint listIndex = 0;

int iBunnyNum = 1;

void DrawTable()
{
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(16, 2, 16);
	//在(0,0,0)位置绘制边长x的正方体
	//使用glScale改变边长，绘制长方体
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

//绘制多个兔子，x为绘制兔子的个数
//兔子的位置是固定的，从桌面右侧近端开始逐行绘制
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
	//可以使用glNewList(GLuint listName,GLenum mode)直接创建列表，但listName可能已经被占用
	//在listName被占用的情况下调用glNewList将删除原来的列表
	//GLuint glGenlists(GLsize range)生成range个连续的未被占用的列表空间，返回首个列表的名称
	//注意：这些显示列表的名称是unsigned int型的，因而可以通过传入range生成连续的显示列表
	GLint lid = glGenLists(1);
	//开始列表声明
	//GL_COMPILE:只编译；GL_COMPILE_AND_EXECUTE:编译后立即执行一次
	glNewList(lid, GL_COMPILE);
	
	drawMultiBunny(bunnyNum);
	DrawTable();

	//结束列表声明
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
		bDrawList = !bDrawList;	// 切换显示列表和非显示列表绘制方式
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
			//void glDeleteLists(GLuint list,GLsizei range)删除从list开始连续range个列表
			//当这一范围内有某一索引并没有对应到某个显示列表，该索引将被忽略
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
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glOrtho(0, 480, 0, 480, -1, 1);    // 位置正投影
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glRasterPos2f(10, 10);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5, 0, 1);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0, 5, 50)，Y轴向上

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