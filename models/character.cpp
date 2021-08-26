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
Character::Character(int x, int y, char skin, int life, int numberLife) {
  this->direction = 0;
  this->x = x;
  this->y = y;
  this->skin = skin;
  this->life = life;
  this->Nbullet = 0;
  this->numberLife = numberLife;
  Gun tmpGun(' ', 0, 0, 0);
  this->gun = tmpGun;
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

void Character::increaseLife(int life) { this->life += life; if(this->life > 100) this->life = 100;}
void Character::decreaseLife(int life) { this->life -= life; }
int Character::getLife() { return this->life; }
void Character::setLife(int life) { this->life = life; }
int Character::getNumberLife() { return this->numberLife; }
void Character::setNumberLife(int numberLife) { this->numberLife = numberLife; }

Gun Character::getGun() { return this->gun; }
void Character::setGun(Gun in_gun) { this->gun = in_gun; }
void Character::setGunDamage(int damage) {
  this->gun.setDamage(damage);
}
void Character::increaseDamageGun(int damage) {
  this->gun.increaseDamage(damage);
}
void Character::setTotalAmmo(int ammo) { this->gun.setTotalAmmo(ammo); }

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
  if (gun.getTotalAmmo() >= 10) {
    int magazineBeforReload = this->gun.getMagazineAmmo();
    this->gun.setMagazineAmmo(this->gun.getMagazineCapacity());
    this->gun.decreaseTotalAmmo(this->gun.getMagazineCapacity() -
                                magazineBeforReload);
  } else if (gun.getTotalAmmo() < 10) {
    this->gun.setMagazineAmmo(this->gun.getTotalAmmo());
    this->gun.setTotalAmmo(0);
  }
}
