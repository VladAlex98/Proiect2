#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <complex>
#include <algorithm>
#include <vector>
#include <regex>

using namespace std;

#define PI 3.14159265359

unsigned KNN(Point arrh[], Point arrm[], Point arrn[], unsigned n, Point p);
double RMS(vector<double> v);
void FFT(const unsigned int N, vector<double> values, vector<double>& values_fft);

struct Point//structura ce contine coordonatele si distantele fiecarui punct;
{
	double x, y;
	double dist;
};


unsigned KNN(Point arrh[], Point arrm[], Point arrn[], unsigned n, Point p)//aici dau ca parametrii vectori ce contin valori pt fiecare tip
{                                                                          //tip de bola si un vector de test pentru care voi primi un rezultat
	for (unsigned i = 0; i < n; i++)
	{//am calculat distantele pctului de test fata de fiecare tip de punct 
		arrh[i].dist = sqrt((arrh[i].x - p.x) * (arrh[i].x - p.x) + (arrh[i].y - p.y) * (arrh[i].y - p.y));
		arrm[i].dist = sqrt((arrm[i].x - p.x) * (arrm[i].x - p.x) + (arrm[i].y - p.y) * (arrm[i].y - p.y));
		arrn[i].dist = sqrt((arrn[i].x - p.x) * (arrn[i].x - p.x) + (arrn[i].y - p.y) * (arrn[i].y - p.y));
	}//in fiecare tip de boala am salvat distanta fata de pctul de test


	unsigned freq1 = 0;
	unsigned freq2 = 0;
	unsigned freq3 = 0;
	//am calculat distanta minima iar apoi am numarat cate din pctele de test erau mai apropiate de unul din simptome
	for (unsigned i = 0; i < n; i++)
	{
		double min = 1000;
		if (arrh[i].dist < min)
			min = arrh[i].dist;
		if (arrm[i].dist < min)
			min = arrm[i].dist;
		if (arrn[i].dist < min)
			min = arrn[i].dist;

		if (arrh[i].dist == min)
			freq1++;
		if (arrm[i].dist == min)
			freq2++;
		if (arrn[i].dist == min)
			freq3++;
	}

	int max = 0;
	if (freq1 > max) 
		max = freq1;
	if (freq2 > max)
		max = freq2;
	if (freq3 > max) 
		max = freq3;

	//tipul de simptom cel mai des intalnit ne da verdictul final si boala de care sufera pacientul
	if (max == freq1)
	{
		return 1;
	}
	if (max == freq2)
	{
		return 2;
	}
	if (max == freq3)
	{
		return 3;
	}

}

double RMS(vector<double> v)
{
	double sum = 0;

	for (unsigned i = 0; i < v.size(); i++)
	{
		sum = sum + (v[i] * v[i]);
	}

	return sqrt(sum / v.size());
}

void FFT(const unsigned int N, vector<double> values, vector<double> &values_fft)
{

	for (unsigned int k = 0; k < N; k++)
	{
		complex<double> sum(0.0, 0.0);
		for (unsigned int j = 0; j < N; j++)
		{
			int integers = -2 * j * k;
			complex<double> exponent(0.0, PI / N * (double)integers);
			sum += values[j] * exp(exponent);
		}
		values_fft.push_back(abs(sum) / N);
	}
}

// Am folosit FFT-ul din matlab deoarece nu ne-a iesit in c++


int main()
{
	unsigned nr = 0;
	ifstream myfile;
	string line;
	vector<string> valori_healthy, valori_myopathy, valori_neuropathy;
	string x;
	vector<double> val_healthy, val_myopathy, val_neuropathy, rms_healthy, rms_myopathy, rms_neuropathy, val_fft;
	int a;

	//Valorile semnalului pacientului sanatus
	myfile.open("emg_healthy.txt");

	while (myfile >> line)
	{
		if (nr % 2 == 1)
			valori_healthy.push_back(line);
		nr++;
	}

	myfile.close();

	vector<double> val_double_healthy(valori_healthy.size());

	transform(valori_healthy.begin(), valori_healthy.end(), val_double_healthy.begin(),
		[](string const& val) {return stod(val); });

	a = 0;
	for (int i = 0; i < val_double_healthy.size() / 35; i++)
	{
		for (int j = a; j < a + 35; j++)
		{
			val_healthy.push_back(val_double_healthy[j]);
		}
		FFT(35, val_healthy, val_fft);
		rms_healthy.push_back(RMS(val_fft));
		val_fft.clear();
		a += 15;
	}

	myfile.open("emg_myopathy.txt");

	while (myfile >> line)
	{
		if (nr % 2 == 1)
			valori_myopathy.push_back(line);
		nr++;
	}

	myfile.close();

	vector<double> val_double_myopathy(valori_myopathy.size());

	transform(valori_myopathy.begin(), valori_myopathy.end(), val_double_myopathy.begin(),
		[](string const& val) {return stod(val); });


	a = 0;
	for (int i = 0; i < val_double_myopathy.size() / 35; i++)
	{
		for (int j = a; j < a + 35; j++)
		{
			val_myopathy.push_back(val_double_myopathy[j]);
		}
		FFT(35, val_myopathy, val_fft);
		rms_myopathy.push_back(RMS(val_fft));
		val_fft.clear();
		a += 15;
	}

	myfile.open("emg_neuropathy.txt");

	while (myfile >> line)
	{
		if (nr % 2 == 0)
			valori_neuropathy.push_back(line);
		nr++;
	}

	myfile.close();

	vector<double> val_double_neuropathy(valori_neuropathy.size());

	transform(valori_neuropathy.begin(), valori_neuropathy.end(), val_double_neuropathy.begin(),
		[](string const& val) {return stod(val); });


	a = 0;
	for (int i = 0; i < val_double_neuropathy.size() / 35; i++)
	{
		a = 0;
		for (int j = a; j < a + 35; j++)
		{
			val_neuropathy.push_back(val_double_neuropathy[j]);
		}
		FFT(35, val_neuropathy, val_fft);
		rms_neuropathy.push_back(RMS(val_fft));
		val_fft.clear();
		a += 15;
	}

	Point vect1[35];
	Point vect2[35];
	Point vect3[35];

	for (unsigned i = 0; i < 35; i++)
	{
		vect1[i].x = i;
		vect1[i].y = rms_healthy[i];

	}

	for (unsigned i = 0; i < 35; i++)
	{
		vect2[i].x = i;
		vect2[i].y = rms_myopathy[i];

	}

	for (unsigned i = 0; i < 35; i++)
	{
		vect3[i].x = i;
		vect3[i].y = rms_neuropathy[i];

	}

	int f = 10;
	int boala = KNN(vect1, vect2, vect3, f, vect1[2]); //ultimul parametru trebuie o coordonata de test pe baza caruia programul sa spuna de ce sufera pacientul

	if (boala == 1)
	{
		cout << "Sanatos" << endl;
	}
	if (boala == 2)
	{
		cout << "Miopatie" << endl;
	}
	if (boala == 3)
	{
		cout << "Neuropatie" << endl;
	}

	system("pause");
	return 0;
}
