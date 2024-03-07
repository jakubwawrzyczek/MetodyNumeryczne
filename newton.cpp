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

double calc_b_k(int k, Point* points) {

    double b_k = 0;
    int i = 0;

    while (i <= k) {
        int j = 0;
        double mianownik = 1;

        while (j <= k) {
            if (i == j) {
                j++;
                continue;
            }

            mianownik *= (points[i].x - points[j].x);

            j++;
        }

        b_k += points[i].y / mianownik;
        i++;
    }

    return b_k;
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

    // obliczanie p_k dla k do n-1 i zapisywanie do tablicy
    double p_table[n];

    for (int i = 0; i < n; i++) {
        p_table[i] = calc_p_k(i, x, points);
    }

    // wypisywanie tablicy z p

    for (int i = 0; i < n; i++) {
        cout << "\np_" << i << " = " << p_table[i];
    }

    // obliczanie b_k i zapisywanie do tablicy
    double b_table[n];

    for (int i = 0; i < n; i++) {
        b_table[i] = calc_b_k(i, points);
    }

    // wypisywanie tablicy z b
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << "\nb_" << i << " = " << b_table[i];
    }

    // wartosc wielomianu Newtona w danym punkcie
    double w_x = 0;

    for (int i = 0; i < n; ++i) {
        w_x += p_table[i]*b_table[i];
    }

    cout << "\n\nWartość wielomianu w punkcie podanym przez użytkownika:" << endl;
    cout << "f(" << x <<") = " << w_x << endl;
}