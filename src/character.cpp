#include <iostream>
#include <ncurses.h>
#include "character.h"
#define SKIN '&'
#define EMPTY ' '

	Character::Character(){
		this->direction = 0;
		this->x = 0;
		this->y = 0;
	}
	void Character::moveCharacter(int x, int y){	// 48 18
		do { 						// di base abbiamo un carattere bianco se non lo settiamo 
			mvaddch(y, x, SKIN);	// muove il nostro carattere settato (SKIN)
			move(y, x);				// muove il cursore (altrimenti il carattere sarebbe sempre avanti di un blocco)
			direction = getch();	//prendo in input un carattere da tastiera
			
			switch (direction) {	// controllo quale carattere è stato spinto muovo il cursore e il nostro character 
			case KEY_UP:
				if (y > 0 && y > 11) mvaddch(y--, x, EMPTY);	// <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_DOWN:
				if (y < LINES - 1 && y < 25 ) mvaddch(y++, x, EMPTY);			// <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_LEFT: 
				if (x > 0 && x > 45) mvaddch(y, x--, EMPTY);  // <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_RIGHT:
				if (x < COLS - 1 && x < 122)	mvaddch(y, x++, EMPTY); // <-------------- TROVARE EQUAZIONE BORDI
				break;
			}
			refresh();
		} while (direction != 27);		// fino a che l'utente non spinge il tasto esc il gioco continua
	}