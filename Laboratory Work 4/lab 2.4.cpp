#include "Header.h"

using namespace std;

void printMenu() {
    cout << "\tМеню операций:" << endl;
    cout << "1. Чтение и запись элементов из файла" << endl;
    cout << "2. Добавить элемент в начало" << endl;
    cout << "3. Добавить элемент в конец" << endl;
    cout << "4. Добавить элемент по индексу" << endl;
    cout << "5. Удалить элемент в начале" << endl;
    cout << "6. Удалить элемент в конце" << endl;
    cout << "7. Удалить элемент по индексу" << endl;
    cout << "8. Удалить все элементы списка" << endl;
    cout << "9. Сортировка списка" << endl;
    cout << "10. Вывод списка на консоль" << endl;
    cout << "11. Запись списка в файл" << endl;
    cout << "12. Выход из программы" << endl;
    cout << "Выберите операцию: ";
}

int main() {
    setlocale(LC_ALL, "rus");
    BusRoute* head = nullptr;
    BusRoute* tail = nullptr;
    int choice;

    while (true) {
        printMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            string filename = "data.txt";
            readFromFile(head, tail, filename);
            cout << "Данные успешно считаны из файла." << endl;
            break;
        }
        case 2: {
            int num;
            float time;
            string name;
            cout << "Введите номер рейса: ";
            cin >> num;
            cout << "Введите длительность рейса: ";
            cin >> time;
            cin.ignore();
            cout << "Введите название рейса: ";
            getline(cin, name);
            BusRoute* uzel = createUzel(num, time, name);
            addFirst(head, tail, uzel);
            cout << "Элемент добавлен в начало списка." << endl;
            break;
        }
        case 3: {
            int num;
            float time;
            string name;
            cout << "Введите номер рейса: ";
            cin >> num;
            cout << "Введите длительность рейса: ";
            cin >> time;
            cin.ignore();
            cout << "Введите название рейса: ";
            getline(cin, name);
            BusRoute* uzel = createUzel(num, time, name);
            addLast(head, tail, uzel);
            cout << "Элемент добавлен в конец списка." << endl;
            break;
        }
        case 4: {
            int index;
            int num;
            float time;
            string name;
            cout << "Введите индекс для вставки (начиная с 0): ";
            cin >> index;
            cout << "Введите номер рейса: ";
            cin >> num;
            cout << "Введите длительность рейса: ";
            cin >> time;
            cin.ignore();
            cout << "Введите название рейса: ";
            getline(cin, name);
            BusRoute* uzel = createUzel(num, time, name);
            addAtIndex(head, tail, uzel, index);
            cout << "Элемент добавлен по индексу." << endl;
            break;
        }
        case 5:
            removeFirst(head, tail);
            cout << "Первый элемент удалён." << endl;
            break;
        case 6:
            removeLast(head, tail);
            cout << "Последний элемент удалён." << endl;
            break;
        case 7: {
            int index;
            cout << "Введите индекс для удаления: ";
            cin >> index;
            removeAtIndex(head, tail, index);
            cout << "Элемент по индексу удалён." << endl;
            break;
        }
        case 8:
            clearList(head, tail);
            cout << "Все элементы списка удалены." << endl;
            break;
        case 9:
            sortList(head);
            cout << "Сортировка прошла успешно." << endl;
            break;
        case 10:
            printList(head);
            break;
        case 11: {
            string filename = "result.txt";
            writeToFile(head, filename);
            cout << "Двусвязный список записан в файл." << endl;
            break;
        }
        case 12:
            cout << "Выход из программы." << endl;
            clearList(head, tail);
            return 0;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
        }
    }
    return 0;
}
