#include "drawWindow.hpp"
#include "engineGame.hpp"

#include <ncurses.h>

#include <cmath>
#include <ctime>
#include <iostream>


// Numero di casi dello switch che gestisce i bonus. Equivale a: n bonus
#define N_SWITCH_CASE 15

const int scoreForKill = 300;
float finalScore = 0;

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

Pbullet EngineGame::createBullet(Character character, bool isPlayerBullet,
                                 bool moveFoward, Pbullet &shoots) {
  Pbullet bullet = new Bullet;
  bullet->x = character.getX();
  bullet->y = character.getY();
  bullet->speed = 1;
  bullet->skin = character.getGun().getBulletSkin();
  bullet->isPlayerBullet = isPlayerBullet;
  bullet->moveFoward = moveFoward;
  bullet->next = shoots;
  return bullet;
}

void EngineGame::enemyShootBullets(pEnemyList listEnemy, Character character) {
  while (listEnemy != NULL) {
    if (this->whileCountEnemy % 20 == 0) {
      bool shootFoward = false;
      if (character.getX() >
          listEnemy->enemy.getX())  // Se il player è alla sx del nemico
        shootFoward = true;         // Lo sparo sarà verso sx
      this->shootsEnemys =
          // Colpo del nemico -> false; Sparo avanti/indieto -> moveFoward
          createBullet(listEnemy->enemy, false, shootFoward,
                       this->shootsEnemys);
    }
    listEnemy = listEnemy->next;
  }
}

void EngineGame::shootPlayerBullet(Gun playerGun) {
  Pbullet bullet = this->shoots;
  while (bullet != NULL) {
    if (bullet->moveFoward)
      bullet->x += bullet->speed;
    else
      bullet->x -= bullet->speed;
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
    if (bullet->moveFoward)
      bullet->x += bullet->speed;
    else
      bullet->x -= bullet->speed;
    ;
    move(bullet->y, bullet->x);
    printw("-");
    // printw((const char *)enemyGun.getBulletSkin());
    bullet = bullet->next;
  }
}

void EngineGame::destroyBullet(Pbullet &shoots) {
  Pbullet head = shoots, prev = shoots, tmp;
  while (head != NULL) {
    int range = -1;
    if (head->moveFoward) range = 1;
    /* isPlayerBullet è da passare alla funzione
    int range = 0;
    if (isPlayerBullet) {                 // Se spara il player
      if (head->moveFoward) range = 1;    // e spara in avanti (verso dx)
      else range = -1; // 0;
    } else {                              // Se spara il nemico
      if (head->moveFoward) range = 1;    // e spara in avanti (verso sx)
      else range = -1; // 0;
    }
    */
    bool mustDestroyCondition = !isEmpty(head->x + range, head->y) &&
                        !isBonus(head->x + range, head->y);
    if (head->isPlayerBullet == false)
      mustDestroyCondition &= !isEnemy(head->x + range, head->y);


    if (mustDestroyCondition || head->x > 70 || head->x < 23) {
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
  pEnemyList tmp = enemyList;
  while (enemyList != NULL) {
    if ((character.getX() - 1 == enemyList->enemy.getX() &&
         character.getY() == enemyList->enemy.getY()) ||
        (character.getX() == enemyList->enemy.getX() &&
         character.getY() + 1 == enemyList->enemy.getY()) ||
        (character.getX() == enemyList->enemy.getX() &&
         character.getY() - 1 == enemyList->enemy.getY())) {
      character.decreaseLife(
          1);  // In uno scontro fisico il player perde 1 di vita
      enemyList->enemy.decreaseLife(
          2);  // In uno scontro fisico il nemico perde 2 di vita

      if (enemyList->enemy.getLife() <= 0)
        enemyList = destroyEnemy(tmp, enemyList->enemy);

      init_pair(13, COLOR_RED, -1);
      attron(COLOR_PAIR(13));
      mvprintw(character.getY(), character.getX(),
               "M");  // Il player diventa rosso quando si scontra coi nemici
      mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(),
               "E");  // Il nemico diventa rosso quando si scontra col player
      attroff(COLOR_PAIR(13));
    }

    if (character.getX() + 1 == enemyList->enemy.getX() &&
        character.getY() == enemyList->enemy.getY()) {  // collissione frontale
      character.decreaseLife(1);

      init_pair(13, COLOR_RED, -1);
      attron(COLOR_PAIR(13));
      mvprintw(character.getY(), character.getX(),
               "M");  // Il player diventa rosso quando si scontra coi nemici
      attroff(COLOR_PAIR(13));
    }
    enemyList = enemyList->next;
  }
}

void EngineGame::checkShootEnemyCollision(pEnemyList enemyList,
                                          Character &character, Pbullet &shoots,
                                          float &pointOnScreen,
                                          bool immortalityCheck) {
  bool isCollisionEnemy = false, isCollisionCharacter = false, pause = false;
  Pbullet head = shoots;
  pEnemyList tmp = enemyList;
  // int range = -1;
  while (enemyList != NULL && !isCollisionEnemy &&
         !isCollisionCharacter) {  // Per ogni nemico
    while (shoots != NULL && !isCollisionEnemy &&
           !isCollisionCharacter) {  // Per ogni priettile di ogni nemico
      /* NON CANCELLARE - Utile per capire meglio il sottostante codice ridotto
      if (shoots->isPlayerBullet) {     // Colpo del player
        int x = enemyList->enemy.getX(), y = enemyList->enemy.getY();
        if (shoots->moveFoward) {         // Sparato verso dx
          if (x == shoots->x + 1 && y == shoots->y) // Ergo si ha +1
            isCollisionEnemy = true;
        } else {                          // Sparato verso sx
          if (x == shoots->x - 1 && y == shoots->y) // Ergo si ha -1
            isCollisionEnemy = true;
        }
      } else {                          // Colpo del nemico
        int x = character.getX(), y = character.getY();
        if (shoots->moveFoward) {         // Sparato verso sx
          if (x == shoots->x + 1 && y == shoots->y) // Ergo si ha -1
            isCollisionCharacter = true;
        } else {                          // Sparato verso dx
          if (x == shoots->x - 1 && y == shoots->y) // Ergo si ha +1
            isCollisionCharacter = true;
        }
      }
      */
      if (shoots->isPlayerBullet) {  // Colpo del player
        int x = enemyList->enemy.getX(), y = enemyList->enemy.getY();
        if ((x == shoots->x + 1 && y == shoots->y) ||
            (x == shoots->x - 1 &&
             y == shoots->y))  // Controllo valido per i foward and backward
                               // bullets del player
          isCollisionEnemy = true;
      } else {  // Colpo del nemico
        int x = character.getX(), y = character.getY();
        if ((x == shoots->x + 1 && y == shoots->y) ||
            (x == shoots->x - 1 &&
             y == shoots->y))  // Controllo valido per i foward and backward
                               // bullets del nemico
          isCollisionCharacter = true;
      }
      shoots = shoots->next;
    }
    shoots = head;
    if (isCollisionEnemy || isCollisionCharacter)
      break;
    else
      enemyList = enemyList->next;
  }

  init_pair(13, COLOR_RED, -1);
  attron(COLOR_PAIR(13));

  if (isCollisionEnemy) {
    mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(),
             "E");  // Il nemico diventa rosso quando viene colpito dal
                    // proiettile del player
    enemyList->enemy.decreaseLife(character.getGun().getDamage());
    if (enemyList->enemy.getLife() <= 0) {
      enemyList = destroyEnemy(tmp, enemyList->enemy);
      increasePointOnScreen(pointOnScreen, scoreForKill);
    }
  } else if (isCollisionCharacter && immortalityCheck == false) {
    character.decreaseLife(enemyList->enemy.getGun().getDamage());
    checkDeath(pause, character);

    // Skin del player rossa qunado viene colpito
    mvprintw(character.getY(), character.getX(), "M");
  }

  attroff(COLOR_PAIR(13));
}

bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }
bool EngineGame::isBonus(int x, int y) { return mvinch(y, x) == '?'; }
bool EngineGame::isMountain(int x, int y) { return mvinch(y, x) == '^'; }
bool EngineGame::isEnemy(int x, int y) { return mvinch(y, x) == 'E'; }

void EngineGame::moveCharacter(DrawWindow drawWindow, Character &character,
                               int direction, pRoom &roomList,
                               pEnemyList enemyList, int round,
                               float &pointsOnScreen, int &bananas,
                               int &powerUpDMG, bool &bonusPicked,
                               int &bonusType, int &bonusTime,
                               bool &upgradeBuyed, int &upgradeType,
                               int &upgradeTime, bool &immortalityCheck, int &immortalityTime) {
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
        bonusType = rand() % N_SWITCH_CASE;  // 0 <= bonusType < N_SWITCH_CASE
        roomList->bonusList =
            getBonus(drawWindow, character.getX(), character.getY() - 1,
                     roomList->next->bonusList, enemyList, round,
                     pointsOnScreen, character, bonusType, immortalityCheck, immortalityTime);
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
        roomList->bonusList =
            getBonus(drawWindow, character.getX(), character.getY() + 1,
                     roomList->next->bonusList, enemyList, round,
                     pointsOnScreen, character, bonusType, immortalityCheck, immortalityTime);
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
        roomList->bonusList =
            getBonus(drawWindow, character.getX() - 1, character.getY(),
                     roomList->next->bonusList, enemyList, round,
                     pointsOnScreen, character, bonusType, immortalityCheck, immortalityTime);
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
        roomList->bonusList =
            getBonus(drawWindow, character.getX() + 1, character.getY(),
                     roomList->next->bonusList, enemyList, round,
                     pointsOnScreen, character, bonusType, immortalityCheck, immortalityTime);
        character.directionRight();
      }
      break;
    case 'E':  // Sparo in avanti del player
    case 'e':
      if (whileCount / 2 > 1 && character.getGun().getTotalAmmo() > 0 &&
          character.getGun().getMagazineAmmo() > 0) {
        character.decreaseTotalAmmo(1);
        character.decreaseMagazineAmmo(1);
        this->shoots = createBullet(character, true, true, this->shoots);
        whileCount = 0;
      }
      break;
    case 'W':  // Sparo all'indietro del player
    case 'w':
      if (whileCount / 2 > 1 && character.getGun().getTotalAmmo() > 0 &&
          character.getGun().getMagazineAmmo() > 0) {
        character.decreaseTotalAmmo(1);
        character.decreaseMagazineAmmo(1);
        this->shoots = createBullet(character, true, false, this->shoots);
        whileCount = 0;
      }
      break;
    case 'R':
    case 'r':
      if (character.getGun().getMagazineAmmo() >= 0 &&
          character.getGun().getMagazineAmmo() <
              character.getGun().getMagazineCapacity() &&
          character.getGun().getTotalAmmo() > 0)
        character.reload();
      break;
    case 'a':  // CONTROLLA L'AQUISTO DI VITE, MASSIMO 3 -------------------
    case 'A':
      if (bananas >= upgradeCost && character.getNumberLife() < 3) {
        upgradeBuyed = true;  // INDICA CHE È STATO COMPRATO UN UPGRADE
        upgradeType = 0;      // INDICA IL TIPO DI UPGRADE.
        upgradeTime = 0;  // RESETTA IL TEMPO DI APPARIZIONE SE HAI COMPRATO UN
                          // ALTRO UPGRADE
        character.setNumberLife(character.getNumberLife() + 1);
        bananas = bananas - upgradeCost;
      }
      break;
    case 's':  // CONTROLLA L'AQUISTO DI POWERUP AL DANNO, SONO ACQUISTABILI AL
               // MASSIMO 4 DURANTE TUTTA LA RUN
    case 'S':
      if (bananas >= upgradeCost && powerUpDMG < 4) {
        upgradeBuyed = true;
        upgradeType = 1;
        upgradeTime = 0;
        character.increaseDamageGun(10);
        bananas = bananas - upgradeCost;
        powerUpDMG++;
      }
      break;
  }
}

void EngineGame::gorillaPunch(int direction, Character &character,
                              pEnemyList enemyList, float &pointOnScreen) {
  pEnemyList tmp = enemyList;

  if (direction == 32) {
    mvprintw(character.getY(), character.getX() + 1, "o");

    while (enemyList != NULL) {
      if (character.getX() + 1 == enemyList->enemy.getX() &&
          character.getY() == enemyList->enemy.getY()) {
        enemyList->enemy.decreaseLife(40);

        if (enemyList->enemy.getLife() <= 0) {
          enemyList = destroyEnemy(tmp, enemyList->enemy);
          increasePointOnScreen(pointOnScreen, scoreForKill);
        }

        init_pair(13, COLOR_RED, -1);
        attron(COLOR_PAIR(13));
        mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(),
                 "E");  // Il nemico diventa rosso quando si scontra col player
        attroff(COLOR_PAIR(13));
      }
      enemyList = enemyList->next;
    }
  }
}

void EngineGame::showBonusOnScreen(bool &upgradeBuyed, int &upgradeType,
                                   int &upgradeTime, bool &bonusPicked,
                                   int bonustype, int &bonusTime,
                                   bool &immortalityCheck,
                                   int &immortalityTime) {
  int x = 25;
  int y = 6;
  int disclaimerTimeLimit = 40;
  int immortalityTimeLimit = 120;

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
    mvprintw(y, x, "PEEL LOADER [+20 PEELS]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 10) {
    mvprintw(y, x, "PEEL LOADER [+40 PEELS]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 11) {
    mvprintw(y, x, "PEACE MISSION [+100 PEELS]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 12) {
    mvprintw(y, x, "PISSED OF ENEMY MONKEYS");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 13) {
    mvprintw(y, x, "PEELS ON FIRE! [+5 DAMAGE]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 14) {
    mvprintw(y, x, "MONKEY GOD! [IMMORTALITY]");
    bonusTime++;
  }
  if (immortalityCheck == true) {
    init_pair(24, -1, COLOR_MAGENTA);
    attron(COLOR_PAIR(24));
    mvprintw(22, 56, "                    ");
    attroff(COLOR_PAIR(24));
    immortalityTime++;
  }

  if (bonusTime >
      disclaimerTimeLimit) {  // LASCIA IL BONUS VISIBILE PER "X" CICLI
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

  if (immortalityTime >
      immortalityTimeLimit) {  //   GESTISCE LA DURATA DELL'IMMORTALITÀ
    immortalityCheck = false;
    immortalityTime = 0;
  }

  if (upgradeTime >
      disclaimerTimeLimit) {  // STESSO DI SOPRA MA CON GLI UPGRADE
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

pEnemyList EngineGame::generateNormalEnemy(int *monsterCount, char skin,
                                           Gun gun, int life, pEnemyList list,
                                           int &round, DrawWindow drawWindow) {
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
                               pPosition bonusList, pEnemyList &enemyList,
                               int round, float &pointsOnScreen,
                               Character &character, int &bonusType, bool &immortalitycheck, int &immortalityTime) {
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
          if (character.getLife() > 100) {
            character.setLife(100);
          }
          end = true;
          break;
        case 7:  // Bonus name: "EAT 2 BANANA [+20 HP]"
          character.increaseLife(20);
          if (character.getLife() > 100) {
            character.setLife(100);
          }
          end = true;
          break;
        case 8:  // Bonus name: "BANANA SMOOTHIE [+40 HP]"
          character.increaseLife(40);
          if (character.getLife() > 100) {
            character.setLife(100);
          }
          end = true;
          break;
        case 9:  // Bonus name: "PEEL LOADER [+20 PEELS]"
          character.increaseTotalAmmo(20);
          end = true;
          break;
        case 10:  // Bonus name: "PEEL BOX [+40 PEELS]"
          character.increaseTotalAmmo(40);
          end = true;
          break;
        case 11:  // Bonus name: "PEACE MISSION [+100 PEELS]"
          character.increaseTotalAmmo(100);
          end = true;
          break;
        case 12:  // Malus name: "PISSED OFF MONKEYS"
          while (enemyList != NULL) {
            enemyList->enemy.increaseLife(25);  // Aumenta la vita dei nemici
            Gun tmpBetterGun = enemyList->enemy.getGun();
            tmpBetterGun.increaseDamage(10);  // Aumenta il danno dei nemici
            enemyList->enemy.setGun(tmpBetterGun);
            enemyList = enemyList->next;
          }
          end = true;
          break;
        case 13:  // Bonus name: "PEELS ON FIRE! [+5 DAMAGE]"
          if (character.getGun().getDamage() < 40) {
            Gun tmpBetterGun = character.getGun();
            tmpBetterGun.increaseDamage(
                5);  // Aumenta il danno dell'arma del player
            character.setGun(tmpBetterGun);
          } else
            character.getGun().increaseTotalAmmo(30);
          end = true;
          break;
        case 14:  // Bonus name: "MONKEY GOD! [IMMORTALITY]"
          immortalityTime = 0;
          immortalitycheck = true;
          end = true;
          break;
          /*
         case n:     // Malus name: "BANANA FRAGRANCE" // Genera n nemici
             int tmpQuantity = 3, tmpRound = round;
             enemyList = generateNormalEnemy (&tmpQuantity, 'X', 10, 100,
         enemyList, tmpRound, drawWindow); drawWindow.printEnemy (enemyList,
         drawWindow); end = true; break;
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
        drawWindow.loseScreen(direction, finalScore);
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
    if (maxRound >= 2 && maxRound <= 5) {
      character.increaseTotalAmmo(25);
    } else if (maxRound > 5 && maxRound <= 8) {
      character.increaseTotalAmmo(40);
    } else if (maxRound > 8 && maxRound <= 12) {
      character.increaseTotalAmmo(50);
    } else if (maxRound > 15) {
      character.increaseTotalAmmo(80);
    }
    roundPayed++;
  }
  init_pair(20, COLOR_GREEN, -1);
  attron(COLOR_PAIR(20));
  if (bananas >= 10) {
    mvprintw(24, 52, "UPGRADE PURCHASABLE!");
  }
  attroff(COLOR_PAIR(20));
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

void EngineGame::increasePointOnScreen(float &pointOnScreen, int pointsAdded) {
  pointOnScreen += pointsAdded;
}

void EngineGame::runGame(Character character, DrawWindow drawWindow,
                         int direction) {
  bool upgradeBuyed = false, bonusPicked = false;
  bool immortalityCheck = false;
  float pointsOnScreen = 0;
  long points = 0;
  int powerUpDMG = 0;  // NUMERO DI POWERUP AL DANNO AQUISTATI
  int bananas = 0;
  int roundPayed = 0;
  int immortalityTime = 0;
  int bonusTime = 0, upgradeTime = 0;
  int bonusType = 0, upgradeType = 0;
  // int monsterCount = 1, bonusCount = 1;
  int monsterCount = 1;
  int round = 0, maxRound = 1;
  pEnemyList enemyList = NULL;
  pPosition mountainList = new Position;
  pPosition bonusList = new Position;
  pRoom roomList = new Room;
  Gun basicEnemyGun('-', 10, -1, -1);  // CHANGE
  clear();
  while (!pause) {
    roomList =
        drawWindow.changeRoom(character, monsterCount, round, enemyList,
                              mountainList, bonusList, roomList, maxRound);
    enemyList = generateNormalEnemy(&monsterCount, 'E', basicEnemyGun, 100,
                                    enemyList, round, drawWindow);

    getInput(direction);
    moveCharacter(drawWindow, character, direction, roomList, enemyList, round,
                  pointsOnScreen, bananas, powerUpDMG, bonusPicked, bonusType,
                  bonusTime, upgradeBuyed, upgradeType, upgradeTime,
                  immortalityCheck, immortalityTime);
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
      checkMountainDamage(this->shoots, true, roomList->next->mountainList, 1);
      checkMountainDamage(this->shootsEnemys, false,
                          roomList->next->mountainList, 1);
    }

    increaseCount(this->whileCount, points, enemyList);
    drawWindow.printEnemy(enemyList, drawWindow);
    drawWindow.moveEnemy(enemyList, character, drawWindow, points);

    shootPlayerBullet(character.getGun());  // Sparo del player
    shootEnemyBullet();                     // Sparo dei nemici

    enemyShootBullets(enemyList, character);
    checkEnemyCollision(character, enemyList);
    gorillaPunch(direction, character, enemyList, pointsOnScreen);

    money(bananas, enemyList, maxRound, roundPayed, character);
    checkShootEnemyCollision(enemyList, character, this->shoots, pointsOnScreen,
                             immortalityCheck);
    checkShootEnemyCollision(enemyList, character, this->shootsEnemys,
                             pointsOnScreen, immortalityCheck);
    refresh();

    destroyBullet(this->shoots);  // Check per i colpi sparati dai nemici (???)
    destroyBullet(
        this->shootsEnemys);  // Check per i colpi sparati dal player (???)

    showBonusOnScreen(upgradeBuyed, upgradeType, upgradeTime, bonusPicked,
                      bonusType, bonusTime, immortalityCheck, immortalityTime);
    checkDeath(pause, character);

    timeout(50);
    isPause(direction, pause);
    finalScore = pointsOnScreen;
  }
}
// x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD
