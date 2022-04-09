#include <iostream>
#include "hxlbmpfile.h"
#include "func.h"

using namespace std;

int main()
{

	HXLBMPFILE bmpfile;
	HXLBMPFILE bmpout1, bmpout2;
	if(!bmpfile.LoadBMPFile("input.bmp"))
	{
		return 1;
	}
	printf("Image in!\n");

	double *spchg = hgen();
	outputcsv("spchg.csv", spchg);
	cout << "Specify histograms is generated!" << endl;

	int *ohg = statishgram(&bmpfile);
	outputcsv("ohg.csv", ohg);
	cout << "The original histogram is generated!\n" << endl;

	int *myEqchange = eqchange(ohg);
	outputcsv("eqchange.csv", myEqchange);
	cout << "The eqchange function is generated!\n" << endl;

	transbmp(&bmpfile, myEqchange, "output1.bmp");
	cout << "The eqchange image is generated!\n" << endl;

	int *myspechange = spechange(ohg, spchg);
	outputcsv("spechange.csv", myspechange);
	cout << "The spechange function is generated!\n" << endl;

	transbmp(&bmpfile, myspechange, "output2.bmp");
	cout << "The spechange image is generated!\n" << endl;

	return 0;
}
