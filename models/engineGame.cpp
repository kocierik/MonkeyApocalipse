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
Pbullet EngineGame::createBullet(int x, int y, int direction) {
  Pbullet bullet = new Bullet;
  bullet->x = x;
  bullet->y = y;
  bullet->speed = 1;
  bullet->direction = direction;
  bullet->next = this->shoots;
  return bullet;
}
void EngineGame::shootBullet() {
  Pbullet bullet = this->shoots;
  while (bullet != NULL) {
      bullet->x += bullet->speed;
      move(bullet->y, bullet->x);
      printw("-");
      bullet = bullet->next;
  }
}

Pbullet EngineGame::destroyBullet(){
  Pbullet head = this->shoots, prev = this->shoots, tmp;
	while (this->shoots != NULL) {
		if (!isEmpty(this->shoots->x+1, this->shoots->y)) {
			if (this->shoots == head) {
				tmp = head ;
				head = this->shoots->next;
				delete tmp ;
				prev = head;
				this->shoots = head ;
			} else {
				tmp = prev->next ;
				prev->next = this->shoots->next;
				delete tmp ;
				this->shoots = prev->next ;
			}
		} else {
			prev = this->shoots;
			this->shoots = this->shoots->next;
		}
 }
  return head;
}


pEnemyList EngineGame::destroyEnemy(pEnemyList list, Enemy enemy){
  pEnemyList head = list, prev = list, tmp;
	while (list != NULL) {
		if (list->enemy.getX() == enemy.getX() && list->enemy.getY() == enemy.getY()) {
			if (list == head) {
				tmp = head ;
				head = list->next;
				delete tmp ;
				prev = head;
				list = head ;
			} else {
				tmp = prev->next ;
				prev->next = list->next;
				delete tmp ;
				list = prev->next ;
			}
		} else {
			prev = list;
			list = list->next;
		}
 }
  return head;
}
int EngineGame::lenghtList(pEnemyList list){
  int i = -1;
  while (list != NULL){
    i++;
    list = list->next;
  }
  return i;
}

void EngineGame::checkEnemyCollision(pEnemyList enemys){
  bool isCollision = false;
  Pbullet head = this->shoots;
  pEnemyList tmp = enemys;
  while(enemys != NULL && !isCollision){
    while(this->shoots != NULL && !isCollision){
      if(enemys->enemy.getX() == this->shoots->x+1 && enemys->enemy.getY() == this->shoots->y){
        isCollision = true;
      }
      this->shoots = this->shoots->next;
    }
  this->shoots = head;
  if(isCollision) break;
  else enemys = enemys->next;
  }
  if(isCollision){
    enemys->enemy.decreaseLife(10);
    if(enemys->enemy.getLife() <= 0) {
        enemys = destroyEnemy(tmp, enemys->enemy);
    }
  }
}

void EngineGame::printList(pEnemyList list){
  int i = 26;
  mvprintw(i, 60, "enemy == %d",lenghtList(list));
  while(list != NULL){
    if(list->enemy.getX()!=0){
      mvprintw(i, 28, "life == %d",list->enemy.getLife());
      mvprintw(i, 10, "X == %d",list->enemy.getX());
      mvprintw(i, 40, "Y == %d",list->enemy.getY());
    }
    i++;
    list = list->next;
  }
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
      if (isEmpty(character.getX() + 1, character.getY() ) == true)
        character.directionRight();
      break;  // ESCE DALLO SWITCH
    case 'e':
      if (whileCount / 2 > 1) {
        this->shoots = createBullet(character.getX(), character.getY(),direction);
        whileCount = 0;
      }
      break;
  }
}

void EngineGame::choiceGame(DrawWindow drawWindow, int *direction,int *selection) {
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

pEnemyList EngineGame::generateEnemy(int *monsterCount, char character, int damage, int life, pEnemyList list) {
  while(*monsterCount > 0){
    int x = randomPosition(23,70).x;
    int y = randomPosition(8,19).y;
    pEnemyList head = new EnemyList;
    Enemy enemy(x,y,character,damage,life);
    head->enemy = enemy;
    head->next = list;
    *monsterCount= *monsterCount - 1;
    list = head;
  }
    pEnemyList head = new EnemyList;
    Enemy enemy(0,0,' ',damage,life);
    head->enemy = enemy;
    head->next = list;
    list = head;
  return list;
}

void EngineGame::printEnemy(pEnemyList list, DrawWindow drawWindow){
  while(list != NULL){
    drawWindow.printCharacter(list->enemy.getX(),list->enemy.getY(),list->enemy.getCharacter());
    list = list->next;
  }
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
        drawWindow.HowToPlay(direction);
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

Position EngineGame::randomPosition(int startRange, int endRange){
  Position pos;
  pos.x = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
  pos.y = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
  while(!isEmpty(pos.x,pos.y)){
    pos.x = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
    pos.y = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
  }
  return pos;
}

void EngineGame::runGame(Character character, DrawWindow drawWindow,int direction) {
  long points = 0;
  int monsterCount = 3;
  pEnemyList enemyList = NULL;
  enemyList = generateEnemy(&monsterCount,'A',10,40,enemyList);
  while (!pause) {
    direction = getch();
    moveCharacter(character, direction);
    clear();
    drawWindow.printCharacter(character.getX(), character.getY(), character.getCharacter());
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->widht,this->height);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->widht,this->height, &points);
    printEnemy(enemyList,drawWindow);  // x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD
    shootBullet();
    this->whileCount += 1;    
    checkEnemyCollision(enemyList);
    points +=1;
    refresh();
    this->shoots = destroyBullet();
    printList(enemyList);
    timeout(50);
    if (direction == 27) pause = true;
  }
}
