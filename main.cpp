#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"
#define WIDTH COLS/2 // dimensione blocco di gioco
#define HEIGHT LINES/2.5 // dimensione blocco di gioco
#define STARTXPLAYER (COLS - WIDTH) / 2 // coordinate del blocco centrale
#define STARTYPLAYER (LINES - HEIGHT) / 2 // coordinate del blocco centrale
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
    start_color();			
    
	int direction;
    int menuSelected = printMenu();
    if(menuSelected == 0){     
        Character actor;       
        system("clear");
        WINDOW* my_win = create_newwin('!','-');
        do{    
            actor.moveCharacter(STARTXPLAYER+2,STARTYPLAYER+HEIGHT/2-1);
            refresh();
            wrefresh(my_win);
        } while ((direction = getch()) != 27);
    }
	endwin();			
	return 0;
}

