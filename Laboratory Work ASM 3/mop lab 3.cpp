#include <iostream>

using namespace std;

int Square(int value) {
	value *= value;
	return value;
}

void Printf(int value) {
	cout << "Результат вычисления на ассемблере = " << value << endl;
}

int main() {

	setlocale(LC_ALL, "rus");

	cout << "ВЫЧИСЛЕНИЕ РЕЗУЛЬТАТА НА АССЕМБЛЕРЕ (__int32): " << endl;
	int ya, yc, x, a, b, c, result, temp;
	bool overflowch = false;
	bool zeroch = false;
	cout << "ВВЕДИТЕ ЗНАЧЕНИЯ ПЕРЕМЕННЫХ x, a, b, c: " << endl;
	cin >> x >> a >> b >> c;

	__asm {

		mov eax, x
		imul eax, c
		jo overflow
		mov ebx, eax
		mov eax, b
		push eax
		call Square
		add esp, 4
		jo overflow
		add ebx, eax
		jo overflow

		mov eax, c
		imul eax, 4
		jo overflow
		mov ecx, x
		imul ecx, 2
		jo overflow
		test ecx, ecx
		jz zero
		cdq
		idiv ecx;
		add ebx, eax
			jo overflow

			mov eax, x
			imul eax, eax
			jo overflow
			imul eax, 3
			jo overflow
			mov ecx, eax
			mov edx, a
			mov eax, b
			test edx, edx
			jz zero
			cdq
			idiv a
			sub ecx, eax

			mov eax, ebx
			test ecx, ecx
			jz zero
			cdq
			idiv ecx
			jmp done
			overflow :
		mov overflowch, 1
			jmp done

			zero :
		mov zeroch, 1

			done :
			push eax
			call Printf
			add esp, 4
	}

	if (overflowch) {
		cout << "ОШИБКА! ПРОИЗОШЛО ПЕРЕПОЛНЕНИЕ! " << endl;
	}
	else if (zeroch) {
		cout << "ОШИБКА! ДЕЛЕНИЕ НА НОЛЬ! " << endl;
	}

	yc = ((x * c) + (b * b) + ((4 * c) / (2 * x))) / ((3 * x * x) - (b / a));
	cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА C++: Y = " << yc << endl;

	return 0;
}