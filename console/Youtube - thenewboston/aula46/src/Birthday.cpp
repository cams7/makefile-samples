#include "Birthday.h"

#include <iostream>
using namespace std;

Birthday::Birthday(unsigned int year, unsigned int month, unsigned int day):
    year(year), month(month), day(day)
{
    cout << "Create Birthday" << endl;
}

Birthday::~Birthday()
{
    cout << "Destroy Birthday" << endl;
}

void Birthday::printDate() {
    cout << day << "/" << month << "/" << year << endl;
}
