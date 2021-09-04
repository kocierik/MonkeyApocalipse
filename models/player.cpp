#include "player.hpp"
Player::Player(int x, int y, char skin, int life, int numberLife, Gun gun)
    : Character::Character(x, y, skin, life, numberLife, gun) {}
Player::Player(int x, int y, char skin, int life, int numberLife)
    : Character::Character(x, y, skin, life, numberLife) {}
