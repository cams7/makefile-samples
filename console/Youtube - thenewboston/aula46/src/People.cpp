#include "People.h"

#include <iostream>
using namespace std;

People::People(string name, Birthday& birthday):
    name(name), birthday(birthday)
{
    cout << "Create People" << endl;
}

People::~People()
{
    cout << "Destroy People" << endl;
}

void People::printInfo() {
    cout << "Address of birthday: " << &birthday << endl;
    cout << name << " was born on ";
    birthday.printDate();
}
