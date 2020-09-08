#include <stdlib.h>
#include "glut/glut.h"
#include "bmp/BMPOps.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;
//0���Ѻۣ�1��Ī�Σ�2�Ź�ߣ�3���Զ���
unsigned textArr[4];

void Draw_Leg();
void drawTable();
void initText();

void Draw_Scene() // This function draws a triangle with RGB colors
{
	//���ò������ɫ�;��淴����
	float reflectance[] = { 1,1,1, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, reflectance);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, reflectance);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textArr[1]);
	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	//glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, reflectance);
	reflectance[0] = reflectance[1] = reflectance[2] = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, reflectance);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);

	drawTable();
}

void Draw_Leg() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textArr[0]);
	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3d(-0.5, 1.5, 0.5);
	glTexCoord2d(0, 0.25);
	glVertex3d(-0.5, -1.5, 0.5);
	glTexCoord2d(0.25, 0.25);
	glVertex3d(0.5, -1.5, 0.5);
	glTexCoord2d(0.25, 1);
	glVertex3d(0.5, 1.5, 0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0.25, 1);
	glVertex3d(0.5, 1.5, 0.5);
	glTexCoord2d(0.25, 0.25);
	glVertex3d(0.5, -1.5, 0.5);
	glTexCoord2d(0.5, 0.25);
	glVertex3d(0.5, -1.5, -0.5);
	glTexCoord2d(0.5, 1);
	glVertex3d(0.5, 1.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0.5, 1);
	glVertex3d(0.5, 1.5, -0.5);
	glTexCoord2d(0.5, 0.25);
	glVertex3d(0.5, -1.5, -0.5);
	glTexCoord2d(0.75, 0.25);
	glVertex3d(-0.5, -1.5, -0.5);
	glTexCoord2d(0.75, 1);
	glVertex3d(-0.5, 1.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0.75, 1);
	glVertex3d(-0.5, 1.5, -0.5);
	glTexCoord2d(1, 1);
	glVertex3d(-0.5, 1.5, 0.5);
	glTexCoord2d(1, 0.25);
	glVertex3d(-0.5, -1.5, 0.5);
	glTexCoord2d(0.75, 0.25);
	glVertex3d(-0.5, -1.5, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0.75);
	glVertex3d(-0.5, 1.5, 0.5);
	glTexCoord2d(0.25, 0.75);
	glVertex3d(0.5, 1.5, 0.5);
	glTexCoord2d(0.25, 1);
	glVertex3d(0.5, 1.5, -0.5);
	glTexCoord2d(0, 1);
	glVertex3d(-0.5, 1.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0.75);
	glVertex3d(-0.5, -1.5, 0.5);
	glTexCoord2d(0.25, 0.75);
	glVertex3d(0.5, -1.5, 0.5);
	glTexCoord2d(0.25, 1);
	glVertex3d(0.5, -1.5, -0.5);
	glTexCoord2d(0, 1);
	glVertex3d(-0.5, -1.5, -0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void drawTable() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textArr[0]);
	glColor3d(1, 1, 1);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-3, 1.5, 3);
	glTexCoord2d(1, 0);
	glVertex3d(3, 1.5, 3);
	glTexCoord2d(1, 1);
	glVertex3d(3, 1.5, -3);
	glTexCoord2d(0, 1);
	glVertex3d(-3, 1.5, -3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-3, 2.5, 3);
	glTexCoord2d(1, 0);
	glVertex3d(3, 2.5, 3);
	glTexCoord2d(1, 1);
	glVertex3d(3, 2.5, -3);
	glTexCoord2d(0, 1);
	glVertex3d(-3, 2.5, -3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0.75);
	glVertex3d(-3, 1.5, 3);
	glTexCoord2d(1, 0.75);
	glVertex3d(3, 1.5, 3);
	glTexCoord2d(1, 1);
	glVertex3d(3, 2.5, 3);
	glTexCoord2d(0, 1);
	glVertex3d(-3, 2.5, 3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0.5);
	glVertex3d(3, 1.5, 3);
	glTexCoord2d(1, 0.5);
	glVertex3d(3, 1.5, -3);
	glTexCoord2d(1, 0.75);
	glVertex3d(3, 2.5, -3);
	glTexCoord2d(0, 0.75);
	glVertex3d(3, 2.5, 3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0.25);
	glVertex3d(3, 1.5, -3);
	glTexCoord2d(1, 0.25);
	glVertex3d(-3, 1.5, -3);
	glTexCoord2d(1, 0.5);
	glVertex3d(-3, 2.5, -3);
	glTexCoord2d(0, 0.5);
	glVertex3d(3, 2.5, -3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-3, 1.5, -3);
	glTexCoord2d(1, 0);
	glVertex3d(-3, 1.5, 3);
	glTexCoord2d(1, 0.25);
	glVertex3d(-3, 2.5, 3);
	glTexCoord2d(0, 0.25);
	glVertex3d(-3, 2.5, -3);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-1.5, 0, 1.5);
	Draw_Leg();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1.5, 0, -1.5);
	Draw_Leg();
	glPopMatrix();
	glPushMatrix();
	glTranslated(1.5, 0, -1.5);
	Draw_Leg();
	glPopMatrix();
	glPushMatrix();
	glTranslated(1.5, 0, 1.5);
	Draw_Leg();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void updateView(int width, int height) {
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

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y) {
	switch (k) {
		case 27:
		case 'q': { exit(0); break; }
		case 'p': { bPersp = !bPersp; break; }

		case ' ': { bAnim = !bAnim; break; }
		case 'o': { bWire = !bWire; break; }

		case 'a':
		{
			eye[0] -= 0.2f;
			center[0] -= 0.2f;
			break;
		}
		case 'd':
		{
			eye[0] += 0.2f;
			center[0] += 0.2f;
			break;
		}
		case 'w':
		{
			eye[1] -= 0.2f;
			center[1] -= 0.2f;
			break;
		}
		case 's':
		{
			eye[1] += 0.2f;
			center[1] += 0.2f;
			break;
		}
		case 'z':
		{
			eye[2] -= 0.2f;
			center[2] -= 0.2f;
			break;
		}
		case 'c':
		{
			eye[2] += 0.2f;
			center[2] += 0.2f;
			break;
		}
	}

	updateView(wHeight, wWidth);
}

void redraw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	float ambient[] = { 0.2,0.2,0.2,1 };
	GLfloat light_pos[] = { 5,5,5,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_LIGHT0);

	//glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	//glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	initText();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

//�����Զ�����������Ϊ�����Σ����Ϊ����������񣬳�����Ϊ32�ı���������������ָ��
//��������һ��������Ϊ�������ò���ָ��������ı߳�Ϊ32�ļ���
BYTE* geneText(int k) {
	int edge = 32 * k;
	BYTE* data = new BYTE[edge * 3 * edge];
	int x, y;
	for (int i = 0; i <= k - 1; i++) {
		for (int j = 0; j <= k - 1; j++) {
			int delta = i * edge * 32 * 3 + j * 32 * 3;
			//���Ƶ�λͼ��
			for (x = 0; x <= 15; x++) {
				//����Ϊ��
				for (y = 0; y <= 15; y++) {
					data[delta + y * edge * 3 + x * 3] = data[delta + y * edge * 3 + x * 3 + 1] = data[delta + y * edge * 3 + x * 3 + 2] = 0;
				}
				//����Ϊ��
				for (y = 16; y <= 31; y++) {
					data[delta + y * edge * 3 + x * 3] = 255;
					data[delta + y * edge * 3 + x * 3 + 1] = data[delta + y * edge * 3 + x * 3 + 2] = 0;
				}
			}
			for (x = 16; x <= 31; x++) {
				//����Ϊ��
				for (y = 0; y <= 15; y++) {
					data[delta + y * edge * 3 + x * 3] = 255;
					data[delta + y * edge * 3 + x * 3 + 1] = data[delta + y * edge * 3 + x * 3 + 2] = 0;
				}
				//����Ϊ��
				for (y = 16; y <= 31; y++) {
					data[delta + y * edge * 3 + x * 3] = data[delta + y * edge * 3 + x * 3 + 1] = data[delta + y * edge * 3 + x * 3 + 2] = 0;
				}
			}
		}
	}
	return data;
}

void initText() {
	//��ȡ�봦��BMP�ļ�
	RGBInfo crack = imread_RGB("bmp\\Crack.bmp");
	RGBInfo monet = imread_RGB("bmp\\Monet.bmp");
	RGBInfo spot = imread_RGB("bmp\\Spot.bmp");
	BYTE* crackData_RGB = swapBR(crack);
	BYTE* monetData_RGB = swapBR(monet);
	BYTE* spotData_RGB = swapBR(spot);
	glGenTextures(4, textArr);

	//���ø������������
	glBindTexture(GL_TEXTURE_2D, textArr[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, crack.InfoHeader.biWidth,
		crack.InfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, crackData_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textArr[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, monet.InfoHeader.biWidth,
		monet.InfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, monetData_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textArr[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spot.InfoHeader.biWidth,
		spot.InfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, spotData_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//�����Զ�������
	BYTE* customizedText = geneText(4);
	glBindTexture(GL_TEXTURE_2D, textArr[3]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //���ֽڶ�ȡ������Խ��
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE,
		customizedText);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//�������
	glBindTexture(GL_TEXTURE_2D, 0);
}