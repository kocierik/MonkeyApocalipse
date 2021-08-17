#include "gun.hpp"

Gun::Gun() {}
Gun::Gun(char in_bulletSkin, int in_damage, int in_totalAmmo,
         int in_magazineCapacity) {
  this->bulletSkin = in_bulletSkin;
  this->damage = in_damage;
  this->totalAmmo = in_totalAmmo;
  this->magazineAmmo = in_magazineCapacity;
  this->magazineCapacity = in_magazineCapacity;
}

char Gun::getBulletSkin() { return this->bulletSkin; }
void Gun::setBulletSkin(char newSkin) { this->bulletSkin = newSkin; }

int Gun::getDamage() { return this->damage; }
void Gun::setDamage(int in_damage) { this->damage = in_damage; }
void Gun::increaseDamage(int plusDMG) { this->damage += plusDMG; }
void Gun::decreaseDamage(int lessDMG) { this->damage -= lessDMG; }

int Gun::getMagazineAmmo() { return this->magazineAmmo; }
void Gun::setMagazineAmmo(int in_magazineAmmo) {
  this->magazineAmmo = in_magazineAmmo;
}
void Gun::increaseMagazineAmmo(int plusAmmo) { this->magazineAmmo += plusAmmo; }
void Gun::decreaseMagazineAmmo(int lessAmmo) { this->magazineAmmo -= lessAmmo; }

void Gun::reloadMagazine() {
  if (this->magazineAmmo >= 0 &&
      this->magazineAmmo <
          this->magazineCapacity) {  // Se ilcaricatore non è pieno
    if (this->totalAmmo <= this->magazineCapacity) {
      this->magazineAmmo = this->totalAmmo;
      this->totalAmmo = 0;
    } else if (this->totalAmmo > this->magazineCapacity) {
      this->magazineAmmo = this->magazineCapacity;
      this->totalAmmo -= this->magazineCapacity;
    }
  }
}
int Gun::getMagazineCapacity() { return this->magazineCapacity; }
void Gun::setMagazineCapacity(int in_magazineCapacity) {
  this->magazineCapacity = in_magazineCapacity;
}

int Gun::getTotalAmmo() { return this->totalAmmo; }
void Gun::setTotalAmmo(int in_ammo) { this->totalAmmo = in_ammo; }
void Gun::increaseTotalAmmo(int plusAmmo) { this->totalAmmo += plusAmmo; }
void Gun::decreaseTotalAmmo(int lessAmmo) { this->totalAmmo -= lessAmmo; }
