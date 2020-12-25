#include <iostream>
#include <stdio.h>
#include <curses.h>
#include "menu.h"
#include "actor.h"
using namespace std;

int main(){
  int c,x=0,y=0;
  initscr();
  keypad(stdscr,TRUE);
  noecho();

  Actor actor(x,y);
  actor.moveCharacter(getch(),x,y);

  
  endwin();
  return 0;
}
