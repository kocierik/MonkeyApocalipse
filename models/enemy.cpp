#include "enemy.hpp"

Enemy::Enemy() : Character::Character() {}
Enemy::Enemy(int x, int y, char skin, int life, int numberLife, Gun gun)
    //: Character::Character(x, y, skin, damage, life, numberLife) {
    : Character::Character(x, y, skin, life, numberLife, gun) {
    //: Character::Character(x, y, skin, life, numberLife) {
  this->x = x;
  this->y = y;
  this->skin = skin;
  this->life = life;
  this->numberLife = numberLife;
}