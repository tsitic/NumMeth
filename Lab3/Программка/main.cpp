#include <iostream>
#include <locale.h>
#include <math.h>

double f(double x, double y) {
    return -y/x - 1/(x * x);
}

double rf(double x) {
    return (1 - log(fabs(x))) / x;
}

//фиксированный шаг
void methfs(double x0, double y0, double h, double xn) {
    
    double x = x0;
    double y = y0;

    std::cout << "h =" << h << "\n";
    std::cout << x << " : " << y << "\n";
    while (x < xn) {
        double yv = y + h * f(x, y); 
        y = y + h * (f(x, y) + f(x + h, yv)) / 2; 
        x += h;
        std::cout << x << " : " << y << "\n";
    }
    std::cout << "\n";
}

//точность
void methnfs(double x0, double y0, double h, double xn, double e) {
    double x = x0;
    double y = y0;

    double error = 0;
    while (x < xn) {
        while (true) {
            //шаг h
            double yv = y + h * f(x, y);
            double y1 = y + h * (f(x, y) + f(x + h, yv)) / 2;

            //шаг h/2
            double h05 = h / 2;
            yv = y + h05 * f(x, y);
            double y21 = y + h05 * (f(x, y) + f(x + h05, yv)) / 2;

            yv = y21 + h05 * f(x + h05, y21);
            double y22 = y21 + h05 * (f(x + h05, y21) + f(x + h, yv)) / 2;

            double runge = fabs(y1 - y22) / 3;

            if (runge < e) {
                x += h;  
                y = y1;
                error = fabs(rf(x) - y) > error ? fabs(rf(x) - y) : error;

                std::cout << x << " : " << h << "\n";

                if (runge < e / 10) {
                    h *= 2;
                }
                break;
            }
            else {
                h /= 2;
            }
        }
    }
    std::cout << error<<" : " <<e<< "\n";
}




int main() {
    setlocale(LC_CTYPE, "Russian");
    double h = 0.5;
    double e = 1e-1;
    
    //methfs(1, 1, 0.5, 3);
    //methfs(1, 1, 0.25, 3);
    //for (int i = 0;i < 10;i++){
      //  methnfs(1, 1, 1, 3, e);
        //e /= 10;
    //}
    e = 1e-9;
    methnfs(1, 1, 1, 3, e);
    return 0;
}
