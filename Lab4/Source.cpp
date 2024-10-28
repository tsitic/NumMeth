#include <iostream>
#include <cmath>
#include <fstream>
#include <vector> 
#include <locale.h>

#define pi 3.1415926

double sol(double x) {
    return sin(x);
}

void eulerMethod(double& y, double& yp, double h, double x, double (*func)(double, double, double)) {
    double yp_next = yp + h * func(x, y, yp);
    y = y + h * yp;
    yp = yp_next;
}

//неоду
double eq_u(double x, double y, double yp) {
    return -cos(x) * yp - sin(x) * y + (1 - sin(x));
}

//оду
double eq_vw(double x, double y, double yp) {
    return -cos(x) * yp - sin(x) * y;
}

std::vector<std::pair<double, double>> superpositionMeth(double h, double x_max) {
    double x = 0.0;

    std::vector<double> x_vals;
    std::vector<double> u_vals, v_vals, w_vals;

    double u = 0.0, up = 0.0;
    double v = 1.0, vp = 0.0;
    double w = 0.0, wp = 1.0;

    double max_error = 0.0; 

    while (x < x_max) {
        if (x_max - x < h) {
            h = x_max - x;
        }

        x_vals.push_back(x);
        u_vals.push_back(u);
        v_vals.push_back(v);
        w_vals.push_back(w);

        eulerMethod(u, up, h, x, eq_u);
        eulerMethod(v, vp, h, x, eq_vw);
        eulerMethod(w, wp, h, x, eq_vw);

        x += h;
    }

    double y_end = 1.0;
    double C1 = (y_end - u_vals.back() - w_vals.back()) / (v_vals.back() - w_vals.back());
    double C2 = 1.0 - C1;

    std::vector<std::pair<double, double>> rezult;  // Вектор пар для значений x и y

    for (int i= 0; i < x_vals.size(); ++i) {
        double y_val = u_vals[i] + C1 * v_vals[i] + C2 * w_vals[i];
        rezult.push_back({ x_vals[i], y_val});
    }


    std::cout << "\n";
    std::cout << "C1 = " << C1 << "\n";
    std::cout << "C2 = " << C2 << "\n";
    return rezult;
}

std::vector<std::pair<double, double>> nfsSuppositMeth(double eps, double x_max) {
    double x = 0.0, h = 0.1;
    std::vector<double> x_vals, u_vals, v_vals, w_vals;
    std::vector<double> h_vals;
    double error = 0;

    double u = 0.0, up = 0.0;
    double v = 1.0, vp = 0.0;
    double w = 0.0, wp = 1.0;

    while (x < x_max) {
        if (x + h > x_max) {
            h = x_max - x;
        }

        // Сначала считаем для шага h
        double u_temp = u, up_temp = up;
        double v_temp = v, vp_temp = vp;
        double w_temp = w, wp_temp = wp;
        eulerMethod(u_temp, up_temp, h, x, eq_u);
        eulerMethod(v_temp, vp_temp, h, x, eq_vw);
        eulerMethod(w_temp, wp_temp, h, x, eq_vw);

        while (true) {
            double u_half = u, up_half = up;
            double v_half = v, vp_half = vp;
            double w_half = w, wp_half = wp;
            
            double h05 = h / 2;
            eulerMethod(u_half, up_half, h05 , x, eq_u);
            eulerMethod(v_half, vp_half, h05 , x, eq_vw);
            eulerMethod(w_half, wp_half, h05 , x, eq_vw);

            eulerMethod(u_half, up_half, h05, x + h05, eq_u);
            eulerMethod(v_half, vp_half, h05, x + h05, eq_vw);
            eulerMethod(w_half, wp_half, h05, x + h05, eq_vw);

            double runge1 = fabs(u_temp - u_half) / 3;
            double runge2 = fabs(v_temp - v_half) / 3;
            double runge3 = fabs(w_temp - w_half) / 3;
            //максимальня погрешность из трех
            double runge = (runge1 > runge2) ? ((runge1 > runge3) ? runge1 : runge3) : ((runge2 > runge3) ? runge2 : runge3);

            if (runge < eps) {
                u = u_temp;
                up = up_temp;
                v = v_temp;
                vp = vp_temp;
                w = w_temp;
                wp = wp_temp;
                x += h;

                h_vals.push_back(h);

                if (runge < eps / 10) {
                    h *= 2;
                }

                error = std::max(error, runge);
                break;
            }
            else {
                h /= 2;
                u_temp = u_half;
                up_temp = up_half;
                v_temp = v_half;
                vp_temp = vp_half;
                w_temp = w_half;
                wp_temp = wp_half;
            }
        }

        x_vals.push_back(x);
        u_vals.push_back(u);
        v_vals.push_back(v);
        w_vals.push_back(w);
    }

    double y_end = 1.0;
    double C1 = (y_end - u_vals.back() - w_vals.back()) / (v_vals.back() - w_vals.back());
    double C2 = 1.0 - C1;

    std::vector<std::pair<double, double>> rezult;

    for (int i = 0; i < x_vals.size(); ++i) {
        double y_val = u_vals[i] + C1 * v_vals[i] + C2 * w_vals[i];
        rezult.push_back({ x_vals[i], y_val });
    }

    return rezult;
}


void analyzeRezult(std::vector<std::pair<double, double>> rez) {
    double max_error = 0;

    for (int i = 1; i < rez.size(); ++i) {
        double h = std::fabs(rez[i].first - rez[i - 1].first);
        double error = std::fabs(sol(rez[i].first) - rez[i].second);
        max_error = std::max(max_error, error);
        std::cout << "h =" << h << " x = " << rez[i].first << " y = " << rez[i].second << " error "<< error << "\n";
    }
    std::cout << "Максимальная ошибка: " << max_error;
}


int main() {
    setlocale(LC_CTYPE, "Russian");
    double h, x_max = pi / 2;
    double eps = 1e-6;
    
    std::cout << "Введите шаг для метода Эйлера: ";
    std::cin >> h;
    std::vector<std::pair<double, double>> rez = superpositionMeth(h, x_max);
    analyzeRezult(rez);
    return 0;
}
