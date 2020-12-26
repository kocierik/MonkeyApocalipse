#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
#define startx COLS/2
#define starty LINES/2
#define width (COLS - width) / 2
#define height (LINES - height) / 2

using namespace std;


int main(){
    initscr();
    cbreak();			
    noecho();
    keypad(stdscr, TRUE);	
	int direction;
    int menuSelected = printMenu();

    if(menuSelected == 0){     
        Character actor(startx, starty, SKIN);
        
        system("clear");
        do{
            WINDOW* my_win = create_newwin('|','-');
            wrefresh(my_win);
            actor.moveCharacter(startx,starty,SKIN);
            refresh();
        }
        while ((direction = getch()) != 27);
    }

		
	endwin();			
	return 0;
}

