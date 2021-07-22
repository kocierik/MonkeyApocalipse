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
  this->shootsEnemys = NULL;
  this->quit = false;
  this->pause = true;
  this->isEnemyShoots = false;
  this->whileCount = 0;
  this->whileCountEnemy = 0;
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
Pbullet EngineGame::createBullet(int x, int y, Pbullet &shoots) {
  Pbullet bullet = new Bullet;
  bullet->x = x;
  bullet->y = y;
  bullet->speed = 1;
  bullet->next = shoots;
  return bullet;
}

void EngineGame::enemyShootBullets(pEnemyList listEnemy) {
  while (listEnemy != NULL) {
    if (this->whileCountEnemy % 20 == 0) {
      this->shootsEnemys = createBullet(
          listEnemy->enemy.getX(), listEnemy->enemy.getY(), this->shootsEnemys);
    }
    listEnemy = listEnemy->next;
  }
}

void EngineGame::shootBullet() {
  Pbullet bullet = this->shoots;
  while (bullet != NULL) {
    bullet->x += bullet->speed;
    move(bullet->y, bullet->x);
    init_pair(10, COLOR_YELLOW, -1); // SPARA BANANE GIALLE
    attron(COLOR_PAIR(10));
    printw("~");
    attroff(COLOR_PAIR(10));
    bullet = bullet->next;
  }
}

void EngineGame::shootEnemyBullet() {
  Pbullet bullet = this->shootsEnemys;
  while (bullet != NULL) {
    bullet->x -= bullet->speed;
    move(bullet->y, bullet->x);
    printw("-");
    bullet = bullet->next;
  }
}

void EngineGame::destroyBullet(Pbullet &shoots, int isEnemy) {
  Pbullet head = shoots, prev = shoots, tmp;
  while (head != NULL) {
    if (!isEmpty(head->x + isEnemy, head->y) || head->x > 70 || head->x < 23) {
      if (head == shoots) {
        tmp = shoots;
        shoots = head->next;
        delete tmp;
        prev = shoots;
        head = shoots;
      } else {
        tmp = prev->next;
        prev->next = head->next;
        delete tmp;
        head = prev->next;
      }
    } else {
      prev = head;
      head = head->next;
    }
  }
}

pEnemyList EngineGame::destroyEnemy(pEnemyList list, Enemy enemy) {
  pEnemyList head = list, prev = list, tmp;
  while (list != NULL) {
    if (list->enemy.getX() == enemy.getX() &&
        list->enemy.getY() == enemy.getY()) {
      if (list == head) {
        tmp = head;
        head = list->next;
        delete tmp;
        prev = head;
        list = head;
      } else {
        tmp = prev->next;
        prev->next = list->next;
        delete tmp;
        list = prev->next;
      }
    } else {
      prev = list;
      list = list->next;
    }
  }
  return head;
}

void EngineGame::checkEnemyCollision(Character &character,
                                     pEnemyList enemyList) {
  while (enemyList != NULL) {
    if ((character.getX() + 1 == enemyList->enemy.getX() &&
         character.getY() == enemyList->enemy.getY()) ||
        (character.getX() - 1 == enemyList->enemy.getX() &&
         character.getY() == enemyList->enemy.getY()) ||
        (character.getX() == enemyList->enemy.getX() &&
         character.getY() + 1 == enemyList->enemy.getY()) ||
        (character.getX() == enemyList->enemy.getX() &&
         character.getY() - 1 == enemyList->enemy.getY())) {
      character.decreaseLife(1);
      init_pair(13, COLOR_RED, -1);
      attron(COLOR_PAIR(13));
      mvprintw(character.getY(), character.getX(), "C");   // GENERA UN CARATTERE ROSSO QUANDO SI SOTTO IL NEMICO
      attroff(COLOR_PAIR(13));
    }
    enemyList = enemyList->next;
  }
}

void EngineGame::checkShootEnemyCollision(pEnemyList enemys,
                                          Character &character, Pbullet &shoots,
                                          int isEnemy) {
  bool isCollisionEnemy = false;
  bool isCollisionCharacter = false;
  bool pause = false;
  Pbullet head = shoots;
  pEnemyList tmp = enemys;
  while (enemys != NULL && !isCollisionEnemy && !isCollisionCharacter) {
    while (shoots != NULL && !isCollisionEnemy && !isCollisionCharacter) {
      if ((enemys->enemy.getX() == shoots->x + isEnemy &&
           enemys->enemy.getY() == shoots->y) &&
          isEnemy == 1) {
        isCollisionEnemy = true;
      } else if ((character.getX() == shoots->x + isEnemy &&
                  character.getY() == shoots->y) &&
                 isEnemy == -1) {
        isCollisionCharacter = true;
      }
      shoots = shoots->next;
    }
    shoots = head;
    if (isCollisionEnemy || isCollisionCharacter)
      break;
    else
      enemys = enemys->next;
  }
  if (isCollisionEnemy && isEnemy == 1) {
    enemys->enemy.decreaseLife(character.getDamage());
    if (enemys->enemy.getLife() <= 0) {
      enemys = destroyEnemy(tmp, enemys->enemy);
    }
  } else if (isCollisionCharacter && isEnemy == -1) {
    character.decreaseLife(enemys->enemy.getDamage());
    checkDeath(pause, character);

    init_pair(13, COLOR_RED, -1);
    attron(COLOR_PAIR(13));
    mvprintw(character.getY(), character.getX(), "C");    // GENERA UN CARATTERE ROSSO QUANDO SI VIENE COLPITI
    attroff(COLOR_PAIR(13));
  }
}

// controllo che la posizione x y sia uno spazio vuoto
bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }

void EngineGame::moveCharacter(Character &character, int direction, int &bananas, int &powerUpDMG) {
  int upgradeCost = 20;
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
      if (isEmpty(character.getX() + 1, character.getY()) == true)
        character.directionRight();
      break;  // ESCE DALLO SWITCH
    case 'e':
    case 'E':
      if (whileCount / 2 > 1) {
        this->shoots =
            createBullet(character.getX(), character.getY(), this->shoots);
        whileCount = 0;
      }
      break;
    case 'q':           // CONTROLLA L'AQUISTO DI VITE, MASSIMO 3
    case 'Q':          
      if (bananas >= upgradeCost && character.getNumberLife() < 3) {
        character.setNumberLife(character.getNumberLife() + 1);
        bananas = bananas - upgradeCost;
      }
      break;
    case 'r':           // CONTROLLA L'AQUISTO DI POWERUP AL DANNO, SONO ACQUISTABILI AL MASSIMO 4 DURANTE TUTTA LA RUN
    case 'R':          
      if (bananas >= upgradeCost && powerUpDMG < 4) {
        character.setDamage(character.getDamage() + 10);
        bananas = bananas - upgradeCost;
        powerUpDMG++;
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

pEnemyList EngineGame::generateEnemy(int *monsterCount, char character,
                                     int damage, int life, pEnemyList list,
                                     int &round, DrawWindow drawWindow) {
  bool isEmpty = false;
  while (*monsterCount > 0) {
    int x = drawWindow.randomPosition(40, 70).x;
    int y = drawWindow.randomPosition(8, 19).y;
    pEnemyList head = new EnemyList;
    Enemy enemy(x, y, character, damage, life, 1);
    head->enemy = enemy;
    head->next = list;
    *monsterCount -= 1;
    list = head;
    isEmpty = true;
  }
  if (isEmpty) {
    round += 1;
    pEnemyList head = new EnemyList;
    Enemy enemy(0, 0, ' ', damage, life, 1);
    head->enemy = enemy;
    head->next = list;
    list = head;
    isEmpty = false;
  }

  return list;
}

void EngineGame::checkDeath(bool &pause, Character &character) {
  if (character.getLife() <= 0) {
    character.setNumberLife(character.getNumberLife() - 1);
    if(character.getNumberLife() > 0) { character.setLife(100); }
  }
  if (character.getNumberLife() <= 0){
    pause = true;
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

void EngineGame::increaseCount(int &whileCount, long &points,
                               pEnemyList enemyList) {
  whileCount += 1;
  if (enemyList->next != NULL) points += 1;
  this->whileCountEnemy += 1;
}

void EngineGame::money(int &bananas, pEnemyList enemyList, int maxRound, int &roundPayed){ // SISTEMA DI VALUTA CHE GENERA DA 1 A 3 BANANE AD OGNI CLEAR DEL LIVELLO
  srand(time(NULL));
  if(enemyList->next == NULL && maxRound != roundPayed){       // CONTROLLA CHE LA STANZA SIA PULITA E CHE L'ULTIMO ROUND SIA STATO PAGATO
    bananas = bananas + rand() % 3 + 1;
    roundPayed++;
  }

}



void EngineGame::getInput(int &direction) { direction = getch(); }

void EngineGame::isPause(int &direction, bool &pause) {
  if (direction == 27) pause = true;
}


void EngineGame::runGame(Character character, DrawWindow drawWindow,
                         int direction) {
  int powerUpDMG = 0; // NUMERO DI POWERUP AL DANNO AQUISTATI
  int bananas = 0;
  int roundPayed = 0;
  long points = 0;
  int monsterCount = 1;
  int round = 0;
  int maxRound = 1;
  pEnemyList enemyList = NULL;
  pPosition mountainList = NULL;
  pRoom listRoom = new Room;
  while (!pause) {
    listRoom = drawWindow.changeRoom(character, monsterCount, round, enemyList,
                                     mountainList, listRoom, maxRound);
    enemyList = generateEnemy(&monsterCount, 'X', 10, 100, enemyList, round,
                              drawWindow);
    getInput(direction);
    moveCharacter(character, direction, bananas, powerUpDMG);
    clear();
    drawWindow.printCharacter(character.getX(), character.getY(),
                              character.getCharacter());
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->widht,
                        this->height, enemyList, round, false);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->widht,
                         this->height, &points, character, enemyList, powerUpDMG);
    drawWindow.printCharacterStats(enemyList, character);
    if (drawWindow.lenghtRoom(listRoom) > 1)
      drawWindow.printMountain(listRoom->next->listMountain);
    increaseCount(this->whileCount, points, enemyList);
    drawWindow.printEnemy(enemyList, drawWindow);
    drawWindow.moveEnemy(enemyList, character, drawWindow, points);
    shootBullet();
    shootEnemyBullet();
    enemyShootBullets(enemyList);
    checkEnemyCollision(character, enemyList);
    money(bananas, enemyList, maxRound, roundPayed);
    checkShootEnemyCollision(enemyList, character, this->shoots, 1);
    checkShootEnemyCollision(enemyList, character, this->shootsEnemys, -1);
    refresh();
    destroyBullet(this->shoots, 1);
    destroyBullet(this->shootsEnemys, -1);
    checkDeath(pause, character);
    mvprintw(25, 52, "BANANAS                 %d", bananas);
    mvprintw(26, 52, "ROOM                  %d/%d", drawWindow.lenghtRoom(listRoom), maxRound);
    mvprintw(27, 52, "ROUND MAX               %d", maxRound);
    timeout(50);
    isPause(direction, pause);
  }
}
// x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD