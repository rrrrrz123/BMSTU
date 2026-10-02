/*
#include <iostream>
#include <cmath>

using namespace std;
void calc(double x, double eps); // функция проверки
int main() {
    double x;
    cout << "Enter x (in radians): ";
    cin >> x;

    cout << "\nsin(x) = " << sin(x) << endl;

    // функции для разных точностей
    calc(x, 1e-2);
    calc(x, 1e-4);
    calc(x, 1e-6);
    calc(x, 1e-8);

    return 0;
}
// функция для вычисления sin(x) с точностью eps
void calc(double x, double eps) {
    double pr = x;
    int iterations = 0;
    long long n = 1;

    const double pi = acos(-1.0);
    double x_sq = x * x;
    double pi_sq = pi * pi;

    while (true) {
        double t = x_sq / (n * n * pi_sq);

        // проверка точности
        if (abs(pr * t) < eps) {
            break;
        }

        pr *= (1.0 - t);
        iterations++;
        n++;
    }

    cout << "Tochnost: " << eps
         << "| sin(x) = " << pr
         << "| Iteracia: " << iterations << endl;
}
*/
