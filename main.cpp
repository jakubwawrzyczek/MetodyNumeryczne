#include <iostream>
#include <fstream>
using namespace std;

double mnoznik(int i1, int i2, double** macierz) {
    return macierz[i1][0]/macierz[i2][0];
}

int main() {

    int n;

    fstream file("gauss-data.txt");

    file >> n;
    cout << "Liczba rownan: " << n << endl;

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

    // Wypisywanie wspolczynnikow przed rownaniami
    cout << "\nMacierz:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+1; ++j) {
            cout << "|\t" << rownania[i][j] << "\t";
        }
        cout << "|";
        cout << "\n";
    }

    // cout << mnoznik(2, 0, rownania); // sprawdzenie czy mnoznik jest wyliczany prawidlowo

    
}