#include <iostream>
#include <ncurses.h>
#include "character.h"
#define SKIN '&'
#define EMPTY ' '
#define startx COLS / 2
#define starty LINES / 2
#define width 80
#define height 20
#define GRASS_PAIR     1
#define EMPTY_PAIR     1
#define WATER_PAIR     2
#define MOUNTAIN_PAIR  3
#define PLAYER_PAIR    4


// int is_move_okay(int y, int x)
// {
//     int direction = mvinch(y, x);
//     return (((direction & A_CHARTEXT) == ' ') || ((direction & A_CHARTEXT) == EMPTY));
// }

	Character::Character(int x, int y){
		this->direction = 0;
		this->x = x;
		this->y = y;
	}
	void Character::moveCharacter(int x, int y){
		
		do { 						// di base abbiamo un carattere bianco se non lo settiamo 
			mvaddch(y, x, SKIN);	// muove il nostro carattere settato (SKIN)
			move(y, x);				// muove il cursore (altrimenti il carattere sarebbe sempre avanti di un blocco)
			direction = getch();	//prendo in input un carattere da tastiera

			switch (direction) {	// controllo quale carattere è stato spinto 	//muovo il cursore e il nostro character 
			case KEY_UP:
				if ((y > 0)){
				 mvaddch(y--, x, EMPTY);	// <-------------- TROVARE EQUAZIONE BORDI
				}
				break;
			case KEY_DOWN:
				if ((y < LINES - 1)) mvaddch(y++, x, EMPTY);			// <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_LEFT: 
				if (x > 0) mvaddch(y, x--, EMPTY);  // <-------------- TROVARE EQUAZIONE BORDI
				break;
			case KEY_RIGHT:
				if (x < COLS - 1)	mvaddch(y, x++, EMPTY); // <-------------- TROVARE EQUAZIONE BORDI
				break;
			}
			refresh();
		} 
		while (direction != 27);		// fino a che l'utente non spinge il tasto esc il gioco continua
	}