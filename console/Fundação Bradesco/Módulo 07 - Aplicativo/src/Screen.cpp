#include "Screen.h"

#include <iostream>
#include <assert.h>
//#include <conio.h>

using namespace std;

const char BELL = '\007';

/**
* Calcula as coordenadas de início e fim de tela. Depois preenche o plano de fundo com o caractere especificado.
*/
Screen::Screen(int height, int width, char background):
    height(height), //Inicializa a altura da tela
    width(width) //Inicializa a largura da tela
{
    int size = height * width;
    cursor = screen = new char[size + 1]; //Inicializa a posição atual do cursor e do buffer de tela
    assert(cursor != 0);
    char* ptr = screen;
    char* endptr = screen + size;
    while(ptr != endptr) //Preencher a tela inteira com caracteres de plano de fundo
        *ptr++ = background;
    *ptr = '\0'; //Final da tela marcado por nulo
}

/**
*
*/
Screen::~Screen()
{
    //delete cursor;
    //delete screen;
}

/**
* Recupera o caractere na posição atual do cursor.
*/
inline char Screen::get() {
    return *cursor;
}

/**
* Recupera o caractere em uma coordenada especificada.
*/
inline char Screen::get(int row, int column) {
    move(row, column); //Posiciona o cursor
    return get();
}

/**
* Escreve um caractere na posição atual do cursor.
*/
Screen& Screen::set(char character) {
    if(character == '\0')
        cerr << "Screen warning: null caracter (ignored)" << endl;
    else
        *cursor = character;
    return *this;
}

/**
* Escreve uma sequência de caracteres na posição atual do cursor.
*/
Screen& Screen::set(string sequence) {
    int space = remspace(); //Espaço restante
    int len = sequence.length(); //Comprimento da sequência
    if(space < len){
        cerr << "Warning truncation: space = " << space << ", string length = " << len << endl;
        len = space;
    }

    for(int i = 0; i < len; ++i)
        *cursor++ = sequence.at(i);
    return *this;
}

/**
* Posiciona o cursor na margem superior esquerda da tela.
*/
inline Screen& Screen::home() {
    cursor = screen;
    return *this;
}

/**
* Coloca o cursor na última coluna da tela.
*/
inline Screen& Screen::botton() {
    int size = width * height - 1;
    cursor = screen + size;
    return *this;
}

/**
* Move o cursor uma posição para direita.
* Se o cursor estiver na parte inferior da tela, o cursor dá a volta e se posiciona na primeira coordenada.
*/
inline Screen& Screen::forward() {
    ++cursor; //Avança o curso na tela
    if(*cursor=='\0')
        home();
    return *this;
}

/**
* Move o cursor uma posição para a esquerda.
* Se o cursor estiver na parte superior da tela , o cursor dá a volta e se posiona na última coordenada.
*/
inline Screen& Screen::back() {
    if(cursor == screen)
        botton();
    else
        --cursor;
    return *this;
}

/**
* Move o cursor, na tela, uma linha para cima.
* Ao atingir a parte superior da tela, o cursor não dá a volta.
* Em vez disso, a função emite um som e o cursor permace onde está.
*/
inline Screen& Screen::up() {
    if(row() == 1)
        cout.put(BELL);//Emite um som
    else
        cursor -= width;
    return *this;
}

/**
* Move o cursor, na tela, uma linha para baixo.
* Ao atingir a parte inferior da tela, o cursor não dá a volta.
* Em vez disso, a função emite um som e o cursor permace onde está.
*/
inline Screen& Screen::down() {
    if(row()==height)
        cout.put(BELL);//Emite um som
    else
        cursor +=width;
    return *this;
}

/**
* Move o cursor para a posição da linha e colunas especificadas.
*/
Screen& Screen::move(int row, int column) {
    chkrange(row, column); //Endereço válido
    cursor = screen + (row - 1) * width + column - 1;
    return *this;
}

/**
* Redefine o cursor e limpa a tela.
* Além disso, redefine o plano de fundo com o caratere especificado.
*/
Screen& Screen::clear(char background) {
        char* p = cursor = screen; //Redefine o cursor;
        while(*p)
            *p++ = background;
        return *this;
}

/**
* Retorna o número da linha da posição do cursor.
*/
inline int Screen::row() {
    int pos = cursor - screen + 1;
    return (pos + width - 1) / width;
}

/**
* Retora o número da coluna da posição do cursor.
*/
inline int Screen::col() {
    int pos = cursor - screen + 1;
    return (pos + width - 1) % width + 1;
}

/**
* Valida as coordenadas especificadas para a tela.
*/
inline void Screen::chkrange(int row, int column) {
     if(row<1 || column < 1 || row > height || column > width)
        cerr << "Window coordinates (" << row << ", " << column << ") out bounds." << endl;
}

/**
* Retorna a quantidade de espaço livre na tela.
*/
inline int Screen::remspace() {
    int size = width * height;
    return screen + size - cursor - 1;
}

/**
* Desenha uma linha horizontal a partir da posição, do comprimento e do caractere especificado.
*/
Screen& Screen::linex(int row, int length, int column, char character) {
    move(row, column);//r-linha, o-coluna, l-comprimento
    for(int i=0; i<length; ++i)
        set(character).forward(); //ch-caracter de plano de fundo
    return *this;
}

/**
* Desenha uma linha vertical a partir da posição, do comprimento e do caractere especificado.
*/
Screen& Screen::liney(int row, int length, int column, char character) {
    move(row, column);
    for(int i=0; i<length; ++i)
        set(character).down();
    return *this;
}

/**
* Exibe o número de caracteres de (width) e depois insere um caractere de nova linha antes de exibir a próxima linha.
* Calcula a posição da linha e exibe os caracteres em cada coluna no intervalo de (0) a (width).
*/
Screen& Screen::display() {
    gotoxy(1, 1);
    for(int i = 0; i < height; ++i){//Apenas para número de linhas height
        int offset = width * i; //Posição de linha
        for(int j = 0; j < width; ++j){//Para número de comprimentos de coluna
            char* p = screen+offset+j;
            cout.put(*p); //Exibe o caracter
        }
        cout << endl;
    }

    return *this;
}
