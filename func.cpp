#include<cmath>
#include<fstream>
#include"hxlbmpfile.h"


using namespace std;

bool outputcsv(const char *outpath, double *myfunc)
{
	ofstream out(outpath, ios::out | ios::trunc);
	out << "����ֵ" << "," << "����ֵ" << endl;
	for(int i = 0; i < 256; i++)
	{
		out << i << "," << myfunc[i] << endl;
	}
	return TRUE;
}

bool outputcsv(const char *outpath, int *myfunc)
{
	ofstream out(outpath, ios::out | ios::trunc);
	out << "����ֵ" << "," << "����ֵ" << endl;
	for(int i = 0; i < 256; i++)
	{
		out << i << "," << myfunc[i] << endl;
	}
	return TRUE;
}


double *hgen()
{					//���ɹ�һ���˵�Ŀ��ֱ��ͼ
	double *ptr = new double[256];
	double sum = 0;
	for(int i = 0; i < 256; i++)
	{
		ptr[i] = (0.25 - pow(((double(i) / 256) - 0.5), 2));
		sum += ptr[i];
	}
	for(int i = 0; i < 256; i++)
	{
		ptr[i] /= sum;
	}
	return ptr;
}

int *statishgram(HXLBMPFILE *bmp)
{				//ͳ��ͼƬ��ֱ��ͼ���ǹ�һ����
	int *ptr = new int[256];
	for(int i = 0; i < 256; i++)
	{
		ptr[i] = 0;
	}
	for(int i = 0; i < bmp->iImageh; i++)
	{
		for(int j = 0; j < bmp->iImagew; j++)
		{
			ptr[bmp->pDataAt(i)[j]] += 1;
		}
	}
	return ptr;
}

int *eqchange(int *inptr)
{					//���⻯�仯����
	int *outptr = new int[256];
	double *normalinptr = new double[256];
	double *sumnormalinptr = new double[256];
	double sum = 0;
	double sumnormal = 0;
	for(int i = 0; i < 256; i++)
	{
		outptr[i] = 0;
		sum += inptr[i];
	}
	for(int i = 0; i < 256; i++)
	{
		normalinptr[i] = inptr[i] / sum;
		sumnormal += normalinptr[i];
		sumnormalinptr[i] = sumnormal;
	}
	for(int i = 0; i < 256; i++)
	{
		outptr[i] = int(255 * sumnormalinptr[i] + 0.5);
	}
	delete[] normalinptr;
	delete[] sumnormalinptr;
	return outptr;
}

int *spechange(int *inptr, double *spcptr)
{			//�涨���仯����
	int *outptr = new int[256];
	double sum = 0;
	double sumnormal = 0;
	double *normalinptr = new double[256];
	double *sumnormalinptr = new double[256];
	for(int i = 0; i < 255; i++)
	{
		spcptr[i + 1] += spcptr[i];
	}
	for(int i = 0; i < 256; i++)
	{
		sum += inptr[i];
	}
	for(int i = 0; i < 256; i++)
	{
		normalinptr[i] = inptr[i] / sum;
		sumnormal += normalinptr[i];
		sumnormalinptr[i] = sumnormal;
	}

	for(int i = 0; i < 256; i++)
	{
		double now = 1;

		for(int j = 0; j < 256; j++)
		{
			if(abs(sumnormalinptr[i] - spcptr[j]) <= now)
			{
				now = abs(sumnormalinptr[i] - spcptr[j]);
			}
			else
			{
				outptr[i] = j - 1;
				break;
			}

		}
	}
	return outptr;

}

void transbmp(HXLBMPFILE *bmp, int *func, const char *oname)
{				//���仯������ͼ��ʩ�Ա仯
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