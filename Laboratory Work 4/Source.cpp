#include "Header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

int getListSize(const BusRoute* head) {
    int count = 0;
    while (head != nullptr) {
        ++count;
        head = head->next;
    }
    return count;
}

BusRoute* createUzel(int routeNumber, float time, const string& routeName) {
    try {
        BusRoute* uzel = new BusRoute;
        uzel->routeNumber = routeNumber;
        uzel->time = time;
        uzel->routeName = routeName;
        uzel->next = nullptr;
        uzel->prev = nullptr;
        return uzel;
    }
    catch (const bad_alloc& e) {
        throw string("������ ��������� ������");
    }
}

void addFirst(BusRoute*& head, BusRoute*& tail, BusRoute* uzel) {
    try {
        if (!uzel)
            throw string("������ ����");

        uzel->next = head;
        uzel->prev = nullptr;
        if (head != nullptr)
            head->prev = uzel;
        head = uzel;
        if (tail == nullptr)
            tail = uzel;
    }
    catch (...) {
        delete uzel;
        throw;
    }
}

void addLast(BusRoute*& head, BusRoute*& tail, BusRoute* uzel) {
    try {
        if (!uzel)
            throw string("������ ����");

        uzel->next = nullptr;
        uzel->prev = tail;
        if (tail != nullptr)
            tail->next = uzel;
        tail = uzel;
        if (head == nullptr)
            head = uzel;
    }
    catch (...) {
        delete uzel;
        throw;
    }
}

void addAtIndex(BusRoute*& head, BusRoute*& tail, BusRoute* uzel, int index) {
    try {
        if (index < 0)
            throw string("������������� ������");
        if (!uzel)
            throw string("������ ����");

        if (index == 0) {
            addFirst(head, tail, uzel);
            return;
        }

        BusRoute* tekelem = head;
        int tekelemIndex = 0;
        while (tekelem != nullptr && tekelemIndex < index - 1) {
            tekelem = tekelem->next;
            ++tekelemIndex;
        }

        if (tekelem == nullptr) {
            if (index == tekelemIndex + 1)
                addLast(head, tail, uzel);
            else
                throw string("������ �� ��������� ������");
            return;
        }

        uzel->next = tekelem->next;
        uzel->prev = tekelem;
        if (tekelem->next != nullptr)
            tekelem->next->prev = uzel;
        else
            tail = uzel;
        tekelem->next = uzel;
    }
    catch (...) {
        delete uzel;
        throw;
    }
}

void removeFirst(BusRoute*& head, BusRoute*& tail) {
    try {
        if (head == nullptr)
            throw string("������ ����");

        BusRoute* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
    }
    catch (const string& e) {
        cerr << "������: " << e << endl;
        throw;
    }
}

void removeLast(BusRoute*& head, BusRoute*& tail) {
    try {
        if (tail == nullptr)
            throw string("������ ����");

        BusRoute* temp = tail;
        tail = tail->prev;
        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
    }
    catch (const string& e) {
        cerr << "������: " << e << endl;
        throw;
    }
}

void removeAtIndex(BusRoute*& head, BusRoute*& tail, int index) {
    try {
        if (index < 0)
            throw string("������������� ������");
        if (head == nullptr)
            throw string("������ ����");

        if (index == 0) {
            removeFirst(head, tail);
            return;
        }

        BusRoute* tekelem = head;
        int tekelemIndex = 0;
        while (tekelem != nullptr && tekelemIndex < index) {
            tekelem = tekelem->next;
            ++tekelemIndex;
        }

        if (tekelem == nullptr)
            throw string("������ �� ��������� ������");

        if (tekelem->prev != nullptr)
            tekelem->prev->next = tekelem->next;
        if (tekelem->next != nullptr)
            tekelem->next->prev = tekelem->prev;
        if (tekelem == tail)
            tail = tekelem->prev;
        delete tekelem;
    }
    catch (const string& e) {
        cerr << "������: " << e << endl;
        throw;
    }
}

void clearList(BusRoute*& head, BusRoute*& tail) {
    try {
        while (head != nullptr) {
            removeFirst(head, tail);
        }
    }
    catch (...) {
        cerr << "������ ��� ������� ������" << endl;
        throw;
    }
}

void sortList(BusRoute* head) {
    try {
        if (head == nullptr)
            return;

        bool sortirovka;
        do {
            sortirovka = false;
            BusRoute* tekelem = head;
            while (tekelem != nullptr && tekelem->next != nullptr) {
                if (tekelem->routeNumber > tekelem->next->routeNumber) {
                    swap(tekelem->routeNumber, tekelem->next->routeNumber);
                    swap(tekelem->time, tekelem->next->time);
                    swap(tekelem->routeName, tekelem->next->routeName);
                    sortirovka = true;
                }
                tekelem = tekelem->next;
            }
        } while (sortirovka);
    }
    catch (const string& e) {
        cerr << "������ ����������: " << e << endl;
        throw;
    }
}

void printList(const BusRoute* head) {
    try {
        const BusRoute* tekelem = head;
        while (tekelem != nullptr) {
            cout << "����: " << tekelem->routeNumber
                << ", ������������: " << tekelem->time
                << ", ��������: " << tekelem->routeName << endl;
            tekelem = tekelem->next;
        }
    }
    catch (...) {
        cerr << "������ ������ ������" << endl;
        throw;
    }
}

void writeToFile(const BusRoute* head, const std::string& filename) {
    try {
        ofstream outFile(filename);
        if (!outFile)
            throw string("������ �������� �����");

        const BusRoute* tekelem = head;
        while (tekelem != nullptr) {
            outFile << tekelem->routeNumber << " "
                << tekelem->time << " "
                << tekelem->routeName;
            if (!outFile)
                throw string("������ ������");
            outFile << "\n";
            tekelem = tekelem->next;
        }
        outFile.close();
    }
    catch (const string& e) {
        cerr << "������ ������ � ����: " << e << endl;
        throw;
    }
}

void readFromFile(BusRoute*& head, BusRoute*& tail, const std::string& filename) {
    try {
        ifstream inFile(filename);
        if (!inFile)
            throw string("������ �������� �����");

        string line;
        while (getline(inFile, line)) {
            try {
                if (line.empty())
                    continue;

                istringstream iss(line);
                int routeNum;
                float time;
                string routeName;
                if (!(iss >> routeNum >> time))
                    throw string("������������ ������");

                iss >> ws;
                getline(iss, routeName);

                if (routeName.empty())
                    throw string("����������� ��������");

                BusRoute* uzel = createUzel(routeNum, time, routeName);
                addLast(head, tail, uzel);
            }
            catch (const string& e) {
                cerr << "������ ��������� ������: " << line << " - " << e << endl;
            }
        }
        inFile.close();
    }
    catch (const string& e) {
        cerr << "������ ������ �����: " << e << endl;
        throw;
    }
}
