#include "drawWindow.hpp"
#include "engineGame.hpp"

#include <ncurses.h>

#include <cmath>
#include <ctime>
#include <iostream>


#define N_SWITCH_CASE \
  11  // Numero di casi dello switch che gestisce i bonus. Equivale a: n bonus -
      // 1

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

Pbullet EngineGame::createBullet(int x, int y, Pbullet &shoots, Gun gun) {
  Pbullet bullet = new Bullet;
  bullet->x = x;
  bullet->y = y;
  bullet->speed = 1;
  bullet->skin = gun.getBulletSkin();
  bullet->next = shoots;
  return bullet;
}

void EngineGame::enemyShootBullets(pEnemyList listEnemy) {
  while (listEnemy != NULL) {
    if (this->whileCountEnemy % 20 == 0) {
      this->shootsEnemys =
          createBullet(listEnemy->enemy.getX(), listEnemy->enemy.getY(),
                       this->shootsEnemys, listEnemy->enemy.getGun());
    }
    listEnemy = listEnemy->next;
  }
}

void EngineGame::shootBullet(Gun playerGun) {
  Pbullet bullet = this->shoots;
  while (bullet != NULL) {
    bullet->x += bullet->speed;
    move(bullet->y, bullet->x);
    init_pair(10, COLOR_YELLOW, -1);  // SPARA BANANE GIALLE
    attron(COLOR_PAIR(10));
    // printw("~");
    char tmp[2];
    tmp[0] = playerGun.getBulletSkin();
    // printw((const char *) playerGun.getBulletSkin());
    printw(tmp);
    attroff(COLOR_PAIR(10));
    bullet = bullet->next;
  }
}

// void EngineGame::shootEnemyBullet (Gun enemyGun) {
void EngineGame::shootEnemyBullet() {
  Pbullet bullet = this->shootsEnemys;
  while (bullet != NULL) {
    bullet->x -= bullet->speed;
    move(bullet->y, bullet->x);
    printw("-");
    // printw((const char *)enemyGun.getBulletSkin());
    bullet = bullet->next;
  }
}

void EngineGame::destroyBullet(Pbullet &shoots, int isEnemy) {
  Pbullet head = shoots, prev = shoots, tmp;
  while (head != NULL) {
    bool tmpCondition = !isEmpty(head->x + isEnemy, head->y) &&
                        !isBonus(head->x + isEnemy, head->y);
    if (tmpCondition || head->x > 70 || head->x < 23) {
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

pPosition EngineGame::deletePosition(pPosition list, pPosition toDelete) {
  /**
   * Essendo bonus e montagne la stessa tipologia di dato (pPosition), questa
   * funzione elimina un elemento (toDelete) da una lista, che sia un bonus o
   * una montagna.
   */
  pPosition head = list, prev = list, tmp;
  while (list != NULL) {
    if (list->x == toDelete->x && list->y == toDelete->y) {
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
      mvprintw(character.getY(), character.getX(),
               "M");  // GENERA UN CARATTERE ROSSO QUANDO SI VIENE ATTACATI
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
    enemys->enemy.decreaseLife(character.getGun().getDamage());
    if (enemys->enemy.getLife() <= 0) {
      enemys = destroyEnemy(tmp, enemys->enemy);
    }
  } else if (isCollisionCharacter && isEnemy == -1) {
    character.decreaseLife(enemys->enemy.getGun().getDamage());
    checkDeath(pause, character);

    init_pair(13, COLOR_RED, -1);
    attron(COLOR_PAIR(13));
    mvprintw(character.getY(), character.getX(),
             "C");  // GENERA UN CARATTERE ROSSO QUANDO SI VIENE COLPITI
    attroff(COLOR_PAIR(13));
  }
}

// Controllo che la posizione x y sia uno spazio vuoto
bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }
bool EngineGame::isBonus(int x, int y) { return mvinch(y, x) == '?'; }
bool EngineGame::isMountain(int x, int y) { return mvinch(y, x) == '^'; }

void EngineGame::moveCharacter(DrawWindow drawWindow, Character &character,
                               int direction, pRoom &roomList,
                               pEnemyList enemyList, int round,
                               float &pointsOnScreen, int &bananas,
                               int &powerUpDMG, bool &bonusPicked,
                               int &bonusType, int &bonusTime,
                               bool &upgradeBuyed, int &upgradeType,
                               int &upgradeTime) {
  int upgradeCost = 10;
  srand(time(0));
  switch (direction) {  // CONTROLLO IL TASTO SPINTO
    case KEY_UP:  // --------------------------------------------------------
      if (isEmpty(character.getX(), character.getY() - 1))
        character.directionUp();
      else if (isBonus(character.getX(), character.getY() - 1)) {
        bonusTime = 0;       // RESETTA IL TEMPO DI APPARIZIONE SE IL TIMER
                             // ERA GIA ATTIVO PER IL PRECEDENTE BONUS.
        bonusPicked = true;  // FLAG CHE INDICA SE È STATO RACCOLTO
        bonusType = rand() % N_SWITCH_CASE;  // 0 <= bonusType <= N_SWITCH_CASE
        roomList -> bonusList = getBonus(drawWindow, character.getX(), character.getY() - 1,
                             roomList -> next -> bonusList, enemyList, round, pointsOnScreen,
                             character, bonusType);
        character.directionUp();
      }
      break;
    case KEY_DOWN:  // ------------------------------------------------------
      if (isEmpty(character.getX(), character.getY() + 1))
        character.directionDown();
      else if (isBonus(character.getX(), character.getY() + 1)) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % N_SWITCH_CASE;
        roomList -> bonusList = getBonus(drawWindow, character.getX(), character.getY() + 1,
                             roomList -> next -> bonusList, enemyList, round, pointsOnScreen,
                             character, bonusType);
        character.directionDown();
      }
      break;
    case KEY_LEFT:  // ------------------------------------------------------
      if (isEmpty(character.getX() - 1, character.getY()))
        character.directionLeft();
      else if (isBonus(character.getX() - 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % N_SWITCH_CASE;  // GENERA IL TIPO DI BONUS.
        roomList -> bonusList = getBonus(drawWindow, character.getX() - 1, character.getY(),
                             roomList -> next -> bonusList, enemyList, round, pointsOnScreen,
                             character, bonusType);
        character.directionLeft();
      }
      break;
    case KEY_RIGHT:  // -----------------------------------------------------
      if (isEmpty(character.getX() + 1, character.getY()))
        character.directionRight();
      else if (isBonus(character.getX() + 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % N_SWITCH_CASE;
        roomList -> bonusList = getBonus(drawWindow, character.getX() + 1, character.getY(),
                             roomList -> next -> bonusList, enemyList, round, pointsOnScreen,
                             character, bonusType);
        character.directionRight();
      }
      break;
    case 'e':  // -----------------------------------------------------------
    case 'E':
      if (whileCount / 2 > 1) {
        if (character.getGun().getAmmo() > 0) {
          character.setAmmo(character.getAmmo() - 1);
          this->shoots = createBullet(character.getX(), character.getY(),
                                      this->shoots, character.getGun());
          whileCount = 0;
        }
      }
      break;
    case 'q':  // CONTROLLA L'AQUISTO DI VITE, MASSIMO 3 -------------------
    case 'Q':
      if (bananas >= upgradeCost && character.getNumberLife() < 3) {
        upgradeBuyed = true;  // INDICA CHE È STATO COMPRATO UN UPGRADE
        upgradeType = 0;      // INDICA IL TIPO DI UPGRADE.
        upgradeTime = 0;  // RESETTA IL TEMPO DI APPARIZIONE SE HAI COMPRATO UN
                          // ALTRO UPGRADE
        character.setNumberLife(character.getNumberLife() + 1);
        bananas = bananas - upgradeCost;
      }
      break;
    case 'r':  // CONTROLLA L'AQUISTO DI POWERUP AL DANNO, SONO ACQUISTABILI AL
               // MASSIMO 4 DURANTE TUTTA LA RUN
    case 'R':
      if (bananas >= upgradeCost && powerUpDMG < 4) {
        upgradeBuyed = true;
        upgradeType = 1;
        upgradeTime = 0;
        character.getGun().increaseDamage(10);
        bananas = bananas - upgradeCost;
        powerUpDMG++;
      }
      break;
  }
}

void EngineGame::showBonusOnScreen(bool &upgradeBuyed, int &upgradeType,
                           int &upgradeTime, bool &bonusPicked, int bonustype,
                           int &bonusTime) {
  int x = 25;
  int y = 6;
  int timeLimit = 30;

  if (bonusPicked == true && bonustype == 0) {
    mvprintw(y, x, "BUNCH OF BANANAS [+50]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 1) {
    mvprintw(y, x, "CRATE OF BANANAS [+300]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 2) {
    mvprintw(y, x, "SUPPLY OF BANANAS [+1000]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 3) {
    mvprintw(y, x, "ROTTEN BANANAS [-100]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 4) {
    mvprintw(y, x, "BANANAS SPIDER [-10 HP]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 5) {
    mvprintw(y, x, "MONKEY TRAP [-30 HP]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 6) {
    mvprintw(y, x, "EAT 1 BANANA [+10 HP]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 7) {
    mvprintw(y, x, "EAT 2 BANANA [+20 HP]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 8) {
    mvprintw(y, x, "BANANA SMOOTHIE [+40 HP]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 9) {
    mvprintw(y, x, "PEEL LOADER [+12 PEELS]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 10) {
    mvprintw(y, x, "PEEL LOADER [+20 PEELS]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 11) {
    mvprintw(y, x, "PEACE MISSION [+100 PEELS]");
    bonusTime++;
  }

  if (bonusTime > timeLimit) {  // LASCIA IL BONUS VISIBILE PER "X" CICLI
    bonusPicked = false;
    bonusTime = 0;  // RESETTA IL TIMER PER IL PROSSIMO BONUS UNA VOLTA SCADUTO
  }

  if (upgradeBuyed == true && upgradeType == 0) {
    mvprintw(y, x + 29, "MORE LIFE!");
    upgradeTime++;
  } else if (upgradeBuyed == true && upgradeType == 1) {
    mvprintw(y, x + 29, "DAMAGE UPGRADE!");
    upgradeTime++;
  }

  if (upgradeTime > timeLimit + 10) {  // STESSO DI SOPRA MA CON GLI UPGRADE
    upgradeBuyed = false;
    upgradeTime = 0;
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

pEnemyList EngineGame::generateEnemy(int *monsterCount, char skin, Gun gun,
                                     int life, pEnemyList list, int &round,
                                     DrawWindow drawWindow) {
  bool isEmpty = false;
  while (*monsterCount > 0) {
    int x = drawWindow.randomPosition(40, 70).x;
    int y = drawWindow.randomPosition(8, 19).y;
    pEnemyList head = new EnemyList;
    Enemy enemy(x, y, skin, life, 1, gun);
    head->enemy = enemy;
    head->next = list;
    *monsterCount -= 1;
    list = head;
    isEmpty = true;
  }
  if (isEmpty) {
    round += 1;
    pEnemyList head = new EnemyList;
    Enemy enemy(0, 0, ' ', life, 1, gun);
    head->enemy = enemy;
    head->next = list;
    list = head;
    isEmpty = false;
  }

  return list;
}

pPosition EngineGame::getBonus(DrawWindow drawWindow, int x, int y,
                               pPosition bonusList, pEnemyList enemyList,
                               int round, float &pointsOnScreen,
                               Character &character, int &bonusType) {
  pPosition tmpHead = bonusList;
  while (bonusList->next != NULL) {
    if (bonusList->x == x && bonusList->y == y && bonusList->skin == '?') {
      bool end = false;
      switch (bonusType) {
        case 0:  // Bonus name: "BUNCH OF BANANAS"
          pointsOnScreen += 50;
          end = true;
          break;
        case 1:  // Bonus name: "CRATE OF BANANAS"
          pointsOnScreen += 300;
          end = true;
          break;
        case 2:  // Bonus name: "SUPPLY OF BANANAS"
          pointsOnScreen += 1000;
          end = true;
          break;
        case 3:  // Malus name: "ROTTEN BANANAS"
          pointsOnScreen -= 100;
          end = true;
          break;
        case 4:  // Malus name: "BANANAS SPIDER"
          character.decreaseLife(10);
          end = true;
          break;
        case 5:  // Malus name: "MONKEY TRAP"
          character.decreaseLife(30);
          end = true;
          break;
        case 6:  // Bonus name: "EAT 1 BANANA [+10 HP]"
          character.increaseLife(10);
          if(character.getLife() > 100) { character.setLife(100);}
          end = true;
          break;
        case 7:  // Bonus name: "EAT 2 BANANA [+20 HP]"
          character.increaseLife(20);
          if(character.getLife() > 100) { character.setLife(100);}
          end = true;
          break;
        case 8:  // Bonus name: "BANANA SMOOTHIE [+40 HP]"
          character.increaseLife(40);
          if(character.getLife() > 100) { character.setLife(100);}
          end = true;
          break;
        case 9:  // Bonus name: "PEEL LOADER [+12 PEELS]"
          character.getGun().increaseAmmo(20);
          end = true;
          break;
        case 10:  // Bonus name: "PEEL BOX [+20 PEELS]"
          character.getGun().increaseAmmo(40);
          end = true;
          break;
        case 11:  // Bonus name: "PEACE MISSION [+100 PEELS]"
          character.getGun().increaseAmmo(100);
          end = true;
          break;
          /*
          case n:     // Malus name: "BANANA FRAGRANCE"
            int tmpQuantity = 3, tmpRound = round;
            enemyList = generateEnemy (&tmpQuantity, 'X', 10, 100, enemyList,
          tmpRound, drawWindow); drawWindow.printEnemy (enemyList, drawWindow);
            end = true;
            break;
            */
      }
      if (end) {
        bonusList = deletePosition(tmpHead, bonusList);
        return bonusList;
      }
    }
    bonusList = bonusList->next;
  }
  return tmpHead;
}

void EngineGame::checkDeath(bool &pause, Character &character) {
  if (character.getLife() <= 0) {
    character.setNumberLife(character.getNumberLife() - 1);
    if (character.getNumberLife() > 0) {
      character.setLife(100);
    }
  }
  if (character.getNumberLife() <= 0) {
    pause = true;
  }
}

void EngineGame::checkMountainDamage(Pbullet bulletList, bool isPlayer,
                                     pPosition &mountainList, int damage) {
  pPosition tmpMountainList = mountainList;
  int extraRange = -2;
  if (isPlayer) extraRange = 2;
  while (bulletList != NULL) {
    while (tmpMountainList != NULL) {
      if (bulletList->x + extraRange == tmpMountainList->x &&
          bulletList->y == tmpMountainList->y) {
        tmpMountainList->life -= damage;
        if (tmpMountainList->life <= 0)
          mountainList = deletePosition(mountainList, tmpMountainList);
      }
      tmpMountainList = tmpMountainList->next;
    }
    tmpMountainList = mountainList;

    bulletList = bulletList->next;
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
        clear();
        drawWindow.loseScreen(direction);
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

void EngineGame::money(int &bananas, pEnemyList enemyList, int maxRound,
                       // int &roundPayed, Gun &playerGun) {  // SISTEMA DI
                       // VALUTA CHE GENERA DA 1 A 3 BANANE AD OGNI
                       int &roundPayed,
                       Character &character) {  // SISTEMA DI VALUTA CHE GENERA
                                                // DA 1 A 3 BANANE AD OGNI
                                                // CLEAR DEL LIVELLO
  srand(time(NULL));
  if (enemyList->next == NULL &&
      maxRound != roundPayed) {  // CONTROLLA CHE LA STANZA SIA PULITA E CHE
                                 // L'ULTIMO ROUND SIA STATO PAGATO
    bananas = bananas + rand() % 3 + 1;
    if (maxRound >= 3 && maxRound <= 5) {
      character.increaseAmmo(30);
    } else if (maxRound > 5 && maxRound <= 8) {
      character.increaseAmmo(50);
    } else if (maxRound > 8 && maxRound <= 12) {
      character.increaseAmmo(60);
    } else if (maxRound > 15) {
      character.increaseAmmo(80);
    }
    roundPayed++;
  }
}

void EngineGame::printList(pPosition list) {
  int i = 2;
  while (list != NULL) {
    mvprintw(i, 0, "Vita montagna  %d", list->life);
    list = list->next;
    i++;
  }
}

void EngineGame::getInput(int &direction) { direction = getch(); }

void EngineGame::isPause(int &direction, bool &pause) {
  if (direction == 27) pause = true;
}

void EngineGame::pointOnScreen(
    float &pointOnScreen,
    pEnemyList EnemyList) {  // GESTISCE QUANTO VELOCEMENTE AUMENTA IL PUNTEGGIO
                             // A SCHERMO
  if (EnemyList->next != NULL) pointOnScreen = pointOnScreen + 0.5;
}

void EngineGame::runGame(Character character, DrawWindow drawWindow,
                         int direction) {
  bool upgradeBuyed = false;
  bool bonusPicked = false;
  float pointsOnScreen = 0;
  long points = 0;
  int powerUpDMG = 0;  // NUMERO DI POWERUP AL DANNO AQUISTATI
  int bananas = 0;
  int roundPayed = 0;
  int bonusTime = 0, upgradeTime = 0;
  int bonusType = 0, upgradeType = 0;
  //int monsterCount = 1, bonusCount = 1;
  int monsterCount = 1;
  int round = 0, maxRound = 1;
  pEnemyList enemyList = NULL;
  pPosition mountainList = new Position;
  pPosition bonusList = new Position;
  pRoom roomList = new Room;
  Gun basicEnemyGun('-', 10, -1);
  // Gun basicPlayerGun ('~', 25);
  while (!pause) {
    roomList =
        drawWindow.changeRoom(character, monsterCount, round,
                              enemyList, mountainList, bonusList, roomList,
                              maxRound);
    enemyList = generateEnemy(&monsterCount, 'E', basicEnemyGun, 100, enemyList,
                              round, drawWindow);

    getInput(direction);
    moveCharacter(drawWindow, character, direction, roomList, enemyList, round,
                  pointsOnScreen, bananas, powerUpDMG, bonusPicked, bonusType,
                  bonusTime, upgradeBuyed, upgradeType, upgradeTime);
    pointOnScreen(pointsOnScreen, enemyList);
    clear();
    drawWindow.printCharacter(character.getX(), character.getY(),
                              character.getSkin());
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->widht,
                        this->height, enemyList, round, false);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->widht,
                         this->height, &pointsOnScreen, character, enemyList,
                         powerUpDMG, bananas, maxRound, roomList);
    drawWindow.printCharacterStats(enemyList, character);

    if (drawWindow.lenghtRoom(roomList) > 1) {
      drawWindow.printMountain(roomList->next->mountainList);
      drawWindow.printBonus(roomList->next->bonusList);
      //drawWindow.printBonus(roomList->bonusList);
      // printList(roomList->next->mountainList);
      checkMountainDamage(this->shoots, true, roomList->next->mountainList, 1);
      checkMountainDamage(this->shootsEnemys, false,
                          roomList->next->mountainList, 1);
    }

    increaseCount(this->whileCount, points, enemyList);
    drawWindow.printEnemy(enemyList, drawWindow);
    drawWindow.moveEnemy(enemyList, character, drawWindow, points);

    shootBullet(character.getGun());  // Sparo del player
    shootEnemyBullet();               // Sparo dei nemici

    enemyShootBullets(enemyList);
    checkEnemyCollision(character, enemyList);

    money(bananas, enemyList, maxRound, roundPayed, character);
    checkShootEnemyCollision(enemyList, character, this->shoots, 1);
    checkShootEnemyCollision(enemyList, character, this->shootsEnemys, -1);
    refresh();

    destroyBullet(this->shoots, 1);
    destroyBullet(this->shootsEnemys, -1);
    checkDeath(pause, character);

    showBonusOnScreen(upgradeBuyed, upgradeType, upgradeTime, bonusPicked, bonusType,
              bonusTime);
    timeout(50);
    isPause(direction, pause);
  }
}
// x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD