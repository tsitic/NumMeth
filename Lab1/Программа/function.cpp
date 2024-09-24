#include "function.h"
#include <math.h>
#include "grid.h"
double f1(double x)
{
    double y = x * log(1 + x * x); //[-3,3]
    return y;
}

double f2(double x)
{
    double y = x * x * x - 3 * x * x + 2 * fabs(x); //[-4,1]
    return y;
}

double poly(double* coeffs, grid* set, int n, double dot)
{
		double rez = 0;
		for (int i = 0;i < n;i++) {
			double term = coeffs[i];
			for (int j = 0;j < i;j++) {
				term *= (dot - set[j].x);
			}
			rez += term;
		}
		return rez;
}
