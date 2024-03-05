#include <iostream>
#include <fstream>
using namespace std;

struct Point {
    double x;
    double y;
};

double li(int i, double x, int n, Point points[]) {

    double ai = 1;
    double bi = 1;

    for (int j = 0 ; j < n ; j++) {
        if (j == i) {
            continue;
        }

        ai *= (x - points[j].x);
        bi *= (points[i].x - points[j].x);
    }

    return ai/bi;
}

int main() {

    int n;

    fstream file("lagrange-data.txt");

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

    double x;
    cout << "\nPodaj wartosc x: ";
    cin >> x;

    double y = 0;

    for (int m = 0 ; m < n ; m++) {
        y += li(m, x, n, points) * points[m].y;
    }

    cout << "\nWykonując interpolację dla punktu podanego przez użytkownika: " << endl;
    cout << "f(" << x << ") = " << y << endl;
}
