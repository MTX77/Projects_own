#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

const int _size = 5;
fstream dane;

void wczytaj_dane(double Tablica[_size][_size + 1]);

void wyswietl_dane(double Tablica[_size][_size + 1]);

void swap_row(double matrix[_size][_size + 1], int i, int j);

int forwardElim(double matrix[_size][_size + 1]);

void backSub(double matrix[_size][_size + 1]);

void gaussianElimination(double matrix[_size][_size + 1]);

int main() {
    double tab_1[_size][_size + 1], tab_2[_size][_size + 1], tab_3[_size][_size + 1];
    cout << setprecision(2) << fixed;

    dane.open("dane.txt", ios::in);
    if (dane.good() == true) {
        wczytaj_dane(tab_1);
        wczytaj_dane(tab_2);
        wczytaj_dane(tab_3);
    }
    dane.close();

    cout << "Przed eliminacja Gaussa:\n";
    wyswietl_dane(tab_1); cout << "\n";
    wyswietl_dane(tab_2); cout << "\n";
    wyswietl_dane(tab_3); cout << "\n";

    cout << "*** Tablica 1 ***";
    gaussianElimination(tab_1);
    cout << "\n*** Tablica 2 ***\n";
    gaussianElimination(tab_2);
    cout << "\n\n*** Tablica 3 ***";
    gaussianElimination(tab_3);

    cout << "\nPo eliminacja Gaussa:\n";
    wyswietl_dane(tab_1); cout << "\n";
    wyswietl_dane(tab_2); cout << "\n";
    wyswietl_dane(tab_3); cout << "\n";


    return 0;
}

void wczytaj_dane(double Tablica[_size][_size + 1]) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size + 1; j++) {
            dane >> Tablica[i][j];
        }
    }
}

void wyswietl_dane(double Tablica[_size][_size + 1]) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size + 1; j++) {
            cout << Tablica[i][j] << "\t";
        }
        cout << "\n";
    }
}

void swap_row(double matrix[_size][_size + 1], int i, int j){
    for (int k = 0; k <= _size; k++){
        double temp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = temp;
    }
}

int forwardElim(double matrix[_size][_size + 1]){ //pivoting
    
    for (int k = 0; k < _size; k++){
        int index_max = k;
        int value_max = matrix[index_max][k];

        /* find greater amplitude for pivot if any */
        for (int i = k + 1; i < _size; i++)
            if (abs(matrix[i][k]) > value_max)
                value_max = matrix[i][k], index_max = i;

        /* if a principal diagonal element  is zero,
         * it denotes that matrixrix is singular, and
         * will lead to a division-by-zero later. */
        if (!matrix[k][index_max])
            return k; // matrixrix is singular

        /* Swap the greatest value row with current row */
        if (index_max != k)
            swap_row(matrix, k, index_max);

        for (int i = k + 1; i < _size; i++){
            /* factor f to set current row kth element to 0,
             * and subsequently remaining kth column to 0 */
            double f = matrix[i][k] / matrix[k][k];

            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j = k + 1; j <= _size; j++)
                matrix[i][j] -= matrix[k][j] * f;

            /* filling lower triangular matrixrix with zeros*/
            matrix[i][k] = 0;
        }
    }
    return -1;
}

void backSub(double matrix[_size][_size + 1]){
    double x[_size];  // An array to store solution

    /* Start calculating from last equation up to the
       first */
    for (int i = _size - 1; i >= 0; i--)
    {
        /* start with the RHS of the equation */
        x[i] = matrix[i][_size];

        /* Initialize j to i+1 since matrixrix is upper
           triangular*/
        for (int j = i + 1; j < _size; j++)
        {
            /* subtract all the lhs values
             * except the coefficient of the variable
             * whose value is being calculated */
            x[i] -= matrix[i][j] * x[j];
        }

        /* divide the RHS by the coefficient of the
           unknown being calculated */
        x[i] = x[i] / matrix[i][i];
    }

    printf("\nRozwiazanie:\n");
    for (int i = 0; i < _size; i++)
        cout << x[i] << endl;
}

void gaussianElimination(double matrix[_size][_size + 1]){
    /* reduction into r.e.f. */
    int singular_flag = forwardElim(matrix);

    /* if matrixrix is singular */
    if (singular_flag != -1)
    {
        printf("Macierz osobliwa - wyznacznik 0\n");

        /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
        if (matrix[singular_flag][_size])
            printf("Uklad sprzeczny");
        else
            printf("Moze miec nieskonczenie wiele rozwiazan");

        return;
    }

    /* get solution to system and print it using
       backward substitution */
    backSub(matrix);
}