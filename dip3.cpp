#include <iostream>
#include<vector>
#include "hxlbmpfile.h"
#include "enhancement.h"

using namespace std;


int main()
{

	HXLBMPFILE bmpfile;
	if(!bmpfile.LoadBMPFile("input.bmp"))
	{
		return 1;
	}
	printf("Image in!\n");

	//生成规定化目标直方图
	vector<double> spchg = hgen();
	outputcsv("spchg.csv", spchg);
	cout << "Specify histograms is generated!" << endl;

	//统计原图像的直方图
	vector<int> ohg= statishgram(&bmpfile);
	outputcsv("ohg.csv", ohg);
	cout << "The original histogram is generated!\n" << endl;

	//生成均衡化变化函数
	vector<int> myEqchange = eqchange(ohg);
	outputcsv("eqchange.csv", myEqchange);
	cout << "The eqchange function is generated!\n" << endl;
	//对原图像做均衡化
	transbmp(&bmpfile, myEqchange, "output1.bmp");
	cout << "The eqchange image is generated!\n" << endl;

	//读入均衡化之后的图像
	HXLBMPFILE eqbmpfile;
	if(!eqbmpfile.LoadBMPFile("output1.bmp"))
	{
		return 1;
	}
	printf("Equalized Image in!\n");
	//统计均衡化图像的直方图
	vector<int> ehg = statishgram(&eqbmpfile);
	outputcsv("ehg.csv", ehg);
	cout << "The Equalized histogram is generated!\n" << endl;


	//生成规定化变化函数
	vector<int> mySpechange = spechange(ohg, spchg);
	outputcsv("spechange.csv", mySpechange);
	cout << "The spechange function is generated!\n" << endl;
	//对原图像做规定化
	transbmp(&bmpfile, mySpechange, "output2.bmp");
	cout << "The Specificed image is generated!\n" << endl;

	//读入规定化之后的图像
	HXLBMPFILE spbmpfile;
	if(!spbmpfile.LoadBMPFile("output2.bmp"))
	{
		return 1;
	}
	printf("specificed Image in!\n");
	//统计规定化图像的直方图
	vector<int> shg = statishgram(&spbmpfile);
	outputcsv("shg.csv", shg);
	cout << "The Specificed histogram is generated!\n" << endl;

	return 0;
}
