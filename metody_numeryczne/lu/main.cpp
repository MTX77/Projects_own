#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

const int n = 5;

void rozwiazanie(double matrix[n][n + 1], double matrix_x[n][n + 1], double U[n][n]);

void result(double matrix[n][n + 1]);

int main(){
    ifstream _data("dane.txt");

    double matrix[n][n]{ }, b[n]{ }, l[n][n]{ }, u[n][n]{ }, lx[n][n + 1]{ }, lz[n][n + 1]{ };

    for (int i{ 0 }; i < n; i++){
        _data >> b[i];
    }
 
    for (int k{ 0 }; k < n; k++){
        for (int j{ 0 }; j < n; j++){
            _data >> matrix[k][j];
        }
    }

    for (int m{ 0 }; m < n; m++){
        cout << "\tU:\n\n";

        for (int j{ 0 }; j < n; j++){

            double suma{ 0 };

            for (int h{ 0 }; h < m; h++){
                suma += (l[m][h] * u[h][j]);
            }

            u[m][j] = matrix[m][j] - suma;

            for (int i{ 0 }; i < n; i++){
                for (int b{ 0 }; b < n; b++){
                    cout << setw(8) << setprecision(3) << u[i][b] << " ";
                }cout << "\n";
            }cout << "\n";
        }

        cout << "\tL:\n\n";

        for (int k{ 0 }; k < n; k++){
            if (m == k)
                l[m][m] = 1;
            else{

                double suma{ 0 };

                for (int d{ 0 }; d < m; d++){
                    suma += (l[k][d] * u[d][m]);
                }

                l[k][m] = (matrix[k][m] - suma) / u[m][m];

                for (int i{ 0 }; i < n; i++){
                    for (int f{ 0 }; f < n; f++){
                        cout << setw(8) << setprecision(3) << l[i][f] << " ";
                    }cout << "\n";
                }
            }cout << "\n";
        }
    }

    cout << "\tLZ:\n\n";

    for (int h{ 0 }; h < n; h++){
        for (int j{ 0 }; j < n + 1; j++){

            lz[h][j] = l[h][j];
            lz[h][n] = b[h];
            cout << setw(8) << setprecision(3) << lz[h][j] << " ";
        }
        cout << "\n";
    }

    rozwiazanie(lz, lx, u);

    result(lx);

    _data.close();
    return 0;
}

void rozwiazanie(double matrix[n][n + 1], double matrix_x[n][n + 1], double U[n][n]){
    double temp[n];

    for (int i{ 0 }; i < n; i++){
        temp[i] = matrix[i][n];
        for (int b{ 0 }; b < i; b++){
            temp[i] -= matrix[i][b] * temp[b];
        }

        temp[i] = temp[i] / matrix[i][i];
    }

    cout << "\nZ:\n";
    for (int k{ 0 }; k < n; k++){
        cout << setw(8) << setprecision(3) << temp[k] <<"\t";
    }

    for (int g{ 0 }; g < n; g++){
        for (int j{ 0 }; j < n + 1; j++){
            matrix_x[g][j] = U[g][j];
            matrix_x[g][n] = temp[g];
        }
    }
}

void result(double matrix[n][n + 1]){
    double temp[n];

    for (int h = n - 1; h >= 0; h--){
        temp[h] = matrix[h][n];
        for (int k = h + 1; k < n; k++){
            temp[h] -= matrix[h][k] * temp[k];
        }

        temp[h] = temp[h] / matrix[h][h];
    }

    cout << "\n\nRozwiazania ukladu:\n";
    for (int f{ 0 }; f < n; f++) {
        cout << setw(8) << setprecision(3) << temp[f] << "\t";
    }cout << "\n";
}