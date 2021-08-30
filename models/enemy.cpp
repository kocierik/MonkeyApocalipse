#include "enemy.hpp"

Enemy::Enemy() : Character::Character() {}
Enemy::Enemy(int x, int y, char skin, int life, int numberLife, Gun gun)
    : Character::Character(x, y, skin, life, numberLife, gun) {
}