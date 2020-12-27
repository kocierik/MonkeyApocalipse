#include <iostream>
#include <curses.h>
#include "enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
#define startx (COLS - width) / 2 // coordinate del blocco
#define starty (LINES - height) / 2 // coordinate del blocco
#define width COLS/2 // dimesione blocco di gioco
#define height LINES/2.5 // dimesione blocco di gioco


    
    EnemyKamikaze::EnemyKamikaze():Character::Character(x, y){
//        this->direction = 0;
        this->x = x;
        this->y = y;
    }

    /*
    void EnemyKamikaze::moveEnemyKamikaze(int x, int y, char SKIN){
        
    }
    */
