#include <iostream>
#include <fstream>
using namespace std;

struct Point {
    double x;
    double y;
};

int main() {

    int n;

    fstream file("data.txt");

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
}
