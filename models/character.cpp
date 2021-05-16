#include "character.hpp"

#include <ncurses.h>
Character::Character(int x, int y, char character) {
  this->direction = 0;
  this->x = x;
  this->y = y;
  this->character = character;
  this->life = 100;
  this->Nbullet = 0;
}
int Character::getX() { return this->x; }
int Character::getY() { return this->y; }
char Character::getCharacter() { return this->character; }
void Character::directionUp() { this->y--; }
void Character::directionDown() { this->y++; }
void Character::directionRight() { this->x++; }
void Character::directionLeft() { this->x--; }
