#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

using namespace std;

const double eps{ 1e-10 };

double f1(double x) {
	return 4*x + sin(x) - exp(x);
}

double f2(double x) {
	return 3*pow(x,4) - 6*pow(x,2) + x + 2;
}

double f3(double x) {
	return pow(x,2) - 3*x*sin(x) + pow(3*sin(x),2) - 6;
}

double Bisection(double a, double b, double (*f)(double)){
    if (f(a) * f(b) >= 0){
        cout << "Bisection method failed." << endl;
        return -1;
    }

    int i = 1;
    double c = 0;
    cout << "nr:\tx:\t\tf(x):\n";

    do {
        c = (a + b) / 2;
        cout << i << ";\t" << c << ";\t" << f(c) << endl;

        if (f(a) * f(c) < 0)
            b = c;
        else 
            a = c;

        i += 1;
    } while (fabs(f(c)) > eps);

    cout << " - Bisection root: " << c << "\n\n";
    return c;
}

void pomBisection(double (*f)(double), int n, int ilosc, double l_limit, double r_limit) {
    double h = (r_limit - l_limit) / ilosc;

    for (double i = l_limit; i < r_limit - h; i += h) {
        double j = i + h;

        if (f(i) * f(j) <= 0)
            Bisection(i, j, f);
    }
}

double FalsePosition(double a, double b, double (*f)(double)){

    if (f(a) * f(b) >= 0)
    {
        cout << "False position method failed." << endl;
        return -1;
    }

    int i = 1;
    double c;
    cout << "nr:\tx:\t\tf(x):\n";

    do{
        c = a - (a - b) * f(a) / (f(a) - f(b));
        cout << i << ";\t" << c << ";\t" << f(c) << endl;
        if (f(a) * f(b) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
        i += 1;
    } while (fabs(f(c)) > eps);

    cout << " - FalsePosition root: " << c << "\n\n";
    return c;
}

void pomFalsePosition(double (*f)(double), int n, int ilosc, double l_limit, double r_limit) {
    double h = (r_limit - l_limit) / ilosc;

    for (double i = l_limit; i < r_limit - h; i += h) {
        double j = i + h;

        if (f(i) * f(j) <= 0)
            FalsePosition(i, j, f);
    }
}

int main() {

	int n{ 100 }, ilosc{ 500 };
    cout << fixed << setprecision(10);

	cout << "------------- Funkcja nr 1: -------------\n";

    cout << "Bisection:\n";
	    pomBisection(f1, n, ilosc, 0.0, 3.0);
    cout << "FalsePosition:\n";
        pomFalsePosition(f1, n, ilosc, 0.0, 3.0);

	cout << "\n------------- Funkcja nr 2: -------------\n";

    cout << "Bisection:\n";
        pomBisection(f2, n, ilosc, -2.0, 2.0);
    cout << "FalsePosition:\n";
        pomFalsePosition(f2, n, ilosc, -2.0, 2.0);

	cout << "\n------------- Funkcja nr 3: -------------\n";

    cout << "Bisection:\n";
        pomBisection(f3, n, ilosc, -4.0, 4.0);
    cout << "FalsePosition:\n";
        pomFalsePosition(f3, n, ilosc, -4.0, 4.0);

	return 0;
}