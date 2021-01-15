#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "menu.h"
#include "window.h"
#include <signal.h>
#define STARTX (COLS - WIDTH) / 2 // coordinate del blocco centrale
#define STARTY (LINES - HEIGHT) / 2 // coordinate del blocco centrale
#define WIDTH COLS/2 // dimensione blocco di gioco
#define HEIGHT LINES/2.5 // dimensione blocco di gioco


void printTitle(){
    init_pair(1, COLOR_RED,232);
    attron(COLOR_PAIR(1));
    mvprintw(11,30,"                                                                                                            ");
    mvprintw(12,30,"    b    d  P*Y  8b 8 8  d 88888 Yb  dP        A   8**Y  P*Y   P**b8   b    8     Yb  dP 8**Y .P*Y8 88888   ");
    mvprintw(13,30,"    8b  d8 P   Y 8Yb8 8od  8__    YbdP        PY   8__P P   Y P   `*   PY   8      YbdP  8__P `Yo.* 8__     ");
    mvprintw(14,30,"    8Yb P8 b   d 8 Y8 8*Y  8**     8P        P__Y  8**  b   P Y       P__Y  8  .o   8P   8**  o.`Y8 8**     ");
    mvprintw(15,30,"    8 Y  8  Ybo  8  Y 8  Y 88888  dP        P****Y 8     P*Y   YoodP P****Y 8ood8  dP    8     8oP* 88888   ");
    mvprintw(16,30,"                                                                                                            ");
    mvprintw(17,30,"     THE REVENGE OF THE MONKEYS HAS JUST BEGUN!                                                             ");
    mvprintw(18,30,"                                                                                                            ");
    attroff(COLOR_PAIR(1)); //CHIUSURA DEL COLORE ROSSO E NERO
}

void printCommand(int* cnt){
    if(*cnt == 0) mvprintw(22,35,"==>  (X) START THE FIGHT!"); else mvprintw(22,35,"     START THE FIGHT!    ");
    if(*cnt == 1) mvprintw(24,35,"==>  (X) HOW TO PLAY"); else mvprintw(24,35,"     HOW TO PLAY    ");
    if(*cnt == 2) mvprintw(26,35,"==>  (X) CREDITS"); else mvprintw(26,35,"     CREDITS      ");
    if(*cnt == 3) mvprintw(28,35,"==>  (X) QUIT"); else mvprintw(28,35,"     QUIT     ");
    mvprintw(30,35,"Press space to continue or use the arrow to move");
}


void printMenu(int *menuSelected, bool *enterWin){
        int cnt, direction;	  // carattere premuto su tastiera in ascii		
        int y,x;	 		
	    getmaxyx(stdscr,y, x); 
        WINDOW* winMenu;
        winMenu = subwin(stdscr,0,0,1,1);
        touchwin(winMenu);
        do{
        box(winMenu, '|' , '-');	
            printTitle();
            printCommand(&cnt);
            direction = getch();
            if(direction == 32){
                werase(winMenu);
                destroy_win(winMenu);
                system("clear");
                refresh();
                *menuSelected = cnt;
                *enterWin = true;
                break;
            }
            if(direction == KEY_UP) cnt--;
            if(direction == KEY_DOWN) cnt++;
            if(cnt > 3) cnt = 0;
            if(cnt < 0) cnt = 3;
        }while(direction != 27);
    system("clear");
}