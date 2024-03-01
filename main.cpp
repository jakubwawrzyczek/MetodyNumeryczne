#include <iostream>
#include <fstream>
using namespace std;

int main() {

    int n;

    fstream file("data.txt");

    file >> n;
    cout << "Liczba węzłów: " << n << endl;
}
