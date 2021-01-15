#include <ncurses.h>

struct SBullet{
	float xPos, yPos, speed;
};

SBullet* createBullet(float x, float y, float speed);
void updateB(SBullet *pBUllet);
void destroyBullet(SBullet *pBullet);