#include <iostream>
#include <ncurses.h>
#include "character.h"
#define SKIN '&'
#define EMPTY ' '

	Character::Character(int x, int y){
		this->direction = 0;
		this->x = x;
		this->y = y;
	}

	int Character::getX(){
		return this->x;
	}
	int Character::getY(){
		return this->y;
	}

	int Character::moveCharacter(){	// 48 18
			mvaddch(y, x, SKIN);	
			move(y,x);
			refresh();	
			direction = getch();
			switch (direction) {		
				case KEY_UP:
					if (y > 0 && y > 11){ mvaddch(y--, x, EMPTY);}	
					break;
				case KEY_DOWN:
					if (y < LINES - 1 && y < 25 ){ mvaddch(y++, x, EMPTY);}		
					break;
				case KEY_LEFT: 
					if (x > 0 && x > 45){ mvaddch(y, x--, EMPTY);}  
					break;
				case KEY_RIGHT:
					if (x < COLS - 1 && x < 122){ mvaddch(y, x++, EMPTY);}
					break;
			}
			refresh();
	return direction;
	}