#include "drawWindow.hpp"
#include "engineGame.hpp"

#include <ncurses.h>

#include <cmath>
#include <ctime>
#include <iostream>


// Numero di casi dello switch che gestisce i bonus. Equivale a: n bonus
#define N_SWITCH_CASE 15
#define SPECIAL_ENEMY_FREQUENCY 5 // Spawn ogni 5 round
#define BOSS_ENEMY_FREQUENCY 10   // Spawn ogni 10 round

const int scoreForKill = 300;
float finalScore = 0;

EngineGame::EngineGame(int frameGameX, int frameGameY, int height, int width) {
  this->frameGameX = frameGameX;
  this->frameGameY = frameGameY;
  this->height = height;
  this->widht = width;
  this->playerBullets = NULL;
  this->normalEnemyBullets = NULL;
  this->quit = false;
  this->pause = true;
  // this->isEnemyShoots = false;
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

Pbullet EngineGame::generateBullets(Character character, bool isPlayerBullet,
                                    bool moveFoward, Pbullet &bulletList) {
  Pbullet bullet = new Bullet;
  bullet->x = character.getX();
  bullet->y = character.getY();
  bullet->speed = 1;
  bullet->skin = character.getGun().getBulletSkin();
  bullet->isPlayerBullet = isPlayerBullet;
  bullet->moveFoward = moveFoward;
  bullet->next = bulletList;
  return bullet;
}

void EngineGame::generateEnemyBullets(pEnemyList enemyList, Pbullet &enemyBulletList,
                                      Character character) {
  bool shootFoward;
  while (enemyList != NULL) {
    if (this->whileCountEnemy % 20 == 0) {
      shootFoward = true;
      // Se il player è alla sx del nemico, spara a sx
      if (character.getX() > enemyList->enemy.getX())
        shootFoward = false;
      // Colpo del nemico -> false; Sparo avanti/indieto -> moveFoward
      enemyBulletList = generateBullets(enemyList->enemy, false, shootFoward, this->normalEnemyBullets);
    }
    enemyList = enemyList->next;
  }
}

void EngineGame::shootPlayerBullet() {
  Pbullet bulletList = this->playerBullets;
  char tmp[2];
  while (bulletList != NULL) {
    if (bulletList->moveFoward)
      bulletList->x += bulletList->speed;
    else
      bulletList->x -= bulletList->speed;
    move(bulletList->y, bulletList->x);
    init_pair(10, COLOR_YELLOW, -1);  // SPARA BANANE GIALLE
    attron(COLOR_PAIR(10));
    tmp[0] = bulletList->skin;
    printw(tmp);
    attroff(COLOR_PAIR(10));
    bulletList = bulletList->next;
  }
}

void EngineGame::shootEnemyBullet(Pbullet enemyBulletList) {
  //Pbullet bulletList = this->normalEnemyBullets;
  Pbullet bulletList = enemyBulletList;
  char tmpSkin[2];
  while (bulletList != NULL) {
    if (bulletList->moveFoward)
      bulletList->x -= bulletList->speed;
    else
      bulletList->x += bulletList->speed;
    move(bulletList->y, bulletList->x);
    tmpSkin[0] = bulletList->skin;
    printw(tmpSkin);
    bulletList = bulletList->next;
  }
}

void EngineGame::destroyBullet(Pbullet &bulletList) {
  Pbullet head = bulletList, prev = bulletList, tmp;
  bool mustDestroyCondition = false;
  int range;
  while (head != NULL) {
    range = -1;
    if ((head->isPlayerBullet && head->moveFoward) ||
        (!head->isPlayerBullet && !head->moveFoward))
      range = 1;

    mustDestroyCondition = !isEmpty(head->x + range, head->y) &&
                           !isBonus(head->x + range, head->y) && !isBullet(head->x + range, head->y);
    if (!head->isPlayerBullet)  // HO rimesso questo
      mustDestroyCondition &= !isEnemy(head->x + range, head->y);

    // if (head->isPlayerBullet)
    //   mustDestroyCondition = isEnemy(head->x + range, head->y) ||
    //   isMountain(head->x + range, head->y);
    // else NON FUNZIONA?? le montagne vengono attraversate dai colpi
    //   // Le montagne non vengono colpite dai priettili perchè sono colorate
    //   mustDestroyCondition = isPlayer(head->x + range, head->y) ||
    //   isMountain(head->x + range, head->y);

    if (mustDestroyCondition || head->x > 70 || head->x < 23) {
      if (head == bulletList) {
        tmp = bulletList;
        bulletList = head->next;
        delete tmp;
        prev = bulletList;
        head = bulletList;
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

pEnemyList EngineGame::destroyEnemy(pEnemyList enemyList, Enemy enemy) {
  pEnemyList head = enemyList, prev = enemyList, tmp;
  char tmpSkin[2];
  while (enemyList != NULL) {
    if (enemyList->enemy.getX() == enemy.getX() &&
        enemyList->enemy.getY() == enemy.getY()) {
      tmpSkin[0] = enemyList->enemy.getSkin();
      mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);
      if (enemyList == head) {
        tmp = head;
        head = enemyList->next;
        delete tmp;
        prev = head;
        enemyList = head;
      } else {
        tmp = prev->next;
        prev->next = enemyList->next;
        delete tmp;
        enemyList = prev->next;
      }
    } else {
      prev = enemyList;
      enemyList = enemyList->next;
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

/**
 * Funzione per la collisione fisica tra player e nemici.
 * Controlla la presenza di uno scontro in qualsiasi direzione,
 * danneggia 1 il player, 3 il nemico (soluzione kamikaze efficace),
 * e colora di rosso i protagonisti dello scontro.
 */
void EngineGame::checkEnemyCollision(Character &character,
                                     pEnemyList enemyList) {
  pEnemyList tmp = enemyList;
  char tmpSkin[2];
  int xP = character.getX(), yP = character.getY();
  int xE, yE;
  while (enemyList != NULL) {
    xE = enemyList->enemy.getX(), yE = enemyList->enemy.getY();

    if ((xP == xE && yP + 1 == yE) || (xP == xE && yP - 1 == yE)) {
      character.decreaseLife(1);
      enemyList->enemy.decreaseLife(2);

      if (enemyList->enemy.getLife() <= 0)
        enemyList = destroyEnemy(tmp, enemyList->enemy);

      init_pair(13, COLOR_RED, -1);
      attron(COLOR_PAIR(13));
      tmpSkin[0] = character.getSkin();
      mvprintw(character.getY(), character.getX(), tmpSkin);
      tmpSkin[0] = enemyList->enemy.getSkin();
      mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);
      attroff(COLOR_PAIR(13));
    }
    enemyList = enemyList->next;
  }
}

void EngineGame::checkBulletCollision(pEnemyList enemyList,
                                      Character &character, Pbullet &bulletList,
                                      int &pointOnScreen,
                                      bool immortalityCheck) {
  bool isCollisionEnemy = false, isCollisionCharacter = false, pause = false;
  Pbullet head = bulletList;
  pEnemyList tmp = enemyList;
  while (enemyList != NULL && !isCollisionEnemy &&
         !isCollisionCharacter) {  // Per ogni nemico
    while (bulletList != NULL && !isCollisionEnemy && !isCollisionCharacter) {
      if (bulletList->isPlayerBullet) {
        int x = enemyList->enemy.getX(), y = enemyList->enemy.getY();
        if ((x == bulletList->x + 1 && y == bulletList->y) ||
            (x == bulletList->x - 1 &&
             y == bulletList->y))  // Controllo valido per i foward and backward
                                   // bullets del player
          isCollisionEnemy = true;
      } else {
        int x = character.getX(), y = character.getY();
        if ((x == bulletList->x + 1 && y == bulletList->y) ||
            (x == bulletList->x - 1 &&
             y == bulletList->y))  // Controllo valido per i foward and backward
                                   // bullets del nemico
          isCollisionCharacter = true;
      }
      bulletList = bulletList->next;
    }
    bulletList = head;
    if (isCollisionEnemy || isCollisionCharacter)
      break;
    else
      enemyList = enemyList->next;
  }

  init_pair(13, COLOR_RED, -1);
  attron(COLOR_PAIR(13));
  char tmpSkin[2];
  if (isCollisionEnemy) {
    tmpSkin[0] = enemyList->enemy.getSkin();
    mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);
    enemyList->enemy.decreaseLife(character.getGun().getDamage());
    if (enemyList->enemy.getLife() <= 0) {
      enemyList = destroyEnemy(tmp, enemyList->enemy);
      increasePointOnScreen(pointOnScreen, scoreForKill);
    }
  } else if (isCollisionCharacter && immortalityCheck == false) {
    character.decreaseLife(enemyList->enemy.getGun().getDamage());
    checkDeath(pause, character);
    tmpSkin[0] = character.getSkin();
    mvprintw(character.getY(), character.getX(), tmpSkin);
  }
   attroff(COLOR_PAIR(13));
}

bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }
bool EngineGame::isBonus(int x, int y) { return mvinch(y, x) == '?'; }
bool EngineGame::isMountain(int x, int y) { return mvinch(y, x) == '^'; }
bool EngineGame::isPlayer(int x, int y) { return mvinch(y, x) == 'M'; }
bool EngineGame::isEnemy(int x, int y) {
  return mvinch(y, x) == 'e' || mvinch(y, x) == 'E' || mvinch(y, x) == 'B';
}
bool EngineGame::isBullet(int x, int y) {
  return mvinch(y, x) == '~' || mvinch(y, x) == '-' || mvinch(y, x) == '=' ||
         mvinch(y, x) == '*';
}
bool EngineGame::isPlayerBullet(int x, int y) { return mvinch(y, x) == '~'; }
bool EngineGame::isEnemyBullet(int x, int y) {
  return mvinch(y, x) == '-' || mvinch(y, x) == '=' || mvinch(y, x) == '*';
}

void EngineGame::moveCharacter(
    DrawWindow drawWindow, Character &character, int direction, pRoom &roomList,
    pEnemyList normalEnemyList, int round, int &pointsOnScreen, int &bananas,
    int &powerUpDMG, bool &bonusPicked, int &bonusType, int &bonusTime,
    bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
    bool &immortalityCheck, int &immortalityTime, bool &toTheRight) {
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
        roomList->bonusList = getBonus(
            drawWindow, character.getX(), character.getY() - 1,
            roomList->next->bonusList, normalEnemyList, round, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
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
        roomList->bonusList = getBonus(
            drawWindow, character.getX(), character.getY() + 1,
            roomList->next->bonusList, normalEnemyList, round, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
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
        roomList->bonusList = getBonus(
            drawWindow, character.getX() - 1, character.getY(),
            roomList->next->bonusList, normalEnemyList, round, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
        character.directionLeft();
      }
      toTheRight = false;
      break;
    case KEY_RIGHT:  // -----------------------------------------------------
      if (isEmpty(character.getX() + 1, character.getY()))
        character.directionRight();
      else if (isBonus(character.getX() + 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % N_SWITCH_CASE;
        roomList->bonusList = getBonus(
            drawWindow, character.getX() + 1, character.getY(),
            roomList->next->bonusList, normalEnemyList, round, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
        character.directionRight();
      }
      toTheRight = true;
      break;
    case 'E':  // Sparo in avanti del player
    case 'e':
      if (whileCount / 2 > 1 && character.getGun().getMagazineAmmo() > 0) {
        character.decreaseMagazineAmmo(1);
        this->playerBullets =
            generateBullets(character, true, true, this->playerBullets);
        whileCount = 0;
      }
      break;
    case 'W':  // Sparo all'indietro del player
    case 'w':
      if (whileCount / 2 > 1 && character.getGun().getMagazineAmmo() > 0) {
        character.decreaseMagazineAmmo(1);
        this->playerBullets =
            generateBullets(character, true, false, this->playerBullets);
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
      if (character.getGun().getDamage() < 50) {
        if (bananas >= upgradeCost && powerUpDMG < 4) {
          upgradeBuyed = true;
          upgradeType = 1;
          upgradeTime = 0;
          character.increaseDamageGun(10);
          if (character.getGun().getDamage() >= 50)
            character.setGunDamage(50);
          bananas = bananas - upgradeCost;
          powerUpDMG++;
        }
      } else {
        // MESSAGGIO CHE SEGNALE IL FATTO CHE QUESTO UPGRADE NON è DISPONIBILE
        //mvprintw(?, ?, "MAX DAMAGE OBTAINED");
      }
      break;
  }
}

void EngineGame::gorillaPunch(int direction, Character &character,
                              pEnemyList enemyList, int &pointOnScreen,
                              bool toTheRight) {
  pEnemyList tmp = enemyList;

  if (direction == 32) {
    if (toTheRight ==
        true) {  //---------------------------------------------------------
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
          // Il nemico diventa rosso quando si scontra col player
          char tmpSkin[0];
          tmpSkin[0] = enemyList->enemy.getSkin();
          mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);
          attroff(COLOR_PAIR(13));
        }
        enemyList = enemyList->next;
      }
    } else if (toTheRight ==
               false) {  //--------------------------------------------------
      mvprintw(character.getY(), character.getX() - 1, "o");

      while (enemyList != NULL) {
        if (character.getX() - 1 == enemyList->enemy.getX() &&
            character.getY() == enemyList->enemy.getY()) {
          enemyList->enemy.decreaseLife(40);

          if (enemyList->enemy.getLife() <= 0) {
            enemyList = destroyEnemy(tmp, enemyList->enemy);
            increasePointOnScreen(pointOnScreen, scoreForKill);
          }

          init_pair(13, COLOR_RED, -1);
          attron(COLOR_PAIR(13));
          // Il nemico diventa rosso quando si scontra col player
          char tmpSkin[0];
          tmpSkin[0] = enemyList->enemy.getSkin();
          mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);
          attroff(COLOR_PAIR(13));
        }
        enemyList = enemyList->next;
      }
    }
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
}

pEnemyList EngineGame::generateEnemy(int *enemyCount, int type, pEnemyList list,
                                     int &round, DrawWindow drawWindow) {
  // Variables 4 basic enemies
  char skin = 'e';
  int life = 100;
  Gun gun('-', 10, -1, -1);
  switch (type) {
    case 0:  // Basic enemies, no variables changes
      break;
    case 1:  // Elite enemies
      skin = 'E';
      life = 150;
      gun.setBulletSkin('=');
      gun.setDamage(20);
      break;
    case 2:  // Boss enemy
      skin = 'B';
      life = 400;
      gun.setBulletSkin('*');
      gun.setDamage(35);
      break;
  }

  bool isEmpty = false;
  while (*enemyCount > 0) {
    int x = drawWindow.randomPosition(40, 69).x;
    int y = drawWindow.randomPosition(8, 19).y;
    pEnemyList head = new EnemyList;
    Enemy enemy(x, y, skin, life, 1, gun);
    head->enemy = enemy;
    head->next = list;
    *enemyCount -= 1;
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
                               int round, int &pointsOnScreen,
                               Character &character, int &bonusType,
                               bool &immortalitycheck, int &immortalityTime) {
  pPosition tmpHead = bonusList;
  bool end;
  while (bonusList->next != NULL) {
    if (bonusList->x == x && bonusList->y == y && bonusList->skin == '?') {
      end = false;
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
        case 4:  // Malus name: "BANANAS SPIDER [-10 HP]"
          if (character.getNumberLife() == 1 && character.getLife() <= 10)
            character.setLife(5);
          else
            character.decreaseLife(10);
          end = true;
          break;
        case 5:  // Malus name: "MONKEY TRAP [-30 HP]"
          if (character.getNumberLife() == 1 && character.getLife() <= 30)
            character.setLife(5);
          else
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
          if (character.getGun().getDamage() < 50) {
            Gun tmpBetterGun = character.getGun();
            tmpBetterGun.increaseDamage(5);
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

/**
 * Funzione per stabilire se e quanti nemici non-normali bisogna generare.
*/
void EngineGame::checkEnemyGeneration(pRoom &room, int maxRound, int &specialEnemyCount, int &bossEnemyCount) {
  if (maxRound % SPECIAL_ENEMY_FREQUENCY == 0 && room->spawnSpecialEnemy) {
    if (maxRound <= 10) specialEnemyCount = 2;
    else if (maxRound == 15) specialEnemyCount = 3;
    else if (maxRound > 15) specialEnemyCount = 4;
    room->spawnSpecialEnemy = false;
  } else if (maxRound % BOSS_ENEMY_FREQUENCY == 0 && room->spawnBossEnemy) {
    if (maxRound <= 10) bossEnemyCount = 1;
    else if (maxRound == 20) bossEnemyCount = 2;
    else if (maxRound >= 30) bossEnemyCount = 3;
    room->spawnBossEnemy = false;
  } else {
    specialEnemyCount = 0;
    bossEnemyCount = 0;
  }
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

void EngineGame::checkMountainDamage(Pbullet bulletList,
                                     pPosition &mountainList) {
  pPosition tmpMountainList = mountainList;
  int range;
  while (bulletList != NULL) {
    range = -2;
    if ((bulletList->isPlayerBullet && bulletList->moveFoward) ||
        (!bulletList->isPlayerBullet && !bulletList->moveFoward))
      range = 2;

    while (tmpMountainList != NULL) {
      if (bulletList->x + range == tmpMountainList->x &&
          bulletList->y == tmpMountainList->y) {
        tmpMountainList->life -= 1;
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
      clear();
        drawWindow.HowToPlay(direction);
        selection = 4;
        break;
      case 2:
        clear();
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

void EngineGame::increasePointOnScreen(int &pointOnScreen, int pointsAdded) {
  pointOnScreen += pointsAdded;
}

void EngineGame::runGame(Character character, DrawWindow drawWindow,
                         int direction) {
  bool toTheRight = true;
  bool upgradeBuyed = false, bonusPicked = false, immortalityCheck = false;
  int immortalityTime = 0;
  int pointsOnScreen = 0;
  long points = 0;
  int powerUpDMG = 0;  // NUMERO DI POWERUP AL DANNO AQUISTATI
  int bananas = 0, roundPayed = 0;
  int bonusTime = 0, upgradeTime = 0, bonusType = 0, upgradeType = 0;
  int normalEnemyCount = 1, specialEnemyCount = 0, bossEnemyCount = 0;
  int round = 0, maxRound = 1;
  pEnemyList normalEnemyList = NULL, specialEnemyList = NULL,
             bossEnemyList = NULL;
  pPosition mountainList = new Position, bonusList = new Position;
  pRoom roomList = new Room;

  Gun basicPlayerGun('~', 25, 40, 10);
  character.setGun(basicPlayerGun);
  clear();
  while (!pause) {
    roomList = drawWindow.changeRoom(character, normalEnemyCount, round,
                                     normalEnemyList, mountainList, bonusList,
                                     roomList, maxRound);
    normalEnemyList =
        generateEnemy(&normalEnemyCount, 0, normalEnemyList, round, drawWindow);

    if (roomList->spawnSpecialEnemy || roomList->spawnBossEnemy)
      checkEnemyGeneration (roomList, maxRound, specialEnemyCount, bossEnemyCount);

    if (specialEnemyCount > 0)
      specialEnemyList = generateEnemy(&specialEnemyCount, 1, specialEnemyList, round, drawWindow);
    if (bossEnemyCount > 0)
      bossEnemyList = generateEnemy(&bossEnemyCount, 2, bossEnemyList, round, drawWindow);
    getInput(direction);
    moveCharacter(drawWindow, character, direction, roomList, normalEnemyList,
                  round, pointsOnScreen, bananas, powerUpDMG, bonusPicked,
                  bonusType, bonusTime, upgradeBuyed, upgradeType, upgradeTime,
                  immortalityCheck, immortalityTime, toTheRight);
    clear();
    drawWindow.printCharacter(character.getX(), character.getY(),
                              character.getSkin());
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->widht,
                        this->height, normalEnemyList, round, false);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->widht,
                         this->height, pointsOnScreen, character,
                         normalEnemyList, powerUpDMG, bananas, maxRound,
                         roomList);
    drawWindow.printCharacterStats(normalEnemyList, specialEnemyList, bossEnemyList, character);

    if (drawWindow.lenghtRoom(roomList) > 1) {
      drawWindow.printMountain(roomList->next->mountainList);
      drawWindow.printBonus(roomList->next->bonusList);
      checkMountainDamage(this->playerBullets, roomList->next->mountainList);
      checkMountainDamage(this->normalEnemyBullets,
                          roomList->next->mountainList);
      //checkMountainDamage(this->specialEnemyBullets,      // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
          //                roomList->next->mountainList);
      //checkMountainDamage(this->bossEnemyBullets,         // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
        //                  roomList->next->mountainList);
    }

    increaseCount(this->whileCount, points, normalEnemyList);

    drawWindow.printEnemy(normalEnemyList, drawWindow);
    drawWindow.printEnemy(specialEnemyList, drawWindow);
    drawWindow.printEnemy(bossEnemyList, drawWindow);

    drawWindow.moveEnemy(normalEnemyList, character, drawWindow, points);
    drawWindow.moveEnemy(specialEnemyList, character, drawWindow, points);
    drawWindow.moveEnemy(bossEnemyList, character, drawWindow, points);

    generateEnemyBullets(normalEnemyList, this->normalEnemyBullets, character);
    generateEnemyBullets(specialEnemyList, this->specialEnemyBullets, character);
    generateEnemyBullets(bossEnemyList, this->bossEnemyBullets, character);

    shootPlayerBullet();
    shootEnemyBullet(this->normalEnemyBullets);
    //shootEnemyBullet(this->specialEnemyBullets);    // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
    //shootEnemyBullet(this->bossEnemyBullets);       // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE

    checkEnemyCollision(character, normalEnemyList);
    checkEnemyCollision(character, specialEnemyList);
    checkEnemyCollision(character, bossEnemyList);

    gorillaPunch(direction, character, normalEnemyList, pointsOnScreen,
                 toTheRight);
    gorillaPunch(direction, character, specialEnemyList, pointsOnScreen,
                 toTheRight);
    gorillaPunch(direction, character, bossEnemyList, pointsOnScreen,
                 toTheRight);

    money(bananas, normalEnemyList, maxRound, roundPayed, character);
    checkBulletCollision(normalEnemyList, character, this->playerBullets,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(normalEnemyList, character, this->normalEnemyBullets,
                         pointsOnScreen, immortalityCheck);
    //checkBulletCollision(normalEnemyList, character, this->specialEnemyBullets,   // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
       //                  pointsOnScreen, immortalityCheck);
    //checkBulletCollision(normalEnemyList, character, this->bossEnemyBullets,      // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
     //                    pointsOnScreen, immortalityCheck);
    refresh();

    destroyBullet(this->playerBullets);
    destroyBullet(this->normalEnemyBullets);
    // destroyBullet(this->specialEnemyBullets);      // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
    // destroyBullet(this->bossEnemyBullets);         // DA FIXARE, GENERA ERRORE DI SEGMENTAZIONE
    drawWindow.showBonusOnScreen(upgradeBuyed, upgradeType, upgradeTime,
                                 bonusPicked, bonusType, bonusTime,
                                 immortalityCheck, immortalityTime);
    checkDeath(pause, character);

    timeout(50);
    isPause(direction, pause);
    finalScore = pointsOnScreen;
  }
}
// x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD
