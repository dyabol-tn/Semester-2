#include <iostream>

extern "C" int __cdecl __main_asm(int x1, int a1, int b1, int c1, int *temp);

using namespace std;

void Foo() {
	int yc, x, a, b, c, temp = 1, ya = 0;
	cout << "Введите значения переменных: " << endl;
	cin >> x >> a >> b >> c;

	ya = __main_asm(x, a, b, c, &temp);
	if (temp == 0) {
		cout << "Произошло переполнение!" << endl;
	}
	if (temp == 2) {
		cout << "Деление на ноль! " << endl;
	}
	if (temp == 1) {
		cout << "Результат вычисления на ассемблере: " << ya << endl;
	yc = ((x * c) + (b * b) + ((4 * c) / (2 * x))) / ((3 * x * x) - (b / a));
	cout << "Результат вычисления на С++: " << yc << endl;
	}
}

int main() {

	setlocale(LC_ALL, "rus");
	Foo();
	return 0;
}