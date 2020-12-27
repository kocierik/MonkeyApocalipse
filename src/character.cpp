#include <iostream>
#include <ncurses.h>
#include "character.h"
#define SKIN '&'
#define EMPTY ' '
#define STARTX (COLS - WIDTH) / 2 // coordinate del blocco centrale
#define STARTY (LINES - HEIGHT) / 2 // coordinate del blocco centrale
#define WIDTH COLS/2 // dimensione blocco di gioco
#define HEIGHT LINES/2.5 // dimensione blocco di gioco

	Character::Character(){
		this->direction = 0;
		this->x = 0;
		this->y = 0;
	}
	void Character::moveCharacter(int x, int y){	
		do { 						// di base abbiamo un carattere bianco se non lo settiamo 
			mvaddch(y, x, SKIN);	// muove il nostro carattere settato (SKIN)
			move(y, x);				// muove il cursore (altrimenti il carattere sarebbe sempre avanti di un blocco)
			direction = getch();	//prendo in input un carattere da tastiera
			
			switch (direction) {	// controllo quale carattere è stato spinto muovo il cursore e il nostro character 
			case KEY_UP:
				if (y > 0 && y > STARTY+1) mvaddch(y--, x, EMPTY);	// <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_DOWN:
				if (y < LINES - 1 && y < STARTY+HEIGHT-4 ) mvaddch(y++, x, EMPTY);			// <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_LEFT: 
				if (x > 0 && x > STARTX+1) mvaddch(y, x--, EMPTY);  // <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_RIGHT:
				if (x < COLS - 1 && x < STARTX+WIDTH-3)	mvaddch(y, x++, EMPTY); // <-------------- TROVARE EQUAZIONE BORDI
				break;
			}
			refresh();
		} while (direction != 27);		// fino a che l'utente non spinge il tasto esc il gioco continua
	}