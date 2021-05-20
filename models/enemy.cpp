#include "enemy.hpp"

Enemy::Enemy(int x, int y, char character, bool isEnemy, int damage, int life) : Character::Character(x, y, character, damage, life){
    this->x = x;
    this->y = y;
    this->character = character;
    this->isEnemy = true;
    this->damage = damage;
    this->life = life;
}
