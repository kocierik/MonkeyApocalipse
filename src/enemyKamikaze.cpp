#include <iostream>
#include <curses.h>
#include "enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
#define startx (COLS - width) / 2
#define starty (LINES - height) / 2
#define width 80
#define height 20


    
    EnemyKamikaze::EnemyKamikaze():Character::Character(x, y){
//        this->direction = 0;
        this->x = x;
        this->y = y;
    }

    /*
    void EnemyKamikaze::moveEnemyKamikaze(int x, int y, char SKIN){
        
    }
    */
