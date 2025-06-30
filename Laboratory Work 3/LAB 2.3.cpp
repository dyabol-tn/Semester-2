#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

void TextFromFile(string*& textArr, int& size, const string& file) {
    ifstream ReadFile(file);
    if (!ReadFile.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        cout << "Файл успешно открыт!" << endl;
        string line;
        int count = 0;

        while (getline(ReadFile, line)) {
            count++;
        }

        ReadFile.clear();
        ReadFile.seekg(0, ios::beg);
        textArr = new string[count];
        size = count;
        int index = 0;
        while (getline(ReadFile, line)) {
            textArr[index++] = line;
        }
        ReadFile.close();
    }
}

void TextInFile(string* resArr, int size, const string& FileName) {
    ofstream WriteFile(FileName);
    if (!WriteFile.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        for (int i = 0; i < size; i++) {
            WriteFile << resArr[i] << endl;
        }
        cout << "Результаты записаны в файл!" << endl;
    }
    WriteFile.close();
}

int main() {
    setlocale(LC_ALL, "rus");

    string* textArr = nullptr;
    int size = 0;

    string* resultArr = nullptr;
    int resSize = 0;

    TextFromFile(textArr, size, "lab3.txt");

    regex email(R"(^[a-zA-Z1-9]+[-\.]+[a-zA-Z1-9]+@\w+\.(ru|com|by|info|su)$)");

    for (int i = 0; i < size; i++) {
        auto words_begin = sregex_iterator(textArr[i].begin(), textArr[i].end(), email);
        auto words_end = sregex_iterator();

        for (sregex_iterator it = words_begin; it != words_end; ++it) {
            smatch match = *it;

            string* tempArr = new string[resSize + 1];
            for (int j = 0; j < resSize; j++) {
                tempArr[j] = resultArr[j];
            }
            tempArr[resSize] = match.str();
            resSize++;

            delete[] resultArr;
            resultArr = tempArr;

            cout << match.str() << endl;
        }
    }

    TextInFile(resultArr, resSize, "result.txt");

    delete[] textArr;
    delete[] resultArr;

    return 0;
}
