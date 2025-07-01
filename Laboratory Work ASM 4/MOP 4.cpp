#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib> 
#include <ctime>
#include <vector>

extern "C" int __cdecl __copy_asm();
extern "C" int __cdecl __search_asm(const char* str1, int num1, const char* str2, int num2);
extern "C" int __cdecl __compare_asm(const char* str1, int num1, const char* str2, int num2);
extern "C" int __cdecl __replace_asm();

using namespace std;

void CompareASM() {
    const char* str1 = "Hello, pidor";
    int num1 = strlen(str1);
    const char* str2 = "Hello, eblan";
    int num2 = strlen(str2);
    int resCMP;
    resCMP = __compare_asm(str1, num1, str2, num2);
    if (resCMP) {
        cout << "Строки равны!" << endl;
    }
    if (!resCMP) {
        cout << "Строки не равны!" << endl;
    }
}

void SearchASM() {
    const char* str1 = "12441";
    int num1 = strlen(str1);
    const char* str2 = "12441";
    /*str2 = new char[10];
    cout << "str2" << endl;
    for (int i = 0; i < 10; i++) {
        cin >> str2[i];
    }*/
    int num2 = strlen(str2);
    int resSRCH;
    resSRCH = __search_asm(str1, num1, str2, num2);
    if (!resSRCH) {
        cout << "Размер разыскиваемой строки больше изначальной строки!" << endl;
    }
    if (resSRCH == 1) {
        cout << "Подстрока найдена!" << endl;
    }
    if (resSRCH == 2) {
        cout << "Подстрока не найдена!" << endl;
    }
}

void fWrite(string* path) {
    ofstream fout;
    fout.open(*path, ofstream::app);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        const int BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];
        cout << "Введите строку для записи в файл" << endl;
        cin.getline(buffer, BUFFER_SIZE);
        fout << buffer << endl;
        cout << "Введенная строка успешно записана в файл!" << endl;
    }
    fout.close();
}

void fRead(string* path, char str1[], char str2[]) {
    ifstream fin;
    fin.open(*path);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        cout << "Файл успешно открыт!" << endl;
        fin.getline(str1, 1024);
        fin.getline(str2, 1024);
    }
    fin.close();
}

void Razb(char str[], const char delimiters[]) {
    char* token = strtok(str, delimiters);
    while (token != nullptr) {
        cout << token << endl;
        token = strtok(nullptr, delimiters);
    }
}

bool ss6(const char* str) {
    char* end;
    long int number = strtol(str, &end, 6);
    if (*end != '\0') return false;
    return true;
}

void SixCC(char str[], const char delimiters[], string& newString, char* numbers[], int& count) {
    char tempStr[1024];
    strcpy(tempStr, str);
    char* token = strtok(tempStr, delimiters);
    newString.clear();
    count = 0;

    while (token != nullptr) {
        if (ss6(token)) {
            newString += token;
            newString += " ";

            numbers[count] = token;
            count++;

            char* pos = strstr(str, token);
            while (pos != nullptr && (pos == str || *(pos - 1) == ' ') && (*(pos + strlen(token)) == '\0' || *(pos + strlen(token)) == ' ')) {
                strncpy(pos, "0", strlen(token));
                pos = strstr(pos + 1, token);
            }
        }

        token = strtok(nullptr, delimiters);
    }
}

void chSort(char* numbers[], int count) {
    for (int i = 1; i < count; ++i) {
        char* key = numbers[i];
        int j = i - 1;

        while (j >= 0 && strtol(numbers[j], nullptr, 6) > strtol(key, nullptr, 6)) {
            numbers[j + 1] = numbers[j];
            --j;
        }
        numbers[j + 1] = key;
    }
}

void addedString(string& str, const string& INS, const string& delimiters) {
    size_t last = str.find_last_of(delimiters);
    size_t underLast = str.find_last_of(delimiters, last - 1);

    str.insert(last + 1, INS + " ");
}

void random6ss(string& str, const string& delimiters) {
    srand(time(0));
    size_t start = 0;
    size_t end = str.find_first_of(delimiters);
    size_t count = 0;
    vector<size_t> positions;
    vector<string> tokens;

    while (end != string::npos) {
        string token = str.substr(start, end - start);
        if (ss6(token.c_str())) {
            positions.push_back(start);
            tokens.push_back(token);
            count++;
        }
        start = end + 1;
        end = str.find_first_of(delimiters, start);
    }

    string lastToken = str.substr(start);
    if (ss6(lastToken.c_str())) {
        positions.push_back(start);
        tokens.push_back(lastToken);
        count++;
    }

    if (count > 0) {
        size_t randomIndex = rand() % count;
        str.erase(positions[randomIndex], tokens[randomIndex].length());
        if (str[positions[randomIndex]] == ' ') {
            str.erase(positions[randomIndex], 1);
        }
    }
}

template<typename x>
void result(const string& path, const x& text) {
    ofstream fout;
    fout.open(path, ofstream::app);

    if (!fout.is_open()) {
        cout << "Ошибка записи в файл" << endl;
    }
    else {
        fout << text;
    }
    fout.close();
}

int main() {
    setlocale(LC_ALL, "RU");

    CompareASM();
    SearchASM();

    string path = "myFile.txt";
    fWrite(&path);
    fWrite(&path);

    const int BUFFER_SIZE = 1024;
    char str1[BUFFER_SIZE] = { 0 };
    char str2[BUFFER_SIZE] = { 0 };

    fRead(&path, str1, str2);

    cout << "Строки считаны из файла." << endl;
    cout << "Первая строка: " << str1 << endl;
    cout << "Строка с разделителями: " << str2 << endl;

    string str1String = str1;

    cout << "Разбивка строки на лексемы:\n";
    Razb(str1, str2);

    fRead(&path, str1, str2);

    string newString;
    char* numbers[BUFFER_SIZE];
    int count = 0;
    SixCC(str1, str2, newString, numbers, count);

    chSort(numbers, count);

    cout << "Отсортированные числа в 6-й системе: ";
    string sortedNumbers;
    for (int i = 0; i < count; ++i) {
        cout << numbers[i] << " ";
        sortedNumbers += string(numbers[i]) + " ";
    }
    cout << endl;

    cout << "Первая строка (String): " << str1String << endl;

    addedString(str1String, "added string", str2);

    cout << "Строка после вставки: " << str1String << endl;

    random6ss(str1String, str2);

    cout << "Строка после удаления случайного числа в 6сс: " << str1String << endl;

    string results = "Первая строка: " + string(str1) + "\n" +
        "Строка с разделителями: " + string(str2) + "\n" +
        "Новая строка из чисел в 6-й системе: " + newString + "\n" +
        "Отсортированные числа в 6-й системе: " + sortedNumbers + "\n" +
        "Первая строка (String): " + str1String + "\n" +
        "Строка после вставки: " + str1String + "\n" +
        "Строка после удаления случайного числа в 6сс: " + str1String;

    result(path, results);

    return 0;
}