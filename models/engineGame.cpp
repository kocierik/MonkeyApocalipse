#include "drawWindow.hpp"
#include "engineGame.hpp"

#include <ncurses.h>

#include <cmath>
#include <ctime>
#include <iostream>

// Numero di casi dello switch che gestisce i bonus. Equivale a: n bonus
#define BONUS 15

float finalScore = 0;

EngineGame::EngineGame(int frameGameX, int frameGameY, int topHeigth, int bottomHeigth, int leftWidth, int rightWidth) {
  this->frameGameX = frameGameX;
  this->frameGameY = frameGameY;
  this->topHeigth = topHeigth;
  this->bottomHeigth = bottomHeigth;
  this->leftWidth = leftWidth;
  this->rightWidth = rightWidth;
  this->playerBullets = NULL;
  this->playerBullets2 = NULL;
  this->normalEnemyBullets = NULL;
  this->specialEnemyBullets = NULL;
  this->bossEnemyBullets = NULL;
  this->quit = false;
  this->pause = true;
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
  if (moveFoward)
    bullet->x = character.getX() - 1;
  else
    bullet->x = character.getX() + 1;
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
      enemyBulletList = generateBullets(enemyList->enemy, false, shootFoward, enemyBulletList);
    }
    enemyList = enemyList->next;
  }
}

void EngineGame::moveBullets(Pbullet bulletList) {
  char tmpSkin[2];
  while (bulletList != NULL) {
    if ((bulletList->isPlayerBullet && bulletList->moveFoward) ||
        (!bulletList->isPlayerBullet && !bulletList->moveFoward))
      bulletList->x += bulletList->speed;
    else
      bulletList->x -= bulletList->speed;

    move(bulletList->y, bulletList->x);
    tmpSkin[0] = bulletList->skin;
    if (bulletList->isPlayerBullet) {
      init_pair(10, COLOR_YELLOW, -1);  // SPARA BANANE GIALLE
      attron(COLOR_PAIR(10));
      printw(tmpSkin);
      attroff(COLOR_PAIR(10));
    } else
      printw(tmpSkin);
    bulletList = bulletList->next;
  }
}

void EngineGame::destroyBullet(Pbullet &bulletList, int xP) {
  if (xP == this->leftWidth || xP == this->rightWidth)
    bulletList = NULL;
  else {
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
      if (!head->isPlayerBullet)
        mustDestroyCondition &= !isEnemy(head->x + range, head->y);

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

pPosition EngineGame::deletePosition(pPosition positionList, pPosition toDelete) {
  /**
   * Essendo bonus e montagne la stessa tipologia di dato (pPosition), questa
   * funzione elimina un elemento (toDelete) da una lista, che sia un bonus o
   * una montagna.
   */
  pPosition head = positionList, prev = positionList, tmp;
  while (positionList != NULL) {
    if (positionList->x == toDelete->x && positionList->y == toDelete->y) {
      if (positionList == head) {
        tmp = head;
        head = positionList->next;
        delete tmp;
        prev = head;
        positionList = head;
      } else {
        tmp = prev->next;
        prev->next = positionList->next;
        delete tmp;
        positionList = prev->next;
      }
    } else {
      prev = positionList;
      positionList = positionList->next;
    }
  }
  return head;
}

bool EngineGame::checkNoEnemy(DrawWindow drawWindow, pEnemyList enemyList1, pEnemyList enemyList2, pEnemyList enemyList3) {
  int length1 = drawWindow.lengthEnemyList(enemyList1);
  int length2 = drawWindow.lengthEnemyList(enemyList2);
  int length3 = drawWindow.lengthEnemyList(enemyList3);
  if (length1 + length2 + length3 == 0) return true;
  else return false;
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

void EngineGame::checkBulletCollision(Pbullet &bulletList, Character &character,
                                      pEnemyList enemyList, int &pointOnScreen,
                                      bool immortalityCheck) {
  bool enemyHit = false, characterHit = false, pause = false;
  Pbullet head = bulletList;
  pEnemyList tmp = enemyList;
  int xE, yE, xP, yP;
  while (enemyList != NULL && !enemyHit && !characterHit) {
    while (bulletList != NULL && !enemyHit && !characterHit) {
      if (bulletList->isPlayerBullet) {
        xE = enemyList->enemy.getX(), yE = enemyList->enemy.getY();
        if ((xE == bulletList->x + 1 && yE == bulletList->y) ||
            (xE == bulletList->x - 1 && yE == bulletList->y))
          enemyHit = true;
      } else {
        xP = character.getX(), yP = character.getY();
        if ((xP == bulletList->x + 1 && yP == bulletList->y) ||
            (xP == bulletList->x - 1 && yP == bulletList->y))
          characterHit = true;
      }
      bulletList = bulletList->next;
    }
    bulletList = head;
    if (enemyHit || characterHit)
      break;
    else
      enemyList = enemyList->next;
  }

  init_pair(13, COLOR_RED, -1);
  attron(COLOR_PAIR(13));
  char tmpSkin[2];
  if (enemyHit) {
    tmpSkin[0] = enemyList->enemy.getSkin();
    mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);
    enemyList->enemy.decreaseLife(character.getGun().getDamage());
    if (enemyList->enemy.getLife() <= 0) {
      enemyList = destroyEnemy(tmp, enemyList->enemy);
      increasePointOnScreen(pointOnScreen, enemyList->enemy.getDeathScore());
    }
  } else if (characterHit && immortalityCheck == false) {
    character.decreaseLife(enemyList->enemy.getGun().getDamage());
    checkDeath(pause, character);
    tmpSkin[0] = character.getSkin();
    mvprintw(character.getY(), character.getX(), tmpSkin);
  }
  attroff(COLOR_PAIR(13));
}

bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }
bool EngineGame::isBonus(int x, int y) { return mvinch(y, x) == '?'; }
bool EngineGame::isPlayer(int x, int y) { return mvinch(y, x) == 'M'; }
bool EngineGame::isEnemy(int x, int y) { return mvinch(y, x) == 'e' || mvinch(y, x) == 'E' || mvinch(y, x) == 'B'; }
bool EngineGame::isBullet(int x, int y) { return mvinch(y, x) == '~' || mvinch(y, x) == '-' || mvinch(y, x) == '=' || mvinch(y, x) == '*'; }
bool EngineGame::isPlayerBullet(int x, int y) { return mvinch(y, x) == '~'; }

void EngineGame::moveCharacter(
    DrawWindow drawWindow, Character &character, int direction, pRoom &roomList,
    pEnemyList normalEnemyList, int &pointsOnScreen, int &bananas,
    int &powerUpDMG, bool &bonusPicked, int &bonusType, int &bonusTime,
    bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
    bool &immortalityCheck, int &immortalityTime, bool &toTheRight, int upgradeCost, pPosition mountainList) {
  srand(time(0));
  switch (direction) {  // Movimento con wasd per il player 1 e frecce per il player 2
    case KEY_UP:
      if (isEmpty(character.getX(), character.getY() - 1))
        character.directionUp();
      else if (isBonus(character.getX(), character.getY() - 1)) {
        bonusTime = 0;       // RESETTA IL TEMPO DI APPARIZIONE SE IL TIMER
                             // ERA GIA ATTIVO PER IL PRECEDENTE BONUS.
        bonusPicked = true;  // FLAG CHE INDICA SE È STATO RACCOLTO
        bonusType = rand() % BONUS;  // 0 <= bonusType < BONUS
        roomList->bonusList = getBonus(
            drawWindow, character.getX(), character.getY() - 1,
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
        character.directionUp();
      }
      break;
    case KEY_DOWN:
      if (isEmpty(character.getX(), character.getY() + 1))
        character.directionDown();
      else if (isBonus(character.getX(), character.getY() + 1)) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList = getBonus(
            drawWindow, character.getX(), character.getY() + 1,
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
        character.directionDown();
      }
      break;
    case KEY_LEFT:
      if (isEmpty(character.getX() - 1, character.getY()))
        character.directionLeft();
      else if (isBonus(character.getX() - 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;  // GENERA IL TIPO DI BONUS.
        roomList->bonusList = getBonus(
            drawWindow, character.getX() - 1, character.getY(),
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
        character.directionLeft();
      }
      toTheRight = false;
      break;
    case KEY_RIGHT:
      if (isEmpty(character.getX() + 1, character.getY()))
        character.directionRight();
      else if (isBonus(character.getX() + 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList = getBonus(
            drawWindow, character.getX() + 1, character.getY(),
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character, bonusType, immortalityCheck, immortalityTime);
        character.directionRight();
      }
      toTheRight = true;
      break;
    case 'M':  // Sparo in avanti del player
    case 'm':
      // Controllo della condizione di assenza della montagna NON FUNZIONANTE (non so come mai)
      if (whileCount / 2 > 1 && character.getGun().getMagazineAmmo() > 0) {
        character.decreaseMagazineAmmo(1);
        this->playerBullets =
            generateBullets(character, true, true, this->playerBullets);
        whileCount = 0;
      }
      break;
    case 'N':  // Sparo all'indietro del player
    case 'n':
      // Controllo della condizione di assenza della montagna NON FUNZIONANTE (non so come mai)
      if (whileCount / 2 > 1 && character.getGun().getMagazineAmmo() > 0) {
        character.decreaseMagazineAmmo(1);
        this->playerBullets =
            generateBullets(character, true, false, this->playerBullets);
        whileCount = 0;
      }
      break;
    case 'L':
    case 'l':
      if (character.getGun().getMagazineAmmo() >= 0 &&
          character.getGun().getMagazineAmmo() <
              character.getGun().getMagazineCapacity() &&
          character.getGun().getTotalAmmo() > 0)
        character.reload();
      break;
    case 'o':  // CONTROLLA L'AQUISTO DI VITE, MASSIMO 3 -------------------
      if (bananas >= (upgradeCost/2) && character.getNumberLife() < 3) {
        upgradeBuyed = true;  // INDICA CHE È STATO COMPRATO UN UPGRADE
        upgradeType = 0;      // INDICA IL TIPO DI UPGRADE.
        upgradeTime = 0;  // RESETTA IL TEMPO DI APPARIZIONE SE HAI COMPRATO UN
                          // ALTRO UPGRADE
        character.setNumberLife(character.getNumberLife() + 1);
        bananas = bananas - (upgradeCost/2);
      }
      break;
    case 'p':  // CONTROLLA L'AQUISTO DI POWERUP AL DANNO, SONO ACQUISTABILI AL
               // MASSIMO 4 DURANTE TUTTA LA RUN
      if (character.getGun().getDamage() < 50) {
        if (bananas >= upgradeCost && powerUpDMG < 3) {
          upgradeBuyed = true;
          upgradeType = 1, upgradeTime = 0;
          character.increaseDamageGun(5);
          if (character.getGun().getDamage() >= 50) character.setGunDamage(50);
          bananas -= upgradeCost;
          powerUpDMG++;
        } else if (bananas >= upgradeCost && (powerUpDMG == 3)) {
          upgradeBuyed = true;
          upgradeType = 1, upgradeTime = 0;
          character.increaseDamageGun(10);
          if (character.getGun().getDamage() >= 50) character.setGunDamage(50);
          bananas = bananas - upgradeCost;
          powerUpDMG++;
        }
        // MESSAGGIO CHE SEGNALE IL FATTO CHE QUESTO UPGRADE NON è DISPONIBILE
        //mvprintw(?, ?, "MAX DAMAGE OBTAINED");
      }
      break;

  }
}

void EngineGame::moveCharacter2(
    DrawWindow drawWindow, Character &character2, int direction, pRoom &roomList,
    pEnemyList normalEnemyList, int &pointsOnScreen, int &bananas,
    int &powerUpDMG, bool &bonusPicked, int &bonusType, int &bonusTime,
    bool &upgradeBuyed, int &upgradeType, int &upgradeTime,
    bool &immortalityCheck, int &immortalityTime, bool &toTheRight, int upgradeCost, pPosition mountainList) {
  switch (direction) {  // Movimento con wasd per il player 1 e frecce per il player 2
  case 'w':
      if (isEmpty(character2.getX(), character2.getY() - 1))
        character2.directionUp();
      else if (isBonus(character2.getX(), character2.getY() - 1)) {
        bonusTime = 0;       // RESETTA IL TEMPO DI APPARIZIONE SE IL TIMER
                             // ERA GIA ATTIVO PER IL PRECEDENTE BONUS.
        bonusPicked = true;  // FLAG CHE INDICA SE È STATO RACCOLTO
        bonusType = rand() % BONUS;  // 0 <= bonusType < BONUS
        roomList->bonusList = getBonus(
            drawWindow, character2.getX(), character2.getY() - 1,
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character2, bonusType, immortalityCheck, immortalityTime);
        character2.directionUp();
      }
      break;
    case 's':
      if (isEmpty(character2.getX(), character2.getY() + 1))
        character2.directionDown();
      else if (isBonus(character2.getX(), character2.getY() + 1)) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList = getBonus(
            drawWindow, character2.getX(), character2.getY() + 1,
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character2, bonusType, immortalityCheck, immortalityTime);
        character2.directionDown();
      }
      break;
    case 'a':
      if (isEmpty(character2.getX() - 1, character2.getY()))
        character2.directionLeft();
      else if (isBonus(character2.getX() - 1, character2.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;  // GENERA IL TIPO DI BONUS.
        roomList->bonusList = getBonus(
            drawWindow, character2.getX() - 1, character2.getY(),
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character2, bonusType, immortalityCheck, immortalityTime);
        character2.directionLeft();
      }
      toTheRight = false;
      break;
    case 'd':
      if (isEmpty(character2.getX() + 1, character2.getY()))
        character2.directionRight();
      else if (isBonus(character2.getX() + 1, character2.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList = getBonus(
            drawWindow, character2.getX() + 1, character2.getY(),
            roomList->next->bonusList, normalEnemyList, pointsOnScreen,
            character2, bonusType, immortalityCheck, immortalityTime);
        character2.directionRight();
      }
      toTheRight = true;
      break;
    case 'C':  // Sparo in avanti del player
    case 'c':
      // Controllo della condizione di assenza della montagna NON FUNZIONANTE (non so come mai)
      if (whileCount / 2 > 1 && character2.getGun().getMagazineAmmo() > 0) {
        character2.decreaseMagazineAmmo(1);
        this->playerBullets2 =
            generateBullets(character2, true, true, this->playerBullets2);    
        whileCount = 0;
      }
      break;
    case 'X':  // Sparo all'indietro del player
    case 'x':
      // Controllo della condizione di assenza della montagna NON FUNZIONANTE (non so come mai)
      if (whileCount / 2 > 1 && character2.getGun().getMagazineAmmo() > 0) {
        character2.decreaseMagazineAmmo(1);
        this->playerBullets2 =
            generateBullets(character2, true, false, this->playerBullets2);
        whileCount = 0;
      }
      break;
    case 'R':
    case 'r':
      if (character2.getGun().getMagazineAmmo() >= 0 &&
          character2.getGun().getMagazineAmmo() <
              character2.getGun().getMagazineCapacity() &&
          character2.getGun().getTotalAmmo() > 0)
        character2.reload();
      break;
    case 'f':  // CONTROLLA L'AQUISTO DI VITE, MASSIMO 3 -------------------
      if (bananas >= (upgradeCost/2) && character2.getNumberLife() < 3) {
        upgradeBuyed = true;  // INDICA CHE È STATO COMPRATO UN UPGRADE
        upgradeType = 0;      // INDICA IL TIPO DI UPGRADE.
        upgradeTime = 0;  // RESETTA IL TEMPO DI APPARIZIONE SE HAI COMPRATO UN
                          // ALTRO UPGRADE
        character2.setNumberLife(character2.getNumberLife() + 1);
        bananas = bananas - (upgradeCost/2);
      }
      break;
    case 'g':  // CONTROLLA L'AQUISTO DI POWERUP AL DANNO, SONO ACQUISTABILI AL
               // MASSIMO 4 DURANTE TUTTA LA RUN
      if (character2.getGun().getDamage() < 50) {
        if (bananas >= upgradeCost && powerUpDMG < 3) {
          upgradeBuyed = true;
          upgradeType = 1, upgradeTime = 0;
          character2.increaseDamageGun(5);
          if (character2.getGun().getDamage() >= 50) character2.setGunDamage(50);
          bananas -= upgradeCost;
          powerUpDMG++;
        } else if (bananas >= upgradeCost && (powerUpDMG == 3)) {
          upgradeBuyed = true;
          upgradeType = 1, upgradeTime = 0;
          character2.increaseDamageGun(10);
          if (character2.getGun().getDamage() >= 50) character2.setGunDamage(50);
          bananas = bananas - upgradeCost;
          powerUpDMG++;
        }
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
    int range = -1;
    if (toTheRight) range = 1;
    // Con questa condizione, l'animazione del danno è più chiara
    if (isEmpty(character.getY(), character.getX() + range))
      mvprintw(character.getY(), character.getX() + range, "o");

    while (enemyList != NULL) {
      if (character.getX() + range == enemyList->enemy.getX() &&
          character.getY() == enemyList->enemy.getY()) {
        // Nemico rosso quando riceve il punch
        init_pair(13, COLOR_RED, -1);
        attron(COLOR_PAIR(13));
        char tmpSkin[0];
        tmpSkin[0] = enemyList->enemy.getSkin();
        mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);

        enemyList->enemy.decreaseLife(40);
        if (enemyList->enemy.getLife() <= 0) {
          enemyList = destroyEnemy(tmp, enemyList->enemy);
          increasePointOnScreen(pointOnScreen, enemyList->enemy.getDeathScore());
        }
        attroff(COLOR_PAIR(13));
      }
      enemyList = enemyList->next;
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
    if (cnt > 5) cnt = 0;
    if (cnt < 0) cnt = 5;
  }
}

void EngineGame::generateFictionalEnemy(pEnemyList &specialEnemyList, pEnemyList &bossEnemyList) {
  Gun tmpGun(' ', 10, -1, -1);
  Enemy enemy1(0, 0, ' ', 1, 1, tmpGun, 0);
  Enemy enemy2(0, 0, ' ', 1, 1, tmpGun, 0);
  specialEnemyList->enemy = enemy1;
  specialEnemyList->next = NULL;
  bossEnemyList->enemy = enemy2;
  bossEnemyList->next = NULL;
}

pEnemyList EngineGame::generateEnemy(int *enemyCount, int type, pEnemyList enemyList,
                                     DrawWindow drawWindow) {
  // Variables 4 basic enemies
  char skin = 'e';
  int life = 10, deathScore = 100;
  Gun gun('-', 10, -1, -1);
  switch (type) {
    case 0:  // Basic enemies, no variables changes
      break;
    case 1:  // Elite enemies
      skin = 'E';
      life = 10, deathScore = 250;
      gun.setBulletSkin('=');
      gun.setDamage(15);
      break;
    case 2:  // Boss enemy
      skin = 'B';
      life = 10, deathScore = 800;
      gun.setBulletSkin('*');
      gun.setDamage(25);
      break;
  }

  bool isEmpty = false;
  int x, y;
  while (*enemyCount > 0) {
    x = drawWindow.randomPosition(40, 69).x;
    y = drawWindow.randomPosition(8, 19).y; 
    pEnemyList head = new EnemyList;
    Enemy enemy(x, y, skin, life, 1, gun, deathScore);
    head->enemy = enemy;
    head->next = enemyList;
    *enemyCount -= 1;
    enemyList = head;
    isEmpty = true;
  }
  if (isEmpty) {
    gun.setBulletSkin(' ');
    pEnemyList head = new EnemyList;
    Enemy enemy(0, 0, ' ', life, 1, gun, deathScore);
    head->enemy = enemy;
    head->next = enemyList;
    enemyList = head;
    isEmpty = false;
  }
  return enemyList;
}

pPosition EngineGame::getBonus(DrawWindow drawWindow, int x, int y,
                               pPosition bonusList, pEnemyList &enemyList,
                               int &pointsOnScreen, Character &character,
                               int &bonusType, bool &immortalitycheck,
                               int &immortalityTime) {
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
          if(immortalitycheck == false){
            if (character.getNumberLife() == 1 && character.getLife() <= 10)
              character.setLife(5);
            else
              character.decreaseLife(10);
          }
          end = true;
          break;
        case 5:  // Malus name: "MONKEY TRAP [-30 HP]"
          if(immortalitycheck == false){
            if (character.getNumberLife() == 1 && character.getLife() <= 30)
              character.setLife(5);
            else
              character.decreaseLife(30);
          }
          end = true;
          break;
        case 6:  // Bonus name: "EAT 1 BANANA [+10 HP]"
          character.increaseLife(10);
          end = true;
          break;
        case 7:  // Bonus name: "EAT 2 BANANA [+20 HP]"
          character.increaseLife(20);
          end = true;
          break;
        case 8:  // Bonus name: "BANANA SMOOTHIE [+40 HP]"
          character.increaseLife(40);
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

void EngineGame::engine(Character character,Character character2, DrawWindow drawWindow) {
  int direction, selection;
  baseCommand();
  choiceGame(drawWindow, &direction, &selection);
  while (pause) {
    switch (selection) {
      case 0:     // FUN (single player)
        pause = false;
        clear();
        drawWindow.splashScreen(direction);
        runGame(character,character2, drawWindow, direction,false);
        clear();
        drawWindow.loseScreen(direction, finalScore);
        selection = 6;
        break;
      case 1:     // MORE FUN (multiplayer)
        pause = false;
        runGame(character, character2, drawWindow, direction,true);
        clear();
        drawWindow.loseScreen(direction, finalScore);
        selection = 6;
        break;
      case 2:     // HOW TO PLAY
        clear();
        drawWindow.HowToPlay(direction);
        selection = 6;
        break;
      case 3:     // LEADERBOARD
        clear();
        drawWindow.leaderboardScreen(direction);
        selection = 6;
        break;
      case 4:     // CREDITS
        clear();
        drawWindow.credits(direction);
        selection = 6;
        break;
      case 5:     // QUIT!
        refresh();
        std::cout << "Thanks for playing ;) ";
        exit(1);
        break;
      case 6:     // MENU INIZIALE
        clear();
        engine(character, character2, drawWindow);
        break;
    }
  }
  endwin();
}

void EngineGame::increaseCount(long &points) {
  whileCount += 1;
  points += 1;
  this->whileCountEnemy += 1;
}

void EngineGame::money(int &bananas, bool noEnemy, int maxRoom, int &roundPayed, Character &character, int upgradeCost) {
  srand(time(NULL));
  if (noEnemy && (maxRoom != roundPayed)) {  // CONTROLLA CHE LA STANZA SIA PULITA E CHE L'ULTIMO ROUND SIA STATO PAGATO
    bananas = bananas + rand() % 3 + 1;
    character.increaseLife((rand() % 20 + 20));
    if (maxRoom >= 2 && maxRoom <= 5)
      character.increaseTotalAmmo(30);
    else if (maxRoom > 5 && maxRoom <= 8)
      character.increaseTotalAmmo(40);
    else if (maxRoom > 8 && maxRoom <= 12)
      character.increaseTotalAmmo(50);
    else if (maxRoom > 15)
      character.increaseTotalAmmo(80);
    roundPayed++;
  }
  init_pair(20, COLOR_GREEN, -1);
  attron(COLOR_PAIR(20));
  if (bananas >= upgradeCost) {
    if (character.getNumberLife() < 3)
      mvprintw(24, 52, "BUYABLE LIFE OR DAMAGE UPGRADE");
    else
      mvprintw(24, 52, "BUYABLE DAMAGE UPGRADE!");
  }
  else if(bananas >= (upgradeCost/2) && character.getNumberLife() < 3)
    mvprintw(24, 52, "BUYABLE EXTRA LIFE!"); 
  attroff(COLOR_PAIR(20));
}

void EngineGame::printList(pPosition positionList) {
  int i = 2;
  while (positionList != NULL) {
    mvprintw(i, 0, "Vita montagna  %d", positionList->life);
    positionList = positionList->next;
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

void EngineGame::runGame(Character character, Character character2, DrawWindow drawWindow,
                         int direction, bool multiplayer) {
  bool toTheRight = true;
  int direction2 = 0;
  bool upgradeBuyed = false, bonusPicked = false, immortalityCheck = false;
  int upgradeCost = 10;
  bool noEnemy = false;
  int immortalityTime = 0;
  int pointsOnScreen = 0;
  long points = 0;
  int powerUpDMG = 0;  // NUMERO DI POWERUP AL DANNO AQUISTATI
  int bananas = 0, roundPayed = 0;
  int bonusTime = 0, upgradeTime = 0, bonusType = 0, upgradeType = 0;
  int normalEnemyCount = 1, specialEnemyCount = 0, bossEnemyCount = 0;
  int maxRoom = 1;
  pEnemyList normalEnemyList = NULL, specialEnemyList = new EnemyList, bossEnemyList = new EnemyList;
  generateFictionalEnemy(specialEnemyList, bossEnemyList);
  pPosition mountainList = new Position, bonusList = new Position;
  pRoom roomList = new Room;

  Gun basicPlayerGun('~', 25, 40, 10);
  character.setGun(basicPlayerGun);
  character2.setGun(basicPlayerGun);
  clear();

  while (!pause) {
    roomList = drawWindow.changeRoom(character, character2, normalEnemyCount, specialEnemyCount, bossEnemyCount, normalEnemyList, specialEnemyList,
                                     bossEnemyList, mountainList, bonusList, roomList, maxRoom);
    normalEnemyList = generateEnemy(&normalEnemyCount, 0, normalEnemyList, drawWindow);
    specialEnemyList = generateEnemy(&specialEnemyCount, 1, specialEnemyList, drawWindow);
    bossEnemyList = generateEnemy(&bossEnemyCount, 2, bossEnemyList, drawWindow);

    getInput(direction);

    moveCharacter(drawWindow, character, direction, roomList, normalEnemyList,
                  pointsOnScreen, bananas, powerUpDMG, bonusPicked, bonusType,
                  bonusTime, upgradeBuyed, upgradeType, upgradeTime, immortalityCheck,
                  immortalityTime, toTheRight, upgradeCost, roomList->mountainList);
    if(multiplayer) moveCharacter2(drawWindow, character2, direction, roomList, normalEnemyList,
                  pointsOnScreen, bananas, powerUpDMG, bonusPicked, bonusType,
                  bonusTime, upgradeBuyed, upgradeType, upgradeTime, immortalityCheck,
                  immortalityTime, toTheRight, upgradeCost, roomList->mountainList);
    clear();

    noEnemy = checkNoEnemy(drawWindow, normalEnemyList, specialEnemyList, bossEnemyList);
    
    drawWindow.printCharacter(character.getX(), character.getY(),
                              character.getSkin());
    if(multiplayer) drawWindow.printCharacter(character2.getX(), character2.getY(),
                              character2.getSkin());
    
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->rightWidth,
                        this->bottomHeigth, noEnemy, maxRoom, false, roomList);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->rightWidth,
                         this->bottomHeigth, pointsOnScreen, character,
                         noEnemy, powerUpDMG, bananas, maxRoom, roomList);
    drawWindow.drawLeaderboardOnScreen();
    drawWindow.printCharacterStats(normalEnemyList, specialEnemyList, bossEnemyList, character);

    if (drawWindow.lengthListRoom(roomList) > 1) {
      drawWindow.printMountain(roomList->next->mountainList);
      drawWindow.printBonus(roomList->next->bonusList);
      checkMountainDamage(this->playerBullets, roomList->next->mountainList);
      if(multiplayer) checkMountainDamage(this->playerBullets2, roomList->next->mountainList);
      checkMountainDamage(this->normalEnemyBullets,
                          roomList->next->mountainList);
      checkMountainDamage(this->specialEnemyBullets,
                          roomList->next->mountainList);
      checkMountainDamage(this->bossEnemyBullets,
                          roomList->next->mountainList);
    }

    increaseCount(points);
    /**
     * Temporanea soluzione affinché point non raggiunga valori esorbitanti.
     * In futuro verrà resettata quando verranno uccisi tutti i nemici e si potrà
     * dunque accedere alle altre stanze.
    */
    if (points > 500) points = 0;

    drawWindow.printEnemy(normalEnemyList, drawWindow);
    drawWindow.printEnemy(specialEnemyList, drawWindow);
    drawWindow.printEnemy(bossEnemyList, drawWindow);

    drawWindow.moveEnemy(normalEnemyList, character, drawWindow, points);
    drawWindow.moveEnemy(specialEnemyList, character, drawWindow, points);
    drawWindow.moveEnemy(bossEnemyList, character, drawWindow, points);

    generateEnemyBullets(normalEnemyList, this->normalEnemyBullets, character);
    generateEnemyBullets(specialEnemyList, this->specialEnemyBullets, character);
    generateEnemyBullets(bossEnemyList, this->bossEnemyBullets, character);

  if(multiplayer){
    generateEnemyBullets(normalEnemyList, this->normalEnemyBullets, character2);
    generateEnemyBullets(specialEnemyList, this->specialEnemyBullets, character2);
    generateEnemyBullets(bossEnemyList, this->bossEnemyBullets, character2);
  }
    moveBullets(this->playerBullets);
  if(multiplayer) moveBullets(this->playerBullets2);
    moveBullets(this->normalEnemyBullets);
    moveBullets(this->specialEnemyBullets);
    moveBullets(this->bossEnemyBullets);

    checkEnemyCollision(character, normalEnemyList);
    checkEnemyCollision(character, specialEnemyList);
    checkEnemyCollision(character, bossEnemyList);

  if(multiplayer){
    checkEnemyCollision(character2, normalEnemyList);
    checkEnemyCollision(character2, specialEnemyList);
    checkEnemyCollision(character2, bossEnemyList);
  }

    gorillaPunch(direction, character, normalEnemyList, pointsOnScreen,
                 toTheRight);
    gorillaPunch(direction, character, specialEnemyList, pointsOnScreen,
                 toTheRight);
    gorillaPunch(direction, character, bossEnemyList, pointsOnScreen,
                 toTheRight);

  if(multiplayer){
    gorillaPunch(direction2, character2, normalEnemyList, pointsOnScreen,
                 toTheRight);
    gorillaPunch(direction2, character2, specialEnemyList, pointsOnScreen,
                 toTheRight);
    gorillaPunch(direction2, character2, bossEnemyList, pointsOnScreen,
                 toTheRight);
  }

    money(bananas, noEnemy, maxRoom, roundPayed, character, upgradeCost);
    checkBulletCollision(this->playerBullets, character, normalEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->playerBullets, character, specialEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->playerBullets, character, bossEnemyList,
                         pointsOnScreen, immortalityCheck);
  if(multiplayer){
    checkBulletCollision(this->playerBullets2, character2, normalEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->playerBullets2, character2, specialEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->playerBullets2, character2, bossEnemyList,
                         pointsOnScreen, immortalityCheck);
  }

    checkBulletCollision(this->normalEnemyBullets, character, normalEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->specialEnemyBullets, character, specialEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->bossEnemyBullets, character, bossEnemyList,
                         pointsOnScreen, immortalityCheck);
    
  if(multiplayer){
    checkBulletCollision(this->normalEnemyBullets, character2, normalEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->specialEnemyBullets, character2, specialEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->bossEnemyBullets, character2, bossEnemyList,
                         pointsOnScreen, immortalityCheck);
  }
    refresh();
  
    destroyBullet(this->playerBullets, character.getX());
    destroyBullet(this->normalEnemyBullets, character.getX());
    destroyBullet(this->specialEnemyBullets, character.getX());
    destroyBullet(this->bossEnemyBullets, character.getX());
  if(multiplayer) {
    destroyBullet(this->playerBullets2, character2.getX());
    destroyBullet(this->normalEnemyBullets, character2.getX());
    destroyBullet(this->specialEnemyBullets, character2.getX());
    destroyBullet(this->bossEnemyBullets, character2.getX());
    }
    drawWindow.showBonusOnScreen(upgradeBuyed, upgradeType, upgradeTime,
                                 bonusPicked, bonusType, bonusTime,
                                 immortalityCheck, immortalityTime);
    checkDeath(pause, character);
    checkDeath(pause, character2);
    timeout(50);
    isPause(direction, pause);
    finalScore = pointsOnScreen;
  }
}
// x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD
