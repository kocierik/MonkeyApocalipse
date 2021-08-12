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
  Pbullet createBullet(int x, int y, bool moveFoward, Pbullet &shoots, Gun gun);
  void enemyShootBullets(pEnemyList listEnemy, bool fowardEnemyShoot);

  void shootPlayerBullet(Gun playerGun);
  void shootEnemyBullet();

  void destroyBullet(Pbullet &shoots, int isEnemy);
  pEnemyList destroyEnemy(pEnemyList list, Enemy enemy);
  pPosition deletePosition(pPosition list, pPosition bonus);

  void checkEnemyCollision(Character &character, pEnemyList enemyList);
  void checkShootEnemyCollision(pEnemyList enemys, Character &character,
                                Pbullet &shoots, int isEnemy, float &pointOnScreen);
  bool isEmpty(int x, int y);
  bool isBonus(int x, int y);
  bool isMountain(int x, int y);

  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
  void moveCharacter(DrawWindow drawWindow, Character &character, int direction,
                     pRoom &roomList, pEnemyList enemyList, int round,
                     float &pointsOnScreen, int &bananas, int &powerUpDMG,
                     bool &bonusPicked, int &bonustype, int &bonusTime,
                     bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
                     bool &immortalityCheck, bool &fowardPlayerShoot);

  pEnemyList generateEnemy(int *monsterCount, char skin, Gun gun, int life,
                           pEnemyList list, int &round, DrawWindow drawWindow);
  
  
  
  pPosition getBonus(DrawWindow drawWindow, int x, int y, pPosition bonusList,
                     pEnemyList &enemyList, int round, float &pointsOnScreen,
                     Character &character, int &bonusType);

  void checkDeath(bool &pause, Character &character);

  void checkMountainDamage(Pbullet bulletList, bool isPlayer,
                           pPosition &mountainList, int damage);

  void engine(Character character, DrawWindow printer);
  void increaseCount(int &whileCount, long &points, pEnemyList enemyList);

  void getInput(int &direction);
  void isPause(int &direction, bool &pause);
  void runGame(Character character, DrawWindow drawWindow, int direction);

  void money(int &bananas, pEnemyList enemyList, int maxRound, int &roundPayed,
             Character &character);
  void increasePointOnScreen(float &pointOnScreen, int pointsAdded);
  void showBonusOnScreen(bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
                 bool &bonusPicked, int bonusType, int &bonusTime, bool &immortalitycheck, int &immortalityTime, Character &character);
  void gorillaPunch(int direction, Character &character, pEnemyList enemyList, float &pointOnScreen);
};
