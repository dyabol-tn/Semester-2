#include <iostream>

extern "C" int64_t __cdecl __main_asm(long long int x1, long long int a1, long long int b1, long long int c1, int* temp);

using namespace std;

void Foo() {
	long long int x, a, b, c, yc, ya;
	int temp = 1;
	cout << "Введите значения перемнных: " << endl;
	cin >> x >> a >> b >> c;
	ya = __main_asm(x, a, b, c, &temp);
	if (temp == 0) {
		cout << "Произошло переполнение!" << endl;
	}
	if (temp == 2) {
		cout << "Выявлено деление на 0!" << endl;
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