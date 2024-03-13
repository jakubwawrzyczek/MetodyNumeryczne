#include <iostream>
#include <fstream>
using namespace std;

void wypisz_macierz(double** macierz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+1; ++j) {
            cout << "|\t" << macierz[i][j] << "\t";
        }
        cout << "|";
        cout << "\n";
    }
}

double mnoznik(int i1, int i2, int j, double** macierz) {
//    cout << macierz[i1][j];
//    cout << macierz[i2][j];
    return macierz[i1][j]/macierz[i2][j];
}
                        // wa - wb*mab
void odejmij_wiersze(int wa, int wb, double mab, int n, double** macierz) {

    for (int i = 0; i <= n; ++i) {
        macierz[wa][i] = macierz[wa][i] - macierz[wb][i]*mab;
    }

}

void wyzeruj_po_przekatnej(double** macierz, int n) {
    // w1 - w0*m10, w2 - w0*m20, w3 - w0*m30
    // w2 - w1*m21, w3 - w1*m31
    // w3 - w2*m32

    int wb = 0; // wiersz ktory odejmujemy

    while (wb < n-1) {
        for (int wa = wb+1; wa < n; ++wa) {
            // pomocnicze printowanie, zeby zobaczyc czy petle dzialaja odpowiednio
//            cout << "Wiersz od ktorego odejmujemy: " << wa << ", Wiersz ktory odejmujemy: " << wb << endl;

            // odejmowanie
            double mab = mnoznik(wa, wb, wb, macierz);
//            cout << mab;

            odejmij_wiersze(wa, wb, mab, n, macierz);
        }

        wb++;
    }
}

double wylicz_x(int i, int n, double** macierz, double* x) {
    double b_i = macierz[i][n];

    double a_ii = macierz[i][i];

    double E_aikXxk = 0;

    int k = i+1;

    while (k < n) {

        E_aikXxk += macierz[i][k]*x[k];

        k++;
    }

    return (b_i - E_aikXxk)/a_ii;

}

int main() {

    int n;

    fstream file("gauss-data.txt");

    file >> n;
    cout << "--- Liczba rownan: ---" << "\nn = " << n << endl;

    double **rownania = new double*[n];
    for (int i = 0; i < n; ++i) {
        rownania[i] = new double[n+1];
    }

    int wartosci[n];

    // Wypelniane tablicy wartosciami wspolczynnikow
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+1; ++j) {
            double g;
            file >> g;
            rownania[i][j] = g;
        }
    }


    cout << "\n---Macierz rozszerzona: ---" << endl;
    wypisz_macierz(rownania, n); // przed odejmowaniem wierszy


    //    cout << mnoznik(2, 1, 1, rownania); // sprawdzenie czy mnoznik jest wyliczany prawidlowo
    wyzeruj_po_przekatnej(rownania, n);

    cout << "\n---Macierz rozszerzona po przeksztalceniach: ---" << endl;
    wypisz_macierz(rownania, n);    // po odjeciu wierszy


    // tablica przechowuajca wartosci x
    double x[n];

    // wartosc x_n
    x[n-1] = rownania[n-1][n]/rownania[n-1][n-1];

    for (int i = n-2; i >= 0; --i) {
        x[i] = wylicz_x(i, n, rownania, x);
    }
    
    // wypisywanie x
    cout << "\n--- Wyliczone wartosci x ---" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x_" << i << " = " << x[i] << endl;
    }
}   