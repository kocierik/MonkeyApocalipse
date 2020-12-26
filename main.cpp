#include <iostream>
#include <stdio.h>
#include <curses.h>
#include "src/menu.h"
#include "src/actor.h"
#define PLAYER '&'
#define EMPTY ' '
using namespace std;

int main(){
    int y, x; // coordinate della scheda
    int ch;	  // carattere premuto su tastiera
    initscr();	// inizializzazione dello schermo (OBLIGATORIA)
    keypad(stdscr, TRUE);	//consento l'utilizzo dei caratteri esc, delete, enter
    cbreak();		//disabilita il buffer dei caratteri
    noecho();		//toglie l'eco dei tasti premuti

    y = 0;
    x = 0;

    do { 	// di base abbiamo un carattere bianco se non lo settiamo 
	mvaddch(y, x, PLAYER);	// muove il nostro carattere settato (PLAYER)
	move(y, x);	// muove il cursore (altrimenti il carattere sarebbe sempre avanti di un blocco)
	refresh();	// ricarico la scheda
	ch = getch();	//prendo in input un carattere da tastiera

	switch (ch) {	// controllo quale carattere è stato spinto
	case KEY_UP:
	    if ((y > 0)) {
		mvaddch(y--, x, EMPTY);	
		//y--;		// muovo il carattere
	    }
	    break;
	case KEY_DOWN:
	    if ((y < LINES - 1) ) {
		mvaddch(y++, x, EMPTY);		// se invertiamo le due istruzioni la lettera vecchia non si cancella
		//y++;						// si cancella perchè è sovrascritta da EMPTY che sarebbe uno spazio
	    }
	    break;
	case KEY_LEFT:
	    if ((x > 0) ) {
		mvaddch(y, x--, EMPTY);
		//x--;
	    }	
	    break;
	case KEY_RIGHT:
	    if ((x < COLS - 1) ) {
		mvaddch(y, x++, EMPTY);
		//x++;
	    }
	    break;
	}
    } while (ch != 27);		// fino a che l'utente non spinge il tasto esc il gioco continua

    endwin();				// chiusura della scheda obbligatoria
    return 0;
}