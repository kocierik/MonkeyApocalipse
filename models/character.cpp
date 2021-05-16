#include "character.hpp"

#include <ncurses.h>
Character::Character(int x, int y, char character, int damage, int life) {
  this->direction = 0;
  this->x = x;
  this->y = y;
  this->character = character;
  this->life = life;
  this->Nbullet = 0;
  this->damage = damage;
}
int Character::getX() { return this->x; }
int Character::getY() { return this->y; }
int Character::getLife() { return this->life; }
int Character::getDamage() { return this->damage; }
char Character::getCharacter() { return this->character; }
void Character::directionUp() { this->y--; }
void Character::directionDown() { this->y++; }
void Character::directionRight() { this->x++; }
void Character::directionLeft() { this->x--; }
