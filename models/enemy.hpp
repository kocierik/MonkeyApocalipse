#ifndef CHARACTER
#define CHARACTER
#include "character.hpp"
#endif
class Enemy : public Character {
 protected:
  int deathScore;

 public:
  Enemy();
  Enemy(int x, int y, char skin, int life, int numberLife, Gun gun,
        int deathScore);
  int getDeathScore();
  void setDeathScore(int deathScore);
};

struct EnemyList {
  Enemy enemy;
  EnemyList* next;
};
typedef EnemyList* pEnemyList;