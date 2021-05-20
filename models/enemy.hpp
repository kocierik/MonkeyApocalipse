#ifndef CHARACTER
#define CHARACTER
#include "character.hpp"
#endif
class Enemy : public Character {
public:
    Enemy(int x, int y, char character, bool isEnemy, int damage, int life);
  };

struct EnemyList{
  Enemy enemy;
  EnemyList *next;
};typedef EnemyList* pEnemyList;