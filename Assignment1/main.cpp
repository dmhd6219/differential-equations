#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

double max(const double arr[], int n){
    double mx = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > mx){
            mx = arr[i];
        }
    }
    return mx;

}

double f(double x, double y) {
    return cos(x);
}

void exact_solution(int n, double y[], const double xi[]) {
    for (int i = 0; i <= n; i++) {
        y[i] = sin(xi[i]);
    }
}

void euler(double a, double b, int n, double y[], const double xi[]) {
    double h = (b - a) / (n - 1);

    y[0] = 0;
    for (int i = 1; i < n; i++) {
        y[i] = y[i - 1] + h * f(xi[i - 1], y[i - 1]);
    }
}

void improved_euler(double a, double b, int n, double y[], const double xi[]) {
    double h = (b - a) / (n - 1);

    y[0] = 0;
    for (int i = 1; i < n; i++) {
        double k1 = f(xi[i - 1], y[i - 1]);
        double k2 = f(xi[i - 1] + h, y[i - 1] + h * k1);

        y[i] = y[i - 1] + (h / 2) * (k1 + k2);
    }
}

void runge_kutta(double a, double b, int n, double y[], const double xi[]) {
    double h = (b - a) / (n - 1);

    y[0] = 0;
    for (int i = 1; i < n; i++) {
        double k1 = f(xi[i - 1], 1);
        double k2 = f(xi[i - 1] + 0.5 * h, 1);
        double k3 = f(xi[i - 1] + 0.5 * h, 1);
        double k4 = f(xi[i - 1] + h, 1);

        y[i] = y[i - 1] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    }
}

void local_error(const double solution[], const double exactSolution[], int n, double y[]){
    for (int i = 0; i < n; i++){
        y[i] = fabs(solution[i] - exactSolution[i]);
    }
}


void printArray(const string &name, double arr[], int n) {
    cout << name << endl;
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(5) << arr[i] << " ";

    cout << endl;
}

void solutions(int n, int task, double h, double a, double b, int n1, int n2) {
    double xi[n];
    for (int i = 0; i < n; i++) {
        xi[i] = i * h;
    }
    printArray("xi=", xi, n);

    double exactSol[n], eulerSol[n], impEulerSol[n], rungeKuttaSol[n];
    double eulerError[n], impEulerError[n], rungeKuttaError[n];
    double eulerGlobalError[n2 - n1], impEulerGlobalError[n2 - n1], rungeKuttaGlobalError[n2 - n1];

    exact_solution(n, exactSol, xi);
    euler(a, b, n, eulerSol, xi);
    improved_euler(a, b, n, impEulerSol, xi);
    runge_kutta(a, b, n, rungeKuttaSol, xi);

    local_error(eulerSol, exactSol, n, eulerError);
    local_error(impEulerSol, exactSol, n, impEulerError);
    local_error(rungeKuttaSol, exactSol, n, rungeKuttaError);



    for (int i = n1; i < n2; i++){
        double yEuler[i - 1];
        double yImpEuler[i - 1];
        double yRungeKutta[i - 1];

        double localEuler[i - 1];
        double localImpEuler[i - 1];
        double localRungeKutta[i - 1];

        double exact[i - 1];

        euler(a, b, i - 1, yEuler, xi);
        improved_euler(a, b, i - 1, yImpEuler, xi);
        runge_kutta(a, b, i - 1, yRungeKutta, xi);

        exact_solution(i - 1, exact, xi);

        local_error(yEuler, exact, i - 1, localEuler);
        local_error(yImpEuler, exact, i - 1, localImpEuler);
        local_error(yRungeKutta, exact, i - 1, localRungeKutta);

        eulerGlobalError[i - n1] = max(localEuler, i - 1);
        impEulerGlobalError[i - n1] = max(localImpEuler, i - 1);
        rungeKuttaGlobalError[i - n1] = max(localRungeKutta, i - 1);


    }



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
            printArray("Euler_LE(xi)=", eulerError, n);
            break;
        case 6:
            printArray("iEuler_LE(xi)=", impEulerError, n);
            break;
        case 7:
            printArray("RK4_LE(xi)=", rungeKuttaError, n);
            break;
        case 8:
            printArray("Euler_GE(n)=", eulerGlobalError, n2 - n1);
            break;
        case 9:
            printArray("iEuler_GE(n)=", impEulerGlobalError, n2 - n1);
            break;
        case 10:
            printArray("RK4_GE(n)=", rungeKuttaGlobalError, n2 - n1);
            break;
        default:
            cout << "No such task as " << task << "!!!" << endl;


    }
}


int main() {
    int n, task, n1, n2;

    n = 10;
    n1 = 10;
    n2 = 20;
    task = 7;

    scanf("%d %lf %lf %d", &n, &n1, &n2, &task);



    double a = 0;
    double b = M_PI;

    double h = (b - a) / (n - 1);

    solutions(n, task, h, a, b, n1, n2);


}