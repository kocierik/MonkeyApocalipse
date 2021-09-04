#include "enemy.hpp"

Enemy::Enemy() : Character::Character() {}
Enemy::Enemy(int x, int y, char skin, int life, int numberLife, Gun gun,
             int deathScore)
    : Character::Character(x, y, skin, life, numberLife, gun) {
  this->deathScore = deathScore;
}

int Enemy::getDeathScore() { return this->deathScore; }
void Enemy::setDeathScore(int deathscore) { this->deathScore = deathscore; }