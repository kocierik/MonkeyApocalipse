#include <iostream>
#include "menu.h"
#include <curses.h>
#include "actor.h"
using namespace std;

	Actor::Actor(int x, int y){
		this->ch = 0;
		this->x = x;
		this->y = y;
	}
	void Actor::moveCharacter(int ch ,int x, int y){
		ch = getch();
		while(ch!=27){
			switch (ch){
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
			ch = getch();
			refresh();
		}
	}