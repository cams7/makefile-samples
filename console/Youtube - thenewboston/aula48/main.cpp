#include "StankFirst.h"

#include <iostream>
using namespace std;

void stinkysFriend(StankFirst& sf){
    sf.number = 27;
    sf.printCrap();
}

int main()
{
    StankFirst sf(59);
    sf.printCrap();

    stinkysFriend(sf);

    return 0;
}
