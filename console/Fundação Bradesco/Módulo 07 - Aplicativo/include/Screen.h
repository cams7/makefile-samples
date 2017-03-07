#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using namespace std;

static void gotoxy(int x, int y){
     //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

/**
* As funções membros da classe Screen podem ser classificadas de acordo com as quatros categorias mostradas abaixo:
* Função de gerenciamento: As funções de gerenciamento lidam com atividades como inicialização, atribuição de tarefa,
* gerenciamento de memória e conversão de tipo. A função contrutor pertence a essa categoria.
*
* Funçao de acesso: As funções de acesso dão suporte ao usuário no acesso a objetos da classe.
* As funções get() e set() pertencem a essa categoria.
*
* Função implementar: As funções de implementador são suporte aos movimentos do cursor.
* As funções home() e move() pertence a essa categoria.
*
* Funçao de ajuda: As funções de ajuda executam tarefa auxiliares, como validação de coordenadas da tela.
* As funções clear(), display(), row(), col(), chkrange() e remspace() pertecem a essa categoria.
*/
class Screen
{
    public:
        //Função de gerenciamento
        Screen(int, int, char);
        virtual ~Screen();

        //Funções de acesso
        char get();
        char get(int, int);
        Screen& set(char);
        Screen& set(string);

        //Funções implementar
        Screen& home();
        Screen& botton();
        Screen& forward();
        Screen& back();
        Screen& up();
        Screen& down();
        Screen& move(int, int);

        //Funções de ajuda
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
