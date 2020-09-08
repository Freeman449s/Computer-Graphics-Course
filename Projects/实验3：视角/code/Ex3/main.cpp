// This assignment may cost you some efforts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

// ʵ�鱨�������д����룬���Ժ�������⣬�Լ����õ�˳�򣬲���ȡ�˼��Ϊʲô�������ӵ��õģ�Ϊʲô���������������õģ��������ȵ������ֵ���о������⡣
#include <stdlib.h>
#include "glut\glut.h"


float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f
double dTeapotRotate = 0;

bool bPersp = false; //�Ƿ�͸��ͶӰ
bool bAnim = false; //�Ƿ���ת
bool bWire = false; //�Ƿ���״��ʾ
bool doesTeapotRotate = false; //����Ƿ���ת

int wHeight = 0;
int wWidth = 0;

//todo
//hint: some additional parameters may needed here when you operate the teapot

void Draw_Leg() {
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

double teapotCenter[] = { 0, 0, 0 };
//double objCenter[] = { 0, 0, 0 };

void Draw_Scene() {
	//���Ʋ��
	glPushMatrix();
	glTranslated(teapotCenter[0], teapotCenter[1], 4 + 1);
	glRotated(dTeapotRotate, 0, 0, 1);
	glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	//todo; hint: when operate the teapot, you may need to change some parameters
	glutSolidTeapot(1);
	glPopMatrix();

	//��������
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}

void updateView(int width, int height) {
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp) {
		gluPerspective(90, whRatio, 1, 100);
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height) {
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle() {
	glutPostRedisplay();
}

float eye[] = { 0, 0, 3.5 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y) {
	switch (k) {
		case 27:
		case 'q': { exit(0); break; }
		case 'p': { bPersp = !bPersp; updateView(wHeight, wWidth); break; }

		case ' ': { bAnim = !bAnim; break; }
		case 'o': { bWire = !bWire; break; }

		case 'a':
		{//todo, hint: eye[] and center[] are the keys to solve the problems
			eye[0] += 0.2;
			center[0] += 0.2;
			break;
		}
		case 'd':
		{
			eye[0] -= 0.2;
			center[0] -= 0.2;
			break;
		}
		case 'w':
		{
			eye[1] -= 0.2;
			center[1] -= 0.2;
			break;
		}
		case 's':
		{
			eye[1] += 0.2;
			center[1] += 0.2;
			break;
		}
		case 'z':
		{
			eye[2] -= 0.2;
			break;
		}
		case 'c':
		{
			eye[2] += 0.2;
			break;
		}

		//�����ز���
		case 'l':
		{
			if (teapotCenter[0] <= 2.5) {
				//�ƶ��ĴΣ��պõ���߽�
				teapotCenter[0] += 0.3125;
			}
			break;
		}
		case 'j':
		{
			if (teapotCenter[0] >= -2.5) {
				teapotCenter[0] -= 0.3125;
			}
			break;
		}
		case 'i':
		{
			if (teapotCenter[1] <= 2) {
				teapotCenter[1] += 0.25;
			}
			break;
		}
		case 'k':
		{
			if (teapotCenter[1] >= -2) {
				teapotCenter[1] -= 0.25;
			}
			break;
		}
		case 'e':
		{
			if (doesTeapotRotate) doesTeapotRotate = false;
			else doesTeapotRotate = true;
			break;
		}
	}
}


void redraw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	//��һ�����eyex, eyey, eyezȷ����������������λ��
	//�ڶ������centerx, centery, centerzȷ�������ͷ��׼�����������������λ��
	//������˵ȷ���˾�ͷ�ĳ���
	//���������upx, upy, upzȷ��������ϵķ��������������еķ���
	//��ȷ�����λ�ú;�ͷ���������������ƾ�ͷ������ת������Ҫ������������������̶������
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//�������
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	//�丩��Ϊƽ�ӡ��⽫������Ļ����ʾ���Ϸ���Ϊz������
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate += 0.5f;
	if (doesTeapotRotate) dTeapotRotate += 0.5;

	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("���ӺͲ��");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}