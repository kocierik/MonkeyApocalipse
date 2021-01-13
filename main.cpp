
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
    bool enterWin = false;
    bool quitMenu = false;
	int direction;
    int menuSelected = 0;

    do{    
        printMenu(&menuSelected, &enterWin);
        refresh();
        if(enterWin){
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
                        if(direction == 27){ game = false; enterWin = false;} 
                    } while (game);
                    break;
                case 1:    
                    break;
                case 2:     
                    do{
                        printTitle();      
                        printCredits();
                        direction = getch();
                    }while(direction != 27);
                    direction = 0;
                    enterWin = false;
                    system("clear");
                    break;
                case 3:
                    printf("Thank you for playing our game. Have a good day!\n");
                    quitGame = false;
                    exit(1);
                    break;
            }
        }
        clear();
        refresh();
        if(direction == 27 && quitMenu) quitGame = false;
    }while(quitGame);
	endwin();			
	return 0;
}
