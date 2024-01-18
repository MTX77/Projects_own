#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;

double horner(double tablica_wsp_wiel[], int n, double x){
    double wynik = tablica_wsp_wiel[n];

    for (int i = n - 1; i >= 0; i--){
        wynik = wynik * x + tablica_wsp_wiel[i];
    }

    return wynik;
}

int main()
{
    cout << "\n\tObliczanie wartosci wielomianu w postaci naturalnej:\n\n";
    ifstream plik("10_Horner.txt");

    const int stopien{ 9 }, l_punktów{ 119 };
    double wielomian_naturalny[l_punktów]{};
    double tablica_wsp_wiel[stopien + 1]{}, tablica_punktow[l_punktów]{};

    for (int i{ 0 }; i <= stopien; i++) {
        plik >> tablica_wsp_wiel[i];
    }

    auto start = chrono::high_resolution_clock::now();

    for (int n{ 0 }; n < l_punktów; n++) {

        plik >> tablica_punktow[n];

        for (int h{ 0 }; h <= stopien; h++) {
            wielomian_naturalny[n] += tablica_wsp_wiel[h] * pow(tablica_punktow[n], h);
        }
        cout << wielomian_naturalny[n] << " ";
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "\n\nCzas wykonywania obliczen: " << duration.count() << " mikrosekund\n";

    plik.close();

    //HORNER
    cout << "\n\tObliczanie wartosci wielomianu wedlug schematu Hornera:\n\n";
    double wielomian_hornera[l_punktów]{};

    auto start2 = chrono::high_resolution_clock::now();

    for (int j{ 0 }; j < l_punktów; j++) {
        wielomian_hornera[j] = horner(tablica_wsp_wiel, stopien, tablica_punktow[j]);
        cout << wielomian_hornera[j] << " ";
    }

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
    cout << "\n\nCzas wykonywania obliczen: " << duration2.count() << " mikrosekund" << endl;

    auto roznica = abs(duration2.count() - duration.count());
    cout << "\nRoznica w czasie wynosi: " << roznica << " mikrosekund\n";

    cout << "\nPorownanie dokladnosci obliczen:\n";
    for (int m{ 0 }; m < l_punktów; m++) {
        cout << abs(wielomian_naturalny[m] - wielomian_hornera[m]) << endl;
    }

    //WSPOLCZYNNIKI

    cout << "\nWartosci wspolczynnikow wielomianu w postaci Newtona:\n";
    ifstream plik3("10_Newton.txt");
    const int  l_punktów_n{ 126 };
    double tablica_punktow3[l_punktów_n]{};
    double tablica_punktow_y[l_punktów_n]{};
    double tablica_wsp_wiel3[l_punktów_n]{};

    for (int g{ 0 }; g < l_punktów_n; g++) {
        plik3 >> tablica_punktow3[g];
    }

    for (int b{ 0 }; b < l_punktów_n; b++) {
        plik3 >> tablica_punktow_y[b];
    }

    for (int e{ 0 }; e < l_punktów_n; e++) {
        for (int r{ 0 }; r < e + 1; r++){

            double temp = tablica_punktow_y[r];

            for (int t{ 0 }; t < e + 1; t++){
                if (t != r){
                    temp /= (tablica_punktow3[r] - tablica_punktow3[t]);
                }
            }
            tablica_wsp_wiel3[e] += temp;
        }
        cout << "a[" << e << "] = " << tablica_wsp_wiel3[e] << endl;
    }

    plik3.close();

    double x;
    cout << "\nPodaj x: ";
    cin >> x;

    for (int y{ 0 }; y < l_punktów_n; y++){
        if (tablica_punktow3[y] == x){
            cout << "Wynik dla " << x << " = " << tablica_punktow_y[y] << endl;
        }
    }

    return 0;
}