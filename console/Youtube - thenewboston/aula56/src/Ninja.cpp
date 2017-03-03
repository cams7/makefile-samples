#include "Ninja.h"

#include <iostream>
using namespace std;

Ninja::Ninja()
{
    cout << "Create Ninja" << endl;
}

Ninja::~Ninja()
{
    cout << "Destroy Ninja" << endl;
}

void Ninja::attack() {
    cout << "Ninja attacks!!!" << endl;
}
