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

WINDOW *create_newwin( char borderVertical, char borderOrizontal){			// BORDI DELLA WINDOW
  WINDOW *local_win;
	local_win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
	box(local_win, borderVertical , borderOrizontal);			// CREA UNA WINDOW
  touchwin(local_win);				 
	wrefresh(local_win);		
	return local_win;
}

void destroy_win(WINDOW *local_win){	
	wrefresh(local_win);								// AGGIORNA UNA PAGINA PARTICOLARE
	delwin(local_win);						// ELIMINA LA PAGINA
}

void initWinScreen(){																																// FUNZIONI DA NON MODIFICARE
		if(has_colors() == FALSE){
			endwin();
			printf("Your terminal does not support color\n");
			exit(1);
		}
    cbreak();			
    noecho();
    keypad(stdscr, TRUE);				// PERMETTE L'UTILIZZO DEL TASTO ESC, ENTER, ECC..
    use_default_colors();
    start_color();	
}