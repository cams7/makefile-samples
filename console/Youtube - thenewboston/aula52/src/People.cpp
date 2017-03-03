#include "People.h"

#include <iostream>
using namespace std;

People::People(string name):
    name(name)
{
    cout << "Create People with name: " << name << endl;
}

People::~People()
{
    cout << "Destroy People with name: " << this->name << endl;
}

void People::sayName(){
    cout << "My name is " << this->name << endl;
}

string People::getName(){
    return name;
}
