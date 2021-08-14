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
void Character::setTotalAmmo(int ammo) { this->gun.setTotalAmmo(ammo); }
int Character::getTotalAmmo() { return this->gun.getTotalAmmo(); }

void Character::increaseTotalAmmo(int plusAmmo) {
  this->gun.setTotalAmmo(gun.getTotalAmmo() + plusAmmo);
}
void Character::decreaseTotalAmmo(int lessAmmo) {
  this->gun.setTotalAmmo(gun.getTotalAmmo() - lessAmmo);
}
void Character::increaseMagazineAmmo(int plusAmmo) {
  this->gun.setMagazineAmmo(gun.getMagazineAmmo() + plusAmmo);
}
void Character::decreaseMagazineAmmo(int lessAmmo) {
  this->gun.setMagazineAmmo(gun.getMagazineAmmo() - lessAmmo);
}
void Character::reload() {
  this->gun.setMagazineAmmo(gun.getMagazineCapacity());
}
