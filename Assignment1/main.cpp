#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

double max(vector<double> vec) {
    double mx = vec[0];
    for (double val: vec) {
        mx = max(mx, val);
    }
    return mx;
}

double f(double x) {
    return cos(6 * x);
}

double fs(double x) {
    return sin(6 * x) / 6;
}

void print_vector(const string &name, vector<double> &vec) {
    cout << name << endl;
    for (double i: vec) {
        cout << fixed << setprecision(5) << i << " ";
    }
    cout << endl;
}

void print_vector(const string &name, const vector<int> &vec) {
    cout << name << endl;
    for (double i: vec) {
        cout << i << " ";
    }
    cout << endl;
}

void exact_solution(double y0, double a, double b, int n, vector<double> &xi, vector<double> &yi) {
    xi.push_back(a);
    yi.push_back(y0);

    double h = (b - a) / (n - 1);
    for (int i = 0; i < n - 1; i++) {
        xi.push_back(xi[i] + h);
        yi.push_back(fs(xi[i + 1]));
    }
}

void euler(double y0, double a, double b, int n, vector<double> &xi, vector<double> &yi) {
    xi.push_back(a);
    yi.push_back(y0);

    double h = (b - a) / (n - 1);
    for (int i = 0; i < n - 1; i++) {
        xi.push_back(xi[i] + h);
        yi.push_back(yi[i] + h * f(xi[i]));
    }
}

void improved_euler(double y0, double a, double b, int n, vector<double> &xi, vector<double> &yi) {
    xi.push_back(a);
    yi.push_back(y0);

    double h = (b - a) / (n - 1);
    for (int i = 0; i < n - 1; i++) {
        xi.push_back(xi[i] + h);

        double k1i = f(xi[i]);
        double k2i = f(xi[i] + h);
        yi.push_back(yi[i] + (h / 2) * (k1i + k2i));
    }
}

void runge_kutta(double y0, double a, double b, int n, vector<double> &xi, vector<double> &yi) {
    xi.push_back(a);
    yi.push_back(y0);

    double h = (b - a) / (n - 1);
    for (int i = 0; i < n - 1; i++) {
        xi.push_back(xi[i] + h);

        double k1 = f(xi[i]);
        double k2 = f(xi[i] + h / 2);
        double k3 = f(xi[i] + h / 2);
        double k4 = f(xi[i] + h);
        yi.push_back(yi[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4));
    }
}

void local_errors(vector<double> xi, vector<double> yi, vector<double> &ei) {
    for (int i = 0; i < xi.size(); i++) {
        ei.push_back(abs(fs(xi[i]) - yi[i]));
    }
}

void global_errors(void (*function)(double, double, double, int, vector<double> &, vector<double> &),
                   vector<double> &ge, const vector<int> &ni, double y0, double a, double b) {

    for (int i: ni) {
        vector<double> xi, yi;
        function(y0, a, b, i, xi, yi);
        vector<double> ei;
        local_errors(xi, yi, ei);
        ge.push_back(max(ei));
    }
}


void plot_solutions(vector<double> x_exact, vector<double> y_exact,
                    vector<double> x_euler, vector<double> y_euler,
                    vector<double> x_improved, vector<double> y_improved,
                    vector<double> x_rk, vector<double> y_rk) {

    FILE *gnuplot = popen("gnuplot -persist", "w");

    fprintf(gnuplot, "set title 'Numerical Solutions'\n");

    fprintf(gnuplot, "plot '-' with lines title 'Exact' lw 2, \
         '-' with lines title 'Euler' lw 2, \
         '-' with lines title 'Improved Euler' lw 2, \
	     '-' with lines title 'Runge-Kutta' lw 2\n");

    // Print exact solution
    for(int i = 0; i < x_exact.size(); i++) {
        fprintf(gnuplot, "%f %f\n", x_exact[i], y_exact[i]);
    }
    fprintf(gnuplot, "e\n");

    // Print Euler solution
    for(int i = 0; i < x_euler.size(); i++) {
        fprintf(gnuplot, "%f %f\n", x_euler[i], y_euler[i]);
    }
    fprintf(gnuplot, "e\n");

    // Print improved Euler solution
    for(int i = 0; i < x_improved.size(); i++) {
        fprintf(gnuplot, "%f %f\n", x_improved[i], y_improved[i]);
    }
    fprintf(gnuplot, "e\n");

    // Print Runge-Kutta solution
    for(int i = 0; i < x_rk.size(); i++) {
        fprintf(gnuplot, "%f %f\n", x_rk[i], y_rk[i]);
    }
    fprintf(gnuplot, "e\n");

    pclose(gnuplot);
}



int main() {
    double y0 = 0;
    double a = 0;
    double b = 1;

    int n, n1, n2, task;
    n = 20;
    n1 = 20;
    n2 = 40;
    task = 1;

    cin >> n >> n1 >> n2 >> task;

    vector<double> xi, yi, ei, ge;
    vector<int> ni;
    for (int i = n1; i <= n2; i++) {
        ni.push_back(i);
    }

    switch (task) {
        case 1:
            exact_solution(y0, a, b, n, xi, yi);

            print_vector("xi=", xi);
            print_vector("y(xi)=", yi);
            break;
        case 2:
            euler(y0, a, b, n, xi, yi);

            print_vector("xi=", xi);
            print_vector("Euler_yi=", yi);
            break;
        case 3:
            improved_euler(y0, a, b, n, xi, yi);

            print_vector("xi=", xi);
            print_vector("iEuler_yi=", yi);
            break;
        case 4:
            runge_kutta(y0, a, b, n, xi, yi);

            print_vector("xi=", xi);
            print_vector("RK4_yi=", yi);
            break;
        case 5:
            euler(y0, a, b, n, xi, yi);
            local_errors(xi, yi, ei);

            print_vector("xi=", xi);
            print_vector("Euler_LE(xi)=", ei);
            break;
        case 6:
            improved_euler(y0, a, b, n, xi, yi);
            local_errors(xi, yi, ei);

            print_vector("xi=", xi);
            print_vector("iEuler_LE(xi)=", ei);
            break;
        case 7:
            runge_kutta(y0, a, b, n, xi, yi);
            local_errors(xi, yi, ei);

            print_vector("xi=", xi);
            print_vector("RK4_LE(xi)=", ei);
            break;
        case 8:
            global_errors(euler, ge, ni, y0, a, b);

            print_vector("ni=", ni);
            print_vector("Euler_GE(n)=", ge);
            break;
        case 9:
            global_errors(improved_euler, ge, ni, y0, a, b);


            print_vector("ni=", ni);
            print_vector("iEuler_GE(n)=", ge);
            break;
        case 10:
            global_errors(runge_kutta, ge, ni, y0, a, b);

            print_vector("ni=", ni);
            print_vector("RK4_GE(n)=", ge);
            break;
        default:
            cout << "No such task as " << task << "!!!" << endl;
    }


    vector<double> exi, eyi, euxi, euyi, ixi, iyi, rkxi, rkyi;
    exact_solution(y0, a, b, n, exi, eyi);
    euler(y0, a, b, n, euxi, euyi);
    improved_euler(y0, a, b, n, ixi, iyi);
    runge_kutta(y0, a, b, n, rkxi, rkyi);

    plot_solutions(exi, eyi, euxi, euyi, ixi, iyi, rkxi, rkyi);


    return 0;
}
