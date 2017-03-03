#include <iostream>

using namespace std;


template <class F, class S>
double sum(F, S);

int main()
{
    int a = 15, b = 26;
    cout << a << "\t+ " << b << "\t\t= " << sum(a, b) << endl;

    float c = 265.78, d = 78.69;
    cout << c << "\t+ " << d << "\t\t= " << sum(c, d) << endl;

    double e = 789.4565, f = 498.78;
    cout << e << "\t+ " << f << "\t= " << sum(e, f) << endl;

    cout << a << "\t+ " << c << "\t= " << sum(a, c) << endl;
    cout << b << "\t+ " << e << "\t= " << sum(b, e) << endl;
    cout << c << "\t+ " << e << "\t= " << sum(c, e) << endl;

    return 0;
}

template <class F, class S>
double sum(F number1, S number2){
    return number1 + number2;
}
