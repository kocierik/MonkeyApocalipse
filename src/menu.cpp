#include <iostream>
#include <stdio.h>
#include "menu.h"
#include "curses.h"
using namespace std;


void printMenu(){
     int cnt = 0;
     int ch;	  // carattere premuto su tastiera in ascii
     initscr();	// inizializzazione dello schermo (OBLIGATORIA)
     keypad(stdscr, TRUE);	//consento l'utilizzo dei caratteri esc, delete, enter
     cbreak();		//disabilita il buffer dei caratteri
     noecho();		//toglie l'eco dei tasti premuti
    
        system("cls");
        do{

                    mvprintw(10,19,"       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n");
                    mvprintw(11,19,"       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n");
                    mvprintw(12,19,"       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n");
                    mvprintw(13,19,"       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n");
                    mvprintw(14,19,"                                                                                                                                        \n");
                    mvprintw(15,19,"       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMINCIATA!                                                                         \n");
                    mvprintw(16,19,"                                                                                                                                        \n");

            mvprintw(1,0,"\n\n\n\n");
               
            if(cnt == 0) mvprintw(20,35,"==>  (⤲) START THE FIGHT! \n"); else mvprintw(20,35,"(⤲) START THE FIGHT! \n");
            mvprintw(25,35,"\n\n");
            if(cnt == 1) mvprintw(22,35,"==>  (¿) HOW TO PLAY \n"); else mvprintw(22,35,"(¿) HOW TO PLAY \n");
            mvprintw(23,35,"\n\n");
            if(cnt == 2) mvprintw(24,35,"==>  (¢) CREDITS \n"); else mvprintw(24,35,"(¢) CREDITS \n");
            mvprintw(25,35,"\n\n");
            if(cnt == 3) mvprintw(26,35,"==>  (µ) QUIT \n"); else mvprintw(26,35,"(µ) QUIT \n");
            mvprintw(27,35,"\n\n\n\n\n");
            mvprintw(28,35,"use the arrow for navigate in the menu ");
            
            ch = getch();   
            if(ch == KEY_UP) cnt--;
            if(ch == KEY_DOWN) cnt++;
            if(cnt > 3) cnt = 0;
            if(cnt < 0) cnt = 3;
            refresh();
        }while(ch != 27);
        endwin();  
}