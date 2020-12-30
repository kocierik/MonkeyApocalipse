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



void creditsInfo(){
    
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
    int menuSelected = printMenu();

    Character actor;     
    WINDOW* winCredits;
    WINDOW* winGame;
    switch (menuSelected){
    
    case 0:
        do{    
            winGame = create_newwin('!','-');
            wrefresh(winGame);
            actor.moveCharacter(STARTXPLAYER+2,STARTYPLAYER+HEIGHT/2-1);
        } while ((direction = getch()) != 27);
        break;
    case 1:    
        break;
    case 2:     
        winCredits = newwin(HEIGHT, WIDTH, COLS/2, LINES/2);
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

