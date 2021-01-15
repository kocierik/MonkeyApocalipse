#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include "src/menu.h"
#include "src/window.h"
#include "src/enemyKamikaze.h"
#include "src/credits.h"
#include "src/bullet.h"
#include "src/engineGame.h"

int main(){
    initscr();
    initWinScreen();
    bool quitGame = true;
    bool enterWin = false;
    bool quitMenu = false;
	int direction;
    int menuSelected;
    do{    
        printMenu(&menuSelected, &enterWin);
        refresh();
        if(enterWin){
            switch (menuSelected){    
                case 0:
                    engineGame(direction, &enterWin);
                    break;
                case 1:    
                    break;
                case 2:     
                    credits(direction, &enterWin);
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
