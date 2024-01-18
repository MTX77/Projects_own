#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {
	const int l_wezlow{ 52 }, l_wierszy{ 2 }; // liczba wezlow to liczba kolumn  

	double tablica[l_wierszy][l_wezlow]{};

	ifstream data("nr10.txt");

	for (int m = 0; m < l_wierszy; ++m) {
		for (int n = 0; n < l_wezlow; ++n) {
			data >> tablica[m][n];
		}
	}

	double punkt_interpolacyjny{ 0 };
	cout << "Podaj punkt interpolacyjny: ";
	cin >> punkt_interpolacyjny;

	double wartosc_wielomianu{ 0 };
	double wielomian_pomocniczy[l_wezlow]{};

	for (int e = 0; e < l_wezlow; e++) {
		double licznik{ 1 }, mianownik{ 1 };

		for (int i = 0; i < l_wezlow; i++) {
			if (i != e) {
				licznik *= (punkt_interpolacyjny - tablica[0][i]); 
				mianownik *= (tablica[0][e] - tablica[0][i]);
				wielomian_pomocniczy[e] = licznik / mianownik;	
			}
		}
	}

	for (int k = 0; k < l_wezlow; ++k) {
		wartosc_wielomianu += tablica[1][k] * wielomian_pomocniczy[k];
	}

	cout << "\nWartosc wielomianu interpolacyjnego w punkcie " << punkt_interpolacyjny << " to: " << wartosc_wielomianu << "\n";


	return 0;
}