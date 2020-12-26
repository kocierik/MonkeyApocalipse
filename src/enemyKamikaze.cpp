#include <iostream>
#include <curses.h>
#include "enemyKamikaze.h"
#include "character.h"

#define EMPTY ' '

using namespace std;

    EnemyKamikaze::EnemyKamikaze():Character(x, y, SKIN){
        this->direction = 0;
        this->x = x;
        this->y = y;
        this->SKIN = SKIN;
    }

    /*
    void EnemyKamikaze::moveEnemyKamikaze(int x, int y, char SKIN){
        
    }
    */
