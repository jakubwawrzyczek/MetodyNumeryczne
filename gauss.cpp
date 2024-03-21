#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Struktura reprezentująca macierz rozszerzoną
struct Matrix {
    vector<vector<double>> data; // Dane macierzy
    int size; // Rozmiar macierzy
};

// Funkcja do wczytania macierzy z pliku
Matrix readMatrixFromFile(const string& A, const string& B) {
    ifstream fileA(A);
    ifstream fileB(B);
    if (!fileA || !fileB) {
        cerr << "Nie można otworzyć pliku." << endl;
        exit(EXIT_FAILURE);
    }

    int n = 4;
    Matrix matrix;
    matrix.size = n;
    matrix.data.resize(n, vector<double>(n + 1)); // Macierz rozszerzona [n x (n+1)]

    // Wczytywanie danych z pliku
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fileA >> matrix.data[i][j];
        }
        fileB >> matrix.data[i][n];
    }
    fileA.close();
    fileB.close();

    return matrix;
}

// Funkcja do wypisania macierzy
void printMatrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j <= matrix.size; ++j) {
            cout << "|\t" << matrix.data[i][j] << "\t";
        }
        cout << "\t|" << endl;
    }
}

void swapRows(vector<vector<double>>& matrix, int row1, int row2) {
    if (row1 != row2) {
        swap(matrix[row1], matrix[row2]);
    }
}

// Funkcja do rozwiązania układu równań metodą Gaussa
vector<double> solveGauss(Matrix matrix) {
    int n = matrix.size;

    // Eliminacja współczynników
    for (int i = 0; i < n - 1; ++i) {
        int maxRowIndex = i;
        double maxValue = abs(matrix.data[i][i]);
        for (int k = i + 1; k < n; ++k) {
            if (abs(matrix.data[k][i]) > maxValue) {
                maxValue = abs(matrix.data[k][i]);
                maxRowIndex = k;
            }
        }
        swapRows(matrix.data, i, maxRowIndex);
        for (int k = i + 1; k < n; k++) {
            double factor = matrix.data[k][i] / matrix.data[i][i];
            for (int j = i; j <= n; ++j) {
                matrix.data[k][j] -= factor * matrix.data[i][j];
            }
        }
    }

    cout << "Macierz rozszerzona po obliczeniach:" << endl;
    printMatrix(matrix);

    // Rozwiązywanie układu równań
    vector<double> solutions(n);
    for (int i = n - 1; i >= 0; --i) {
        solutions[i] = matrix.data[i][n];
        for (int j = i + 1; j < n; ++j) {
            solutions[i] -= matrix.data[i][j] * solutions[j];
        }
        solutions[i] /= matrix.data[i][i];
    }

    return solutions;
}

vector<double> solveGaussCrout(Matrix matrix, vector<int>& columnOrder) {
    int n = matrix.size;

    // Initialize column order vector
    columnOrder.resize(n);
    for (int i = 0; i < n; ++i)
        columnOrder[i] = i;

    // Forward elimination
    for (int k = 0; k < n - 1; ++k) {
        // Partial pivoting
        int maxRowIndex = k;
        double maxVal = abs(matrix.data[k][k]);
        for (int i = k + 1; i < n; ++i) {
            if (abs(matrix.data[i][k]) > maxVal) {
                maxVal = abs(matrix.data[i][k]);
                maxRowIndex = i;
            }
        }
        if (maxRowIndex != k) {
            swap(matrix.data[maxRowIndex], matrix.data[k]);
            swap(columnOrder[maxRowIndex], columnOrder[k]);
        }

        // Elimination
        for (int i = k + 1; i < n; ++i) {
            double factor = matrix.data[i][k] / matrix.data[k][k];
            for (int j = k; j < n + 1; ++j)
                matrix.data[i][j] -= factor * matrix.data[k][j];
        }
    }

    printMatrix(matrix);

    // Rozwiązywanie układu równań
    vector<double> solutions(n);
    for (int i = n - 1; i >= 0; --i) {
        solutions[i] = matrix.data[i][n];
        for (int j = i + 1; j < n; ++j) {
            solutions[i] -= matrix.data[i][j] * solutions[j];
        }
        solutions[i] /= matrix.data[i][i];
    }

    return solutions;
}

int main() {
    Matrix matrix = readMatrixFromFile("gauss-data-A.txt","gauss-data-B.txt");

    cout << "Macierz rozszerzona przed obliczeniami:" << endl;
    printMatrix(matrix);
    cout << endl;

    vector<double> initialSolutions = solveGauss(matrix);

    // zadanie 2
//    vector<int> columnOrder;
//    vector<double> initialSolutions = solveGaussCrout(matrix, columnOrder);
//
//    cout << "Numery kolumn: " << endl;
//    for (int i = 0; i < matrix.size; ++i)
//        cout << columnOrder[i] << " ";
//    cout << endl << endl;

    cout << "\nRozwiązanie układu równań:" << endl;
    for (size_t i = 0; i < initialSolutions.size(); ++i) {
        cout << "x_" << i << " = " << initialSolutions[i] << endl;
    }

    return 0;
}
