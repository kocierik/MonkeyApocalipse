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
  Pbullet playerBullets;//playerBullets;
  Pbullet normalEnemyBullets;
  Pbullet specialEnemyBullets;
  Pbullet bossEnemyBullets;
  bool isEnemyShoots;
  int whileCount;
  int whileCountEnemy;
    
 public:
  EngineGame(int frameGameX, int frameGameY, int heigth, int width);
  void printList(pPosition list);
  void baseCommand();
  Pbullet generateBullets(Character character, bool isPlayerBullet,
                       bool moveFoward, Pbullet &shoots);
  void enemyShootBullets(pEnemyList enemyList, Character character);

  void shootPlayerBullet(Gun playerGun);
  void shootEnemyBullet();

  void destroyBullet(Pbullet &shoots);
  pEnemyList destroyEnemy(pEnemyList list, Enemy enemy);
  pPosition deletePosition(
      pPosition list,
      pPosition bonus);  // Funzione per eliminare bonus e montagne

  void checkEnemyCollision(Character &character, pEnemyList enemyList);
  void checkShootEnemyCollision(pEnemyList enemys, Character &character,
                                Pbullet &shoots, int &pointOnScreen,
                                bool immortalityCheck);
  bool isEmpty(int x, int y);
  bool isBonus(int x, int y);
  bool isMountain(int x, int y);
  bool isEnemy(int x, int y);

  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
  void moveCharacter(DrawWindow drawWindow, Character &character, int direction,
                     pRoom &roomList, pEnemyList normalEnemyList, int round,
                     int &pointsOnScreen, int &bananas, int &powerUpDMG,
                     bool &bonusPicked, int &bonustype, int &bonusTime,
                     bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
                     bool &immortalityCheck, int &immortalityTime);

  pEnemyList generateEnemy(int *enemyCount, int type, pEnemyList list, int &round,
                                 DrawWindow drawWindow);

  pPosition getBonus(DrawWindow drawWindow, int x, int y, pPosition bonusList,
                     pEnemyList &enemyList, int round, int &pointsOnScreen,
                     Character &character, int &bonusType, bool &immortalitycheck, int &immortalityTime);

  void checkDeath(bool &pause, Character &character);

  void checkMountainDamage(Pbullet bulletList, pPosition &mountainList);

  void engine(Character character, DrawWindow printer);
  void increaseCount(int &whileCount, long &points, pEnemyList enemyList);

  void getInput(int &direction);
  void isPause(int &direction, bool &pause);
  void runGame(Character character, DrawWindow drawWindow, int direction);

  void money(int &bananas, pEnemyList enemyList, int maxRound, int &roundPayed,
             Character &character);
  void increasePointOnScreen(int &pointOnScreen, int pointsAdded);
  void showBonusOnScreen(bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
                         bool &bonusPicked, int bonusType, int &bonusTime,
                         bool &immortalitycheck, int &immortalityTime);
  void gorillaPunch(int direction, Character &character, pEnemyList enemyList,
                    int &pointOnScreen);
};
