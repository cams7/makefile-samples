#include "Mother.h"

#include <iostream>
using namespace std;

Mother::Mother(string name):
    People(name)
{
    cout << "Create Mother with name: " << name << endl;
}

Mother::~Mother()
{
    cout << "Destroy Mother with name: " << getName() << endl;
}
