#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/enemyKamikaze.h"
#define SKIN '&'
#define EMPTY ' '
using namespace std;



WINDOW *create_newwin(int height, int width, int starty, int startx){
  WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, '|' , '-');	
  touchwin(local_win);				 
	wrefresh(local_win);		
	return local_win;
}

void destroy_win(WINDOW *local_win){	
	wrefresh(local_win);
	delwin(local_win);
}

int main(int argc, char *argv[]){
  WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();			
	cbreak();			
    noecho();
	keypad(stdscr, TRUE);		

	height = 20;
	width = 100;
	starty = (LINES - height) / 2;	
	startx = (COLS - width) / 2;	
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height, width, starty, startx);

	while((ch = getch()) != KEY_F(1))
	{

	}
		
	endwin();			/* End curses mode		  */
	return 0;
}

