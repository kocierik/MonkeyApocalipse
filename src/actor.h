#include <iostream>
#include <curses.h>
using namespace std;

class Actor{
    protected:
        int ch;
        int x;
        int y;
    public:
   		Actor(int x, int y, char PLAYER);
    	void moveCharacter(int x, int y, char PLAYER);
};

