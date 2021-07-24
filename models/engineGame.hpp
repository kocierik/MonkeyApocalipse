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
  void printList(pPosition list);
  void baseCommand();
  Pbullet createBullet(int x, int y, Pbullet &shoots);
  void enemyShootBullets(pEnemyList listEnemy);
  void shootBullet();
  void shootEnemyBullet();

  void destroyBullet(Pbullet &shoots, int isEnemy);
  pEnemyList destroyEnemy  (pEnemyList list, Enemy enemy);
  pPosition deletePosition (pPosition list, pPosition bonus);


  void checkEnemyCollision(Character &character, pEnemyList enemyList);
  void checkShootEnemyCollision(pEnemyList enemys, Character &character,
                                Pbullet &shoots, int isEnemy);
  bool isEmpty    (int x, int y);
  bool isBonus    (int x, int y);
  bool isMountain (int x, int y);

  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
  void moveCharacter (DrawWindow drawWindow, Character &character, int direction,
                      pPosition &bonusList, pEnemyList enemyList, int round,
                      long &points, int &bananas, int &powerUpDMG);

  pPosition generateBonus (DrawWindow drawWindow, int *bonusCount, pPosition bonusList);
  pEnemyList generateEnemy(int *monsterCount, char skin, int damage,
                           int life, pEnemyList list, int &round, DrawWindow drawWindow);
  pPosition getBonus (DrawWindow drawWindow, int x, int y, pPosition bonusList,
                      pEnemyList enemyList, int round, long &points, Character &character);

  void checkDeath(bool &pause, Character &character);

  void checkMountainDamage (Pbullet bulletList, int isEnemy, pPosition &mountainList, int damage);

  void engine(Character character, DrawWindow printer);
  void increaseCount(int &whileCount, long &points, pEnemyList enemyList);

  void getInput(int &direction);
  void isPause(int &direction, bool &pause);
  void runGame(Character character, DrawWindow drawWindow, int direction);

  void money(int &bananas, pEnemyList enemyList, int maxRound, int &roundPayed);
};
