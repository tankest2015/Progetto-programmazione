#include "write_lead.h"

using namespace std;

void insert_line(fstream &newFile, int pos_prec, char Nm[], char Tim[], char copy[], char B[]){
    char mess[80];
    char pc[4];
    //pos insert
    sprintf(pc, "%d", pos_prec);
    strcpy(mess, pc);
    strncat(mess,"      ",5);

    //name_insert
    strncat(mess, Nm, 19);
    strncat(mess,"      ",5);

    //time_insert
    strncat(mess,Tim,9);
    strncat(mess,"      ",5);

    //point_insert
    strncat(mess, copy, 6);
    strncat(mess,"      ",5);

    //line_insert
    strncat(mess, B, 6);

    newFile << mess << endl;
    newFile << "n" << endl;
}

void write(char h[], char min[], char s[], char point[], char name[], char line[]){

    const int length = 100;
    char input[length];

    char time[9];   //time [9] = '\0'
    char mess[80];
    char mess_1[80];

    if (strlen(h) == 1) {
        // Sposta il carattere corrente alla fine e aggiungi '0' all'inizio
        h[1] = h[0];   // Sposta il numero che ho ora a destra
        h[0] = '0';    // Aggiungi '0' all'inizio
        h[2] = '\0';   // Aggiungi il terminatore nullo
    }
    if (strlen(min) == 1) {
        // Sposta il carattere corrente alla fine e aggiungi '0' all'inizio
        min[1] = min[0]; // Sposta il numero che ho ora a destra
        min[0] = '0';    // Aggiungi '0' all'inizio
        min[2] = '\0';   // Aggiungi il terminatore nullo
    }
    if (strlen(s) == 1) {
        // Sposta il carattere corrente alla fine e aggiungi '0' all'inizio
        s[1] = s[0]; // Sposta il numero che ho ora a destra
        s[0] = '0';    // Aggiungi '0' all'inizio
        s[2] = '\0';   // Aggiungi il terminatore nullo
    }

    strcpy(time,h);
    strcat(time,":");
    strncat(time,min,2);
    strcat(time,":");
    strncat(time,s,2);

    char file_tmp[] = {"salvataggio_punteggio/tmp.txt"};
    char file_final[] = {"salvataggio_punteggio/leaderboard.txt"};

    ofstream newF;
    newF.open(file_tmp, ofstream::out | ios::trunc); //"pulisco" il file dove salvo temporaneamente i dati ordinati

    newF.close();

    int j=1;
    fstream file;
    file.open(file_final, ios::in);     //apro in lettura il file dove sono salvati i miei dati ordinati tranne per quello che devo inserire

    fstream newFile;
    newFile.open(file_tmp, ios::app);   //apro il file precedentemente pulito in append

    char line_pos[80];      //con questo leggo le righe del file leaderboard.txt
    char copy[10];          //mi salvo il punteggio della riga corrente
    bool flag = false;
    bool flagI = false;
    int i = 0;
    int pos_prec = 0;       //indice che mi salva la posizione del giocatore corrente
    int count = 0;
    bool is_insert = false;

    char Nm[19];
    char Tim[9];
    char B[6];
    char P[6];

    if(!file.is_open()){ // if file doesn't exits i do an interrupt file = leaderboard.txt
        cout<<"error to open file "<<endl;
    }
    else{
        while(!file.eof()){ //continuo fin tanto che il file non sia arrivato all'ultima riga
                            //mi ricavo se la prima riga del file sia un flag
                            // altrimenti la posizione del giocatore

            //posizione
            file>>line_pos;
            strcpy(mess,line_pos);
            strncat(mess,"      ",5);

            if(!strcmp(line_pos,"ff") == 0 && !strcmp(line_pos,"tt") == 0 && !strcmp(line_pos,"new") == 0){
                if(!strcmp(line_pos,"n") == 0){
                    if(!is_insert) count++;
                    //mi legge i dati della classifica nel file leaderboard.txt
                    pos_prec = stoi(line_pos); //mi salva la posizione in cui sono ora
                    /*
                    posso ricavare solo ora la posizione perché
                    sono sicuro che sia la posizione e non un "\n" o un flag("ff" o "tt");
                    */

                    //name
                    file >> line_pos;
                    strncat(mess, line_pos, 19);
                    strncat(mess, "      ", 5);
                    strcpy(Nm, line_pos);

                    //time
                    file>>line_pos;
                    strncat(mess, line_pos,9);
                    strncat(mess, "      ", 5);
                    strcpy(Tim, line_pos);

                    //point
                    file >> line_pos;
                    strncat(mess, line_pos, 6);
                    strncat(mess, "      ", 5);
                    strcpy(copy, line_pos);

                    //completed rows
                    file >> line_pos;
                    strncat(mess, line_pos, 6);
                    strcpy(B, line_pos);

                    // mi ricavo tutti i dati che mi servono;

                    if(flag){
                        pos_prec++;
                        insert_line(newFile, pos_prec, Nm, Tim, copy, B);     //se flag è attivo vuol dire che ho già inserito il nuovo giocatore
                    }
                    else if(flagI){
                        insert_line(newFile, pos_prec, Nm, Tim, copy, B);     //se flag è attivo vuol dire che ho già inserito il nuovo giocatore
                    }                                                             //quindi inserisco nel file tmp.txt tutti glil altri con la posizione aggiornata,

                    else if(stoi(copy) <= stoi(point) && !flag){
                        if(stoi(copy)==stoi(point)){
                            flagI = true;
                            is_insert = true;
                            insert_line(newFile, pos_prec, name, time, point, line);
                            insert_line(newFile, pos_prec, Nm, Tim, copy, B);
                        }
                        else{
                            flag = true;
                            is_insert = true;
                            insert_line(newFile, pos_prec, name, time, point, line);
                            pos_prec++;
                            insert_line(newFile, pos_prec, Nm, Tim, copy, B);
                        }
                    }
                    else{
                        insert_line(newFile, pos_prec, Nm, Tim, copy, B);
                    }
                }
            }else file>>line_pos;
        }
    }

    if(!flag && !flagI){ //se entrambi sono false deve ancora essere inserito nel file
        flag = true;
        flagI = true;
        is_insert = true;

        pos_prec++;
        count++;
        insert_line(newFile, pos_prec, name, time, point, line);
    }

    file.close();
    newFile.close();
    // chiudo tutti i file;

    char str[4];
    sprintf(str, "%d", count);

    ofstream F;
    F.open(file_final, ofstream::out | ios::trunc); //pulisce tutto il file e mi aggiorna il flag della modifica

    F<<"tt"<<endl; // tt perché ho inserito un nuovo giocatore;
    F<<str<<endl;

    F.close();

    fstream final;
    final.open(file_tmp, ios::in);

    fstream file_text;
    file_text.open(file_final, ios::app);
    char read[80];

    while(!final.eof()){ // ricopio i dati dal file tmp.txt a leaderboard.txt + il relativo flag
        final >> read;
        strcpy(mess, read);
        strncat(mess, "      ", 5);

        if(!strcmp(read, "n") == 0){

            final >> read;
            strncat(mess, read, 19);
            strncat(mess, "      ", 5);

            final >> read;
            strncat(mess, read, 9);
            strncat(mess, "      ", 5);

            final >> read;
            strncat(mess, read, 6);
            strncat(mess, "      ", 5);

            final >> read;
            strncat(mess, read, 6);

            final >> read;
            file_text << mess << endl;
            file_text << "n" << endl;

        }
    }
    file_text.close();
    final.close();

    remove(file_tmp);
}

void del_ch(WINDOW* player, char text[], int i, int limit){
    text[i] = '\0';

    if(i > -1){

        mvwdelch(player, 13, i + 2);
        mvwprintw(player, 13, 2, "%-*s", limit, text);  // Ripulisce la riga e riscrive la stringa aggiornata
        box(player, 0, 0);
        wrefresh(player);
    }
}

bool check(char text[]){
    int i = 0;
    bool flag;
    if(text[i] == '\0')
        flag = true;
    else flag = false;
    return flag;
}

void insert(int p,int h,int min,int s, int row){

    initscr();
    noecho();
    cbreak();
    refresh();


    bool flag = false;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    int i = 0;

    WINDOW *player;
    player = newwin(yMax/2, xMax/2, yMax/2 - yMax/4, xMax/2 - xMax/4);
    box(player, 0, 0);
    mvwprintw(player, 3, 3, "%s", "_____              __  __   _____       ____   __      __  _____  _____");
    mvwprintw(player, 4, 2, "%s", "/ ____|     /\\     |  \\/  | |  __|      / __ \\  \\ \\    / / |  __| |  __ \\");
    mvwprintw(player, 5, 1, "%s", "| |  __     /  \\    | \\  / | | |__      | |  | |  \\ \\  / /  | |__  | |__) |");
    mvwprintw(player, 6, 1, "%s", "| | |_ |   / /\\ \\   | |\\/| | |  __|     | |  | |   \\ \\/ /   |  __| |  _  /");
    mvwprintw(player, 7, 1, "%s", "| |__| |  / ____ \\  | |  | | | |__      | |__| |    \\  /    | |__  | | \\ \\");
    mvwprintw(player, 8, 1, "%s", " \\_____| /_/    \\_\\ |_|  |_| |____|      \\____/      \\/     |____| |_|  \\_\\");
    mvwprintw(player, 12, 1, "INSERT NAME (max: 19 letters):");
    wrefresh(player);

    keypad(player, true);

    int ch;
    bool BSp = false;
    char text[19] = {'\0'};
    char hour[3] = {'\0'};
    char minute[3] = {'\0'};
    char second[3] = {'\0'};
    char point[6] = {'\0'};
    char completed_rows[6] = {'\0'};

    sprintf(point, "%d", p);
    sprintf(hour, "%d", h);
    sprintf(minute, "%d", min);
    sprintf(second, "%d", s);
    sprintf(completed_rows, "%d", row);

    getmaxyx(player, yMax, xMax);

    mvwprintw(player, 15, 50, "%s", "Score: ");
    mvwprintw(player, 15, 57,"%s", point);
    mvwprintw(player, 16, 50, "%s", "Rows: ");
    mvwprintw(player, 16, 57,"%s", completed_rows);

    mvwprintw(player, 17, 50, "%s", "Time: ");
    mvwprintw(player, 17, 57, "%s", hour);
    wprintw(player,"%s", " : ");
    wprintw(player,"%s", minute);
    wprintw(player,"%s", " : ");
    wprintw(player,"%s", second);
    wrefresh(player);


    while(!flag){
        ch = wgetch(player);
        if(ch == 10){ //10 = invio
            BSp = check(text);

            if(BSp){
                mvwprintw(player, 14, 2, "%s", "inserire almeno un carattere valido");
                while(i > 0){
                    i--;
                    del_ch(player, text, i, xMax);
                }
            }
            else{
                write(hour, minute, second, point, text, completed_rows);

                wclear(player);
                wrefresh(player);
                delwin(player);

                flag = true;
            }
        }
        else if(ch == KEY_BACKSPACE){
            if(i > 0){
                i--;
                del_ch(player, text, i, xMax);
            }
        }
        else if(ch>=33 && ch<=126){
            if(i < sizeof(text) - 1){

                wmove(player, 14, 1);
                wclrtoeol(player);
                wrefresh(player);

                box(player, 0, 0);
                wrefresh(player);

                text[i] = (char) ch;
                mvwprintw(player, 13, 2, "%s", text);
                wrefresh(player);
                i++;
            }
        }
        else{
            wmove(player, 14, 1);
            wclrtoeol(player);
            wrefresh(player);

            box(player, 0, 0);
            wrefresh(player);
            mvwprintw(player, 14, 2, "%s", "inserire almeno un carattere valido");
        }
    }
    endwin();
}