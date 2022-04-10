#define _CRT_SECURE_NO_WARNINGS
#ifndef ENHANCEMENT
#define ENHANCEMENT

#include "stdio.h"
#include<vector>
#include<iostream>
#include<fstream>
#include"hxlbmpfile.h"

using namespace std;

vector<double> hgen();
vector<int> statishgram(HXLBMPFILE *bmp);
vector<int> eqchange(vector<int> inptr);
vector<int> spechange(vector<int> invec, vector<double> spc);
void transbmp(HXLBMPFILE *bmp, vector<int> func, const char *oname);

//�����������excel�ļ������ڲ����˷��ͷ���
//������ͷ�ļ���������ʵ��
template <typename T>
bool outputcsv(const char *outpath, vector<T> myfunc)
{
	ofstream out(outpath, ios::out | ios::trunc);
	out << "����ֵ" << "," << "����ֵ" << endl;
	for(int i = 0; i < 256; i++)
	{
		out << i << "," << myfunc[i] << endl;
	}
	return TRUE;
}
#endif 