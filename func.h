#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include"hxlbmpfile.h"

bool outputcsv(const char *outpath, double *myfunc);
bool outputcsv(const char *outpath, int *myfunc);
double *hgen();
int *statishgram(HXLBMPFILE *bmp);
int *eqchange(int *inptr);
int *spechange(int *inptr, double *spcptr);
void transbmp(HXLBMPFILE *bmp, int *func, const char *oname);
