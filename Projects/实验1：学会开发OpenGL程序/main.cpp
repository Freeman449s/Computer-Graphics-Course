#include "glut.h"
#include<cmath>

#define pi 3.14159

void draw_deltoid(float x, float y, double len1, double theta);
double ang2rad(double angle);
void draw_star(float x, float y, double len, double theta);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-1, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(-1, -1, 0);
	glEnd();
	draw_star(-2.0 / 3, 0.5, 0.2, pi / 2);
	draw_star(-1.0 / 3, 0.8, 1.0 / 15, pi + atan(0.6));
	draw_star(-0.2, 0.6, 1.0 / 15, pi + atan(1.0 / 7));
	draw_star(-0.2, 0.3, 1.0 / 15, pi - atan(2.0 / 7));
	draw_star(-1.0 / 3, 0.1, 1.0 / 15, pi - atan(0.8));
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(600, 400);
	glutCreateWindow("���Ǻ���");

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}

//�������Ρ�
//(x,y)Ϊ����36��˵����ꡣ
//thetaΪ������72���Ϊ��㣬36���Ϊ�յ��γɵ������ĽǶȡ���λΪ���ȡ�
//len1_xΪ���������˵�����߳�������һ���ȵı�����ʾ��
void draw_deltoid(float x, float y, double len1_x, double theta) {
	double len3_x = sin(ang2rad(18)) / sin(ang2rad(126))*len1_x;
	double len2_x = sin(ang2rad(36)) / sin(ang2rad(126))*len1_x;
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, 0);
	glVertex3f(x + len3_x * cos(theta - pi / 5), y + len3_x * sin(theta - pi / 5)*1.5, 0);
	glVertex3f(x + len1_x * cos(theta), y + len1_x * sin(theta)*1.5, 0);
	glVertex3f(x + len3_x * cos(theta + pi / 5), y + len3_x * sin(theta + pi / 5)*1.5, 0);
	glEnd();
}

//�������ǡ�
//(x,y)Ϊ����ǵ���㡣
//thetaΪ������ǶԳ���ָ�����μ�˵������ķ���
//lenΪ����36��˵�72��˵ĳ��ȣ�����һ���ȵı�����ʾ��
void draw_star(float x, float y, double len_x, double theta) {
	draw_deltoid(x, y, len_x, theta);
	for (int i = 1; i <= 4; i++) {
		theta += 2.0 / 5 * pi;
		draw_deltoid(x, y, len_x, theta);
	}
}

double ang2rad(double angle) {
	return angle / 360 * 2 * pi;
}