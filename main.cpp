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
    initscr();              // FUNZIONE PER UTILIZZARE NCURSES
    initWinScreen();            // FUNZIONE PER INIZIALIZZARE LA WINDOW
    bool quitGame = true;
    bool enterWin = false;
    bool quitMenu = false;
	int direction;              //INDICA LA POSIZIONE DEL CURSORE 
    int menuSelected;
    do{    
        printMenu(&menuSelected, &enterWin);        // NOTARE PASSO INDIRIZZO DI MEMORIA
        refresh();          // AGGIORNA TUTTE LE PAGINE 
        if(enterWin){
            switch (menuSelected){          
                case 0:
                    engineGame(direction, &enterWin);
                    break;
                case 1:    
                    break;                              // SELEZIONE DEL MENU CON LE FRECCE
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
        if(direction == 27 && quitMenu) quitGame = false;       // 27 = ESC --> ESCI SE SPINGI ESC
    }while(quitGame);
	endwin();			    // CHIUDI LA WINDOW
	return 0;
}
 //test macchina virtuale