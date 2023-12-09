#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

double f(double x, double y) {
    return cos(x);
}

void exact_solution(double h, int n, double *y) {
    for (int i = 0; i <= n; i++) {
        double xi = i * h;
        y[i] = sin(xi);
    }
}

void analytical_solution(double h, int n, double *y) {
    for (int i = 0; i <= n; i++) {
        double xi = i * h;
        y[i] = sin(xi) + 1;
    }
}

void euler(double y0, double h, int n, double *y, double *xi) {
    y[0] = y0;
    for (int i = 1; i <= n; i++) {
        y[i] = y[i - 1] + h * f(xi[i - 1], y[i - 1]);
    }
}

void improved_euler(double y0, double h, int n, double *y, double *xi) {
    y[0] = y0;

    for (int i = 1; i <= n; i++) {
        double k1 = f(xi[i - 1], y[i - 1]);
        double k2 = f(xi[i - 1] + h, y[i - 1] + h * k1);

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


void printArray(const string &name, double *arr, int n) {
    cout << name << endl;
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(5) << arr[i] << " ";

    cout << endl;
}

void solutions(int n, int task, double h, double a, double b, double y0) {
    double xi[n];
    for (int i = 0; i < n; i++)
        xi[i] = i * h;

    printArray("xi=", xi, n);

    if (task == 1) {
        double y[n];
        exact_solution(h, n, y);

        printArray("y(xi)=", y, n);
    } else {
        double eulerSol[n], impEulerSol[n], rungeKuttaSol[n];

        if (task == 2) {
            euler(y0, h, n, eulerSol, xi);
            printArray("Euler_yi=", eulerSol, n);
        } else if (task == 3) {
            improved_euler(y0, h, n, impEulerSol, xi);
            printArray("iEuler_yi=", impEulerSol, n);
        } else if (task == 4) {
            printArray("RK4_yi=", rungeKuttaSol, n);
            runge_kutta(a, y0, h, n, rungeKuttaSol);
        }

        double analyticalSol[n];
        analytical_solution(h, n, analyticalSol);

        if (task == 5) {

            double eulerError[n + 1];
            for (int i = 0; i < n; i++)
                eulerError[i] = fabs(eulerSol[i] - analyticalSol[i]);

            printArray("Euler_LE(xi)=", eulerError, n + 1);
        } else if (task == 6) {

            double impEulerError[n + 1];
            for (int i = 0; i < n; i++)
                impEulerError[i] = fabs(impEulerSol[i] - analyticalSol[i]);

            printArray("iEuler_LE(xi)=", impEulerError, n + 1);

        } else if (task == 7) {

            double rungeKuttaError[n + 1];
            for (int i = 0; i < n; i++)
                rungeKuttaError[i] = fabs(rungeKuttaSol[i] - analyticalSol[i]);

            printArray("RK4_LE(xi)=", rungeKuttaError, n + 1);

        }
    }
}


int main() {
    int n, task;
    double n1, n2;

    scanf("%d %lf %lf %d", &n, &n1, &n2, &task);

    double a = 0;
    double b = M_PI;

    double y0 = 0;

    double h = (b - a) / (n - 1);

    solutions(n, task, h, a, b, y0);


}