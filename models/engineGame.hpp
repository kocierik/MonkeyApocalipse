

#ifndef ENEMY
#define ENEMY
#include "enemy.hpp"
#endif

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
  void printList(pEnemyList list, Character character);

  void baseCommand();
  Pbullet createBullet(int x, int y, Pbullet &shoots);
  void enemyShootBullets(pEnemyList listEnemy);
  void shootBullet();
  void shootEnemyBullet();

  void destroyBullet(Pbullet &shoots, int isEnemy);
  pEnemyList destroyEnemy(pEnemyList list, Enemy enemy);
  void checkEnemyCollision(Character &character, pEnemyList enemyList);
  void checkShootEnemyCollision(pEnemyList enemys, Character &character,
                                Pbullet &shoots, int isEnemy);
  bool isEmpty(int x, int y);
  bool isBonus (int x, int y);

  void moveCharacter(Character &character, int direction, pPosition bonusList, long &points);
  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);

  pEnemyList generateEnemy(int *monsterCount, char character, int damage,
                           int life, pEnemyList list, int &round, DrawWindow drawWindow);
  pPosition generateOneBonus (DrawWindow drawWindow, int *bonusCount, pPosition list);
  void getBonus (int x, int y, pPosition bonusList, long &points);

  void checkDeath(bool &pause, Character &character);
  void engine(Character character, DrawWindow printer);
  void increaseCount(int &whileCount, long &points, pEnemyList enemyList);

  void getInput(int &direction);
  void isPause(int &direction, bool &pause);
  void runGame(Character character, DrawWindow drawWindow, int direction);

};
