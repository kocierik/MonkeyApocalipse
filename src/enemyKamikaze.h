#include <iostream>
#include <curses.h>
#include <iostream>
#include "character.h"
#define SKIN '&'
#define EMPTY ' '
#define startx (COLS - width) / 2
#define starty (LINES - height) / 2
#define width 80
#define height 20

class EnemyKamikaze : public Character{    
    public:
        EnemyKamikaze();
        //void moveEnemyKamikaze(int x, int y );
};