#include <stdio.h>
#include <ncurses.h>
#include "bullet.h"
#include "window.h"
#include "character.h"

WINDOW* winGame;
void resizeWin(int sig){
    endwin();
    refresh();
    clear();
    system("clear");                    // FUNZIONE PER FIXARE IL RIDIMENSIONAMENTO DELLA SCHEDA
    wrefresh(winGame);                  // UTILIZZAVO SIGWINCH CHE VI DA ERRORE
    refresh();                          // ANDAVO SEMPLICEMENTE A RICREARE LA WINDOW
    winGame = subwin(stdscr,17,80,10,44);
    box(winGame, '|' , '-');
    refresh();
    wrefresh(winGame);
}

void engineGame(int direction, bool *enterWin){
  Character actor(48,18);   
  bool shoot = false;
  bool game = true;
  clear();                  // PULISCE LO SCHERMO (NON HO BEN CAPITO NEMMENO IO COME)
  wrefresh(winGame);
  winGame = subwin(stdscr,17,80,10,44);         // CREO UNA SOTTOWINDOW
  touchwin(winGame);                              
  wrefresh(winGame);
  do{    
      //signal(SIGWINCH, resizeWin);
      box(winGame, '|' , '-');
      direction = actor.moveCharacter();
      if(direction == 32){              // SE SPINGI SPAZIO SPARI
          shoot = true;
          SBullet* b = createBullet(actor.getX()+1,actor.getY(),1);     // CREO UN BULLET
          updateB(b);                 // AGGIORNO LA POSIZIONE DEL BULLET
          refresh();
          destroyBullet(b);         // DISTRUGGE IL BULLET
      }
      refresh();
      if(direction == 27){ game = false; *enterWin = false;} 
  }while (game);
  system("clear");
}