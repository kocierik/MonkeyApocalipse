#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"

using namespace std;

WINDOW* winGame;
Character actor(48,18);     
void resizeWin(int sig){
    endwin();
    refresh();
    clear();
    system("clear");
    wrefresh(winGame);
    refresh();
    winGame = subwin(stdscr,17,80,10,44);
    box(winGame, '|' , '-');
    refresh();
    wrefresh(winGame);
}
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
    int menuSelected = 0;
    printMenu(&menuSelected);

    
    WINDOW* winCredits;
    switch (menuSelected){
    
    case 0:
        winGame = subwin(stdscr,17,80,10,44);
        touchwin(winGame);
        do{    
            signal(SIGWINCH, resizeWin);
            box(winGame, '|' , '-');
            actor.moveCharacter();
        } while ((direction = getch()) != 27);
        break;
    case 1:    
        break;
    case 2:     
        do{      
            printTitle();      
        }while((direction = getch()) != 27);
        break;
    case 3:
        exit(1);
        break;
    }



	endwin();			
	return 0;
}

