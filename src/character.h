#include <iostream>
#include <ncurses.h>
using namespace std;

class Character{
    protected:
        int ch;
        int x;
        int y;
    public:
   		Character(int x, int y, char PLAYER);
    	void moveCharacter(int x, int y, char PLAYER);
};

