#include "character.hpp"

#include <ncurses.h>
Character::Character(int x, int y, char skin, int life, int numberLife,
                     Gun gun) {
  this->direction = 0;
  this->x = x;
  this->y = y;
  this->skin = skin;
  this->life = life;
  this->Nbullet = 0;
  this->numberLife = numberLife;
  this->gun = gun;
}

Character::Character() {}

void Character::setX(int x) { this->x = x; }
int Character::getX() { return this->x; }
void Character::setY(int y) { this->y = y; }
int Character::getY() { return this->y; }

void Character::directionUp() { this->y--; }
void Character::directionDown() { this->y++; }
void Character::directionRight() { this->x++; }
void Character::directionLeft() { this->x--; }

char Character::getSkin() { return this->skin; }
void Character::setSkin(char skin) { this->skin = skin; }

void Character::increaseLife(int life) { this->life += life; }
void Character::decreaseLife(int life) { this->life -= life; }
int Character::getLife() { return this->life; }
void Character::setLife(int life) { this->life = life; }
int Character::getNumberLife() { return this->numberLife; }
void Character::setNumberLife(int numberLife) { this->numberLife = numberLife; }

Gun Character::getGun() { return this->gun; }
void Character::setGun(Gun in_gun) { this->gun = in_gun; }
void Character::increaseDamageGun(int damage) { this->gun.increaseDamage(damage); }
void Character::setAmmo(int ammo) { this->gun.setAmmo(ammo); }
int Character::getAmmo() { return this->gun.getAmmo(); }
void Character::decreaseAmmo(int lessAmmo) {
  this->gun.setAmmo(gun.getAmmo() - lessAmmo);
}
void Character::increaseAmmo(int plusAmmo) {
  this->gun.setAmmo(gun.getAmmo() + plusAmmo);
}
