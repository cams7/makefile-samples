#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using namespace std;

static void gotoxy(int x, int y){
     //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

/**
* As fun��es membros da classe Screen podem ser classificadas de acordo com as quatros categorias mostradas abaixo:
* Fun��o de gerenciamento: As fun��es de gerenciamento lidam com atividades como inicializa��o, atribui��o de tarefa,
* gerenciamento de mem�ria e convers�o de tipo. A fun��o contrutor pertence a essa categoria.
*
* Fun�ao de acesso: As fun��es de acesso d�o suporte ao usu�rio no acesso a objetos da classe.
* As fun��es get() e set() pertencem a essa categoria.
*
* Fun��o implementar: As fun��es de implementador s�o suporte aos movimentos do cursor.
* As fun��es home() e move() pertence a essa categoria.
*
* Fun�ao de ajuda: As fun��es de ajuda executam tarefa auxiliares, como valida��o de coordenadas da tela.
* As fun��es clear(), display(), row(), col(), chkrange() e remspace() pertecem a essa categoria.
*/
class Screen
{
    public:
        //Fun��o de gerenciamento
        Screen(int, int, char);
        virtual ~Screen();

        //Fun��es de acesso
        char get();
        char get(int, int);
        Screen& set(char);
        Screen& set(string);

        //Fun��es implementar
        Screen& home();
        Screen& botton();
        Screen& forward();
        Screen& back();
        Screen& up();
        Screen& down();
        Screen& move(int, int);

        //Fun��es de ajuda
        Screen& clear(char);

        int row();
        int col();
        void chkrange(int, int);
        int remspace();
        Screen& linex(int, int, int, char);
        Screen& liney(int, int, int, char);
        virtual Screen& display();
    protected:
        int height;
        int width;

        char* cursor;
        char* screen;
    private:
};

#endif // SCREEN_H
