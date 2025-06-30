/*Создать параметризованный класс данных(шаблон) - массив данных о студентах(с динамическим выделением памяти) - MASSIV". Этот класс предназначен для ввода, хранения и вывода информации. Переменными-членами класса являются количество записей и указатель на массив структур.
Данные о каждой записи хранятся в структуре.

Для класса - шаблона "MASSIV" реализовать основные функции для работы с массивом :
конструкторы, деструктор
ввод из текстового потока(файла) массива данных(operator >>)
вывод в текстовый поток(файл) и на консоль массива данных(operator <<)
вывод в бинарный поток(файл) массива данных или один элемент массива(ф.seek)
ввод из бинарного потока(файла) массив данных или один элемент массива(ф.seek), только после того как записали функцией из пункта е
перегрузка оператора ввода и вывода для Struct(operator >>, operator <<)
operator=
доступ к элементу(operator[])
создать па основе этих данных  новый массив(функц. 1 согласно индивидуальному варианту).
Упорядочить полученный массив в порядке(функц. 3  согласно индивидуальному варианту).

2) Для структур(классов) Element1, Element2, Element3:
конструкторы, деструктор
перегрузка оператора ввода и вывода для Struct(operator >>, operator <<) (можно как ф.шаблон)
operator=, operator<, operator== (можно  и как функция - шаблон)

	3) Х.function1(K, M); //Функция-шаблон  внутри класса-шаблона - объединения(или пересечения, или разности)  массивов (согласно инд. варианту)

4) Создать отдельную функцию шаблон, с параметром класс - шаблон MASSIV и элемент структуры :
search_function2(Х, st) (функц. 2 согласно индивидуальному варианту)

5) Реализовать вне класса - шаблона одну дружественную функцию и любой один метод класса шаблона.

6) В шаблоне MASSIV, обрабатывать только массив, поля структур не использовать!

7) В main должны быть объекты шаблона MASSIV для типов : double(или char или float или long), для трех типов структур(классов) : Element1, Element2, Element3 и вызваны методы поиска и сортировки и слияния массивов(согласно инд.варианту)

8) Частичное описание класса шаблона и, методов, структур и функции main() смотрите в файле : шаблон пример со сложными типами_структурами(скелет лабораторной).doc  в материалах!*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

struct Element1 {
    char Name[50];
    int kurs;

    Element1(const char* name = "", int k = 0) : kurs(k) {
        strncpy(Name, name, 49);
        Name[49] = '\0';
    }

    friend ostream& operator<<(ostream& out, const Element1& other) {
        out << "Name: " << other.Name << ", Kurs: " << other.kurs;
        return out;
    }

    friend istream& operator>>(istream& in, Element1& other) {
        in.getline(other.Name, 50, ' ');
        in >> other.kurs;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        return in;
    }

    Element1& operator=(const Element1& other) {
        if (this != &other) {
            strncpy(Name, other.Name, 49);
            Name[49] = '\0';
            kurs = other.kurs;
        }
        return *this;
    }

    bool operator<(const Element1& other) const {
        if (kurs != other.kurs) return kurs < other.kurs;
        return strcmp(Name, other.Name) < 0;
    }

    bool operator==(const Element1& other) const {
        return (strcmp(Name, other.Name) == 0 && kurs == other.kurs);
    }
};

struct Element2 {
    char Name[50];
    int kurs;

    Element2(const char* name = "", int k = 0) : kurs(k) {
        strncpy(Name, name, 49);
        Name[49] = '\0';
    }

    friend ostream& operator<<(ostream& out, const Element2& other) {
        out << "Name: " << other.Name << ", Kurs: " << other.kurs;
        return out;
    }

    friend istream& operator>>(istream& in, Element2& other) {
        in.getline(other.Name, 50, ' ');
        in >> other.kurs;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        return in;
    }

    Element2& operator=(const Element2& other) {
        if (this != &other) {
            strncpy(Name, other.Name, 49);
            Name[49] = '\0';
            kurs = other.kurs;
        }
        return *this;
    }

    bool operator<(const Element2& other) const {
        if (kurs != other.kurs) return kurs < other.kurs;
        return strcmp(Name, other.Name) < 0;
    }

    bool operator==(const Element2& other) const {
        return (strcmp(Name, other.Name) == 0 && kurs == other.kurs);
    }
};

struct Element3 {
    char Name[50];
    int kurs;

    Element3(const char* name = "", int k = 0) : kurs(k) {
        strncpy(Name, name, 49);
        Name[49] = '\0';
    }

    friend ostream& operator<<(ostream& out, const Element3& other) {
        out << "Name: " << other.Name << ", Kurs: " << other.kurs;
        return out;
    }

    friend istream& operator>>(istream& in, Element3& other) {
        in.getline(other.Name, 50, ' ');
        in >> other.kurs;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        return in;
    }

    Element3& operator=(const Element3& other) {
        if (this != &other) {
            strncpy(Name, other.Name, 49);
            Name[49] = '\0';
            kurs = other.kurs;
        }
        return *this;
    }

    bool operator<(const Element3& other) const {
        if (kurs != other.kurs) return kurs < other.kurs;
        return strcmp(Name, other.Name) < 0;
    }

    bool operator==(const Element3& other) const {
        return (strcmp(Name, other.Name) == 0 && kurs == other.kurs);
    }
};

template <class T>
class MASSIV {
    T* arr;
    int size;

public:
    int count;

    MASSIV(int size = 100) : size(size), count(0) {
        arr = new T[size];
    }

    MASSIV(const MASSIV& other) : size(other.size), count(other.count) {
        arr = new T[size];
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[i];
        }
    }

    ~MASSIV() {
        delete[] arr;
    }

    void WriteBinary(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка открытия файла " << filename << endl;
            return;
        }
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (int i = 0; i < count; i++) {
            if constexpr (is_same_v<T, Element1> || is_same_v<T, Element2> || is_same_v<T, Element3>) {
                file.write(arr[i].Name, 50);
                file.write(reinterpret_cast<const char*>(&arr[i].kurs), sizeof(int));
            }
            else {
                file.write(reinterpret_cast<const char*>(&arr[i]), sizeof(T));
            }
        }
    }

    void ReadBinary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка открытия файла " << filename << endl;
            return;
        }
        int fileCount;
        file.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));
        count = 0;
        for (int i = 0; i < fileCount && count < size; i++) {
            if constexpr (is_same_v<T, Element1> || is_same_v<T, Element2> || is_same_v<T, Element3>) {
                T temp;
                file.read(temp.Name, 50);
                file.read(reinterpret_cast<char*>(&temp.kurs), sizeof(int));
                Add(temp);
            }
            else {
                T temp;
                file.read(reinterpret_cast<char*>(&temp), sizeof(T));
                Add(temp);
            }
        }
    }

    void ReadFromTextFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла " << filename << endl;
            return;
        }

        count = 0;

        if constexpr (is_same_v<T, Element1> || is_same_v<T, Element2> || is_same_v<T, Element3>) {
            string line;
            while (getline(file, line) && count < size) {
                size_t spacePos = line.find(' ');
                if (spacePos != string::npos) {
                    string name = line.substr(0, spacePos);
                    int kurs = stoi(line.substr(spacePos + 1));
                    T temp(name.c_str(), kurs);
                    Add(temp);
                }
            }
        }
        else {
            T temp;
            while (file >> temp && count < size) {
                Add(temp);
            }
        }
    }

    void WriteToTextFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла " << filename << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            file << arr[i] << endl;
        }
    }
    void Add(const T& element) {
        if (count < size) {
            arr[count++] = element;
        }
        else {
            cerr << "Массив переполнен!" << endl;
        }
    }

    friend ostream& operator<<(ostream& out, const MASSIV& m) {
        for (int i = 0; i < m.count; i++) {
            out << m.arr[i] << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, MASSIV& m) {
        T temp;
        while (in >> temp && m.count < m.size) {
            m.Add(temp);
        }
        return in;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Неверный индекс");
        }
        return arr[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw out_of_range("Неверный индекс");
        }
        return arr[index];
    }

    MASSIV& operator=(const MASSIV& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            count = other.count;
            arr = new T[size];
            for (int i = 0; i < count; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    MASSIV<T> Substraction(const MASSIV<T>& other) {
        MASSIV<T> result(size);
        for (int i = 0; i < count; i++) {
            bool found = false;
            for (int j = 0; j < other.count; j++) {
                if (arr[i] == other.arr[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) result.Add(arr[i]);
        }
        return result;
    }

    void SortDescending() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (arr[j] < arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }



    friend void PrintSize(const MASSIV<T>& m) {
        cout << "Размер массива: " << m.count << endl;
    }


};

template <class T>
bool SearchElement(const MASSIV<T>& arr, const T& value) {
    for (int i = 0; i < arr.count; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

void createTestFiles() {
    ofstream file1("Read1.txt");
    if (file1) {
        file1 << "Иванов 2\nПетров 3\nСидоров 1\nКузнецова 4\nСмирнов 2\n";
        file1.close();
    }

    ofstream file2("Read2.txt");
    if (file2) {
        file2 << "Иванов 2\nСидоров 1\nФедорова 3\nВасильев 2\n";
        file2.close();
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    createTestFiles();

    MASSIV<double> doubleArr;
    doubleArr.Add(3.14);
    doubleArr.Add(2.71);
    doubleArr.Add(1.618);
    cout << "Массив double:\n" << doubleArr << endl;

    MASSIV<Element1> elem1Arr;
    elem1Arr.Add(Element1("Иванов", 2));
    elem1Arr.Add(Element1("Петров", 3));
    cout << "Массив Element1:\n" << elem1Arr << endl;

    MASSIV<Element2> elem2Arr;
    elem2Arr.Add(Element2("Сидорова", 1));
    elem2Arr.Add(Element2("Иванова", 4));
    cout << "Массив Element2:\n" << elem2Arr << endl;

    MASSIV<Element3> elem3Arr;
    elem3Arr.Add(Element3("Смирнов", 2));
    elem3Arr.Add(Element3("Кузнецова", 3));
    cout << "Массив Element3:\n" << elem3Arr << endl;

    MASSIV<Element1> fileArr1;
    fileArr1.ReadFromTextFile("Read1.txt");
    cout << "\nДанные из Read1.txt:\n" << fileArr1 << endl;

    MASSIV<Element1> fileArr2;
    fileArr2.ReadFromTextFile("Read2.txt");
    cout << "Данные из Read2.txt:\n" << fileArr2 << endl;

    MASSIV<Element1> fileDiff = fileArr1.Substraction(fileArr2);
    cout << "Разность массивов из файлов:\n" << fileDiff << endl;

    fileArr1.SortDescending();
    cout << "Отсортированные данные из Read1.txt:\n" << fileArr1 << endl;

    fileArr1.WriteToTextFile("Sorted1.txt");
    cout << "Отсортированные данные сохранены в Sorted1.txt\n";

    Element1 searchElem{ "Петров", 3 };
    if (SearchElement(fileArr1, searchElem)) {
        cout << "Элемент " << searchElem << " найден в массиве!\n";
    }
    else {
        cout << "Элемент " << searchElem << " не найден.\n";
    }

    fileArr1.WriteBinary("test.bin");
    MASSIV<Element1> fromBinary;
    fromBinary.ReadBinary("test.bin");
    cout << "\nМассив из бинарного файла:\n" << fromBinary << endl;

    PrintSize(fileArr1);

    return 0;
}