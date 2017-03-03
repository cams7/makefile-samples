#include "Daughter.h"
#include "Mother.h"

#include <iostream>
using namespace std;

int main()
{
    Mother maria("Maria");
    cout << "Address: " << &maria << endl;
    maria.sayName();

    Daughter ana("Ana", maria);
    ana.sayName();

    Mother* motherOfAna = ana.getMother();
    cout << "Address: " << motherOfAna << endl;
    motherOfAna->sayName();

    return 0;
}
