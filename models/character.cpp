#include <ncurses.h>
#include "character.hpp"
	Character::Character(int x, int y){
		this->direction = 0;
		this->x = x;				
		this->y = y;
		this->character = 'c';
		this->life = 100;
		this->Nbullet = 0;
	}
	int Character::getX(){
		return this->x;			
	}
	int Character::getY(){
		return this->y;
	}

	void Character::directionUp(){
		this->y--;
	}
	void Character::directionDown(){
		this->y++;
	}
	void Character::directionRight(){
		this->x++;
	}
	void Character::directionLeft(){
		this->x--;
	}
