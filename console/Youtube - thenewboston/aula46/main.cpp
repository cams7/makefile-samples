#include "Birthday.h"
#include "People.h"

#include <iostream>
using namespace std;

int main()
{
    Birthday birthday(1983, 3, 5);
    cout << "Address of birthday: " << &birthday << endl;
    People person("Jose", birthday);
    person.printInfo();

    return 0;
}
