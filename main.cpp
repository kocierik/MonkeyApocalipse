#include <iostream>
#include <stdio.h>
#include "menu.h"
#include <curses.h>

using namespace std;

void moveCharacter(int c, int x, int y){
    c = getch();
    while(c!=27){
      switch (c){
      case KEY_RIGHT:
        x++;
        move(y,x);
        break;
      case KEY_LEFT:
      if(x>0){
        x--;
        move(y,x);
      }
        break;
      case KEY_UP:
      if(y>0){
        y--;
        move(y,x);
      }
        break;
      case KEY_DOWN:
        y++;
        move(y,x);
        break;
      default:
        break;
      }
    c=getch();
    refresh();
  }
}

int main(){
  int c,x=0,y=0;
  initscr();
  keypad(stdscr,TRUE);
  noecho();
  moveCharacter(c,x,y);
  endwin();
  return 0;
}
