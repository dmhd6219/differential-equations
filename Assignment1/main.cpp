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

void euler(double h, int n, double y[], double xi[]) {
    y[0] = 0;
    for (int i = 1; i < n; i++) {
        y[i] = y[i - 1] + h * f(xi[i - 1], y[i - 1]);
    }
}

void improved_euler(double h, int n, double y[], double xi[]) {
    y[0] = 0;

    for (int i = 1; i < n; i++) {
        double k1 = f(xi[i - 1], y[i - 1]);
        double k2 = f(xi[i - 1] + h, y[i - 1] + h * k1);

        y[i] = y[i - 1] + (h / 2) * (k1 + k2);
    }
}

void runge_kutta(double h, int n, double y[], double xi[]) {
    y[0] = 0;

    for (int i = 1; i < n; i++) {
        double k1 = f(xi[i - 1], 1);
        double k2 = f(xi[i - 1] + 0.5 * h, 1);
        double k3 = f(xi[i - 1] + 0.5 * h, 1);
        double k4 = f(xi[i - 1] + h, 1);

        y[i] = y[i - 1] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    }
}


void printArray(const string &name, double arr[], int n) {
    cout << name << endl;
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(5) << arr[i] << " ";

    cout << endl;
}

void solutions(int n, int task, double h, double a, double b) {
    double xi[n];
    for (int i = 0; i < n; i++) {
        xi[i] = i * h;
    }
    printArray("xi=", xi, n);

    double exactSol[n], eulerSol[n], impEulerSol[n], rungeKuttaSol[n];
    double eulerError[n], impEulerError[n], rungeKuttaError[n];

    exact_solution(h, n, exactSol);
    euler(h, n, eulerSol, xi);
    improved_euler(h, n, impEulerSol, xi);
    runge_kutta(h, n, rungeKuttaSol, xi);

    switch(task){
        case 1:
            printArray("y(xi)=", exactSol, n);
            break;
        case 2:
            printArray("Euler_yi=", eulerSol, n);
            break;
        case 3:
            printArray("iEuler_yi=", impEulerSol, n);
            break;
        case 4:
            printArray("RK4_yi=", rungeKuttaSol, n);
            break;
        case 5:
            for (int i = 0; i < n; i++){
                eulerError[i] = abs(eulerSol[i] - exactSol[i]);
            }
            printArray("Euler_LE(xi)=", eulerError, n);
            break;
        case 6:
            for (int i = 0; i < n; i++){
                impEulerError[i] = fabs(impEulerSol[i] - exactSol[i]);
            }
            printArray("iEuler_LE(xi)=", impEulerError, n);
            break;
        case 7:
            for (int i = 0; i < n; i++){
                rungeKuttaError[i] = fabs(rungeKuttaSol[i] - exactSol[i]);
            }
            printArray("RK4_LE(xi)=", rungeKuttaError, n);
        default:
            cout << "No such task as " << task << "!!!" << endl;


    }
}


int main() {
    int n, task, n1, n2;

    n = 10;
    n1 = 10;
    n2 = 20;
    task = 1;

    // scanf("%d %lf %lf %d", &n, &n1, &n2, &task);



    double a = 0;
    double b = M_PI;

    double h = (b - a) / (n - 1);

    solutions(n, task, h, a, b);


}