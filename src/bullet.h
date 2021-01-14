#include <iostream>
#include <ncurses.h>
using namespace std;

class Bullet{
  protected:
    int x;
    int y;
    double speed;
  public:
    Bullet(int x, int y);
    int getX();
    int getY();
    int createBullet(int x, int y);
    void updateBullet();
};