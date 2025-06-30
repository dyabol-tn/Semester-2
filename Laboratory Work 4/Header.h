#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct BusRoute {
    int routeNumber;
    float time;
    string routeName;
    BusRoute* next;
    BusRoute* prev;
};

const int MAXLEN = 200;

BusRoute* createUzel(int routeNumber, float time, const string& routeName);
void addFirst(BusRoute*& head, BusRoute*& tail, BusRoute* uzel);
void addLast(BusRoute*& head, BusRoute*& tail, BusRoute* uzel);
void addAtIndex(BusRoute*& head, BusRoute*& tail, BusRoute* uzel, int index);
void removeFirst(BusRoute*& head, BusRoute*& tail);
void removeLast(BusRoute*& head, BusRoute*& tail);
void removeAtIndex(BusRoute*& head, BusRoute*& tail, int index);
void clearList(BusRoute*& head, BusRoute*& tail);
void sortList(BusRoute* head);
void printList(const BusRoute* head);
void writeToFile(const BusRoute* head, const string& filename);
void readFromFile(BusRoute*& head, BusRoute*& tail, const string& filename);

#endif HEADER_H
