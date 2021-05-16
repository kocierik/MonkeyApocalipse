#include "enemy.hpp"
#include <ncurses.h>
Enemy::Enemy() : Character::Character(x, y, character){
    this->x = x;
    this->y = y;
    this->character = character;
  }
