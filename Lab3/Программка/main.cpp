#include <iostream>
#include <locale.h>
#include <vector>
#include <math.h>

double f(double x, double y) {
    return -y/x - 1/(x * x);
}

double rf(double x) {
    return (1 - log(fabs(x))) / x;
}

//фиксированный шаг
std::vector<std::pair<double, double>> methfs(double x0, double y0, double h, double xn) {
    double x = x0;
    double y = y0;
    std::vector<std::pair<double, double>> sol; 

    sol.push_back({ x, y });

    while (x < xn) {
        double yv = y + h * f(x, y); 
        y = y + h * (f(x, y) + f(x + h, yv)) / 2; 
        x += h;

        sol.push_back({ x, y });
    }

    return sol;
}



//точность
std::vector<std::pair<double, double>> methnfs(double x0, double y0, double h, double xn, double e) {
    double x = x0;
    double y = y0;
    std::vector<std::pair<double, double>> sol;

    sol.push_back({ x, y });

    while (x < xn) {
        double yv = y + h * f(x, y);
        double y1 = y + h * (f(x, y) + f(x + h, yv)) / 2;

        double y22;
        while (true) {
            double h05 = h / 2;
            //       h/2
            double yv_half = y + h05 * f(x, y);
            double y21 = y + h05 * (f(x, y) + f(x + h05, yv_half)) / 2;

            yv_half = y21 + h05 * f(x + h05, y21);
            y22 = y21 + h05 * (f(x + h05, y21) + f(x + h, yv_half)) / 2;

            double runge = fabs(y1 - y22) / 3;

            if (runge < e) {
                x += h;
                y = y1;

                sol.push_back({ x, y });

                if (runge < e / 10) {
                    h *= 2;
                }

                y1 = y22;
                break;
            }
            else {
                if (h > 1e-10) {
                    h /= 2;
                }
                else {
                    break;
                }
            }
        }
    }

    return sol;
}


void analyzeSol(const std::vector<std::pair<double, double>>& sol, double e) {
    double max_error = 0;

    std::cout << "e: " << e << "\n";

    for (size_t i = 1; i < sol.size(); ++i) {
        double xp = sol[i - 1].first;
        double yp = sol[i - 1].second;
        double x = sol[i].first;
        double y = sol[i].second;

        double h_dot = x - xp;

        double error = std::fabs(rf(x) - y);
        max_error = std::max(max_error, error);

        std::cout << "x = " << x << ", y = " << y
            << ", h = " << h_dot
            << ", error: " << error << "\n";
    }

    std::cout << "Максимальная ошибка: " << max_error << "\n";
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    double h = 0.015625;
    std::vector<std::pair<double, double>> sol = methnfs(1, 1, h, 3, 1e-8);
    analyzeSol(sol, 1e-3);
    return 0;
}
