#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "menu.h"
#include "window.h"
#define SKIN '&'
#define EMPTY ' '
#define STARTX (COLS - WIDTH) / 2 // coordinate del blocco centrale
#define STARTY (LINES - HEIGHT) / 2 // coordinate del blocco centrale
#define WIDTH COLS/2 // dimensione blocco di gioco
#define HEIGHT LINES/2.5 // dimensione blocco di gioco
using namespace std;

WINDOW *create_newwin( char borderVertical, char borderOrizontal){
  WINDOW *local_win;
	local_win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
	box(local_win, borderVertical , borderOrizontal);	
  touchwin(local_win);				 
	wrefresh(local_win);		
	return local_win;
}

void destroy_win(WINDOW *local_win){	
	wrefresh(local_win);
	delwin(local_win);
}

void initWinScreen(){
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
}