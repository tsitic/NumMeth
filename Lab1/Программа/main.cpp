#include <iostream>
#include "grid.h"
#include "meth.h"
#include <locale.h>
#include <fstream>
#include "function.h" //f1 [-3,3]   
					  //f2 [-4,1]

#define NUMF 2 //номер функции
#define GT 2//тип сетки 1- равномерная 2- Чебышевская

using namespace std;
int main() {
	setlocale(LC_CTYPE, "Russian");
	int kdg = 0;
	cout << "Введите количество узлов>>";
	cin >> kdg;
	double* coeffs = new double[kdg];
	grid* set = new grid[kdg];
	if (GT == 1) {
		uni_grid(set, kdg, NUMF);
	}
	else {
		cheb_grid(set, kdg, NUMF);
	}

	ofstream file;
	file.open("apinf//dot.txt");
	for (int i = 0;i < kdg;i++) {
		file << set[i].x << endl;
	}
	file.close();

	methodNewton(set, kdg, coeffs);

	ofstream cofile;
	cofile.open("apinf//coeffs.txt");
	for (int i = 0;i < kdg;i++) {
		cofile << coeffs[i] << endl;
	}
	cofile.close();
	//поточечная ошибка
	/*
	cofile.open("apinf//error//cheb2_10.txt");
	for (double x = -4;x < 1;x+=0.001) {
		cofile <<x<<" : "<< fabs(f2(x) - poly(coeffs, set, kdg, x)) << endl;
	}
	cofile.close();
	*/

	//Норма ошибки 
	/*
	cofile.open("apinf//normerror//cheb1.txt");
	for (int i=5;i<=100;i++){
		double* coeffs = new double[i];
		grid* set = new grid[i];
		if (GT == 1) {
			uni_grid(set, i, NUMF);
		}
		else {
			cheb_grid(set, i, NUMF);
		}

		methodNewton(set, i, coeffs);
		double maxD = 0;
		for (double x = -3;x < 3;x += 0.001) {
			maxD=fabs(f1(x) - poly(coeffs, set, i, x))>maxD? fabs(f1(x) - poly(coeffs, set, i, x)): maxD;
		}
		cofile << i << " : " << maxD <<endl;
	}
	cofile.close();
	*/

	//ошибка в точках

	/*
	cofile.open("apinf//doterror//cheb2d1.txt");
	double x = -1.5;
	for (int i = 5;i <= 100;i++) {
		double* coeffs = new double[i];
		grid* set = new grid[i];
		if (GT == 1) {
			uni_grid(set, i, NUMF);
		}
		else {
			cheb_grid(set, i, NUMF);
		}

		methodNewton(set, i, coeffs);
		double xD = 0;
		xD = fabs(f2(x) - poly(coeffs, set, i, x));
		cofile << i << " : " << xD << endl;
	}
	cofile.close();
	*/
}