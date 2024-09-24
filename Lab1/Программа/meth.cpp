#include "meth.h"

void methodNewton(grid* set, int n, double* coeffs)
{
	double** diff_table = new double* [n];
	for (int i = 0; i < n; ++i) {
		diff_table[i] = new double[n];
		diff_table[i][0] = set[i].y;
	}

	for (int j = 1; j < n; ++j) {
		for (int i = j; i < n; ++i) {
			diff_table[i][j] = (diff_table[i][j - 1] - diff_table[i - 1][j - 1]) / (set[i].x - set[i - j].x);
		}
	}
	for (int i = 0; i < n; ++i) {
		coeffs[i] = diff_table[i][i];
	}
	for (int i = 0; i < n; ++i) {
		delete[] diff_table[i];
	}
	delete[] diff_table;
}
