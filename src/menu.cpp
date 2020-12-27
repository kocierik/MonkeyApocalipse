#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "menu.h"
#include "window.h"
#define SKIN '&'
#define EMPTY ' '
#define startx (COLS - width) / 2.8
#define starty (LINES - height) / 2.2
#define width 110
#define height 25
using namespace std;

int printMenu(){
        int cnt = 0;
        int direction;	  // carattere premuto su tastiera in ascii
        WINDOW *menuWin;
        
        touchwin(menuWin);				 
        refresh();
        menuWin = newwin(height, width, starty, startx);
        
        do{
            resizeterm(LINES,COLS);
            box(menuWin,'|','-');
            init_pair(1, COLOR_BLUE,0);            
            attron(COLOR_PAIR(1));
            refresh();
            wrefresh(menuWin);
        

            mvprintw(11,25,"                                                                                                            ");
            mvprintw(12,25,"    b    d  P*Y  8b 8 8  d 88888 Yb  dP        A   8**Y  P*Y   P**b8   b    8     Yb  dP 8**Y .P*Y8 88888   ");
            mvprintw(13,25,"    8b  d8 P   Y 8Yb8 8od  8__    YbdP        PY   8__P P   Y P   `*   PY   8      YbdP  8__P `Yo.* 8__     ");
            mvprintw(14,25,"    8Yb P8 b   d 8 Y8 8*Y  8**     8P        P__Y  8**  b   P Y       P__Y  8  .o   8P   8**  o.`Y8 8**     ");
            mvprintw(15,25,"    8 Y  8  Ybo  8  Y 8  Y 88888  dP        P****Y 8     P*Y   YoodP P****Y 8ood8  dP    8     8oP* 88888   ");
            mvprintw(16,25,"                                                                                                            ");
            mvprintw(17,25,"    LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMINCIATA!                                                ");
            mvprintw(18,25,"                                                                                                            ");
            attroff(COLOR_PAIR(1));
            refresh();
            if(cnt == 0) mvprintw(22,35,"==>  (X) START THE FIGHT!"); else mvprintw(22,35,"     START THE FIGHT!    ");

            if(cnt == 1) mvprintw(24,35,"==>  (X) HOW TO PLAY"); else mvprintw(24,35,"     HOW TO PLAY    ");

            if(cnt == 2) mvprintw(26,35,"==>  (X) CREDITS"); else mvprintw(26,35,"     CREDITS      ");

            if(cnt == 3) mvprintw(28,35,"==>  (X) QUIT"); else mvprintw(28,35,"     QUIT     ");

            mvprintw(30,35,"Press space to continue or use the arrow to move");
            
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