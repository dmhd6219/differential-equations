#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;


double f_x(double x, double y, double t) {
    return y;
}

double f_y(double x, double y, double t) {
    return x * x - y * y - 1;
}

void print_vector(const string &name, vector<double> &vec) {
    cout << name << endl;
    for (double i: vec) {
        cout << fixed << setprecision(5) << i << " ";
    }
    cout << endl;
}


void euler(double a, double b, double x0, double y0, int n,
           vector<double> &xi, vector<double> &yi, vector<double> &ti) {
    double h = (b - a) / (n - 1);

    xi.push_back(x0);
    yi.push_back(y0);
    ti.push_back(a);

    for (int i = 0; i < n - 1; ++i) {
        ti.push_back(ti[i] + h);
        xi.push_back(xi[i] + h * f_x(xi[i], yi[i], ti[i]));
        yi.push_back(yi[i] + h * f_y(xi[i], yi[i], ti[i]));
    }
}

void improved_euler(double a, double b, double x0, double y0, int n,
                    vector<double> &xi, vector<double> &yi, vector<double> &ti) {
    double h = (b - a) / (n - 1);

    xi.push_back(x0);
    yi.push_back(y0);
    ti.push_back(a);

    for (int i = 0; i < n - 1; ++i) {
        ti.push_back(ti[i] + h);

        double k1_x = f_x(xi[i], yi[i], ti[i]);
        double k1_y = f_y(xi[i], yi[i], ti[i]);

        double k2_x = f_x(xi[i] + h * k1_x, yi[i] + h * k1_y, ti[i + 1]);
        double k2_y = f_y(xi[i] + h * k1_x, yi[i] + h * k1_y, ti[i + 1]);

        xi.push_back(xi[i] + h / 2 * (k1_x + k2_x));
        yi.push_back(yi[i] + h / 2 * (k1_y + k2_y));
    }
}

void runge_kutta(double a, double b, double x0, double y0, int n,
                 vector<double> &xi, vector<double> &yi, vector<double> &ti) {
    double h = (b - a) / (n - 1);

    xi.push_back(x0);
    yi.push_back(y0);
    ti.push_back(a);

    for (int i = 0; i < n - 1; ++i) {
        ti.push_back(ti[i] + h);

        double k1_x = f_x(xi[i], yi[i], ti[i]);
        double k1_y = f_y(xi[i], yi[i], ti[i]);

        double k2_x = f_x(xi[i] + h / 2 * k1_x, yi[i] + h / 2 * k1_y, ti[i] + h / 2);
        double k2_y = f_y(xi[i] + h / 2 * k1_x, yi[i] + h / 2 * k1_y, ti[i] + h / 2);

        double k3_x = f_x(xi[i] + h / 2 * k2_x, yi[i] + h / 2 * k2_y, ti[i] + h / 2);
        double k3_y = f_y(xi[i] + h / 2 * k2_x, yi[i] + h / 2 * k2_y, ti[i] + h / 2);

        double k4_x = f_x(xi[i] + h * k3_x, yi[i] + h * k3_y, ti[i] + h);
        double k4_y = f_y(xi[i] + h * k3_x, yi[i] + h * k3_y, ti[i] + h);

        xi.push_back(xi[i] + h / 6 * (k1_x + 2 * k2_x + 2 * k3_x + k4_x));
        yi.push_back(yi[i] + h / 6 * (k1_y + 2 * k2_y + 2 * k3_y + k4_y));
    }
}

void plot_solutions(vector<double> x_euler, vector<double> y_euler,
                    vector<double> x_improved, vector<double> y_improved,
                    vector<double> x_rk, vector<double> y_rk) {

    FILE *gnuplot = popen("gnuplot -persist", "w");

    fprintf(gnuplot, "set title 'Numerical Solutions'\n");

    fprintf(gnuplot, "plot '-' with lines title 'Euler' lw 2, \
         '-' with lines title 'Improved Euler' lw 2, \
	     '-' with lines title 'Runge-Kutta' lw 2\n");

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
    double x0 = -3;
    double y0 = 0;

    double a = 0;
    double b = 5;

    int n, task;
    n = 40;
    task = 1;

    // cin >> n >> task;

    vector<double> xi, yi, ti;

    switch (task) {
        case 1:
            euler(a, b, x0, y0, n, xi, yi, ti);

            print_vector("ti=", ti);
            print_vector("Euler_xi=", xi);
            print_vector("Euler_yi=", yi);
            break;
        case 2:
            improved_euler(a, b, x0, y0, n, xi, yi, ti);

            print_vector("ti=", ti);
            print_vector("iEuler_xi=", xi);
            print_vector("iEuler_yi=", yi);
            break;
        case 3:
            runge_kutta(a, b, x0, y0, n, xi, yi, ti);

            print_vector("ti=", ti);
            print_vector("RK4_xi=", xi);
            print_vector("RK4_yi=", yi);
            break;

        default:
            cout << "No such task as " << task << "!!!" << endl;
    }

    vector<double> ex, ey;
    vector<double> ix, iy;
    vector<double> rx, ry;

    euler(a, b, x0, y0, n, ex, ey, ti);
    improved_euler(a, b, x0, y0, n, ix, iy, ti);
    runge_kutta(a, b, x0, y0, n, rx, ry, ti);

    plot_solutions(ex, ey, ix, iy, rx, ry);




    return 0;
}
