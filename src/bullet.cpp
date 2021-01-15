#include "bullet.h"
#define SKIN 'o'
#define EMPTY ' '
#define SPEED 1

  SBullet* createBullet(float x, float y, float speed){
    SBullet *bullet = new SBullet();
    bullet->xPos = x;
    bullet->yPos = y;
    return bullet;
  }
  void updateB(SBullet *pBullet){
    for (int i = pBullet->xPos; i < 122; i++){
      mvaddch(pBullet->yPos, i-1, EMPTY);
      mvaddch(pBullet->yPos, i, SKIN);
      move(pBullet->yPos,i);
    }
    refresh();	
  }
  void destroyBullet( SBullet *pBullet){
	delete pBullet;
  pBullet = NULL;
}