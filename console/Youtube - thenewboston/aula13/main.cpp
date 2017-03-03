// rm -r obj/Linux; mkdir obj/Linux && gcc main.cpp -lstdc++ -o obj/Linux/main.o && ./obj/Linux/main.o

// rm -r obj/Linux; mkdir -p obj/Linux && g++ -Wall -fexceptions -g  -c main.cpp -o obj/Linux/main.o
// rm -r bin/Linux; mkdir -p bin/Linux && g++  -o bin/Linux/aula13 obj/Linux/main.o && ./bin/Linux/aula13

#include <iostream>
#include <string>

using namespace std;

class Buck {
public:
    Buck(){}
    Buck(string name){
        setName(name);
    }
    void setName(string name){
        _name = name;
    }
    string getName(){
        return _name;
    }
private:
    string _name;
};

int main()
{
    Buck bo1;
    bo1.setName("C\u00E9sar A. Magalh\u00E3es");
    cout << bo1.getName() << endl;

    Buck bo2("C\u00E9sar A. Magalh\u00E3es");
    cout << bo2.getName() << endl;
    return 0;
}
