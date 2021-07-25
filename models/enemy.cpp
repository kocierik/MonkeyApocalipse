#include "enemy.hpp"
Enemy::Enemy() : Character::Character() {}
Enemy::Enemy(int x, int y, char skin, int damage, int life, int numberLife)
    : Character::Character(x, y, skin, damage, life, numberLife) {
  this->x = x;
  this->y = y;
  this->skin = skin;
  this->damage = damage;
  this->life = life;
  this->numberLife = numberLife;
}