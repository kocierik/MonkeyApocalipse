#include "gun.hpp"

Gun::Gun() {}
Gun::Gun(char in_bulletSkin, int in_damage, int in_ammo) {
  this->bulletSkin = in_bulletSkin;
  this->damage = in_damage;
  this->ammo = in_ammo;
}

char Gun::getBulletSkin() { return this->bulletSkin; }

int Gun::getDamage() { return this->damage; }
void Gun::setDamage(int in_damage) { this->damage = in_damage; }
void Gun::increaseDamage(int plusDMG) { this->damage += plusDMG; }
void Gun::decreaseDamage(int lessDMG) { this->damage -= lessDMG; }

int Gun::getAmmo() { return this->ammo; }
void Gun::setAmmo(int in_ammo) { this->ammo = in_ammo; }
void Gun::increaseAmmo(int plusAmmo) { this->ammo += plusAmmo; }
void Gun::decreaseAmmo(int lessAmmo) { this->ammo -= lessAmmo; }
