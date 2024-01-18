#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int roz{ 5 };
const int st_wiel {roz - 1};

double horner(double x, double* wsp, int st)
{
	double wynik = wsp[st] * x;

	for (int i = st - 1; i > 0; i--)
		wynik = (wynik + wsp[i]) * x;

	wynik += wsp[0];

	return wynik;
}

double f(double x)
{
	return pow(x, 2) * pow(cos(x), 3);;
}

double trapezy_fun(int a, int b, int n)
{
	double h = (b - a) / (double)n; 
	double S = 0.0; 
	double podstawa_a = f(a), podstawa_b;

	for (int i = 1; i <= n; i++)
	{
		podstawa_b = f(a + h * i);
		S += (podstawa_a + podstawa_b);
		podstawa_a = podstawa_b;
	}
	return S * 0.5 * h;
}

double trapezy_wiel(int a, int b, int n, double matrix[roz], int st_wiel)
{
	double h = (b - a) / (double)n; //wysokosæ trapezów
	double S = 0.0; //zmienna bêdzie przechowywaæ sumê pól trapezów
	double podstawa_a = horner(a, matrix, st_wiel), podstawa_b;

	for (int i = 1; i <= n; i++)
	{
		podstawa_b = horner(a + h * i, matrix, st_wiel);
		S += (podstawa_a + podstawa_b);
		podstawa_a = podstawa_b;
	}
	return S * 0.5 * h;
}

double simpson_wiel(int a, int b, int n, double matrix[roz], int st_wiel) {
	double s = 0.0, st = 0.0;
	double x;
	double dx = (static_cast<double>(b) - a) / n;
	for (int i = 1; i <= n; i++)
	{
		x = a + i * dx;
		st += horner(x - dx / 2, matrix, st_wiel);
		if (i < n) s += horner(x, matrix, st_wiel);
	}
	s = dx / 6 * (horner(a, matrix, st_wiel) + horner(b, matrix, st_wiel) + 2 * s + 4 * st);
	return s;
}

double simpson_fun(int a, int b, int n) {
	double s = 0.0, st = 0.0;
	double x;
	double dx = (static_cast<double>(b) - a) / n;
	for (int i = 1; i <= n; i++)
	{
		x = a + i * dx;
		st += f(x - dx / 2);
		if (i < n) s += f(x);
	}
	s = dx / 6 * (f(a) + f(b) + 2 * s + 4 * st);
	return s;
}

int main()
{
	cout << setprecision(2) << fixed;

	ifstream dane("dane.txt");
	int st{ st_wiel }, a{ }, b{ }, n{ 1000 }, a2{2}, b2{6};

	double matrix[roz]{};

	for (int i{ 0 }; i < 5; i++) {
		dane >> matrix[i];
	}
	dane >> a;
	dane >> b;

	cout << "Podaj ilosc przedzialow calkowania (np.:1000): ";
	cin >> n;

	cout << "\nObliczanie kwadratury:\n";
	cout << "\nMetoda Trapezow dla wielomianu z pliku: " << trapezy_wiel(a, b, n, matrix, st) << endl;
	cout << "Metoda Simpsona dla wielomianu z pliku: " << simpson_wiel(a, b, n, matrix, st) << endl;
	cout << setprecision(5) << fixed;
	cout << "\nMetoda Trapezow dla funkcji x^2cos^3(x): " << trapezy_fun(a2, b2, n) << endl;
	cout << "Metoda Simpsona dla funkcji x^2cos^3(x): " << simpson_fun(a2, b2, n) << endl;


	dane.close();
	return 0;
}