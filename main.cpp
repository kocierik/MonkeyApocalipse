#include <iostream>
#include <stdio.h>
#include <curses.h>
#include "src/menu.h"
#include "src/enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
using namespace std;

int main(){
    printMenu();
    int y, x; // coordinate della scheda

    int direction;	  // carattere premuto su tastiera in ascii
    initscr();	// inizializzazione dello schermo (OBLIGATORIA)
    keypad(stdscr, TRUE);	//consento l'utilizzo dei caratteri esc, delete, enter
    cbreak();		//disabilita il buffer dei caratteri
    noecho();		//toglie l'eco dei tasti premuti

    y = 0;
    x = 0;

	Character character(x, y, SKIN);
	character.moveCharacter(x, y, SKIN);

    endwin();				// chiusura della scheda obbligatoria

    return 0;
}