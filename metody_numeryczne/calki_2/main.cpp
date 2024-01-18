#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

double f1(double x) {
    return (pow(x, 2) * pow(sin(x), 3));
}

double f2(double x) {
    return (exp(pow(x, 2)) * (1 - x));
}

double kwadratura_2(double (*f)(double), double a, double b) {
    const double psi = 1.0 / sqrt(3.0);

    const double odejm = (b - a) / 2;
    const double dodaj = (b + a) / 2;
    
    double wynik = f(odejm * (-psi) + dodaj);
    wynik += f(odejm * psi + dodaj);

    return wynik * odejm;

}

double kwadratura_3(double (*f)(double), double a, double b) {
    const double psi = sqrt(3.0 / 5.0);

    const double w0 = 8.0 / 9.0;
    
    const double wPsi = 5.0 / 9.0;
    
    const double odejm = (b - a) / 2;
    const double dodaj = (b + a) / 2;
    
    double wynik = wPsi * f(odejm * (-psi) + dodaj);
    wynik += w0 * f(dodaj);
    wynik += wPsi * f(odejm * psi + dodaj);
    
    return wynik * odejm;
}

double kwadratura_4(double (*f)(double), double a, double b) {
    const double psi1 = sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
    const double psi2 = sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
    
    const double w1 = (18.0 + sqrt(30)) / 36.0;
    const double w2 = (18.0 - sqrt(30)) / 36.0;
    
    const double odejm = (b - a) / 2;
    const double dodaj = (b + a) / 2;
    
    double wynik = w1 * f(odejm * (-psi1) + dodaj);
    wynik += w2 * f(odejm * (-psi2) + dodaj);
    wynik += w1 * f(odejm * psi1 + dodaj);
    wynik += w2 * f(odejm * psi2 + dodaj);
    
    return wynik * odejm;
}

void Przedzialy(double (*f)(double), double a, double b, int n) {
    double ax{ a }, bx{ b };
    double odst = b - a;
    for (int i = 2; i <= n; i++)
    {
        ax = a;
        bx = a + odst / (double)i;
        double v1 = kwadratura_2(f, ax, bx);
        double v2 = kwadratura_3(f, ax, bx);
        double v3 = kwadratura_4(f, ax, bx);

        for (int j = 1; j < i; j++) {
            ax = a + odst * ((double)(j) / (double)i);
            bx = a + odst * ((double)(j + 1) / (double)i);
            v1 += kwadratura_2(f, ax, bx);
            v2 += kwadratura_3(f, ax, bx);
            v3 += kwadratura_4(f, ax, bx);
        }
        cout << "Dla " << i << " przedzialow:\n";
        cout << "2 wezly:\t" << v1 << endl;
        cout << "3 wezly:\t" << v2 << endl;
        cout << "4 wezly:\t" << v3 << endl << endl;
    }
}

int main() {
    double a1{ 1 }, b1{ 4.8 }, a2{ -1.5 }, b2{ 3.2 };
    int n{ 10 };

    cout << "Wyniki dla funkcji x^2*sin^3(x):";
    cout << "\n2-wezlowa kwadratura: " << kwadratura_2(f1, a1, b1);
    cout << "\n3-wezlowa kwadratura: " << kwadratura_3(f1, a1, b1);
    cout << "\n4-wezlowa kwadratura: " << kwadratura_4(f1, a1, b1);

    cout << "\n\nWyniki dla funkcji exp(x^2)(1-x):";  
    cout << "\n2-wezlowa kwadratura: " << kwadratura_2(f2, a2, b2);
    cout << "\n3-wezlowa kwadratura: " << kwadratura_3(f2, a2, b2);
    cout << "\n4-wezlowa kwadratura: " << kwadratura_4(f2, a2, b2);

    cout << "\n\nPodaj maksymalna liczbe przedzialow (np.:15): ";
    cin >> n;
    cout << "\nWyniki po podziale na przedzialy:\n\n";

    cout << "Funkcja x^2*sin^3(x):\n";
    Przedzialy(f1, a1, b1, n);

    cout << "Wynik wedlug Wolframa Alfa:\t -10.9001\n";

    cout << "\nFunkcja exp(x^2)(1-x):\n";
    Przedzialy(f2, a2, b2, n);

    cout << "Wynik wedlug Wolframa Alfa:\t -9358.63\n";

    return 0;
}
