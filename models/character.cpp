#include "character.hpp"

#include <ncurses.h>
Character::Character(int x, int y, char character, int damage, int life, int numberLife) {
  this->direction = 0;
  this->x = x;
  this->y = y;
  this->character = character;
  this->life = life;
  this->Nbullet = 0;
  this->damage = damage;
  this->numberLife = numberLife;
}
void Character::setX(int x) { this->x = x; }
int Character::getX() { return this->x; }
void Character::setY(int y) { this->y = y; }
int Character::getY() { return this->y; }
int Character::getLife() { return this->life; }
void Character::setLife(int life) { this->life = life; }
int Character::getNumberLife() { return this->numberLife; }
void Character::setNumberLife(int numberLife) { this->numberLife = numberLife; }
void Character::decreaseLife(int life) { this->life -= life; }
int Character::getDamage() { return this->damage; }
void Character::setDamage(int damage) { this->damage = damage; }
char Character::getCharacter() { return this->character; }
void Character::setCharacter(char character) { this->character = character; }
void Character::directionUp() { this->y--; }
void Character::directionDown() { this->y++; }
void Character::directionRight() { this->x++; }
void Character::directionLeft() { this->x--; }
