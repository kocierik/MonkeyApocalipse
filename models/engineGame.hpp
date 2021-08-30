#ifndef ENEMY
#define ENEMY
#include "enemy.hpp"
#endif

class EngineGame {
 protected:
  int frameGameX;
  int frameGameY;
  int topHeigth;
  int bottomHeigth;
  int leftWidth;
  int rightWidth;
  bool quit;
  bool pause;
  Pbullet playerBullets;
  Pbullet normalEnemyBullets;
  Pbullet specialEnemyBullets;
  Pbullet bossEnemyBullets;
  int whileCount;
  int whileCountEnemy;

 public:
  EngineGame(int frameGameX, int frameGameY, int topHeigth, int bottomHeigt, int leftWidth, int rightWidth);
  void printList(pPosition positionList);
  void baseCommand();
  Pbullet generateBullets(Character character, bool isPlayerBullet,
                          bool moveFoward, Pbullet &bulletList);
  void generateEnemyBullets(pEnemyList enemyList, Pbullet &enemyBulletList, Character character);

  void moveBullets(Pbullet bulletList);

  void destroyBullet(Pbullet &bulletList, int xP);
  pEnemyList destroyEnemy(pEnemyList enemyList, Enemy enemy);
  pPosition deletePosition(pPosition positionList, pPosition bonus);

  void checkEnemyCollision(Character &character, pEnemyList enemyList);
  void checkBulletCollision(Pbullet &bulletList, Character &character,
                            pEnemyList enemyList, int &pointOnScreen,
                            bool immortalityCheck);

  bool isEmpty(int x, int y);
  bool isBonus(int x, int y);
  bool isMountain(int x, int y);
  bool isEnemy(int x, int y);
  bool isPlayer(int x, int y);
  bool isBullet(int x, int y);
  bool isEnemyBullet(int x, int y);
  bool isPlayerBullet(int x, int y);

  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
  void moveCharacter(DrawWindow drawWindow, Character &character, int direction,
                     pRoom &roomList, pEnemyList normalEnemyList, int &pointsOnScreen,
                     int &bananas, int &powerUpDMG, bool &bonusPicked, int &bonustype,
                     int &bonusTime, bool &upgradeBuyed, int &upgradeType,
                     int &upgradeTime, bool &immortalityCheck, int &immortalityTime,
                     bool &toTheRight, int upgradeCost);

  pEnemyList generateEnemy(int *enemyCount, int type, pEnemyList enemyList,
                           DrawWindow drawWindow);

  pPosition getBonus(DrawWindow drawWindow, int x, int y, pPosition bonusList,
                     pEnemyList &enemyList, int &pointsOnScreen, Character &character,
                     int &bonusType, bool &immortalitycheck, int &immortalityTime);

  bool checkNoEnemy(DrawWindow drawWindow, pEnemyList enemyList1, pEnemyList enemyList2, pEnemyList enemyList3);
  void checkEnemyGeneration(pRoom &room, int maxRoom, int &specialEnemycount, int &bossEnemyCount);
  void checkDeath(bool &pause, Character &character);
  void checkMountainDamage(Pbullet bulletList, pPosition &mountainList);

  void engine(Character character, DrawWindow printer);
  void increaseCount(long &points);

  void getInput(int &direction);
  void isPause(int &direction, bool &pause);
  void runGame(Character character, DrawWindow drawWindow, int direction);

  void money(int &bananas, bool noEnemy, int maxRoom, int &roundPayed,
             Character &character, int upgradeCost);
  void increasePointOnScreen(int &pointOnScreen, int pointsAdded);
  void gorillaPunch(int direction, Character &character, pEnemyList enemyList,
                    int &pointOnScreen, bool toTheRight);
};
