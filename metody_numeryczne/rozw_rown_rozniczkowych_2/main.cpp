#include <iostream>
#include <cmath>
#include<fstream>

using namespace std;

double Pochodna(double temp, double alfa, double beta) {
	return (-alfa * (pow(temp, 4) - beta));
}


double* Euler(double temp, double h, int n, double alfa, double beta) {
    double* dane = new double[n + 1];
    dane[0] = temp;

    for (int g{ 1 }; g <= n; g++) {
        dane[g] = dane[g - 1] + h * Pochodna(dane[g - 1], alfa, beta);
    }
    
    return dane;
}

double* Heun(double temp, double h, int n, double alfa, double beta) {
    double* dane = new double[n + 1];
    dane[0] = temp;

    for (int f{ 1 }; f <= n; f++) {
        double x = dane[f - 1] + h * Pochodna(dane[f - 1], alfa, beta);
        dane[f] = dane[f - 1] + h / 2 * (Pochodna(dane[f - 1], alfa, beta) + Pochodna(x, alfa, beta));
    }

    return dane;
}

double* srodkowy_(double temp, double h, int n, double alfa, double beta) {
    double* dane = new double[n + 1];
    dane[0] = temp;

    for (int r{ 1 }; r <= n; r++) {
        dane[r] = dane[r - 1] + h * Pochodna(dane[r - 1] + h / 2, alfa, beta);
    }

    return dane;
}

double* RungegoKutty(double temp, double h, int n, double alfa, double beta) {
    double* dane = new double[n + 1];
    dane[0] = temp;

    double delt, m1, m2, m3, m4;
    for (int j{ 1 }; j <= n; j++) {
        m1 = h * Pochodna(dane[j - 1], alfa, beta);
        m2 = h * Pochodna(dane[j - 1] + m1 / 2, alfa, beta);
        m3 = h * Pochodna(dane[j - 1] + m2 / 2, alfa, beta);
        m4 = h * Pochodna(dane[j - 1] + m3, alfa, beta);
        delt = (m1 + 2 * m2 + 2 * m3 + m4) / 6;
        dane[j] = dane[j - 1] + delt;
    }

    return dane;
}

int main() {

    ofstream euler("euler.txt");
    ofstream heun("heun.txt");
    ofstream srodkowy("srodkowy.txt");
    ofstream rungegokuty("rungegokuty.txt");

    double temp{ 1200 }, time1{ 300 }, time0{ 0 }, beta{ 0 }, alfa{ pow(10,-12) };
    int n{ 250 };

    for (int x{ 0 }; x < 2; x++) {
        double h{ (time1 - time0) / n };

        cout << "\nLiczba krokow: " << n << endl;

        double* tab = Euler(temp, h, n, alfa, beta);
        cout << "\nMetoda Eulera:\n";
        cout << "Czas:\t\tTemperatura:\n";
        for (int i{ 0 }; i <= n; i++) {
            euler << tab[i] << "\n";
            cout << i * h << "\t\t" << tab[i] << endl;
        }

        tab = Heun(temp, h, n, alfa, beta);
        cout << "\nMetoda Heunta:\n";
        cout << "\nCzas:\t\tTemperatura:\n";
        for (int j{ 0 }; j <= n; j++) {
            heun << tab[j] << "\n";
            cout << j * h << "\t\t" << tab[j] << endl;
        }

        tab = srodkowy_(temp, h, n, alfa, beta);
        cout << "\nMetoda punktu srodkowego:\n";
        cout << "Czas:\t\tTemperatura:\n";
        for (int g{ 0 }; g <= n; g++) {
            srodkowy << tab[g] << "\n";
            cout << g * h << "\t\t" << tab[g] << endl;
        }

        tab = RungegoKutty(temp, h, n, alfa, beta);
        cout << "\nMetoda Rungego-Kuty czwartego rzedu:\n";
        cout << "Czas:\t\tTemperatura:\n";
        for (int e{ 0 }; e <= n; e++) {
            rungegokuty << tab[e] << "\n";
            cout << e * h << "\t\t" << tab[e] << endl;
        }

        n = 10;
        delete[] tab;
    }

    euler.close();
    heun.close();
    srodkowy.close();
    rungegokuty.close();

    return 0;
}
