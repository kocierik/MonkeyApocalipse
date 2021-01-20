#include <ncurses.h>
#include "menu.h"

void printCredits(){
    init_pair(2, COLOR_BLUE,232);           // FUNZIONI PER USARE I COLORI VEDI MENU.CPP
    attron(COLOR_PAIR(2));
    mvprintw(22,33,"                                                                                                       ");
    mvprintw(23,33,"        ____ ____ _ _  _              ____ _  _ ____                 ___  ____ ___  ___  ____          ");
    mvprintw(24,33,"        |___ |__/ | |_/               |___ |\\/| |__|                 |__] |___ |__] |__] |___          ");
    mvprintw(25,33,"        |___ |  \\ | | \\_              |___ |  | |  |                 |__] |___ |    |    |___          ");
    mvprintw(26,33,"                                                                                                       ");
    mvprintw(27,33,"                                                                                                       ");
    attroff(COLOR_PAIR(2)); //CHIUSURA DEL COLORE ROSSO E BLU
}
void credits(int direction, bool *pEnterWin){                  
    do{
        printTitle();      // STAMPA IL TITOLO FINO A CHE NON SI SPINGE ESC
        printCredits();    // STAMPA GLI AUTORI DEL GIOCO
        direction = getch();            // ASPETTA UN TASTO IN INPUT
    }while(direction != 27);    
    *pEnterWin = false;
    system("clear");                    // PULISCE LO SCHERMO
}