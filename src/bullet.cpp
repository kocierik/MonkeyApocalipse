#include "bullet.h"
#define SKIN 'o'
#define EMPTY ' '
#define SPEED 1

  SBullet* createBullet(float x, float y, float speed){
    SBullet *bullet = new SBullet();
    bullet->xPos = x;
    bullet->yPos = y;                         // SEMPLICE DEFINIZIONE DEL BULLET
    return bullet;
  }
  void updateB(SBullet *pBullet){
    for (int i = pBullet->xPos; i < 122; i++){
      mvaddch(pBullet->yPos, i-1, EMPTY);       // AGGIORNO LA POSIZONE DEL BULLET
      mvaddch(pBullet->yPos, i, SKIN);          // SVOLGENDO TUTTO MOLTO VELOCEMENTE NOI VEDIAMO
      move(pBullet->yPos,i);                    // IL BULLET SEMPRE INFONDO 
    }                                           // DA FIXARE IL MOVIMENTO PIU LENTO (GUARDARE I THRED)
    refresh();	
  }
  void destroyBullet( SBullet *pBullet){
	  delete pBullet;                             // DISTRUGGE UN BULLET
    pBullet = NULL;                             // FUNZIONE FONDAMENTALE CHE PUO COSTARE PUNTI ALLA VALUTAZIONE
  }                                             // SE NON USATA