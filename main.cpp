#include <iostream>
#include <fstream>
using namespace std;

int main() {

    int n;

    fstream file("gauss-data.txt");

    file >> n;
    cout << "Liczba rownan: " << n << endl;

    int **rownania = new int*[n];
    for (int i = 0; i < n; ++i) {
        rownania[i] = new int[n+1];
    }

    int wartosci[n];

    // Wypelniane tablicy wartosciami wspolczynnikow
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+1; ++j) {
            int g;
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

}