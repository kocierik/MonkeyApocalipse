#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"
#include "src/credits.h"
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
    bool game = true;
    bool quitGame = true;
	int direction;
    int menuSelected = 0;
    printMenu(&menuSelected);
    // menuSelected = 10;

    //WINDOW* winCredits;
    do{
        switch (menuSelected){
            case 0:
                clear();
                wrefresh(winGame);
                winGame = subwin(stdscr,17,80,10,44);
                touchwin(winGame);
                wrefresh(winGame);
                game = true;
                do{
                    signal(SIGWINCH, resizeWin);
                    box(winGame, '|' , '-');
                    direction = actor.moveCharacter();
                    if(direction == 27){ game = false;}
                } while (game);
                wrefresh(winGame);
                endwin();
                refresh();
                break;
            case 1:
                break;
            case 2:
                winGame = subwin(stdscr,17,80,10,44);
                touchwin(winGame);
                do{
                    // printTitle();
                    // printCredits();
                    // wrefresh(winCredits);
                }while((direction = getch()) != 27);
                break;
            case 3:

                printf("Thank you for playing our game. Have a good day!\n");
                quitGame = false;
                exit(1);
                break;
        }
        endwin();
        werase(winGame);
        wrefresh(winGame);
        refresh();
        printMenu(&menuSelected);
        wrefresh(winGame);
        if(getch() == 27) quitGame = false;
    }while(quitGame);


	endwin();
	return 0;
}

