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
    system("clear");
    wrefresh(winGame);
    refresh();
    winGame = subwin(stdscr,17,80,10,44);
    box(winGame, '|' , '-');
    refresh();
    wrefresh(winGame);
}

void engineGame(int direction, bool *enterWin){
  Character actor(48,18);   
  bool shoot = false;
  bool game = true;
  clear();
  wrefresh(winGame);
  winGame = subwin(stdscr,17,80,10,44);
  touchwin(winGame);
  wrefresh(winGame);
  do{    
      //signal(SIGWINCH, resizeWin);
      box(winGame, '|' , '-');
      direction = actor.moveCharacter();
      if(direction == 32){
          shoot = true;
          SBullet* b = createBullet(actor.getX()+1,actor.getY(),1);
          updateB(b);
          destroyBullet(b);
      }
      refresh();
      if(direction == 27){ game = false; *enterWin = false;} 
  }while (game);
  system("clear");
}