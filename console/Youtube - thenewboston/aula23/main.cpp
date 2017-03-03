#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    float a;
    float p = 10000;//Investimento
    float r = .01;//Taxa

    for(int day = 1; day <= 30; day++) {
        a = p * pow(1 + r, day);
        cout << day << "\t" << fixed << setprecision(2) << setfill('0') << a << endl;
    }
    return 0;
}
