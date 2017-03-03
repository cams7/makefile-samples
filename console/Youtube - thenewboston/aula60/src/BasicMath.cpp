#ifdef BASICMATH_H
//#include "BasicMath.h"

#include <iostream>
using namespace std;

template<class F, class S>
BasicMath<F, S>::BasicMath(F first, S secound):
    first(first), secound(secound)
{
    cout << "Create BasicMath" << endl;
}

template<class F, class S>
BasicMath<F, S>::~BasicMath()
{
    cout << "Destroy BasicMath" << endl;
}

template<class F, class S>
double BasicMath<F, S>::sum(){
    return first + secound;
}

template<class F, class S>
double BasicMath<F, S>::sub(){
    return first - secound;
}

template<class F, class S>
double BasicMath<F, S>::mult(){
    return first * secound;
}

template<class F, class S>
double BasicMath<F, S>::div(){
    return first / secound;
}

#endif // BASICMATH_H
