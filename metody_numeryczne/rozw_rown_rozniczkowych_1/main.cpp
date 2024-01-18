#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

double Pochodna(double alfa, double beta, double temp) {
	return (-alfa * (pow(temp, 4) - beta));
}

int main() {

	ofstream zapis("dane.txt");

	double temp{ 1200 }, time1{ 300 }, time0{ 0 }, beta{ 0 }, alfa{ pow(10,-12) };
	int n{ 250 };

	for (int x = 0; x < 3; x++) {
		cout << "\n\nLiczba krokow: " << n << "\nCzas:\t\tTemperatura:\n";
		zapis << "\n\nLiczba krokow: " << n << "\nCzas:\t\tTemperatura:\n";
		double h = (time1 - time0) / n;
		vector <double> tab_temp{ 0 };
		vector <double> tab_time{ 0 };

		tab_temp.at(0) = temp;
		tab_time.at(0) = time0;

		for (int i{ 0 }; i < n; i++) {
			tab_temp.at(static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1) = tab_temp.at(i) + h * Pochodna(alfa, beta, tab_temp.at(i));
			tab_time.at(static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1) = tab_time.at(i) + h;
		}

		for (int i{ 0 }; i <= n; i++) {
			cout << tab_time.at(i) << "\t\t" << tab_temp.at(i) << endl;
			zapis << tab_time.at(i) << "\t\t" << tab_temp.at(i) << endl;
		}

		n /= 5;
	}

	zapis.close();
	return 0;
}
