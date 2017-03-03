#include "Monster.h"

#include <iostream>
using namespace std;

Monster::Monster()
{
    cout << "Create Monster" << endl;
}

Monster::~Monster()
{
    cout << "Destroy Monster" << endl;
}

void Monster::attack() {
    cout << "Monster attacks!!!" << endl;
}
