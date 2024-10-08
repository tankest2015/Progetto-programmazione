
#ifndef CLASS_MENU_H
#define CLASS_MENU_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <ncurses.h>

using namespace std;

struct choiches{
    char field[13];
};

class menu {     //Classe Principale e padre di tutte le altre
    protected:
    int k;              //indice dell'array
    char* choices[4];
    WINDOW* win;
    int yMax;
    int xMax;

    public:
    menu(WINDOW* win, int k, int y, int x); //Costruttore

    void init();                    //funziona che mi inizializza lo schermo
    int get_y();
    int get_x();
    void create_W();                //mi inizializza la finestra
    void menu_start();              //mi inizializza il menu
    void menu_S(int k, int j);      //evidenzia il corretto campo in cui l'utente si trova
    int get_wg();                   //esegue il getch della finestra
};

class Read_menu:public menu {      // Classe derivata dalla classe menu: MENU_DI_GIOCO
    protected:
    WINDOW* win_rank;
    WINDOW* exit;
    int c, r, i;

    public:
    Read_menu(WINDOW* win, int k, int y, int x, WINDOW* win_rank, WINDOW* exit, int col, int righe, int i);

    void create_win_rank();
    void create_win_exit();
    void scr();
};

class Menu_pausa:public menu {     //Classe derivata dalla classe menu: MENU_DI_PAUSA
    protected:
    WINDOW* P;
    char* choices[2];
    int x;
    int y;
    int k;

    public:
    Menu_pausa(WINDOW* win, int k, int y, int x, WINDOW* P, int xMax, int yMax, int c);

    void create_W();
    void menu_start();
    void menu_S(int k, int j);
    void delete_W();
    int get_wg();
};

#endif