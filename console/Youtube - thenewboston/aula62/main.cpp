#include "AppException.h"

#include <iostream>
using namespace std;

void printMessage(AppException* ex);

int main()
{
    try{
        int momsAge = 30;
        int sonsAge = 34;

        if(sonsAge > momsAge)
            throw new AppException("Son can't be older than mom", 99);

    }catch(AppException* ex){
        printMessage(ex);
    }
    return 0;
}

void printMessage(AppException* ex){
    cout << ex->getMessage() << ", ERROR NUMBER: " << ex->getCode() << endl;
    delete ex;
}
