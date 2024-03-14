#include <iostream>
#include <fstream>
using namespace std;

void print_matrix(double** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+1; ++j) {
            cout << "|\t" << matrix[i][j] << "\t";
        }
        cout << "|";
        cout << "\n";
    }
}

double multiplier(int i1, int i2, int j, double** matrix) {
//    cout << matrix[i1][j];
//    cout << matrix[i2][j];

    if (matrix[i2][j] == 0) {
        cout << "You can't divide by 0!" << endl;
        exit;
    }

    return matrix[i1][j]/matrix[i2][j];
}
                        // ra - rb*mab
void substract_row(int ra, int rb, double mab, int n, double** matrix) {

    for (int i = 0; i <= n; ++i) {
        matrix[ra][i] = matrix[ra][i] - matrix[rb][i]*mab;
    }

}

void upper_triangular(double** matrix, int n) {
    // w1 - w0*m10, w2 - w0*m20, w3 - w0*m30
    // w2 - w1*m21, w3 - w1*m31
    // w3 - w2*m32

    int rb = 0; // wiersz ktory odejmujemy

    while (rb < n-1) {
        for (int ra = rb+1; ra < n; ++ra) {
            // pomocnicze printowanie, zeby zobaczyc czy petle dzialaja odpowiednio
//            cout << "Wiersz od ktorego odejmujemy: " << wa << ", Wiersz ktory odejmujemy: " << wb << endl;

            // odejmowanie
            double mab = multiplier(ra, rb, rb, matrix);
//            cout << mab;

            substract_row(ra, rb, mab, n, matrix);
        }

        rb++;
    }
}

double compute_x(int i, int n, double** matrix, double* x) {
    double b_i = matrix[i][n];

    double a_ii = matrix[i][i];

    double E_aikXxk = 0;

    int k = i+1;

    while (k < n) {

        E_aikXxk += matrix[i][k]*x[k];

        k++;
    }

    return (b_i - E_aikXxk)/a_ii;

}

int main() {

    int n;
    cout << "Podaj n: ";
    cin >> n;
    cout << "\n";

    fstream A("gauss-data-A.txt");
    fstream B("gauss-data-B.txt");

    cout << "--- Liczba rownan ---" << "\nn = " << n << endl;

    double **augmented_matrix = new double*[n];
    for (int i = 0; i < n; ++i) {
        augmented_matrix[i] = new double[n+1];
    }

    // Wypelniane tablicy wartosciami wspolczynnikow
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double g;
            A >> g;
            augmented_matrix[i][j] = g;
        }

        double h;
        B >> h;
        augmented_matrix[i][n] = h;
    }


    cout << "\n--- Macierz rozszerzona ---" << endl;
    print_matrix(augmented_matrix, n); // przed odejmowaniem wierszy


    //    cout << multiplier(2, 1, 1, rownania); // sprawdzenie czy mnoznik jest wyliczany prawidlowo
    upper_triangular(augmented_matrix, n);

    cout << "\n--- Macierz rozszerzona po przeksztalceniach ---" << endl;
    print_matrix(augmented_matrix, n);    // po odjeciu wierszy


    // tablica przechowuajca wartosci x
    double x[n];

    // wartosc x_n
    x[n-1] = augmented_matrix[n-1][n]/augmented_matrix[n-1][n-1];

    for (int i = n-2; i >= 0; --i) {
        x[i] = compute_x(i, n, augmented_matrix, x);
    }
    
    // wypisywanie x
    cout << "\n--- Wyliczone wartosci x ---" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x_" << i << " = " << x[i] << endl;
    }
}   