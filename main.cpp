#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
#define startx COLS / 2
#define starty LINES / 2
#define width 80
#define height 20

#define GRASS_PAIR     1
#define EMPTY_PAIR     1
#define WATER_PAIR     2
#define MOUNTAIN_PAIR  3
#define PLAYER_PAIR    4
using namespace std;


int main(){
    initscr();

    if(has_colors() == FALSE){
    	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    cbreak();			
    noecho();
    keypad(stdscr, TRUE);
    use_default_colors();
    start_color();			/* Start color 			*/
    
	int direction;
    int menuSelected = printMenu();
    if(menuSelected == 0){     
        Character actor(startx, starty);       
        system("clear");

        WINDOW* my_win = create_newwin('|','-');

        do{            
            actor.moveCharacter(60,23);
            refresh();
            wrefresh(my_win);
        }
        while ((direction = getch()) != 27);
    }
	endwin();			
	return 0;
}

