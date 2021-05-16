#include "enemy.hpp"
#include <ncurses.h>
Enemy::Enemy() : Character::Character(x, y, character, damage, life){
    this->x = x;
    this->y = y;
    this->character = character;
    this->isEnemy = true;
    this->damage = damage;
    this->life = life;
  }
