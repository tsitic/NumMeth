#include <iostream>
#include <locale.h>
#include <cmath>
#include <vector>

//ДУ
double f(double x, double y) {
    return -y / x - 1 / (x * x);
}

//Точное решение уравнения
double rf(double x) {
    return (1 - log(fabs(x))) / x;
}

//Метод Хойна
std::vector<std::pair<double, double>> heun(double x0, double y0, double h, double xn, double e) {
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
                if (x + h > xn) {
                    h = xn - x;
                }

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


//Адамса-Моултона 4ого порядка 
std::vector<std::pair<double, double>> adams_moulton(double x0, double y0, double h, double xn, double e) {
    std::vector<std::pair<double, double>> sol = heun(x0, y0, h, x0 + 3 * h, e);

    double x = sol[2].first;
    double y = sol[2].second;

    while (x < xn) {
        double f1 = f(sol[sol.size() - 1].first, sol[sol.size() - 1].second);
        double f2 = f(sol[sol.size() - 2].first, sol[sol.size() - 2].second);
        double f3 = f(sol[sol.size() - 3].first, sol[sol.size() - 3].second);

        double y_new = y + (h / 24) * (9 * f(x + h, y) + 19 * f1 - 5 * f2 + f3);

        double y_new_half;
        while (true) {
            double h05 = h / 2;

            double y_half = y + (h05 / 24) * (9 * f(x + h05, y) + 19 * f1 - 5 * f2 + f3);
            
            f1 = f2;
            f2 = f1;
            f1 = f(x+h05, y_half);


            y_new_half = y_half + (h05 / 24) * (9 * f(x + h, y_half) + 19 * f1 - 5 * f2 + f3);

            double runge = fabs(y_new - y_new_half) / 15;

            if (runge < e) {
                if (x + h > xn) {
                    h = xn - x;
                }

                x += h;
                y = y_new;

                sol.push_back({ x, y });

                if (runge < e / 10) {
                    h *= 2;
                }

                y_new = y_new_half;
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

void analyzeSol(const std::vector<std::pair<double, double>>& solH, const std::vector<std::pair<double, double>>& solAM, double e) {
    double max_error = 0;
    double x_max = 1;
    std::cout << "" << e << " ";

    for (int i = 0; i < solH.size(); ++i) {
        double x = solH[i].first;
        double y = solH[i].second;

        double error = std::fabs(rf(x) - y);
        if (max_error < error) {
            max_error = error;
            x_max = x;
        }
    }
    //xAH //eH
    std::cout << "" << x_max << " " << max_error <<" ";

    max_error = 0;
    x_max = 1;

    for (int i = 0; i < solAM.size(); ++i) {
        double x = solAM[i].first;
        double y = solAM[i].second;

        double error = std::fabs(rf(x) - y);
        if (max_error < error) {
            max_error = error;
            x_max = x;
        }
    }
    //xAM //eAM
    std::cout << "" << x_max << " " << max_error << "\n";
}

int main() {
    double x0 = 1;  
    double y0 = 1;  
    double h = 0.1;   
    double xn = 3;  
    double e = 1e-1;
    for (int i=0;i<4;i++){
        std::vector<std::pair<double, double>> solH= heun(x0,y0,h,xn,e);
        std::vector<std::pair<double, double>> solAM = adams_moulton(x0, y0, h, xn,e);
        analyzeSol(solH, solAM, e);
        e /= 10;
    }
}
