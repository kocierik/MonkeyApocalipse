#include <iostream>
#include <curses.h>
#include "character.h"

using namespace std;

class EnemyKamikaze: public Character{
    protected:
        
    public:
        EnemyKamikaze():Character(x, y, SKIN);
        //void moveEnemyKamikaze(int x, int y, char SKIN);
};