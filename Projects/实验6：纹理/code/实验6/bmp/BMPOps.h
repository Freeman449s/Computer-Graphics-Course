#ifndef _BMP_H_
#define _BMP_H_
#include<cstdio>
#include<cmath>

//(c)2020,Gordon Freeman
//BMPOps.h    Ver.1.01

//���峣��
#define pi 3.1415926

//��������
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

//�ṹ������
class BITMAPFILEHEADER {
public:
	WORD bfType; //�ļ����ͣ�����BMP�ļ�����ֵ��Ϊ"BM",ʮ������ֵΪ42 4D��
	DWORD bfSize; //�ļ���С
	WORD bfReserved1; //�����֣�����
	WORD bfReserved2; //�����֣�����
	DWORD bfOffBits; //����������ļ���ʼλ�õ�ƫ����
	//Ĭ�Ϲ��캯�������г�Ա������ʼ��Ϊ0
	BITMAPFILEHEADER() {
		bfType = 0;
		bfSize = 0;
		bfReserved1 = 0;
		bfReserved2 = 0;
		bfOffBits = 0;
	}
};
class BITMAPINFOHEADER {
public:
	DWORD biSize; //���ṹ��С����Windows����Ϊ40���ֽڣ���
	LONG biWidth; //ͼ���ȣ����أ�
	LONG biHeight; //ͼ��߶ȣ����أ�
	WORD biPlanes;
	WORD biBitCount; //��ɫλ��
	DWORD biCompression;
	DWORD biSizeImage; //��������С���ֽڣ���������ʵ�ʵ���������С��2.
	LONG biXPelsPerMeter; //���������ܶ�
	LONG biYPelsPerMeter; //���������ܶ�
	DWORD biClrUsed;
	DWORD biClrImportant;
	//Ĭ�Ϲ��캯�������г�Ա������ʼ��Ϊ0
	BITMAPINFOHEADER() {
		biSize = 0;
		biWidth = 0;
		biHeight = 0;
		biPlanes = 0;
		biBitCount = 0;
		biCompression = 0;
		biSizeImage = 0;
		biXPelsPerMeter = 0;
		biYPelsPerMeter = 0;
		biClrUsed = 0;
		biClrImportant = 0;
	}
};
class RGBQUAD {
public:
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE reserved;
	//Ĭ�Ϲ��캯�������г�Ա������ʼ��Ϊ0
	RGBQUAD() {
		R = G = B = reserved = 0;
	}
};
class RGBInfo {
public:
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	BYTE *data;
	int width_byte;
	//Ĭ�Ϲ��캯�������г�Ա������ʼ��Ϊ0
	RGBInfo() {
		data = NULL;
		width_byte = 0;
	}
};
class GSInfo {
public:
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	RGBQUAD *palette;
	BYTE *data;
	int width_byte;
	//Ĭ�Ϲ��캯�������г�Ա������ʼ��Ϊ0
	GSInfo() {
		palette = NULL;
		data = NULL;
		width_byte = 0;
	}
};

//����ԭ������
RGBInfo imread_RGB(const char name[]);
GSInfo imread_GS(const char name[]);
void imwrite(RGBInfo info, const char name[]);
void imwrite(GSInfo info, const char name[]);

//ȡ���غ���
//����������RGBͼ����Ϣ��ͼ����ϢӦΪ������ͬ�����ã��ᡢ�������Լ�������Ϊ����
//����ֵ��������ȡ����ָ�������ݵ�����
//ע�⣺RGBֵ���������B,G,R��˳��洢
//     ������Ϊ�������е�һ�����ص�����Ϊ(1,1)
BYTE& GetPixel(RGBInfo& info, int x, int y, int layer);
//����ȡ���غ�����������ֻ����RGB�����������
//����������������ָ�룬��ȣ����ֽڼƣ�����/�����꣬������Ϊ����
//����ֵ��������ȡ����ָ�������ݵ�BYTE������
BYTE& GetPixel(BYTE* data, int w_byte, int x, int y, int layer);
//����ȡ���غ�����������������Ϊ���͵����
//����������������ָ�룬��ȣ������ؼƣ�����/�����꣬������Ϊ����
//����ֵ��������ȡ����ָ�������ݵ�int������
int& GetPixel(int* data, int w_pixel, int x, int y, int layer);
//����ȡ���غ�����������������Ϊ�����͵����
//����������������ָ�룬��ȣ������ؼƣ�����/�����꣬������Ϊ����
//����ֵ��������ȡ����ָ�������ݵ�double������
double& GetPixel(double* data, int w_pixel, int x, int y, int layer);

//RGBתL*a*b*����
//����������RGBInfo�����������Ϊ����
//����ֵ������ָ��L*a*b*��int��ָ��
int* RGB2Lab(RGBInfo& info);
//RGBתL*a*b*��������Ҫ�ĺ���
double f_Lab(double x);
//L*a*b*תRGB����
//����������ָ��L*a*b*��������ָ�룬RGB�����������ؿ�ȣ��ֽڿ���Լ����ظ߶���Ϊ����
//����ֵ������ָ��RGB��������BYTE��ָ��
//ע�⣺���������ͷ�L*a*b*������
BYTE* Lab2RGB(int *Lab, int width_pixel, int width_byte, int height);
//L*a*b*תRGB��������Ҫ�ĺ���
double if_Lab(double x);

//˫���˲�������L*a*b*�ռ䣩
//����������RGBInfo��������ã��ռ����׼�ǿ�����׼����Ϊ����
//����ֵ�����ؾ���˫���˲���ͼ���RGBInfo����
RGBInfo bilateral_Lab(RGBInfo& image, double spa_std_devia, double int_std_devia);
//RGB�ռ�˫���˲�����
RGBInfo bilateral(RGBInfo& image, double spa_std_devia, double int_std_devia);
//����˫���˲�������Ϊ�ӿ��ٶȶ���ƣ��˲�������L*a*b*�ռ���У�����bilateral_Lab��15%����
RGBInfo bilateral_quan(RGBInfo& image, double spa_std_devia, double int_std_devia);
//һԪ��̬�ֲ��ܶȺ���
double norm_dis(double x, double expect, double var);

//����RGBͼ��������B��R������λ�ã�ʹ֮���ڴ��а�R,G,B��˳��洢
//����������RGBInfo�����������Ϊ����
//����ֵ������B��R����λ�þ���������������ָ��
BYTE* swapBR(RGBInfo& image);

#endif