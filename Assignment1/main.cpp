#include <iostream>
#include <iomanip>
#include <cmath>

#define _USE_MATH_DEFINES


using namespace std;

double f(double x, double y) {
    return cos(x);
}

void analytical_solution(double h, int n, double *y) {
    for (int i = 0; i <= n; i++) {
        double xi = i * h;
        y[i] = sin(xi);
    }
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
    cout << name << endl;
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(5) << arr[i] << " ";

    cout << endl;
}

void solutions(int n, int task, double h, double t0, double y0) {
    double xi[n];
    for (int i = 0; i < n; i++)
        xi[i] = i * h;

    printArray("xi=", xi, n);

    if (task == 1) {
        double y[n];
        analytical_solution(h, n, y);

        printArray("y(xi)=", y, n);
    }

    else {
        double eulerSol[n], impEulerSol[n], rungeKuttaSol[n];

        euler(t0, y0, h, n, eulerSol);
        improved_euler(t0, y0, h, n, impEulerSol);
        runge_kutta(t0, y0, h, n, rungeKuttaSol);

        if (task == 2)
            printArray("Euler_yi=", eulerSol, n);
        else if (task == 3)
            printArray("iEuler_yi=", impEulerSol, n);
        else if (task == 4)
            printArray("RK4_yi=", rungeKuttaSol, n);

        double analyticalSol[n];
        analytical_solution(h, n, analyticalSol);

        if (task == 5) {

            double eulerError[n + 1];
            for (int i = 0; i < n; i++)
                eulerError[i] = fabs(eulerSol[i] - analyticalSol[i]);

            printArray("Euler_LE(xi)=", eulerError, n + 1);
        }

        else if (task == 6) {

            double impEulerError[n + 1];
            for (int i = 0; i < n; i++)
                impEulerError[i] = fabs(impEulerSol[i] - analyticalSol[i]);

            printArray("iEuler_LE(xi)=", impEulerError, n + 1);

        }

        else if (task == 7) {

            double rungeKuttaError[n + 1];
            for (int i = 0; i < n; i++)
                rungeKuttaError[i] = fabs(rungeKuttaSol[i] - analyticalSol[i]);

            printArray("RK4_LE(xi)=", rungeKuttaError, n + 1);

        }
    }
}

//void errors(int n,  double n1, double n2, int task, double h, double t0, double y0) {
//    double ni[n2 - n1 + 1];
//    for (int i = 0; i <= n2 - n1; i++)
//        ni[i] = n1 + i;
//
//    printArray("ni=", ni, n2 - n1 + 1);
//
//    if (task == 8 || task == 9 || task == 10) {
//        double eulerSol[n + 1], impEulerSol[n + 1], rungeKuttaSol[n + 1];
//
//        euler(t0, y0, h, n, eulerSol);
//        improved_euler(t0, y0, h, n, impEulerSol);
//        runge_kutta(t0, y0, h, n, rungeKuttaSol);
//
//        double eulerError[n2 - n1 + 1];
//        double impEulerError[n2 - n1 + 1];
//        double rungeKuttaError[n2 - n1 + 1];
//
//        for (int i = n1; i <= n2; i++) {
//            h = 1.0 / i;
//
//            euler(t0, y0, h, i, eulerSol);
//            improved_euler(t0, y0, h, i, impEulerSol);
//            runge_kutta(t0, y0, h, i, rungeKuttaSol);
//
//            eulerError[i - n1] = fabs(eulerSol[i] - exp(-2));
//            impEulerError[i - n1] = fabs(impEulerSol[i] - exp(-2));
//            rungeKuttaError[i - n1] = fabs(rungeKuttaSol[i] - exp(-2));
//        }
//
//        if (task == 8)
//            printArray("Euler_GE(n)=", eulerError, n2 - n1 + 1);
//        else if (task == 9)
//            printArray("iEuler_GE(n)=", impEulerError, n2 - n1 + 1);
//        else if (task == 10)
//            printArray("RK4_GE(n)=", rungeKuttaError, n2 - n1 + 1);
//    }
//
//}

int main() {
    int n, task;
    double n1, n2;

//    scanf("%d", &n);
//    scanf("%lf", &n1);
//    scanf("%lf", &n2);
//    scanf("%d", &task);

    n = 10;
    n1 = 0;
    n2 = M_PI;
    task = 1;

    double t0 = 0;
    double y0 = 1;
    double h = (n2 - n1) / (n - 1);

    solutions(n, task, h, t0, y0);

    // errors(n, n1, n2, task, h, t0, y0);


}