#include <iostream>

using namespace std;

void passByValue(int);
void passByReference(int*);

int main()
{
    int fish = 5;

    cout << "Value\t\tAddress" << endl;
    cout << fish << "\t\t" << &fish << endl;

    int *fishPointer;
    fishPointer = &fish;
    *fishPointer = 10;

    cout << *fishPointer << "\t\t" << fishPointer << endl;

    cout << fish << "\t\t" << &fish << endl;

    int betty = 13;
    int sandy = 23;

    passByValue(betty);
    passByReference(&sandy);

    cout << "Betty is now " << betty << endl;
    cout << "Sandy is now " << sandy << endl;

    return 0;
}

void passByValue(int x){
    x = 99;
}

void passByReference(int* x){
    *x = 66;
}
