#include <iostream>
#include <stdio.h>
#include "menu.h"
#include <curses.h>

using namespace std;

int main(){
  initscr();
  noecho();
  raw();

  int c, x, y;
  getmaxyx(stdscr,y,x);
  move(y/2,x/2);
  printw("§");
  getch();
  refresh();  
  endwin();
  return 0;
}
