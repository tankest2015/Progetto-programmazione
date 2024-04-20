#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "page_save.h"

using namespace std;

char *choices[4] = {"Play","Rank","options","exit"};

/*void menu_start(WINDOW *win)
{
     for(int i = 0;i<4;i++)
        {
            mvwprintw(win,i+1,1,choices[i]);
        }

        wrefresh(win);

        wattron(win,A_REVERSE);
        mvwprintw(win,1,1,choices[0]);
        wattroff(win,A_REVERSE);
        mvwprintw(win,2,1,choices[1]);
        mvwprintw(win,3,1,choices[2]);
        mvwprintw(win,4,1,choices[3]);
}*/

int main(int argc, char ** argv)
{
    int x,y,xMax,yMax;
    
    
    initscr(); //initializeed the screen
    noecho(); 
    cbreak();
    curs_set(0);

    if(!has_colors())
    {
        printw("Terminal doesn't support the color");
        getch();
        return -1;
    }

    getmaxyx(stdscr, yMax,xMax);

    // WINDOW * win = newwin(height,width,start_y,start_x);
    WINDOW * win = newwin(yMax/7,xMax/3,yMax/2,xMax/3);
    refresh();

    box(win,0,0);//initialized my boards of menu
    wrefresh(win);
    
    keypad(win,true);

    char *choices[4] = {"Play","Rank","options","exit"};
    bool pass = true;
    int select;
    int highlight = 0;

    //menu_start(win);
    for(int i = 0;i<4;i++)
        {
            mvwprintw(win,i+1,1,choices[i]);
        }

    wrefresh(win);

    wattron(win,A_REVERSE);
    mvwprintw(win,1,1,choices[0]);
    wattroff(win,A_REVERSE);
    mvwprintw(win,2,1,choices[1]);
    mvwprintw(win,3,1,choices[2]);
    mvwprintw(win,4,1,choices[3]);

    while(pass)
    {
        select = wgetch(win);

        if(select == KEY_UP)
        {
            highlight--;
            if(highlight == -1)
                highlight = 0;
        }
        else if(select==KEY_DOWN)
        {
            highlight++;
            if(highlight == 4)
                highlight = 3;
        }

        if(highlight==0)
        {
            wattron(win,A_REVERSE);
            mvwprintw(win,1,1,choices[0]);
            wattroff(win,A_REVERSE);
            mvwprintw(win,2,1,choices[1]);
            mvwprintw(win,3,1,choices[2]);
            mvwprintw(win,4,1,choices[3]);
        }
        else if(highlight==1)
        {
            mvwprintw(win,1,1,choices[0]);
            wattron(win,A_REVERSE);
            mvwprintw(win,2,1,choices[1]);
            wattroff(win,A_REVERSE);
            mvwprintw(win,3,1,choices[2]);
            mvwprintw(win,4,1,choices[3]);
        }
        else if(highlight==2)
        {
            mvwprintw(win,1,1,choices[0]);
            mvwprintw(win,2,1,choices[1]);
            wattron(win,A_REVERSE);
            mvwprintw(win,3,1,choices[2]);
            wattroff(win,A_REVERSE);
            mvwprintw(win,4,1,choices[3]);
        }
        else if(highlight==3)
        {
            mvwprintw(win,1,1,choices[0]);
            mvwprintw(win,2,1,choices[1]);
            mvwprintw(win,3,1,choices[2]);
            wattron(win,A_REVERSE);
            mvwprintw(win,4,1,choices[3]);
            wattroff(win,A_REVERSE);
        }

        if(select==10)//10 = premo invio per selezionare il campo 
        {
            //if(highlight==0)
            //else 
            if(highlight==1)
            {
                scr();
            }
            else if(highlight==3)
            {
                pass = false;
            }
            //else if(highlight==2)
            

        }
        //menu_start(win);
        refresh();
        
    }

    wclear(win);
    wrefresh(win);
    delwin(win);

    

    

    //getch();
    endwin();
    return 0;
}

