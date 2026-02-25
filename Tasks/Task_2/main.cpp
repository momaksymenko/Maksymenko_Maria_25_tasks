#include <iostream>
#include <windows.h>
#include <cmath> 

using namespace std;

double Sum(const double arr[], int n);
double ProdB(const double a[], int n);
double ProdD(const double c[], int n);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Ukrainian");

    double a[] = { 3, 1.5, 4.2, 3.4, 6.8, 2, 1.3 };
    double c[] = { 6.5, 3, 4.1, 2.3, 1.1, 0.5, 7.3 };
    double x = 5.83;

    double A = Sum(a, 7);
    double C = Sum(c, 7);
    double B = ProdB(a, 4);
    double D = ProdD(c, 5);

    cout << "----- Результати обчислень -----" << endl;
    cout << "A = " << A << endl;
    cout << "C = " << C << endl;
    cout << "B = " << B << endl;
    cout << "D = " << D << endl;
    cout << "--------------------------------" << endl;

    double y = (A * x - B) / (C * x + D);
    cout << "y = " << y << endl;

}

double Sum(const double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

double ProdB(const double a[], int n) {
    double prod = 1;
    for (int i = 0; i < n; i++)
        prod *= (pow(a[i], 2) - a[i]);
    return prod;
}

double ProdD(const double c[], int n) {
    double prod = 1;
    for (int i = 0; i < n; i++)
        prod *= c[i];
    return prod;
}
