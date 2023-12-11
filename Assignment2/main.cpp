#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;


double f_x(double x, double y, double t) {
    return y;
}

double f_y(double x, double y, double t) {
    return -4 * x;
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

void euler(double a, double b, double x0, double y0, int n,
                  vector<double> &xi, vector<double> &yi, vector<double> &ti) {
    double h = (b - a) / (n - 1);

    xi.push_back(x0);
    yi.push_back(y0);

    for (int i = 0; i < n - 1; ++i) {
        ti.push_back(ti[i] + h);
        xi.push_back(xi[i] + h * f_x(xi[i], yi[i], ti[i]));
        yi.push_back(yi[i] + h * f_y(xi[i], yi[i], ti[i]));
    }
}

void improved_euler(double a, double b, double x0, double y0, int n,
                           vector<double> &xi, vector<double> &yi, vector<double> &ti) {
    xi.push_back(x0);
    yi.push_back(y0);
    double h = (b - a) / (n - 1);

    for (int i = 0; i < n - 1; ++i) {
        ti.push_back(ti[i] + h);

        double k1x = f_x(xi[i], yi[i], ti[i]);
        double k1y = f_y(xi[i], yi[i], ti[i]);

        double k2x = f_x(xi[i] + h * k1x, yi[i] + h * k1y, ti[i + 1]);
        double k2y = f_y(xi[i] + h * k1x, yi[i] + h * k1y, ti[i + 1]);

        xi.push_back(xi[i] + h / 2 * (k1x + k2x));
        yi.push_back(yi[i] + h / 2 * (k1y + k2y));
    }
}


int main() {
    double x0 = 1;
    double y0 = 2;

    double a = 0;
    double b = M_PI;

    int n, task;
    cin >> n >> task;

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
        case 3:
//            improved_euler(y0, a, b, n, xi, yi);
//
//            print_vector("xi=", xi);
//            print_vector("iEuler_yi=", yi);
//            break;

        default:
            cout << "No such task as " << task << "!!!" << endl;
    }


    return 0;
}
