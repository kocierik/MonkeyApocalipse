#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
#define startx (COLS - width) / 2
#define starty (LINES - height) / 2
#define width 100
#define height 20

using namespace std;


int main(int argc, char *argv[]){
    
    initscr();
    cbreak();			
    noecho();
    keypad(stdscr, TRUE);	
   WINDOW *my_win;
	int direction;
    int menuSelected = printMenu();
    if(menuSelected == 0){     
        Character actor(startx, starty, SKIN);
        WINDOW* win = create_newwin('|','-');
        do{
            actor.moveCharacter(startx,starty,SKIN);
        }while ((direction = getch()) != 27);
        
    }

		
	endwin();			
	return 0;
}

