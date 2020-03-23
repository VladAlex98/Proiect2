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

void segmentare(vector<double> v, unsigned start, vector<double> &segment);
double RMS(vector<double> v);
void FFT_recursiv(complex<double> *x, unsigned N);
void FFT(double *x_in, complex<double> *x_out, unsigned N);

struct Point//structura ce continele coordonatele si distantele fiecarui punct;
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
		if (arrh[i].dist < min)min = arrh[i].dist;
		if (arrm[i].dist < min)min = arrm[i].dist;
		if (arrn[i].dist < min)min = arrn[i].dist;

		if (arrh[i].dist == min)
			freq1++;
		if (arrm[i].dist == min)
			freq2++;
		if (arrn[i].dist == min)
			freq3++;

	}
	int max = 0;
	if (freq1 > max) max = freq1;
	if (freq2 > max) max = freq2;
	if (freq3 > max) max = freq3;

	//tipul de simptom cel mai des intalnit ne da verdictul final si boala de care sufera pacientul
	if (max == freq1) { return 1; }
	if (max == freq2) { return 2; }
	if (max == freq3) { return 3; }

}

//a)
void segmentare(vector<double> v, unsigned start, vector<double> &segment)
{

	for (unsigned i = start; i < start + 120; i = i++)
	{
		segment.push_back(v[i]);
	}

}

//b)
double RMS(vector<double> v)
{
	double sum = 0;

	for (unsigned i = 0; i < v.size(); i++)
	{
		sum = sum + (v[i] * v[i]);
	}

	return sqrt(sum / v.size());
}

// Am folosit FFT-ul din matlab deoarece nu ne-a iesit in c++

//void FFT_recursiv(complex<double> *x, unsigned N) 
//{
//	// verific daca am impartit suficient
//	if (N <= 1) 
//	{
//		return;
//	}
//
//	// impart in par si impar
//	complex<double> *impar = new complex<double>[N / 2];
//	complex<double> *par = new complex<double>[N / 2];
//
//	for (unsigned i = 0; i < N / 2; i++) 
//	{
//		par[i] = x[i * 2];
//		impar[i] = x[i * 2 + 1];
//	}
//
//	// Split on tasks
//	FFT_recursiv(par, N / 2);
//	FFT_recursiv(impar, N / 2);
//
//	double pi = 3.14159265359;
//
//	// Calculate DFT
//	for (unsigned k = 0; k < N / 2; k++) 
//	{
//		complex<double> t = exp(complex<double>(0, -2 * pi * k / N)) * impar[k];
//		x[k] = par[k] + t;
//		x[N / 2 + k] = par[k] - t;
//	}
//}
//
//void FFT(double *x_in, complex<double> *x_out, unsigned N)
//{
//
//	// fac o copie a vectorului si aplic fereastra
//	for (unsigned i = 0; i < N; i++)
//	{
//		x_out[i] = complex<double>(x_in[i], 0);
//		x_out[i] *= 1;
//	}
//
//	// Incepe recursivitatea
//	FFT_recursiv(x_out, N);
//}


int main()
{
	unsigned nr = 0;
	ifstream myfile;
	ofstream segm_1, segm_2, segm_3, segm_4, segm_5, segm_6, segm_7, segm_8, segm_9, segm_10;
	string line;
	vector<string> timp_healthy, valori_healthy, timp_myopathy, valori_myopathy, timp_neuropathy, valori_neuropathy;

	//Valorile semnalului pacientului sanatus
	myfile.open("emg_healthy.txt");

	while (myfile >> line)
	{
		if (nr % 2 == 0)
		{
			timp_healthy.push_back(line);
		}
		else
			valori_healthy.push_back(line);
		nr++;
	}

	myfile.close();

	vector<double> val_double_healthy(valori_healthy.size());
	vector<double> timp_double_healthy(timp_healthy.size());

	transform(valori_healthy.begin(), valori_healthy.end(), val_double_healthy.begin(),
		[](string const& val) {return stod(val); });
	transform(timp_healthy.begin(), timp_healthy.end(), timp_double_healthy.begin(),
		[](string const& val) {return stod(val); });

	vector<double> segm1_healthy;
	vector<double> segm2_healthy;
	vector<double> segm3_healthy;
	vector<double> segm4_healthy;
	vector<double> segm5_healthy;
	vector<double> segm6_healthy;
	vector<double> segm7_healthy;
	vector<double> segm8_healthy;
	vector<double> segm9_healthy;
	vector<double> segm10_healthy;

	segmentare(val_double_healthy, 0, segm1_healthy);
	segmentare(val_double_healthy, 80, segm2_healthy);
	segmentare(val_double_healthy, 200, segm3_healthy);
	segmentare(val_double_healthy, 280, segm4_healthy);
	segmentare(val_double_healthy, 360, segm5_healthy);
	segmentare(val_double_healthy, 420, segm6_healthy);
	segmentare(val_double_healthy, 510, segm7_healthy);
	segmentare(val_double_healthy, 620, segm8_healthy);
	segmentare(val_double_healthy, 710, segm9_healthy);
	segmentare(val_double_healthy, 800, segm10_healthy);

	segm_1.open("segm1_healthy.txt");
	segm_2.open("segm2_healthy.txt");
	segm_3.open("segm3_healthy.txt");
	segm_4.open("segm4_healthy.txt");
	segm_5.open("segm5_healthy.txt");
	segm_6.open("segm6_healthy.txt");
	segm_7.open("segm7_healthy.txt");
	segm_8.open("segm8_healthy.txt");
	segm_9.open("segm9_healthy.txt");
	segm_10.open("segm10_healthy.txt");


	double a = 0;

	for (unsigned i = 0; i < segm1_healthy.size(); i++)
	{
		segm_1 << a << " " << segm1_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm2_healthy.size(); i++)
	{
		segm_2 << a << " " << segm2_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm3_healthy.size(); i++)
	{
		segm_3 << a << " " << segm3_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm4_healthy.size(); i++)
	{
		segm_4 << a << " " << segm4_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm5_healthy.size(); i++)
	{
		segm_5 << a << " " << segm5_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm6_healthy.size(); i++)
	{
		segm_6 << a << " " << segm6_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm7_healthy.size(); i++)
	{
		segm_7 << a << " " << segm7_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm8_healthy.size(); i++)
	{
		segm_8 << a << " " << segm8_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm9_healthy.size(); i++)
	{
		segm_9 << a << " " << segm9_healthy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm10_healthy.size(); i++)
	{
		segm_10 << a << " " << segm10_healthy[i] << endl;
		a += 0.00025;
	}

	segm_1.close();
	segm_2.close();
	segm_3.close();
	segm_4.close();
	segm_5.close();
	segm_6.close();
	segm_7.close();
	segm_8.close();
	segm_9.close();
	segm_10.close();


	//Valorile semnalului pacientului cu miopatie
	myfile.open("emg_myopathy.txt");

	while (myfile >> line)
	{
		if (nr % 2 == 0)
		{
			timp_myopathy.push_back(line);
		}
		else
			valori_myopathy.push_back(line);
		nr++;
	}

	myfile.close();

	vector<double> val_double_myopathy(valori_myopathy.size());
	vector<double> timp_double_myopathy(timp_myopathy.size());

	transform(valori_myopathy.begin(), valori_myopathy.end(), val_double_myopathy.begin(),
		[](string const& val) {return stod(val); });
	transform(timp_myopathy.begin(), timp_myopathy.end(), timp_double_myopathy.begin(),
		[](string const& val) {return stod(val); });

	vector<double> segm1_myopathy;
	vector<double> segm2_myopathy;
	vector<double> segm3_myopathy;
	vector<double> segm4_myopathy;
	vector<double> segm5_myopathy;
	vector<double> segm6_myopathy;
	vector<double> segm7_myopathy;
	vector<double> segm8_myopathy;
	vector<double> segm9_myopathy;
	vector<double> segm10_myopathy;

	segmentare(val_double_myopathy, 0, segm1_myopathy);
	segmentare(val_double_myopathy, 80, segm2_myopathy);
	segmentare(val_double_myopathy, 200, segm3_myopathy);
	segmentare(val_double_myopathy, 280, segm4_myopathy);
	segmentare(val_double_myopathy, 360, segm5_myopathy);
	segmentare(val_double_myopathy, 420, segm6_myopathy);
	segmentare(val_double_myopathy, 510, segm7_myopathy);
	segmentare(val_double_myopathy, 620, segm8_myopathy);
	segmentare(val_double_myopathy, 710, segm9_myopathy);
	segmentare(val_double_myopathy, 800, segm10_myopathy);

	segm_1.open("segm1_myopathy.txt");
	segm_2.open("segm2_myopathy.txt");
	segm_3.open("segm3_myopathy.txt");
	segm_4.open("segm4_myopathy.txt");
	segm_5.open("segm5_myopathy.txt");
	segm_6.open("segm6_myopathy.txt");
	segm_7.open("segm7_myopathy.txt");
	segm_8.open("segm8_myopathy.txt");
	segm_9.open("segm9_myopathy.txt");
	segm_10.open("segm10_myopathy.txt");


	a = 0;

	for (unsigned i = 0; i < segm1_myopathy.size(); i++)
	{
		segm_1 << a << " " << segm1_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm2_myopathy.size(); i++)
	{
		segm_2 << a << " " << segm2_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm3_myopathy.size(); i++)
	{
		segm_3 << a << " " << segm3_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm4_myopathy.size(); i++)
	{
		segm_4 << a << " " << segm4_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm5_myopathy.size(); i++)
	{
		segm_5 << a << " " << segm5_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm6_myopathy.size(); i++)
	{
		segm_6 << a << " " << segm6_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm7_myopathy.size(); i++)
	{
		segm_7 << a << " " << segm7_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm8_myopathy.size(); i++)
	{
		segm_8 << a << " " << segm8_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm9_myopathy.size(); i++)
	{
		segm_9 << a << " " << segm9_myopathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm10_myopathy.size(); i++)
	{
		segm_10 << a << " " << segm10_myopathy[i] << endl;
		a += 0.00025;
	}

	segm_1.close();
	segm_2.close();
	segm_3.close();
	segm_4.close();
	segm_5.close();
	segm_6.close();
	segm_7.close();
	segm_8.close();
	segm_9.close();
	segm_10.close();


	//Valorile semnalului pacientului cu neuropatie
	myfile.open("emg_neuropathy.txt");

	while (myfile >> line)
	{
		if (nr % 2 == 0)
		{
			timp_neuropathy.push_back(line);
		}
		else
			valori_neuropathy.push_back(line);
		nr++;
	}

	myfile.close();

	vector<double> val_double_neuropathy(valori_neuropathy.size());
	vector<double> timp_double_neuropathy(timp_neuropathy.size());

	transform(valori_neuropathy.begin(), valori_neuropathy.end(), val_double_neuropathy.begin(),
		[](string const& val) {return stod(val); });
	transform(timp_neuropathy.begin(), timp_neuropathy.end(), timp_double_neuropathy.begin(),
		[](string const& val) {return stod(val); });

	vector<double> segm1_neuropathy;
	vector<double> segm2_neuropathy;
	vector<double> segm3_neuropathy;
	vector<double> segm4_neuropathy;
	vector<double> segm5_neuropathy;
	vector<double> segm6_neuropathy;
	vector<double> segm7_neuropathy;
	vector<double> segm8_neuropathy;
	vector<double> segm9_neuropathy;
	vector<double> segm10_neuropathy;

	segmentare(val_double_neuropathy, 0, segm1_neuropathy);
	segmentare(val_double_neuropathy, 80, segm2_neuropathy);
	segmentare(val_double_neuropathy, 200, segm3_neuropathy);
	segmentare(val_double_neuropathy, 280, segm4_neuropathy);
	segmentare(val_double_neuropathy, 360, segm5_neuropathy);
	segmentare(val_double_neuropathy, 420, segm6_neuropathy);
	segmentare(val_double_neuropathy, 510, segm7_neuropathy);
	segmentare(val_double_neuropathy, 620, segm8_neuropathy);
	segmentare(val_double_neuropathy, 710, segm9_neuropathy);
	segmentare(val_double_neuropathy, 800, segm10_neuropathy);

	segm_1.open("segm1_neuropathy.txt");
	segm_2.open("segm2_neuropathy.txt");
	segm_3.open("segm3_neuropathy.txt");
	segm_4.open("segm4_neuropathy.txt");
	segm_5.open("segm5_neuropathy.txt");
	segm_6.open("segm6_neuropathy.txt");
	segm_7.open("segm7_neuropathy.txt");
	segm_8.open("segm8_neuropathy.txt");
	segm_9.open("segm9_neuropathy.txt");
	segm_10.open("segm10_neuropathy.txt");


	a = 0;

	for (unsigned i = 0; i < segm1_neuropathy.size(); i++)
	{
		segm_1 << a << " " << segm1_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm2_neuropathy.size(); i++)
	{
		segm_2 << a << " " << segm2_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm3_neuropathy.size(); i++)
	{
		segm_3 << a << " " << segm3_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm4_neuropathy.size(); i++)
	{
		segm_4 << a << " " << segm4_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm5_neuropathy.size(); i++)
	{
		segm_5 << a << " " << segm5_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm6_neuropathy.size(); i++)
	{
		segm_6 << a << " " << segm6_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm7_neuropathy.size(); i++)
	{
		segm_7 << a << " " << segm7_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm8_neuropathy.size(); i++)
	{
		segm_8 << a << " " << segm8_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm9_neuropathy.size(); i++)
	{
		segm_9 << a << " " << segm9_neuropathy[i] << endl;
		a += 0.00025;
	}

	a = 0;
	for (unsigned i = 0; i < segm10_neuropathy.size(); i++)
	{
		segm_10 << a << " " << segm10_neuropathy[i] << endl;
		a += 0.00025;
	}

	segm_1.close();
	segm_2.close();
	segm_3.close();
	segm_4.close();
	segm_5.close();
	segm_6.close();
	segm_7.close();
	segm_8.close();
	segm_9.close();
	segm_10.close();


	//vectorii ce contin valorile absolute ale FFT
	vector<string> h1, h2, h3, h4, h5, h6, h7, h8, h9, h10;
	vector<string> m1, m2, m3, m4, m5, m6, m7, m8, m9, m10;
	vector<string> n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
	regex e("([,])");

	myfile.open("h1.txt");

	while (myfile >> line)
	{
		h1.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h1_double(h1.size());

	transform(h1.begin(), h1.end(), h1_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h2.txt");

	while (myfile >> line)
	{
		h2.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h2_double(h2.size());

	transform(h2.begin(), h2.end(), h2_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h3.txt");

	while (myfile >> line)
	{
		h3.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h3_double(h3.size());

	transform(h3.begin(), h3.end(), h3_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h4.txt");

	while (myfile >> line)
	{
		h4.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h4_double(h4.size());

	transform(h4.begin(), h4.end(), h4_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h5.txt");

	while (myfile >> line)
	{
		h5.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h5_double(h5.size());

	transform(h5.begin(), h5.end(), h5_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h6.txt");

	while (myfile >> line)
	{
		h6.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h6_double(h6.size());

	transform(h6.begin(), h6.end(), h6_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h7.txt");

	while (myfile >> line)
	{
		h7.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h7_double(h7.size());

	transform(h7.begin(), h7.end(), h7_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h8.txt");

	while (myfile >> line)
	{
		h8.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h8_double(h8.size());

	transform(h8.begin(), h8.end(), h8_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h9.txt");

	while (myfile >> line)
	{
		h9.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h9_double(h9.size());

	transform(h9.begin(), h9.end(), h9_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("h10.txt");

	while (myfile >> line)
	{
		h10.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> h10_double(h10.size());

	transform(h10.begin(), h10.end(), h10_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m1.txt");

	while (myfile >> line)
	{
		m1.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m1_double(m1.size());

	transform(m1.begin(), m1.end(), m1_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m2.txt");

	while (myfile >> line)
	{
		m2.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m2_double(m2.size());

	transform(m2.begin(), m2.end(), m2_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m3.txt");

	while (myfile >> line)
	{
		m3.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m3_double(m2.size());

	transform(m3.begin(), m3.end(), m3_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m4.txt");

	while (myfile >> line)
	{
		m4.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m4_double(m2.size());

	transform(m4.begin(), m4.end(), m4_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m5.txt");

	while (myfile >> line)
	{
		m5.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m5_double(m2.size());

	transform(m5.begin(), m5.end(), m5_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m6.txt");

	while (myfile >> line)
	{
		m6.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m6_double(m2.size());

	transform(m6.begin(), m6.end(), m6_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m7.txt");

	while (myfile >> line)
	{
		m7.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m7_double(m2.size());

	transform(m7.begin(), m7.end(), m7_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m8.txt");

	while (myfile >> line)
	{
		m8.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m8_double(m2.size());

	transform(m8.begin(), m8.end(), m8_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m9.txt");

	while (myfile >> line)
	{
		m9.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m9_double(m2.size());

	transform(m9.begin(), m9.end(), m9_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("m10.txt");

	while (myfile >> line)
	{
		m10.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> m10_double(m2.size());

	transform(m10.begin(), m10.end(), m10_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n1.txt");

	while (myfile >> line)
	{
		n1.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n1_double(m2.size());

	transform(n1.begin(), n1.end(), n1_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n2.txt");

	while (myfile >> line)
	{
		n2.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n2_double(m2.size());

	transform(n2.begin(), n2.end(), n2_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n3.txt");

	while (myfile >> line)
	{
		n3.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n3_double(m2.size());

	transform(n3.begin(), n3.end(), n3_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n4.txt");

	while (myfile >> line)
	{
		n4.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n4_double(m2.size());

	transform(n4.begin(), n4.end(), n4_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n5.txt");

	while (myfile >> line)
	{
		n5.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n5_double(m2.size());

	transform(n5.begin(), n5.end(), n5_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n6.txt");

	while (myfile >> line)
	{
		n6.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n6_double(m2.size());

	transform(n6.begin(), n6.end(), n6_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n7.txt");

	while (myfile >> line)
	{
		n7.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n7_double(m2.size());

	transform(n7.begin(), n7.end(), n7_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n8.txt");

	while (myfile >> line)
	{
		n8.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n8_double(m2.size());

	transform(n8.begin(), n8.end(), n8_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n9.txt");

	while (myfile >> line)
	{
		n9.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n9_double(m2.size());

	transform(n9.begin(), n9.end(), n9_double.begin(),
		[](string const& val) {return stod(val); });

	myfile.open("n10.txt");

	while (myfile >> line)
	{
		n10.push_back(regex_replace(line, e, "."));
	}

	myfile.close();

	vector<double> n10_double(m2.size());

	transform(n10.begin(), n10.end(), n10_double.begin(),
		[](string const& val) {return stod(val); });

	double h1_rms = RMS(h1_double);
	double h2_rms = RMS(h2_double);
	double h3_rms = RMS(h3_double);
	double h4_rms = RMS(h4_double);
	double h5_rms = RMS(h5_double);
	double h6_rms = RMS(h6_double);
	double h7_rms = RMS(h7_double);
	double h8_rms = RMS(h8_double);
	double h9_rms = RMS(h9_double);
	double h10_rms = RMS(h10_double);

	double m1_rms = RMS(m1_double);
	double m2_rms = RMS(m2_double);
	double m3_rms = RMS(m3_double);
	double m4_rms = RMS(m4_double);
	double m5_rms = RMS(m5_double);
	double m6_rms = RMS(m6_double);
	double m7_rms = RMS(m7_double);
	double m8_rms = RMS(m8_double);
	double m9_rms = RMS(m9_double);
	double m10_rms = RMS(m10_double);

	double n1_rms = RMS(n1_double);
	double n2_rms = RMS(n2_double);
	double n3_rms = RMS(n3_double);
	double n4_rms = RMS(n4_double);
	double n5_rms = RMS(n5_double);
	double n6_rms = RMS(n6_double);
	double n7_rms = RMS(n7_double);
	double n8_rms = RMS(n8_double);
	double n9_rms = RMS(n9_double);
	double n10_rms = RMS(n10_double);

	double rmss_h[10] = { h1_rms, h2_rms, h3_rms, h4_rms, h5_rms, h6_rms, h7_rms, h8_rms, h9_rms, h10_rms };
	double rmss_m[10] = { m1_rms, m2_rms, m3_rms, m4_rms, m5_rms, m6_rms, m7_rms, m8_rms, m9_rms, m10_rms };
	double rmss_n[10] = { n1_rms, n2_rms, n3_rms, n4_rms, n5_rms, n6_rms, n7_rms, n8_rms, n9_rms, n10_rms };

	Point vect1[11];
	Point vect2[11];
	Point vect3[11];

	for (unsigned i = 0; i < 10; i++)
	{
		vect1[i].x = i;
		vect1[i].y = rmss_h[i];

	}

	for (unsigned i = 0; i < 10; i++)
	{
		vect2[i].x = i;
		vect2[i].y = rmss_m[i];

	}

	for (unsigned i = 0; i < 10; i++)
	{
		vect3[i].x = i;
		vect3[i].y = rmss_n[i];

	}

	int f = 10;
	int boala = KNN(vect1, vect2, vect3, f, );//ultimul parametru trebuia sa fie un vector de test pe baza caruia programul sa spuna de ce sufera pacientul

	if (boala == 1)
	{
		cout << "Sanatos" << endl;
	}
	if (boala == 2)
	{
		cout << "Miopatie" << endl;
	}
	if (boala == 1)
	{
		cout << "Neuropatie" << endl;
	}
	system("pause");
	return 0;
}