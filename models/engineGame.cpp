#include "character.hpp"
#include "drawWindow.hpp"
#include "engineGame.hpp"
#include <ncurses.h>
#include <cmath>
#include <ctime>
#include <iostream>


EngineGame::EngineGame(int frameGameX, int frameGameY, int height, int width) {
  this->frameGameX = frameGameX;
  this->frameGameY = frameGameY;
  this->height = height;
  this->widht = width;
  this->shoots = NULL;
  this->quit = false;
  this->pause = true;
  this->isShoot = false;
  this->whileCount = 0;
}

void EngineGame::baseCommand() {
  initscr();
  cbreak();
  curs_set(0);
  nodelay(stdscr, TRUE);
  keypad(stdscr, true);
  curs_set(FALSE);
  noecho();
  use_default_colors();
  start_color();
}
Pbullet EngineGame::createBullet(int x, int y) {
  Pbullet bullet = new Bullet;
  bullet->x = x;
  bullet->y = y;
  bullet->speed = 1;
  bullet->next = this->shoots;
  return bullet;
}
void EngineGame::shootBullet() {
  Pbullet bullet = this->shoots;
  while (bullet != NULL) {
    bullet->x += bullet->speed;
    move(bullet->y, bullet->x);
    printw("--");
    bullet = bullet->next;
  }
}
Pbullet EngineGame::destroyBullet() {
  if (this->shoots != NULL) {
    if (this->shoots->next != NULL) {
      Pbullet bullet = this->shoots, prec = this->shoots;
      while (bullet != NULL) {
        if (!isEmpty(bullet->x + 2, bullet->y)) {
          prec->next = NULL;
          delete (bullet);
          bullet = NULL;
          return (this->shoots);
        }
        prec = bullet;
        bullet = bullet->next;
      }
    } else {
      if (this->shoots->x + 2 > widht) {
        delete (this->shoots);
        this->shoots = NULL;
        return NULL;
      }
    }
  }
  return this->shoots;
}
// controllo che la posizione x y sia uno spazio vuoto
bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }
void EngineGame::moveCharacter(Character &character, int direction) {
  switch (direction) {  // CONTROLLO IL TASTO SPINTO
    case KEY_UP:
      if (isEmpty(character.getX(), character.getY() - 1) == true)
        character.directionUp();
      break;
    case KEY_DOWN:
      if (isEmpty(character.getX(), character.getY() + 1) == true)
        character.directionDown();
      break;
    case KEY_LEFT:
      if (isEmpty(character.getX() - 1, character.getY()) == true)
        character.directionLeft();
      break;
    case KEY_RIGHT:
      if (isEmpty(character.getX() + 1, character.getY() - 1) == true)
        character.directionRight();
      break;  // ESCE DALLO SWITCH
    case 'e':
      if (whileCount / 2 > 1) {
        this->shoots = createBullet(character.getX(), character.getY());
        whileCount = 0;
      }
      break;
  }
}
void EngineGame::choiceGame(DrawWindow drawWindow, int *direction,
                            int *selection) {
  int cnt = 0;
  while (*direction != 32) {
    drawWindow.drawMenu();
    drawWindow.printCommand(&cnt);
    *direction = getch();
    if (*direction == 32) *selection = cnt;
    if (*direction == KEY_UP) cnt--;
    if (*direction == KEY_DOWN) cnt++;
    if (cnt > 3) cnt = 0;
    if (cnt < 0) cnt = 3;
  }
  clear();
}
void EngineGame::engine(Character character, DrawWindow drawWindow) {
  int direction, selection;
  baseCommand();
  choiceGame(drawWindow, &direction, &selection);
  while (pause) {
    switch (selection) {
      case 0:
        pause = false;
        runGame(character, drawWindow, direction);
        selection = 4;
        break;
      case 1:
        selection = 4;
        break;
      case 2:
        drawWindow.credits(direction);
        selection = 4;
        break;
      case 3:
        refresh();
        std::cout << "Thanks for playing ;) ";
        exit(1);
        break;
      case 4:
        clear();
        engine(character, drawWindow);
        break;
    }
  }
  endwin();
}
void EngineGame::runGame(Character character, DrawWindow drawWindow,
                         int direction) {
  long points = 0;
  while (!pause) {
    direction = getch();
    moveCharacter(character, direction);
    clear();
    drawWindow.printCharacter(character.getX(), character.getY(), character.getCharacter());
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->widht,
                        this->height);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->widht,
                         this->height, &points);
    shootBullet();
    refresh();
    this->shoots = destroyBullet();
    this->whileCount += 1;
    points +=1;
    timeout(50);
    if (direction == 27) pause = true;
  }
}
