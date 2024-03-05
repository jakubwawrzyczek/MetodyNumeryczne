#include <iostream>
#include <fstream>
using namespace std;

struct Point {
    double x;
    double y;
};

// ∏(x-x_i) dla i od 0 do k-1, gdzie k = n
double calc_p_k(int k, double x, Point* points) {

    double p_k = 1;
    int i = 0;

    while (i < k) {
        p_k *= (x - points[i].x);
        i++;
    }

    return p_k;
}

double calc_b_k(double x, Point* points) {

}

int main() {

    // wczytywanie punktow z pliku do tablicy
    int n;
    fstream file("newton-data.txt");

    file >> n;
    cout << "Liczba węzłów: " << n << endl;

    Point points[n];

    for (int i = 0 ; i < n ; i++ ) {
        double xi;
        double yi;

        file >> xi;
        file >> yi;

        points[i].x = xi;
        points[i].y = yi;
    }

    // wypisywanie punktow zeby sprawdzic czy poprawnie odczytane z pliku
    for ( int i = 0 ; i < n ; i++) {
        cout << "f(" << points[i].x << ") = " << points[i].y << endl;
    }

    // pobieranie wartosci od uzytkownika
    double x;
    cout << "\nPodaj wartosc x: ";
    cin >> x;

    // obliczanie p_k i zapisywanie do zmiennej (testowo bo pozniej trzeba w tabeli wszystkie zapisac)
    double p_k = calc_p_k(2, x, points);
    cout << p_k;

    // obliczanie b_k i zapisywanie do zmiennej (testowo bo pozniej trzeba w tabeli wszystkie zapisac)


    // p_0 = 1
    double p_0 = 1.00;

    // b_0 = f(x_0), czyli wartosc (y) funkcji dla pierwszego x z listy
    double b_0 = points[0].y;

}