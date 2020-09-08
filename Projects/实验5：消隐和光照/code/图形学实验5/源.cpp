#include <stdlib.h>
#include "glut/glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f
float fReflectance[] = { 1,1,1,1 };
GLfloat light0_pos[] = { -5,5,0,1 };
GLfloat light1_pos[] = { 5,5,0,1 };
float spotlightDir[3];
float fCutoff = 30;

//颜色：红梅
const float kohbai[] = { 0.882,0.420,0.549,1 };
//颜色：柳茶
const float yanagicha[] = { 0.576,0.588,0.314,1 };
//白色
const float white[] = { 1,1,1,1 };
const float ambientLight[] = { 0.2,0.2,0.2,1 };
const float *light0Color = white;
const float *light1Color = white;

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;
int lightNo = 0;

void Draw_Leg();

void setReflectance(float reflectR, float reflectG, float reflectB, float reflectAlpha) {
	fReflectance[0] = reflectR;
	fReflectance[1] = reflectG;
	fReflectance[2] = reflectB;
	fReflectance[3] = reflectAlpha;
}

void Draw_Table()
{
	//设置茶壶颜色使之呈现金色；修改茶壶镜面反射率
	setReflectance(0.82, 0.71, 0.45, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fReflectance);
	setReflectance(1, 1, 1, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fReflectance);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	setReflectance(0, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fReflectance);

	//设置桌面颜色
	setReflectance(1, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fReflectance);
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	//设置桌腿
	setReflectance(0, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fReflectance);
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	setReflectance(1, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fReflectance);
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	setReflectance(0, 1, 1, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fReflectance);
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	setReflectance(0, 0, 1, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fReflectance);
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else {
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;
	}
	case 'd': {
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
	}
	case 'w': {
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
	}
	case 's': {
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
	}
	case 'z': {
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
	}
	case 'c': {
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
	}
	case 'f': {
		if (lightNo == 0) lightNo = 1;
		else if (lightNo = 1) lightNo = 0;
		break;
	}
	case '=': {
		if (fCutoff <= 80) fCutoff += 5;
		break;
	}
	case '-': {
		if (fCutoff >= 10) fCutoff -= 5;
		break;
	}

	}
	if (lightNo == 0) {
		switch (k) {
		//移动光源位置
		case 'i': {
			light0_pos[1] += 0.2;
			break;
		}
		case 'k': {
			light0_pos[1] -= 0.2;
			break;
		}
		case 'j': {
			light0_pos[0] -= 0.2;
			break;
		}
		case 'l': {
			light0_pos[0] += 0.2;
			break;
		}
		case 'n': {
			light0_pos[2] += 0.2;
			break;
		}
		case 'm': {
			light0_pos[2] -= 0.2;
			break;
		}
		//循环切换光线颜色
		case 'e': {
			if (light0Color == white) light0Color = kohbai;
			else if (light0Color == kohbai) light0Color = yanagicha;
			else if (light0Color == yanagicha) light0Color = white;
			break;
		}

		}
	}
	else if (lightNo == 1) {
		switch(k) {
		case 'i': {
			light1_pos[1] += 0.2;
			break;
		}
		case 'k': {
			light1_pos[1] -= 0.2;
			break;
		}
		case 'j': {
			light1_pos[0] -= 0.2;
			break;
		}
		case 'l': {
			light1_pos[0] += 0.2;
			break;
		}
		case 'n': {
			light1_pos[2] += 0.2;
			break;
		}
		case 'm': {
			light1_pos[2] -= 0.2;
			break;
		}
		case 'e': {
			if (light1Color == white) light1Color = kohbai;
			else if (light1Color == kohbai) light1Color = yanagicha;
			else if (light1Color == yanagicha) light1Color = white;
			break;
		}

		}
	}
	

	updateView(wHeight, wWidth);
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//0号：点光源
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_LIGHT0);
	
	//1号：聚光灯
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Color);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, fCutoff);
	spotlightDir[0] = -light1_pos[0];
	spotlightDir[1] = 5 - light1_pos[1];
	spotlightDir[2] = -light1_pos[2];
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDir);
	glEnable(GL_LIGHT1);

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Table();

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}