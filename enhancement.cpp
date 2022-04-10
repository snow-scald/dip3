#include<cmath>
#include<fstream>
#include<vector>
#include"enhancement.h"
#include"hxlbmpfile.h"

using namespace std;

//生成归一化了的规定化直方图
vector<double> hgen()
{					
	vector<double> res(256, 0);
	double sum = 0;
	for(int i = 0; i < 256; i++)
	{
		res[i] = (0.25 - pow(((double(i) / 256) - 0.5), 2));
		sum += res[i];
	}
	for(int i = 0; i < 256; i++)
	{
		res[i] /= sum;
	}
	return res;
}

//统计图片的直方图（非归一化）
vector<int> statishgram(HXLBMPFILE *bmp)
{
	vector<int> res(256, 0);
	for(int i = 0; i < 256; i++)
	{
		res[i] = 0;
	}
	for(int i = 0; i < bmp->iImageh; i++)
	{
		for(int j = 0; j < bmp->iImagew; j++)
		{
			res[bmp->pDataAt(i)[j]] += 1;
		}
	}
	return res;
}

//均衡化变化函数
vector<int> eqchange(vector<int> invec) {			
	vector<int> res(256, 0);
	double sum = 0, sumnormal = 0;
	for(int i = 0; i < 256; i++)
	{
		sum += invec[i];
	}
	for(int i = 0; i < 256; i++) {
		sumnormal += invec[i] / sum;
		res[i] = int(255 * sumnormal + 0.5);
	}
	return res;
}


//规定化变化函数的子函数
vector<int> redivide(vector<int> &res,
	vector<double> &spc, vector<double> &sumnormalin){
	for(int i = 0; i < 256; i++)
	{
		double now = 2;

		for(int j = 0; j < 256; j++)
		{
			if(abs(sumnormalin[i] - spc[j]) <= now)
			{
				now = abs(sumnormalin[i] - spc[j]);
				if(j==255)
				{
					res[i] = j;
					break;
				}
			}
			else
			{
				res[i] = j - 1;
				break;
			}
 		}
	}
	return res;
}
//规定化变化函数
vector<int> spechange(vector<int> invec, vector<double> spc)
{
	vector<int> res(256, 0);
	vector<double> sumnormalvec(256, 0);
	double sum = 0;
	double sumnormal = 0;
	for(int i = 0; i < 255; i++)
	{
		spc[i + 1] += spc[i];
	}
	for(int i = 0; i < 256; i++)
	{
		sum += invec[i];
	}
	for(int i = 0; i < 256; i++)
	{
		sumnormal+= invec[i] / sum;
		sumnormalvec[i]=sumnormal;
	}
	res = redivide(res, spc, sumnormalvec);
	
	return res;
}

//按变化函数对图像施以变化
void transbmp(HXLBMPFILE *bmp,vector<int> func, const char *oname)
{
	HXLBMPFILE output;
	output.iImageh = bmp->iImageh;
	output.iImagew = bmp->iImagew;
	output.iYRGBnum = bmp->iYRGBnum;
	if(!output.IspImageDataOk())
	{
		return;
	}
	for(int i = 0; i < bmp->iImageh; i++)
	{
		for(int j = 0; j < bmp->iImagew; j++)
		{
			output.pDataAt(i)[j] = func[bmp->pDataAt(i)[j]];
		}
	}
	output.SaveBMPFile(oname);
}