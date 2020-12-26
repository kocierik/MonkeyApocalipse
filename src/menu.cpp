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

int printMenu(){
        int cnt = 0;
        int direction;	  // carattere premuto su tastiera in ascii
        WINDOW *menuWin;
        menuWin = newwin(height, width, starty, startx);
        box(menuWin, '|' , '-');	
        touchwin(menuWin);				 
        refresh();
        do{
            menuWin = newwin(height, width, starty, startx);
            //box(menuWin, '|' , '-');	
            refresh();
            wrefresh(menuWin);

            mvprintw(10,19,"       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888 ");
            mvprintw(11,19,"       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__  ");
            mvprintw(12,19,"       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**  ");
            mvprintw(13,19,"       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888");
            mvprintw(14,19,"                                                                                                                                   ");
            mvprintw(15,19,"       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMINCIATA!                                                                    ");
            mvprintw(16,19,"                                                                                                                                   ");
               
            if(cnt == 0) mvprintw(20,35,"==>  (X) START THE FIGHT!"); else mvprintw(20,35,"     START THE FIGHT!    ");

            if(cnt == 1) mvprintw(22,35,"==>  (X) HOW TO PLAY"); else mvprintw(22,35,"     HOW TO PLAY    ");

            if(cnt == 2) mvprintw(24,35,"==>  (X) CREDITS"); else mvprintw(24,35,"     CREDITS      ");

            if(cnt == 3) mvprintw(26,35,"==>  (X) QUIT"); else mvprintw(26,35,"     QUIT     ");

            mvprintw(28,35,"Press space to continue or use the arrow to move");
            
            direction = getch();   
            if(direction == 32 && cnt == 0){
                destroy_win(menuWin);
                return 0;
            }
            if(direction == KEY_UP) cnt--;
            if(direction == KEY_DOWN) cnt++;
            if(cnt > 3) cnt = 0;
            if(cnt < 0) cnt = 3;
            
            wrefresh(menuWin);
            refresh();
        }while(direction != 27);
    endwin();
}