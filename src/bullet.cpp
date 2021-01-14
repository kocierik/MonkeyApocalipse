#include <iostream>
#include <ncurses.h>
#include "bullet.h"
#include <thread>
#define SKIN 'o'
#define EMPTY ' '
#define SPEED 1
using namespace std;

    Bullet::Bullet(int x, int y){
      this->x = x;
      this->y = y;
      this->speed = SPEED;
    }
    int Bullet::getX(){
      return this->x;
    }
    int Bullet::getY(){
      return this->y;
    }
    void Bullet::updateBullet(){
      for (int i = this->x; i < 122; i++){
      mvaddch(this->y, i, SKIN);	
			move(this->y,i);    
      }
    }
    int Bullet::createBullet(int x, int y){
      mvaddch(this->y, this->x, SKIN);	
			move(this->y,this->x);    
     	refresh();	
      return 0;
    }