#include <iostream>
#include <stdio.h>
#include "menu.h"
#include <curses.h>

using namespace std;
int main(){
  int c,x=0,y=0;
  initscr();
  keypad(stdscr,TRUE);
  noecho();
  c=getch();
  while(c!=27){
    switch (c){
    case KEY_RIGHT:
      x++;
      move(y,x);
      break;
    case KEY_LEFT:
      x--;
      move(y,x);
      break;
    case KEY_UP:
      y--;
      move(y,x);
      break;
    case KEY_DOWN:
      y++;
      move(y,x);
      break;
    default:
      printw("%c",c);
      x++;
      break;
    }
  c=getch();
}
endwin();
return 0;
}
