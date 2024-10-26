#include "meth.h"
#include <math.h>
#include <iostream>


double rungeRule(double s1, double s2) {
    return fabs(s2 - s1);
}

ret meth(double a, double b, double e)
{
    int k = 1;
    double h = b - a;
    double s1 = (f(a) + f(b)) * h / 2.0;
    double s2;

    do {
        s2 = s1;
        h /= 2;
        double x = a + h;
        s1 = s1 / 2 + h * f(x);
        while (x + h < b) {
            x += 2 * h;
            s1 += h * f(x);
        }
        k++;
    } while (rungeRule(s1, s2) > e);
    ret rez{ s1,k,h };
    
    return rez;
}
