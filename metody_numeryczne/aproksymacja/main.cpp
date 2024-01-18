#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>
using namespace std;

const int _size = 5;

double baza0(double x) {return pow(x, 0);}
double baza1(double x) {return x;}
double baza2(double x) {return pow(x, 2);}
double baza3(double x) {return pow(x, 3);}
double baza4(double x) {return pow(x, 4);}
double baza5(double x) {return pow(x, 5);}
double baza6(double x) {return pow(x, 6);}
double baza7(double x) {return pow(x, 7);}
double baza8(double x) {return pow(x, 8);}

function<double(double)> baza[9] = { baza0, baza1, baza2, baza3, baza4, baza5, baza6, baza7, baza8 };

double calka1(double x) {
    return (exp(x) * sin(x / 2) - pow(x, 3));
}
double calka2(double x) {
    return (exp(x) * sin(x / 2) - pow(x, 3)) * x;
}
double calka3(double x) {
    return (exp(x) * sin(x / 2) - pow(x, 3)) * pow(x, 2);
}
double calka4(double x) {
    return (exp(x) * sin(x / 2) - pow(x, 3)) * pow(x, 3);
}
double calka5(double x) {
    return (exp(x) * sin(x / 2) - pow(x, 3)) * pow(x, 4);
}

function<double(double)> calka[5] = { calka1, calka2, calka3, calka4, calka5 };

double kwadratura_4(function<double(double)>f, double a, double b);

double Przedzialyy(function<double(double)>f, double a, double b, int n);

void wyswietl_dane(double Tablica[_size][_size + 1]);

void swap_row(double matrix[_size][_size + 1], int i, int j);

int forwardElim(double matrix[_size][_size + 1]);

void backSub(double matrix[_size][_size + 1]);

void gaussianElimination(double matrix[_size][_size + 1]);

double** macierz_apro(function<double(double)>* baza, function<double(double)>* calka, double a, double b, int n);

int main() {

    cout << fixed << setprecision(10);

    double a{ -1.0 }, b{ 1.0 };
    double mat[_size][_size + 1]{};

    double** ptr = macierz_apro(baza, calka, a, b, 40);

    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size + 1; j++) {
            mat[i][j] = ptr[i][j];
        }
    }
    wyswietl_dane(mat);

    gaussianElimination(mat);

    return 0;
}

double kwadratura_4(function<double(double)>f, double a, double b) {
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

double Przedzialyy(function<double(double)>f, double a, double b, int n) {
    double ax{ a }, bx{ b }, v3{ 0 };
    double odst = b - a;
    for (int i = 2; i <= n; i++)
    {
        ax = a;
        bx = a + odst / (double)i;
        v3 = kwadratura_4(f, ax, bx);

        for (int j = 1; j < i; j++) {
            ax = a + odst * ((double)(j) / (double)i);
            bx = a + odst * ((double)(j + 1) / (double)i);
            v3 += kwadratura_4(f, ax, bx);
        }
    }
    return v3;
}

double** macierz_apro(function<double(double)>* baza, function<double(double)>* calka, double a, double b, int n) {
    double** tab = new double* [_size];

    for (int g = 0; g < _size; g++) {
        tab[g] = new double[_size + 1];
    }

    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            tab[i][j] = Przedzialyy(baza[j + i], a, b, n);
        }
        tab[i][_size] = Przedzialyy(calka[i], a, b, n);
    }

    return tab;
}

void swap_row(double matrix[_size][_size + 1], int i, int j) {
    for (int k = 0; k <= _size; k++) {
        double temp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = temp;
    }
}

int forwardElim(double matrix[_size][_size + 1]) { //pivoting

    for (int k = 0; k < _size; k++) {
        int index_max = k;
        double value_max = matrix[index_max][k];       

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

        for (int i = k + 1; i < _size; i++) {
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
        wyswietl_dane(matrix);
    }
    return -1;
}

void backSub(double matrix[_size][_size + 1]) {
    double x[_size]{};  // An array to store solution

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

    printf("\nRozwiazanie dla e^x * sin(x/2)x^3:\n");
    for (int i = 0; i < _size; i++)
        cout << "a" << i <<": " << x[i] << endl;
}

void gaussianElimination(double matrix[_size][_size + 1]) {
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

void wyswietl_dane(double Tablica[_size][_size + 1]) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size + 1; j++) {
            cout << Tablica[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}