#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <iostream>


// laba 1 nado reshit metodom lubim no na proizvolnoy oblasti

using namespace std;
const int n = 10;

double a = 0, b = 1, lambda = 1.0;
double h = (b - a) / n;

double X[n + 2], Xi[n], A[n][n + 1], C[n + 1], xe[n * 10];

double ker(double x, double y) {

	return x - y;
}

double u(double x) {

	return pow(x, 2);
}

double f(double x)
{
	return (x * x - lambda * (x / 3.0 - 0.25));
	//return cos(10*x);
}

void MakeGrid() {

	for (int i = 0; i < n + 2; i++)
	{
		X[i] = a + i * h;
		//cout << X[i] << " = X[i]" << endl;
	}
	for (int i = 0; i < n; i++)
	{
		Xi[i] = X[i] + h / 2.0;
		//cout << Xi[i] << " = Xi[i]" << endl;
	}
}



double fII(double x, int j) {
	//int s = 0;
	if ((x >= X[j]) && (x <= X[j + 1])) {
		/*s = */  return (1 / h) + ((x - X[j + 1]) / (h * h));
	}
	else if ((x > X[j + 1]) && (x <= X[j + 2])) {
		/*s =*/return  (1 / h) - ((x - X[j + 1]) / (h * h));
	}
	else
	{
		return 0;
	}
}


double Integral(int i, int j)
{
	int N = 100;
	double I = 0, l, alfa = X[j - 1], beta = X[j + 1], xi = Xi[i];
	l = ((beta - alfa) / N);
	for (int k = 0; k < N; k++)
	{
		I += l * ker(xi, alfa + (k + 0.5) * l) * fII(alfa + (k + 0.5) * l, j);
	}

	return I;
}

double delta(int i, int k) {
	return (i == k);
}

void AAA() {

	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{


			A[i][j] = fII(Xi[i], j) - lambda * Integral(i, j + 1);
		}
	}
	for (int i = 0; i < n; i++)
	{
		A[i][n] = f(Xi[i]);
	}
}


void Gauss(int k, double Matrix[n][n + 1]) {
	if (Matrix[k][k] != 1) {
		double T = Matrix[k][k];
		for (int j = k; j < n + 1; j++) {
			Matrix[k][j] = Matrix[k][j] / T;
		}
	}
	for (int i = 0; i < n; i++) {
		if ((Matrix[i][k] != 0.0) && (i != k)) {
			double T = Matrix[i][k];
			Matrix[i][k] = 0.0;
			for (int j = k + 1; j < n + 1; j++) {
				Matrix[i][j] -= Matrix[k][j] * T;
			}
		}
	}
	if (k < n - 1) {
		Gauss(k + 1, Matrix);
	}
}
//
//double fii(double x, int i) {
//
//	if ((x>=X[i]) && (x<X[i+1]))
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//
//}
//










double Un(double x) {
	double un = 0;

	for (int i = 0; i < n; i++)
	{
		un += C[i] * fII(x, i + 1);
	}
	return un;
}



int main()
{
	MakeGrid();
	AAA();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			cout << A[i][j] << "  ";
		}
		cout << endl;
	}
	Gauss(0, A);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			cout << A[i][j] << "  ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		C[i] = A[i][n];
	}
	int k = 0;



	for (int i = 0; i < n * 10; i++)
	{
		xe[i] = a + (b - a) / (n * 10.0) * i;

		//printf("Xe = %g\n", xe[k]);
		k++;
	};



	//cout << delta(1, 2);

	FILE* tab_file = fopen("result1.xls", "w");
	for (int i = 0; i < n * 10; i++)
	{
		fprintf(tab_file, "%10.6f\n", Un(xe[i])); ;
	}
	fclose(tab_file);
	//system("pause");
	return 1;
}