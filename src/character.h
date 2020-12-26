#include <iostream>
#include <ncurses.h>
using namespace std;

class Character{
    protected:
        int direction; // Input da tastiera per il movimento del character
        int x;
        int y;
        char SKIN;
    public:
   		Character(int x, int y, char SKIN);
    	void moveCharacter(int x, int y, char SKIN);
};

