#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "menu.h"
#include "window.h"
#define SKIN '&'
#define EMPTY ' '
#define startx (COLS - width) / 2
#define starty (LINES - height) / 2
#define width 160
#define height 35
using namespace std;

WINDOW *create_newwin( char borderVertical, char borderOrizontal){
  WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, borderVertical , borderOrizontal);	
    touchwin(local_win);				 
	wrefresh(local_win);		
	return local_win;
}

void destroy_win(WINDOW *local_win){	
	wrefresh(local_win);
	delwin(local_win);
}