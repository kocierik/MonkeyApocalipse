#ifndef CHARACTER
#define CHARACTER
#include "character.hpp"
#endif
class Enemy : public Character {
 public:
  Enemy();
  Enemy(int x, int y, char character, int damage, int life, int numberLife);
};

struct EnemyList {
  Enemy enemy;
  EnemyList* next;
};
typedef EnemyList* pEnemyList;