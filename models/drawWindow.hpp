#include "character.hpp"
#include "coordinate.hpp"
#ifndef ENEMY
#define ENEMY
#include "enemy.hpp"
#endif

struct Room {
  pPosition mountainList;
  pPosition bonusList;
  Room *next;
  Room *prev;
};
typedef Room *pRoom;

class DrawWindow {
 public:
  DrawWindow();
  void printCharacter(int x, int y, char c);
  void drawRect(int startX, int startY, int rightWidth, int bottomHeight,
                bool noEnemy, int maxRoom, bool isScreenBound, pRoom listRoom);
  void drawStats(int startX, int startY, int rightWidth, int bottomHeight,
                 int pointsOnScreen, Character character, bool noEnemy,
                 int powerUp, int bananas, int maxRoom, pRoom roomList);
  void drawLeaderboardOnScreen();
  void drawMenu();

  void printCommand(int *cnt);
  void printCredits();
  void credits(int direction);
  
  void printHowToPlay();
  void HowToPlay(int direction);
  
  void printLoseScreen(float finalScore);
  void loseScreen(int direction, float finalScore);
  
  void printSplashScreen();
  void splashScreen(int direction);
  
  void printLeaderboardScreen();
  void leaderboardScreen(int direction);
  
  int lengthEnemyList(pEnemyList enemyList);
  int lengthListRoom(pRoom roomList);

  void printCharacterStats(pEnemyList enemyList, pEnemyList specialEnemyList, pEnemyList bossEnemyList, Character character);
  void printEnemy(pEnemyList enemyList, DrawWindow drawWindow);

  void showBonusOnScreen(bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
                         bool &bonusPicked, int bonusType, int &bonusTime,
                         bool &immortalitycheck, int &immortalityTime);

  pRoom changeRoom(Character &character, Character &character2, int &normalEnemyCount, int &specialEnemyCount, int &bossEnemyCount,
                   pEnemyList &normalEnemyList, pEnemyList &specialEnemyList, pEnemyList &bossEnemyList,
                   pPosition &mountainList, pPosition &bonusList, pRoom roomList, int &maxRoom);

  Position generateRandomPosition(int startRange, int endRange);
  pPosition generateMountain(pPosition mountainList, int &mountainCount);
  pPosition generateBonus(pPosition bonusList, int &bonusCount);

  void moveEnemyMultiplayer(pEnemyList enemyList, Character character, Character character2, DrawWindow drawWindow,
                 long points);
  void moveEnemySinglePlayer(pEnemyList enemyList, Character character, DrawWindow drawWindow,
                 long points);
  
  void printMountain(pPosition mountainList);
  void printBonus(pPosition bonusList);

  pRoom saveRoom(pPosition mountainList, pPosition bonusList, pRoom roomList);
  void saveRecord(float finalScore, char name[]);
  
  bool ghostNameRecognizer(char name[]);
};
