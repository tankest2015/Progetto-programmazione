#include <ncurses.h>
#include "class_menu.h"

using namespace std;

bool pause(){
    bool pass = true;   //flag falso: l'utente ha cliccato resume o exit, vero: deve ancora scegliere l'opzione
    int select;         //mi rivaca il getch() della finestra del menu di pausa
    int highlight = 0;  //contatore per definire che cosa ha scelto l'utente

    WINDOW *win;
    WINDOW *P;

    Menu_pausa T(win, 0, 0, 0, P, 0, 0, 2); // istanza della classe con costruttore, è una classe derivata dalla classe menu(vedi lib class_menu.h).
    char c;
    int i = 1;

    T.create_W();   //mi costruisco la finestra(nella libreria).
    T.menu_start(); //inizializzo il menu().

    pass = true;
    highlight = 0;

    while(pass){             //logica simile per il menu di gioco
        select = T.get_wg();

        if(select == KEY_UP){
            highlight--;
            if(highlight == -1) highlight = 1;
        }
        else if(select == KEY_DOWN){
            highlight++;
            if(highlight == 2) highlight = 0;
        }

        if(highlight == 0){             //il secondo parametro mi permette di far continuare il for per ogni elemento dell'array
            T.menu_S(highlight,2);
        }
        else{
            T.menu_S(highlight,2);
        }

        if(select == 10){       //10 = premo invio per selezionare il campo
            pass = false;       //così mi esce dal while in ogni caso;
            T.delete_W();       //mi elimina solo la finestra di pausa;
        }
        refresh();
    }

    if(highlight == 1) return true;

    return false;
}