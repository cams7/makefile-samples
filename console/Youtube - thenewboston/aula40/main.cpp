#include <iostream>

using namespace std;

void printLetters(unsigned char*, unsigned int);
void printNumbers(unsigned int*, unsigned int);

int main()
{
    unsigned char letters[] = {'A', 'E', 'i', 'o', 'U'};
    unsigned int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "char: " << sizeof(char) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "float: " << sizeof(float) << endl;
    cout << "double: " << sizeof(double) << endl;
    cout << "numbers: " << sizeof(numbers) << endl;
    cout << "letters: " << sizeof(letters) << endl;

    printLetters(letters, sizeof(letters)/sizeof(letters[0]));
    printNumbers(numbers, sizeof(numbers)/sizeof(numbers[0]));

    return 0;
}

void printLetters(unsigned char* letters, unsigned int size){
    for(unsigned int i=0; i < size; i++)
        cout << *(letters + i) << "\t";
    cout << endl;
}

void printNumbers(unsigned int* numbers, unsigned int size){
    for(unsigned int i=0; i < size; i++)
        cout << *(numbers + i) << "\t";
    cout << endl;
}


