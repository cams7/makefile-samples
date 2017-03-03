#include "Daughter.h"

#include <iostream>
using namespace std;

Daughter::Daughter(string name):
    People(name)
{
    cout << "Create Daughter with name: " << name << endl;
}

Daughter::Daughter(string name, Mother& mother):
    People(name), mother(&mother)
{
    cout << "Create Daughter with params: name = " << name << ", mother = " << this->mother->getName() << endl;
}


Daughter::~Daughter()
{
    cout << "Destroy Daughter with name: " << getName() << endl;
}

Mother* Daughter::getMother()
{
    return mother;
}


