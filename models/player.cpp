#include "player.hpp"
Player::Player(int x, int y, char character) : Character::Character(x, y, character) {
  this->x = x;
  this->y = y;
  this->character = character;
}
