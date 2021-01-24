#include "bullet.h"
#define SKIN 'o'
#define EMPTY ' '
#define SPEED 0.01
#include <thread>

  SBullet* createBullet(float x, float y, float speed){
    SBullet *bullet = new SBullet();
    bullet->xPos = x;
    bullet->yPos = y;                         // SEMPLICE DEFINIZIONE DEL BULLET
    return bullet;
  }

  void updateB(SBullet *pBullet){
    while(pBullet->xPos < 122){
      mvaddch(pBullet->yPos, pBullet->xPos-1, EMPTY);       // AGGIORNO LA POSIZONE DEL BULLET
      mvaddch(pBullet->yPos, pBullet->xPos, SKIN);          // SVOLGENDO TUTTO MOLTO VELOCEMENTE NOI VEDIAMO
      pBullet->xPos +=SPEED;
      move(pBullet->yPos,pBullet->xPos);                    // IL BULLET SEMPRE INFONDO 
      refresh();	
    }             
  }
  void destroyBullet( SBullet *pBullet){
	  delete pBullet;                             // DISTRUGGE UN BULLET
    pBullet = NULL;                             // FUNZIONE FONDAMENTALE CHE PUO COSTARE PUNTI ALLA VALUTAZIONE
  }                                             // SE NON USATA