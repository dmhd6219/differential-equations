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

void runge_kutta(double y0, double h, int n, double *y, double *xi) {
    y[0] = y0;

    for (int i = 1; i <= n; i++) {
        double k1 = f(xi[i - 1], 1);
        double k2 = f(xi[i - 1] + 0.5 * h, 1);
        double k3 = f(xi[i - 1] + 0.5 * h, 1);
        double k4 = f(xi[i - 1] + h, 1);

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
            runge_kutta(y0, h, n, rungeKuttaSol, xi);
            printArray("RK4_yi=", rungeKuttaSol, n);
        }

        double exactSolution[n];
        exact_solution(h, n, exactSolution);

        if (task == 5) {
            euler(y0, h, n, eulerSol, xi);

            double eulerError[n];
            for (int i = 0; i < n; i++){
                eulerError[i] = abs(eulerSol[i] - exactSolution[i]);
            }

            printArray("Euler_LE(xi)=", eulerError, n);
        } else if (task == 6) {
            improved_euler(y0, h, n, impEulerSol, xi);

            double impEulerError[n];
            for (int i = 0; i < n; i++)
                impEulerError[i] = fabs(impEulerSol[i] - exactSolution[i]);

            printArray("iEuler_LE(xi)=", impEulerError, n);

        } else if (task == 7) {
            runge_kutta(y0, h, n, rungeKuttaSol, xi);

            double rungeKuttaError[n];
            for (int i = 0; i < n; i++)
                rungeKuttaError[i] = fabs(rungeKuttaSol[i] - exactSolution[i]);

            printArray("RK4_LE(xi)=", rungeKuttaError, n);

        }
    }
}


int main() {
    int n, task, n1, n2;

    scanf("%d %lf %lf %d", &n, &n1, &n2, &task);

//    n = 10;
//    n1 = 10;
//    n2 = 20;
//    task = 5;


    double a = 0;
    double b = M_PI;

    double y0 = 0;

    double h = (b - a) / (n - 1);

    solutions(n, task, h, a, b, y0);


}