#include <iostream>
#include <ncurses.h>
using namespace std;

WINDOW *create_newwin(char borderVertical, char borderOrizontal);
void destroy_win(WINDOW *local_win);
