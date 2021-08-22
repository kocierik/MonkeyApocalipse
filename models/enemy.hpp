#ifndef CHARACTER
#define CHARACTER
#include "character.hpp"
#endif
class Enemy : public Character {
 public:
  Enemy();
  Enemy(int x, int y, char skin, int life, int numberLife, Gun gun, int typeName);
};

struct EnemyList {
  Enemy enemy;
  EnemyList* next;
};
typedef EnemyList* pEnemyList;