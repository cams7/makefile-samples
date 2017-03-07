#include "Screen.h"
#include "Window.h"

#include <iostream>

using namespace std;

int main()
{
    Screen s(15, 60, '-');
    Window w(6, 40, 10, '.');

    s.linex(1, 60, 1, '$').linex(15, 60, 1, '$');
    s.liney(1, 1, 14, '$').liney(1, 60, 14, '$');
    s.move(4, 4).set("Ol\u00E1");
    s.move(8, 8).set("Como voc\u00EA est\u00E1?");
    s.move(12, 12).set("Seja bem vindo ao C++");
    s.display();
    w.linex(1, 40, 1, '#').linex(6, 40, 1, '#');
    w.liney(1, 1, 5, '#').liney(1, 40, 5, '#').move(2, 20).set("Oi");
    w.move(4, 8).set("Espero que voc\u00EA goste da sess\u00E3o").display();

    return 0;
}
