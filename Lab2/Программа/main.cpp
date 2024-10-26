#include <iostream>
#include <locale.h>
#include "function.h"
#include "meth.h"
const double exactValue = -50.4; // Точное значение интеграла

using namespace std;
int main() {
	setlocale(LC_CTYPE, "Russian");
	double a;
	double b;
	cout << "Введите область ограничения\na: ";
	//cin >> a;
	a = 0;
	cout << "b: ";
	//cin >> b;
	b = 3;
	double e;
	cout << "Введите точность e: ";
	//cin >> e;
	e = 1e-1;
	ret rezult = meth(a, b, e);
	
	double error = fabs(rezult.rezult - exactValue); //точное решение 
	std::cout << "\n" << rezult.k << " " << error << " " << rezult.h << " " << e << std::endl;
	return 0;
}
