//(Двоичный поиск) Дана неубывающая последовательность X = (xi), i = 1..n, n <= 10, целых чисел и число А.Выяснить, содержится ли А в этой последовательности. 
// (Количество действий порядка log n.)



#include <iostream> 
#include <time.h>
#include <algorithm>

using namespace std;

int main() {

	setlocale(LC_ALL, "rus");

	srand(time(0));

	int* arr;
	int sizearr;
	int A;
	bool result = false;
	cout << "Введите размер массива: " << endl;
	cin >> sizearr;
	if (sizearr > 10) {
		cout << "Введен неверный размер массива! " << endl;
	}
	else {
		cout << "Введите число A: " << endl;
		cin >> A;
		arr = new int[sizearr];
		for (int i = 0; i < sizearr; i++) {
			arr[i] = rand() % 10 + 1;
		}

		sort(arr, arr + sizearr);

		cout << "Введенный массив: " << endl;

		for (int i = 0; i < sizearr; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;

		__asm {
			mov ecx, sizearr
			dec ecx
			mov esi, arr
			mov edi, 0

			binarystart:
			mov ebx, 2
				cmp edi, ecx
				jg binaryend

				mov eax, edi
				add eax, ecx
				cdq
				idiv ebx
				mov ebx, A
				mov eax, [esi + eax * 4]
				cmp eax, ebx
				je found
				jg greaterthan
				jl lessthan

				found :
			mov result, 1
				jmp binaryend

				greaterthan :
			dec ecx
				jmp binarystart

				lessthan :
			inc edi
				jmp binarystart


				binaryend :
		}

		if (result) {
			cout << "Элемент " << A << " найден в заданном массиве! " << endl;
		}
		else {
			cout << "Элемент " << A << " не найден в заданном массиве! " << endl;
		}

		delete[] arr;
	}

	return 0;
}