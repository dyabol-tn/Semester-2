/*Вычисления выполнить на Assembler в среде MS VisualStudio, ввод данных и вывод результатов, осуществлять на C\С++.
Вычислить значение  выражения на С++ и Ассемблере используя целые значения  переменных.
Выполнить 3 варианта для целых переменных : однобайтовых(__int8), двухбайтовых(int16 \ short), четырёхбайтовых(__int32\int).
Обязательные операции на ассемблере : +, -, умножение, деление.
Использовать переполнение.
Для проверки результата, вычислить выражение и на С++.
Проверить на Assembler переменные и выражения(если есть), чтобы не было деления на 0.
Y = (x * c + b2 + 4c / 2x) / (3x2 –b / a)*/

#include <iostream>
#include <cmath>

using namespace std;

void CASE1() {

	__int8 ya, yc, x, a, b, c;
	short ya1, yc1, x1, a1, b1, c1;
	short res;
	bool overflowch = false;
	bool zeroch = false;
	cout << "ВВЕДИТЕ ЗНАЧЕНИЯ ПЕРЕМЕННЫХ x, a, b, c: " << endl;
	cin >> x1 >> a1 >> b1 >> c1;

	x = x1;
	a = a1;
	b = b1;
	c = c1;

	cout << "ВЫЧИСЛЕНИЕ РЕЗУЛЬТАТА НА АССЕМБЛЕРЕ (__int8):  " << endl;

	__asm {

		mov al, x
		imul c
		jo overflow
		mov bl, al
		mov al, b
		imul al
		jo overflow
		add bl, al
		jo overflow

		mov al, c
		imul al, 4
		jo overflow
		mov cl, x
		imul cl, 2
		jo overflow
		test cl, cl
		jz zero
		cbw
		idiv cl;
		add bl, al
		jo overflow

		mov al, x
		imul al
		jo overflow
		imul al, 3
		jo overflow
		mov cl, al
		mov dl, a
		mov al, b
		test dl, dl
		jz zero
		cbw
		idiv a
		sub cl, al

		mov al, bl
		test cl, cl
		jz zero
		cbw
		idiv cl
		mov ya, al
		mov res, ax
		jmp done
		overflow:
		mov overflowch, 1

		jmp done

		zero:
		mov	zeroch, 1

		done:

	}

	if (overflowch) {
		cout << "ОШИБКА! ПРОИЗОШЛО ПЕРЕПОЛНЕНИЕ! " << endl;
	}
	else if (zeroch) {
		cout << "ОШИБКА! ДЕЛЕНИЕ НА НОЛЬ! " << endl;
	}
	else {

		cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА АССЕМБЛЕРЕ (__int8): Y =  " << (int)ya << endl << endl;

		yc = ((x * c) + (b * b) + ((4 * c) / (2 * x))) / ((3 * x * x) - (b / a));
		cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА C++: Y = " << (int)yc << endl;
	}

}

void CASE2() {

	cout << "ВЫЧИСЛЕНИЕ РЕЗУЛЬТАТА НА АССЕМБЛЕРЕ (__int16): " << endl;
	__int16 ya, yc, x, a, b, c, result, temp;
	bool overflowch = false;
	bool zeroch = false;
	cout << "ВВЕДИТЕ ЗНАЧЕНИЯ ПЕРЕМЕННЫХ x, a, b, c: " << endl;
	cin >> x >> a >> b >> c;

	__asm {

		mov ax, x
		imul ax, c
		jo overflow
		mov bx, ax
		mov ax, b
		imul ax
		jo overflow
		add bx, ax
		jo overflow

		mov ax, c
		imul ax, 4
		jo overflow
		mov cx, x
		imul cx, 2
		jo overflow
		test cx, cx
		jz zero
		cwd
		idiv cx;
		add bx, ax
		jo overflow

		mov ax, x
		imul ax, ax
		jo overflow
		imul ax, 3
		jo overflow
		mov cx, ax
		mov dx, a
		mov ax, b
		test dx, dx
		jz zero
		cwd
		idiv a
		sub cx, ax

		mov ax, bx
		test cx, cx
		jz zero
		cwd
		idiv cx
		mov ya, ax
		jmp done
		overflow:
		mov overflowch, 1

		jmp done

		zero:
		mov zeroch, 1

		done:

	}

	if (overflowch) {
		cout << "ОШИБКА! ПРОИЗОШЛО ПЕРЕПОЛНЕНИЕ! " << endl;
	}
	else if (zeroch) {
		cout << "ОШИБКА! ДЕЛЕНИЕ НА НОЛЬ! " << endl;
	}
	else {

		cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА АССЕМБЛЕРЕ (__int16): Y = " << ya << endl;

		yc = ((x * c) + (b * b) + ((4 * c) / (2 * x))) / ((3 * x * x) - (b / a));
		cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА C++: Y = " << yc << endl;
	}

}

void CASE3() {

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
		imul eax
		jo overflow
		add ebx, eax
		jo overflow

		mov eax, c
		imul eax, 4
		jo overflow
		mov ecx, x
		imul ecx, 2
		jo overflow
		test ecx,ecx
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
		mov ya, eax
		jmp done
		overflow :
		mov overflowch, 1
		jmp done

		zero:
		mov zeroch, 1

		done:

	}

	if (overflowch) {
		cout << "ОШИБКА! ПРОИЗОШЛО ПЕРЕПОЛНЕНИЕ! " << endl;
	}
	else if (zeroch) {
		cout << "ОШИБКА! ДЕЛЕНИЕ НА НОЛЬ! " << endl;
	}
	else {
		cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА АССЕМБЛЕРЕ (__int32): Y = " << ya << endl;

		yc = ((x * c) + (b * b) + ((4 * c) / (2 * x))) / ((3 * x * x) - (b / a));
		cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ НА C++: Y = " << yc << endl;
	}

}

int main() {

	setlocale(LC_ALL, "rus");

	cout << "ВЫБЕРИТЕ:  " << endl;
	cout << "1) ОДНОБАЙТОВЫЕ ПЕРЕМЕННЫЕ;" << endl << "2) ДВУБАЙТОВЫЕ ПЕРЕМЕННЫЕ;" << endl << "3) ЧЕТЫРЕХБАЙТОВЫЕ ПЕРЕМЕННЫЕ." << endl;
	int number;
	cin >> number;

	switch (number) {
	case 1:
		CASE1();
		break;
	case 2:
		CASE2();
		break;
	case 3:
		CASE3();
		break;
	default:
		cout << "ВВЕДЕНО НЕВЕРНОЕ ЧИСЛО! " << endl;
		break;
	}

	return 0;
}