

#ifndef ENEMY
#define ENEMY
#include "enemy.hpp"
#endif
#include "coordinate.hpp"
class EngineGame {
 protected:
  int frameGameX;
  int frameGameY;
  int height;
  int widht;
  bool quit;
  bool pause;
  Pbullet shoots;
  Pbullet shootsEnemys;
  bool isEnemyShoots;
  int whileCount;
  int whileCountEnemy;
 public:
  EngineGame(int frameGameX, int frameGameY, int heigth, int width);
  void baseCommand();
  void moveCharacter(Character &character, int direction);
  bool isEmpty(int x, int y);
  Pbullet createBullet(int x, int y, Pbullet &shoots);
  void shootBullet();
  Position randomPosition(int startRange, int endRange);
  void engine(Character character, DrawWindow printer);
  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
  void runGame(Character character, DrawWindow drawWindow, int direction);
  pEnemyList generateEnemy(int *monsterCount, char character, int damage,
                           int life, pEnemyList list);
  void checkShootEnemyCollision(pEnemyList enemys, Character &character, Pbullet &shoots, int isEnemy);
  void checkEnemyCollision(Character &character, pEnemyList enemyList);
  pEnemyList destroyEnemy(pEnemyList list, Enemy enemy);
  void destroyBullet(Pbullet &shoots,int isEnemy);
  void printList(pEnemyList list, Character character);
  int lenghtList(pEnemyList list);
  void getInput(int &direction);
  void isPause(int &direction, bool &pause);
  void increaseCount(int &whileCount, long &points);
  void checkDeath(bool &pause, Character &character);
  void enemyShootBullets(pEnemyList listEnemy);
  void shootEnemyBullet();
};
