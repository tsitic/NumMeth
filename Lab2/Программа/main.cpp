#include <iostream>
#include <locale.h>
#include "function.h"
#include "meth.h"

using namespace std;
int main() {
	setlocale(LC_CTYPE, "Russian");
	double a;
	double b;
	cout << "������� ������� �����������\na: ";
	//cin >> a;
	a = 0;
	cout << "b: ";
	//cin >> b;
	b = 3;
	double e;
	cout << "������� �������� e: ";
	//cin >> e;
	e = 1e-10;
	double rezult = meth(a, b, e);
	cout << rezult;
	return 0;
}