#include "player.hpp"
Player::Player (int x, int y, char skin, int life, int numberLife, Gun gun)
    : Character::Character(x, y, skin, life, numberLife, gun) {
  this->x = x;
  this->y = y;
  this->skin = skin;
  this->life = life;
  this->numberLife = numberLife;
  this->gun= gun;
}
