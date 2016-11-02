#include <opencv2/core/core.hpp>//������ͷ�ļ�ʱ֧��opencv�汾��ͷ�ļ����������ݽṹ���������㣬���ݱ任�ڴ������ѧ�ı���
#include <opencv2/highgui/highgui.hpp>//����ͼ�ν������Ƶͼ�����ͷ�ļ�
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>//�ļ�д�������ڴ�д��洢�豸
#include <assert.h>//���ʽ�����ȷ�Բ��Բ���ʹ������ֹ
#include <time.h>
#include <cmath>//��ѧ����

using namespace cv;
using namespace std;

//default filter and iteration number
int ItNum = 10;
int Type = 2;

#include "DM.h"

int main(int argc, char** argv)//��Ҫ���������������·���ļ����������������˲������ͣ�
{
    
    DM DualMesh;
    if (argc!=4)
    {
       cout<<"usage: main filename filterType Iterations.\n For example: ./cf lena.bmp m 30, where m means Mean Curvature Filter. \n";
	   cout << "Possibal Filters: t(Total Variation) \n";
	   cout << "				  m(Mean Curvature) \n";
	   cout << "				  g(Gaussian Curvature) \n";
	   cout << "				  d(Difference Curvature) \n";
	   system("pause");
	   return -1;
    }
    DualMesh.read(argv[1]);//��ȡͼ��֡(ͼ���·����ͼ����)
    ItNum = atoi(argv[3]);//���ַ���ת��������(ѭ����������)

    char * filterType = argv[2];//�����˲�������
    if (*filterType == 't') Type = 0;
    if (*filterType == 'm') Type = 1;
	if (*filterType == 'g') Type = 1;
    if (*filterType == 'd') Type = 3;


    DualMesh.split();//�ָ������������ԭͼ��ָ���������ص㣬��԰��Բ�����Ǻ����ǣ�����ԭͼ����Сһ��
    double mytime;
    DualMesh.Filter(Type, mytime, ItNum);//�����������ѡ���˲������࣬����ͼ��ָ�Ϊ�������ص�
    cout<<"runtime is "<<mytime<<" milliseconds."<<endl;//��ʾ�㷨ִ��ʱ��

    DualMesh.merge();//����������ֵ���Ϊһ��������ͼ��
    DualMesh.write();//��Mat���͵ľ��󱣴浽ͼ��

    DualMesh.read(argv[1]);
    DualMesh.FilterNoSplit(Type, mytime, ItNum);//����ͼ����зָ������������˲�
    cout<<"runtime (noSplit) is "<<mytime<<" milliseconds."<<endl;
    DualMesh.write("CF_NoSplit_result.png");
    
	system("pause");
    return 0;
}


