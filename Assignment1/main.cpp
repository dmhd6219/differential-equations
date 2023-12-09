#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x, double y) {
    return cos(x);
}


void euler(double t0, double y0, double h, int n, double *y) {
    y[0] = y0;

    for (int i = 1; i <= n; i++) {
        double t = t0 + i * h;
        y[i] = y[i - 1] + h * f(t, y[i - 1]);
    }
}

void improved_euler(double t0, double y0, double h, int n, double *y) {
    y[0] = y0;

    for (int i = 1; i <= n; i++) {
        double t = t0 + (i - 1) * h;
        double k1 = f(t, y[i - 1]);
        double k2 = f(t + h, y[i - 1] + h * k1);

        y[i] = y[i - 1] + (h / 2) * (k1 + k2);
    }
}

void runge_kutta(double t0, double y0, double h, int n, double *y) {
    y[0] = y0;

    for (int i = 1; i <= n; i++) {
        double t = t0 + (i - 1) * h;

        double k1 = f(t, y[i - 1]);
        double k2 = f(t + 0.5 * h, y[i - 1] + 0.5 * h * k1);
        double k3 = f(t + 0.5 * h, y[i - 1] + 0.5 * h * k2);
        double k4 = f(t + h, y[i - 1] + h * k3);

        y[i] = y[i - 1] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    }
}


void printArray(const string &name, double arr[], int n) {
    cout << name;
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(5) << arr[i] << " ";
    cout << "\\" << "\\" << "n";

    cout << endl;
}

