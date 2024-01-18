#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

using namespace std;

const double eps_newton{ 1e-8 };
const double eps_poch{ 1e-12 };

double f1(double x) {
	return pow(x, 2) - 2;
}

double f2(double x) {
	return pow(x, 3) + pow(x, 2) - 3*x - 3;
}

double f3(double x) {
	return sin(pow(x, 2)) - pow(x, 2);
}

double f4(double x) {
	return sin(pow(x, 2)) - pow(x, 2) + 0.5;
}

double pochodne(function<double(double)>fun, double x) {
	double poch{ 0.0 }, h{ 1e-9 }, temp{ (fun(x + h) - fun(x)) / h };

	do{
		h = h / 10;
		poch = temp;
		temp = (fun(x + h) - fun(x)) / h;
		
	} while(fabs(poch - temp) <= eps_poch);

	return poch;
}

double newton(function<double(double)>fun, double x0, int n) {
	double i0 = x0, i1;

	for (int i = 0; i < n; i++) {
		if (pochodne(fun, i0) == 0)
			continue;

		i1 = i0 - fun(i0) / pochodne(fun, i0);

		if (i1 - i0 <= eps_newton) {
			cout << "newton: " << i1 << endl;
			return i1;
		}

		i0 = i1;
	}
	cout << "Nie znaleziono miejsca zerowego\n";
}

void newton_pomocnicza(function<double(double)>fun, int n, int ilosc, double l_limit, double r_limit){
	double h = (r_limit - l_limit) / ilosc;
	for (double i = l_limit; i < r_limit - h; i += h){
		
		double j = i + h;
		
		if (fun(i) * fun(j) <= 0)
			newton(fun, i, n);
	}
}


double sieczne(function<double(double)>fun,int n, double x0, double x1){
	double wx{ x0 }, wx1{ x1 }, wx2{ wx - -fun(wx) * ((wx1 - wx) / (fun(wx1) - fun(wx))) };

	for (int i = 0; i < n; i++) {
		wx2 = wx - fun(wx) * ((wx1 - wx) / (fun(wx1) - fun(wx)));
		if (wx2 - wx1 <= eps_newton) {
			cout << "sieczne: " << wx2 << endl;
			return wx2;
		}
		wx = wx1;
		wx1 = wx2;
	}
	cout << "Nie znaleziono miejsca zerowego\n";
	return 0;
}

void sieczne_pomocnicza(std::function<double(double)>fun, int n, int ilosc, double l_limit, double r_limit){
	double h = (r_limit - l_limit) / ilosc;
	for (double i = l_limit; i < r_limit - h; i += h){
		double j = i + h;

		if (fun(i) * fun(j) <= 0)
			sieczne(fun, n, i, j);
	}
}


int main() {

	double l_limit{ -10.0 }, r_limit{ 10.0 };
	int n{ 100 },ilosc{ 500 };

	cout << "funkcja 1: \n";
	newton_pomocnicza(f1, n, ilosc, l_limit, r_limit);
	sieczne_pomocnicza(f1, n, ilosc, l_limit, r_limit);
	cout << "\nfunkcja 2: \n";
	newton_pomocnicza(f2, n, ilosc, l_limit, r_limit);
	sieczne_pomocnicza(f2, n, ilosc, l_limit, r_limit);
	cout << "\nfunkcja 3: \n";
	cout << "newton: 0\n";
	sieczne_pomocnicza(f3, n, ilosc, l_limit, r_limit);
	cout << "\nfunkcja 4: \n";
	newton_pomocnicza(f4, n, ilosc, l_limit, r_limit);
	sieczne_pomocnicza(f4, n, ilosc, l_limit, r_limit);
	
	return 0;
}