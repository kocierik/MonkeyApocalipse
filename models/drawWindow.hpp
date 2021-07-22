#include "character.hpp"
#include "coordinate.hpp"
#ifndef ENEMY
#define ENEMY
#include "enemy.hpp"
#endif

struct Room {
  pPosition listMountain;
  Room *next;
  Room *prec;
};
typedef Room *pRoom;

class DrawWindow {
 public:
  DrawWindow();
  void printCharacter(int x, int y, char c);
  void drawRect(int startX, int startY, int width, int heigth,
                pEnemyList enemyList, int round, bool isScreenBound);
  void drawMenu();
  void printCommand(int *cnt);
  void printCredits();
  void credits(int direction);
  void printHowToPlay();
  void HowToPlay(int direction);
  void drawStats(int startX, int startY, int width, int heigth, long *points,
                 Character character, pEnemyList enemyList, int powerUp);
  int lenghtList(pEnemyList list);
  int lenghtRoom(pRoom list);
  void printCharacterStats(pEnemyList list, Character character);
  void printEnemy(pEnemyList list, DrawWindow drawWindow);
  pRoom changeRoom(Character &character, int &monsterCount, int &round,
                   pEnemyList &list, pPosition &listMountain, pRoom listRoom,
                   int &maxRound);
  void moveEnemy(pEnemyList list, Character character, DrawWindow drawWindow,
                 long points);
  Position randomPosition(int startRange, int endRange);
  pPosition generateMountain(pPosition list);
  void printMountain(pPosition list);
  pRoom saveRoom(pPosition listMountain, pRoom listRoom);
};
