#include "Window.h"

#include <iostream>
#include <assert.h>
//#include <conio.h>

using namespace std;

Window::Window(int height, int width, int orgin, char background):
    Screen(height, width, background), origin(orgin)
{
}

Window::~Window()
{
    //dtor
}


/**
*
*/
Screen& Window::display() {
    gotoxy(1, 1);
    for(int i = 0; i < height; ++i){//Apenas para n�mero de linhas height
        int offset = width * i; //Posi��o de linha
        gotoxy(origin, i + 1);
        for(int j = 0; j < width; ++j){//Para n�mero de comprimentos de coluna
            char* p = screen+offset+j;
            cout.put(*p); //Exibe o caracter
        }
        cout << endl;
    }

    return *this;
}
