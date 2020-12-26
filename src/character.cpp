#include <iostream>
#include <ncurses.h>
#include "character.h"
#define EMPTY ' '
using namespace std;

	Character::Character(int x, int y, char PLAYER){
		this->ch = 0;
		this->x = x;
		this->y = y;
	}
	void Character::moveCharacter(int x, int y, char PLAYER){
		
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
				if (x > 0) mvaddch(y, x--, EMPTY);	// stessa cosa fatta su una riga di codice
				break;
			case KEY_RIGHT:
				if (x < COLS - 1)	mvaddch(y, x++, EMPTY);
				break;
			}
		} 
		while (ch != 27);		// fino a che l'utente non spinge il tasto esc il gioco continua
	}