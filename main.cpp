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
        rownania[i] = new int[n];
    }

    // Wypelniane tablicy wartosciami wspolczynnikow
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int g;
            file >> g;
            rownania[i][j] = g;
        }
    }

    // Wypisywanie wspolczynnikow przed rownaniami
    cout << "\nWspolczynniki:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "|\t" << rownania[i][j] << "\t";
        }
        cout << "|";
        cout << "\n";
    }

}