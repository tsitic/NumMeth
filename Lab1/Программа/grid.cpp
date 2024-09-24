#include "grid.h"
#include "function.h"
#include <math.h>
#define M_PI 3.1415926

void cheb_grid(grid* z, int kol, int nf)
{
	if (nf == 1) {//[-3,3]
		for (int i = 0;i < kol;i++) {
			z[i].x = 3 * cos((2.0 * (double)i + 1) * M_PI / (2.0 * kol));
			z[i].y = f1(z[i].x);
		}
	}
	if (nf == 2) {//[-4,1]
		for (int i = 0;i < kol;i++) {
			z[i].x = 2.5 * cos((2.0 * (double)i + 1) * M_PI / (2.0 * kol)) - 1.5;
			z[i].y = f2(z[i].x);
		}
	}
}

void uni_grid(grid* z, int kol, int nf)
{
	if (nf == 1) {
		double dl = 6.0 / (kol - 1);
		double nx = -3.0;
		for (int i = 0; i < kol; ++i) {
			z[i].x = nx;
			z[i].y = f1(nx);
			nx += dl;
		}
	}
	if (nf == 2) {
		double dl = 5.0 / (kol - 1);
		double nx = -4.0;
		for (int i = 0; i < kol; ++i) {
			z[i].x = nx;
			z[i].y = f2(nx);
			nx += dl;
		}
	}
}
