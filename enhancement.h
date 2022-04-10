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

//将数组输出到excel文件，由于采用了泛型方法
//必须在头文件中声明并实现
template <typename T>
bool outputcsv(const char *outpath, vector<T> myfunc)
{
	ofstream out(outpath, ios::out | ios::trunc);
	out << "像素值" << "," << "函数值" << endl;
	for(int i = 0; i < 256; i++)
	{
		out << i << "," << myfunc[i] << endl;
	}
	return TRUE;
}
#endif 