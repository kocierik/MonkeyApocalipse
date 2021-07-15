

#include "enemy.hpp"
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
  bool isShoot;
  int whileCount;

 public:
  EngineGame(int frameGameX, int frameGameY, int heigth, int width);
  void baseCommand();
  void moveCharacter(Character &character, int direction);
  bool isEmpty(int x, int y);
  Pbullet createBullet(int x, int y, int getLastMove);
  void shootBullet();
  Pbullet destroyBullet();
  Position randomPosition(int startRange, int endRange);
  void engine(Character character, DrawWindow printer);
  void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
  void runGame(Character character, DrawWindow drawWindow, int direction);
  pEnemyList generateEnemy(int *count, int x, int y, char character, int damage, int life, pEnemyList list);
  void printEnemy(pEnemyList list, DrawWindow drawWindow);
  void shootCommand(Character &character, int direction);
};
