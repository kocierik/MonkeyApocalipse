#include "drawWindow.hpp"
#include "engineGame.hpp"

#include <ncurses.h>

#include <cmath>
#include <ctime>
#include <iostream>

#include "player.hpp"

// Numero di casi dello switch che gestisce i bonus. Equivale a: n bonus
#define BONUS 15
// Dimensioni doppie rispetto al numero di tasti usari per includere anche le maiuscole
#define NUMBER_OF_COMMANDS 20

float finalScore = 0;

EngineGame::EngineGame(int frameGameX, int frameGameY, int topHeigth,
                       int bottomHeigth, int leftWidth, int rightWidth) {
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
  /**
   * Funzione per la generazione della singola struttura Bullet.
   * In base ai parametri passati si saprà se il proiettile sia nemico o
   * meno, e se sia sparato verso dx o sx.
   */
  Pbullet bullet = new Bullet;
  int range = 1;
  if (moveFoward) range = -1;
  if (!isPlayerBullet) {
    if (range == -1)
      range = 1;
    else if (range == 1)
      range = 0;
  }

  bullet->x = character.getX() + range;
  bullet->y = character.getY();
  bullet->speed = 1;
  bullet->skin = character.getGun().getBulletSkin();
  bullet->isPlayerBullet = isPlayerBullet;
  bullet->moveFoward = moveFoward;
  bullet->next = bulletList;
  return bullet;
}

void EngineGame::generateEnemyBullets(pEnemyList enemyList,
                                      Pbullet &enemyBulletList,
                                      Character character) {
  /**
   * Funzione per la generazione dei proiettili dei nemici.
   */
  bool shootFoward;
  while (enemyList != NULL) {
    if (this->whileCountEnemy % 20 == 0) {
      shootFoward = true;
      // Se il player è alla sx del nemico, spara a sx
      if (character.getX() > enemyList->enemy.getX()) shootFoward = false;
      // Colpo del nemico -> false; Sparo avanti/indieto -> moveFoward
      enemyBulletList = generateBullets(enemyList->enemy, false, shootFoward,
                                        enemyBulletList);
    }
    enemyList = enemyList->next;
  }
}

void EngineGame::moveBullets(Pbullet bulletList) {
  /**
   * Funzione per il movimento dei proiettili.
   */
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
      init_pair(10, COLOR_YELLOW, -1);
      attron(COLOR_PAIR(10));
      printw(tmpSkin);
      attroff(COLOR_PAIR(10));
    } else
      printw(tmpSkin);
    bulletList = bulletList->next;
  }
}

void EngineGame::destroyBullet(Pbullet &bulletList, int xP1, int xP2) {
  /**
   * Funzione per la distruzione dei proiettili.
   * Scorre la lista data e controlla se le condizioni per
   * l'eliminazione dell'elemento sono soddisfatte.
   */
  if (xP1 == this->leftWidth || xP1 == this->rightWidth ||
      xP2 == this->leftWidth || xP2 == this->rightWidth)
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
                             !isBonus(head->x + range, head->y) &&
                             !isBullet(head->x + range, head->y);
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
  /**
   * Funzione per la distruzione dei nemici.
   * Scorre la lista data e controlla se le condizioni per
   * l'eliminazione dell'elemento sono soddisfatte.
   */
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

pPosition EngineGame::deletePosition(pPosition positionList,
                                     pPosition toDelete) {
  /**
   * Funzione per l'eliminazione di bonus e montagne,
   * ovvero elementi pPosition.
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

bool EngineGame::checkNoEnemy(DrawWindow drawWindow, pEnemyList enemyList1,
                              pEnemyList enemyList2, pEnemyList enemyList3) {
  /**
   * Ritorna true se non vi sono nemici nella stanza, false altrimenti.
   */
  int length1 = drawWindow.lengthEnemyList(enemyList1);
  int length2 = drawWindow.lengthEnemyList(enemyList2);
  int length3 = drawWindow.lengthEnemyList(enemyList3);
  if (length1 + length2 + length3 == 0)
    return true;
  else
    return false;
}

void EngineGame::checkEnemyCollision(Character &character,
                                     pEnemyList enemyList) {
  /**
   * Funzione per la collisione fisica tra player e nemici.
   * Controlla la presenza di uno scontro in qualsiasi direzione,
   * danneggia 1 il player, 3 il nemico (soluzione kamikaze efficace),
   * e colora di rosso i protagonisti dello scontro.
   */
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
  /**
   * Funzione per il check si una collisione del proiettile con un giocatore
   * o con un nemico.
   */
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

/**
 * Funzioni per il controllo della prensenza (tramite il carattere)
 * di vari elementi sulla mappa.
 */
bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }
bool EngineGame::isBonus(int x, int y) { return mvinch(y, x) == '?'; }
bool EngineGame::isEnemy(int x, int y) {
  return mvinch(y, x) == 'e' || mvinch(y, x) == 'E' || mvinch(y, x) == 'B';
}
bool EngineGame::isBullet(int x, int y) {
  return mvinch(y, x) == '~' || mvinch(y, x) == '-' || mvinch(y, x) == '=' ||
         mvinch(y, x) == '*';
}
bool EngineGame::isPlayerBullet(int x, int y) { return mvinch(y, x) == '~'; }

void EngineGame::moveCharacter(DrawWindow drawWindow, Character &character,
                               int direction, int* commands, pRoom &roomList,
                               pEnemyList normalEnemyList, int &pointsOnScreen,
                               int &bananas, int &powerUpDMG, bool &bonusPicked,
                               int &bonusType, int &bonusTime,
                               bool &upgradeBuyed, int &upgradeType,
                               int &upgradeTime, bool &immortalityCheck,
                               int &immortalityTime, bool &toTheRight,
                               int upgradeCost, pPosition mountainList) {
  /**
   * Funzioni che gestisce gli input del giocatore.
   * Gestisce il movimento, lo sparo e il reload dell'arma.
   *
   * Movimento: P1 -> Frecce ; P2 -> WASD
   */

  srand(time(0));
  if (direction == commands[0] || direction == commands[1]) {   // Movimento in alto
    if (isEmpty(character.getX(), character.getY() - 1))
      character.directionUp();
    else if (isBonus(character.getX(), character.getY() - 1)) {
      bonusTime = 0;
      bonusPicked = true;
      bonusType = rand() % BONUS;  // 0 <= bonusType < BONUS
      roomList->bonusList =
          getBonus(drawWindow, character.getX(), character.getY() - 1,
                   roomList->next->bonusList, normalEnemyList, pointsOnScreen,
                   character, bonusType, immortalityCheck, immortalityTime);
      character.directionUp();
    }
  } else if (direction == commands[2] || direction == commands[3]) {  // Movimento a sx
      if (isEmpty(character.getX() - 1, character.getY()))
        character.directionLeft();
      else if (isBonus(character.getX() - 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList =
            getBonus(drawWindow, character.getX() - 1, character.getY(),
                     roomList->next->bonusList, normalEnemyList, pointsOnScreen,
                     character, bonusType, immortalityCheck, immortalityTime);
        character.directionLeft();
      }
      toTheRight = false;
  } else if (direction == commands[4] || direction == commands[5]) {  // Movimento in basso
      if (isEmpty(character.getX(), character.getY() + 1))
        character.directionDown();
      else if (isBonus(character.getX(), character.getY() + 1)) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList =
            getBonus(drawWindow, character.getX(), character.getY() + 1,
                     roomList->next->bonusList, normalEnemyList, pointsOnScreen,
                     character, bonusType, immortalityCheck, immortalityTime);
        character.directionDown();
      }
  } else if (direction == commands[6] || direction == commands[7]) {  // Movimento a dx
      if (isEmpty(character.getX() + 1, character.getY()))
        character.directionRight();
      else if (isBonus(character.getX() + 1, character.getY())) {
        bonusTime = 0;
        bonusPicked = true;
        bonusType = rand() % BONUS;
        roomList->bonusList =
            getBonus(drawWindow, character.getX() + 1, character.getY(),
                     roomList->next->bonusList, normalEnemyList, pointsOnScreen,
                     character, bonusType, immortalityCheck, immortalityTime);
        character.directionRight();
      }
      toTheRight = true;
  } else if (direction == commands[8] || direction == commands[9]) {  // Sparo in avanti (tasto della virgola)
      if (whileCount / 2 > 1 && character.getGun().getMagazineAmmo() > 0) {
        character.decreaseMagazineAmmo(1);
        this->playerBullets =
            generateBullets(character, true, true, this->playerBullets);
        whileCount = 0;
      }
  } else if (direction == commands[10] || direction == commands[11]) {  // Sparo all'indietro (tasto del punto)
    if (whileCount / 2 > 1 && character.getGun().getMagazineAmmo() > 0) {
        character.decreaseMagazineAmmo(1);
        this->playerBullets =
            generateBullets(character, true, false, this->playerBullets);
        whileCount = 0;
      }
  } else if (direction == commands[12] || direction == commands[13]) {  // Ricarica dell'arma
    if (character.getGun().getMagazineAmmo() >= 0 &&
          character.getGun().getMagazineAmmo() <
              character.getGun().getMagazineCapacity() &&
          character.getGun().getTotalAmmo() > 0)
        character.reload();
  } else if (direction == commands[16] || direction == commands[17]) {  // Tasto per l'acquisto di una vita
    if (bananas >= (upgradeCost / 2) && character.getNumberLife() < 3) {
        upgradeBuyed = true;
        upgradeType = 0, upgradeTime = 0;
        character.setNumberLife(character.getNumberLife() + 1);
        bananas = bananas - (upgradeCost / 2);
      }
  } else if (direction == commands[18] || direction == commands[19]) {  // Tasto per l'acquisto di una vita
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
      }
  }

}

void EngineGame::gorillaPunch(int direction, Character &character,
                              pEnemyList enemyList, int &pointOnScreen,
                              bool toTheRight, bool isPlayer1) {
  /**
   * Funzione che gestisce l'input del pugno del giocatore e
   * le relative collisioni.
  */
  pEnemyList tmp = enemyList;
  bool condition = false;

  if (isPlayer1) {
    if (direction == 'k' || direction == 'K') {
      condition = true;
    }
  } else if (direction == 'q' || direction == 'Q') {
    condition = true;
  }

  if (condition) {
    int range = -1;
    if (toTheRight) range = 1;
    // Con questa condizione, l'animazione del danno è più chiara
    if (isEmpty(character.getY(), character.getX() + range))
      mvprintw(character.getY(), character.getX() + range, "o");

    char tmpSkin[0];
    while (enemyList != NULL) {
      if (character.getX() + range == enemyList->enemy.getX() &&
          character.getY() == enemyList->enemy.getY()) {
        init_pair(13, COLOR_RED, -1);
        attron(COLOR_PAIR(13));
        tmpSkin[0] = enemyList->enemy.getSkin();
        mvprintw(enemyList->enemy.getY(), enemyList->enemy.getX(), tmpSkin);

        enemyList->enemy.decreaseLife(40);
        if (enemyList->enemy.getLife() <= 0) {
          enemyList = destroyEnemy(tmp, enemyList->enemy);
          increasePointOnScreen(pointOnScreen,
                                enemyList->enemy.getDeathScore());
        }
        attroff(COLOR_PAIR(13));
      }
      enemyList = enemyList->next;
    }
  }
}

void EngineGame::choiceGame(DrawWindow drawWindow, int *direction,
                            int *selection) {
 /**
   * Funzione che seleziona la scelta di gioco nel menù principale
   */
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

void EngineGame::generateFictionalEnemy(pEnemyList &specialEnemyList,
                                        pEnemyList &bossEnemyList) {
  /**
   * Genera un nemico fittizio iniziale per evitare che la lista sia nulla
   */
  Gun tmpGun(' ', 10, -1, -1);
  Enemy enemy1(0, 0, ' ', 1, 1, tmpGun, 0);
  Enemy enemy2(0, 0, ' ', 1, 1, tmpGun, 0);
  specialEnemyList->enemy = enemy1;
  specialEnemyList->next = NULL;
  bossEnemyList->enemy = enemy2;
  bossEnemyList->next = NULL;
}

pEnemyList EngineGame::generateEnemy(int *enemyCount, int type,
                                     pEnemyList enemyList,
                                     DrawWindow drawWindow) {
  /**
   * Funzione che genera la lista di nemici in una stanza.
  */

  // Variables 4 basic enemies
  char skin = 'e';
  int life = 100, deathScore = 100;
  Gun gun('-', 10, -1, -1);
  switch (type) {
    case 0:  // Basic enemies, no variables changes
      break;
    case 1:  // Elite enemies
      skin = 'E';
      life = 200, deathScore = 250;
      gun.setBulletSkin('=');
      gun.setDamage(20);
      break;
    case 2:  // Boss enemy
      skin = 'B';
      life = 450, deathScore = 800;
      gun.setBulletSkin('*');
      gun.setDamage(35);
      break;
  }

  bool isEmpty = false;
  int x, y;
  while (*enemyCount > 0) {
    x = drawWindow.generateRandomPosition(40, 69).x;
    y = drawWindow.generateRandomPosition(8, 19).y;
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
  /**
   * Funzione che gestisce la raccolta del bonus, scegliendo in maniera
   * pseudo-casuale il l'effetto del bonus (o malus) raccolto.
  */

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
          if (immortalitycheck == false) {
            if (character.getNumberLife() == 1 && character.getLife() <= 10)
              character.setLife(5);
            else
              character.decreaseLife(10);
          }
          end = true;
          break;
        case 5:  // Malus name: "MONKEY TRAP [-30 HP]"
          if (immortalitycheck == false) {
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
  /**
   * Verifica se la vita del player è sufficiente per continuare
   * a giocare
   */
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
  /**
   * Funzione che controlla se un proiettile colpisce una
   * montagna. Scorre tutta la lista dei colpi e delle
   * montagne per verificare la condizione di una
   * collisione.
  */
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

int* EngineGame::decreesCommands(bool isPlayer1) {
  /**
   * Funzione che decreta quali pulsanti della tastiera
   * saranno rilevati come input.
  */
 	int *commands = new int[NUMBER_OF_COMMANDS];
	if (isPlayer1) {
    // Tasti per il movimento
    commands[0] = 259;    // KEY_UP
    commands[2] = 260;    // KEY_LEFT
    commands[4] = 258;    // KEY_DOWN
    commands[6] = 261;    // KEY_RIGHT
    // Tasti per lo sparo e la ricarica dell'arma
    commands[8] = 46;     // '.'
    commands[10] = 44;    // ','
    commands[12] = 108; commands[13] = 76;  // 'l' 'L'
    // Tasti per il pugno e l'acquisto di power-up
    commands[14] = 107; commands[15] = 75;  // 'k' 'K'
    commands[16] = 48;    // '0'
    commands[18] = 57;    // '9'
  } else {
    // Tasti per il movimento
    commands[0] = 119;  commands[1] = 87;   // 'w' 'W'
    commands[2] = 97;  commands[3] = 65;    // 'a' 'A'
    commands[4] = 115;  commands[5] = 83;   // 's' 'S'
    commands[6] = 100;  commands[7] = 68;   // 'd' 'D'
    // Tasti per lo sparo e la ricarica dell'arma
    commands[8] = 98;  commands[9] = 66;    // 'b' 'B'
    commands[10] = 118; commands[11] = 86;  // 'v' 'V'
    commands[12] = 114; commands[13] = 82;  // 'r' 'R'
    // Tasti per il pugno e l'acquisto di power-up
    commands[14] = 113; commands[15] = 81;  // 'q' 'Q'
    commands[16] = 49;  // '1'
    commands[18] = 50;  // '2'
  }
  return commands;
}

void EngineGame::engine(DrawWindow drawWindow) {
  /**
   * Funzione che reindirizza il giocatore in base
   * alla scelta effettuata nel menù principale
   */
  int direction, selection;
  bool multiplayer;
  baseCommand();
  choiceGame(drawWindow, &direction, &selection);
  clear();
  while (pause) {
    switch (selection) {
      case 0:  // FIGHT FOR FREEDOM! (single player)
        pause = false, multiplayer = false;
        clear();
        drawWindow.splashScreen(direction);
        runGame(drawWindow, direction, multiplayer);
        clear();
        drawWindow.loseScreen(direction, finalScore);
        selection = 6;
        break;
      case 1:  // APES STRONG TOGETHER (multiplayer)
        pause = false, multiplayer = true;
        clear();
        drawWindow.splashScreen(direction);
        runGame(drawWindow, direction, multiplayer);
        clear();
        drawWindow.loseScreen(direction, finalScore);
        selection = 6;
        break;
      case 2:  // HOW TO PLAY
        clear();
        drawWindow.HowToPlay(direction);
        selection = 6;
        break;
      case 3:  // LEADERBOARD
        clear();
        drawWindow.leaderboardScreen(direction);
        selection = 6;
        break;
      case 4:  // CREDITS
        clear();
        drawWindow.credits(direction);
        selection = 6;
        break;
      case 5:  // QUIT!
        refresh();
        std::cout << "Thanks for playing!" << std::endl;
        exit(1);
        break;
      case 6:  // MENU INIZIALE
        clear();
        engine(drawWindow);
        break;
    }
  }
  endwin();
}

void EngineGame::increaseCount(long &points) {
  /**
   * funzione che gestisce il punteggio di gioco
   */
  whileCount += 1;
  points += 1;
  if (points > 500) points = 0;
  this->whileCountEnemy += 1;
}

void EngineGame::money(int &bananas, bool noEnemy, int maxRoom, int &roundPayed,
                       Character &character, int upgradeCost, bool multiplayer,
                       bool isPlayer1) {
  /**
   * Funzione che gestisce i banner qualora si avessero
   * abbastanza monete per aquistare potenziamenti
   */
  srand(time(NULL));
  int P2Offsetx = 0;
  if (!isPlayer1) {
    P2Offsetx = 34;
  }
  if (noEnemy && (maxRoom != roundPayed)) {
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
    if (multiplayer == false || isPlayer1 == false) roundPayed++;
  }
  init_pair(20, COLOR_GREEN, -1);
  attron(COLOR_PAIR(20));
  if (bananas >= upgradeCost) {
    if (character.getNumberLife() < 3)
      mvprintw(24, 52 - P2Offsetx, "BUYABLE LIFE OR DAMAGE UPGRADE");
    else
      mvprintw(24, 52 - P2Offsetx, "BUYABLE DAMAGE UPGRADE!");
  } else if (bananas >= (upgradeCost / 2) && character.getNumberLife() < 3)
    mvprintw(24, 52, "BUYABLE EXTRA LIFE!");
  attroff(COLOR_PAIR(20));
}

void EngineGame::printList(pPosition positionList) {
  /**
   * Stampa una lista
   */
  int i = 2;
  while (positionList != NULL) {
    mvprintw(i, 0, "Vita montagna  %d", positionList->life);
    positionList = positionList->next;
    i++;
  }
}

// Prende un tasto da tastiera in input
void EngineGame::getInput(int &direction) { direction = getch(); }

// verifica se il gioco è in pausa
void EngineGame::isPause(int &direction, bool &pause) {
  if (direction == 27) pause = true;
}

// Aumento del punteggio a video
void EngineGame::increasePointOnScreen(int &pointOnScreen, int pointsAdded) {
  pointOnScreen += pointsAdded;
}

void EngineGame::runGame(DrawWindow drawWindow, int direction,
                         bool multiplayer) {
  Player character(this->frameGameY + 5, this->frameGameX + 5, 'M', 100, 3);
  Player character2(this->frameGameY + 6, this->frameGameX + 6, 'm', 100, 3);
  Gun basicPlayerGun('~', 25, 40, 10);
  character.setGun(basicPlayerGun);
  character2.setGun(basicPlayerGun);

  // Array contenenti i tasti interagibili
  int* commands_P1 = decreesCommands(true); int* commands_P2;
  if (multiplayer) commands_P2 = decreesCommands(false);

  // Variabili per la gestire logistica generale della partita
  bool noEnemy = false;
  int normalEnemyCount = 1, specialEnemyCount = 0, bossEnemyCount = 0;
  int maxRoom = 1, pointsOnScreen = 0;
  long points = 0;
  bool toTheRight = true, toTheRightP2 = true;

  // Variabili per la gestire logistica di alcuni bonus
  bool upgradeBuyed = false, bonusPicked = false, immortalityCheck = false;
  int upgradeCost = 10;
  int immortalityTime = 0;
  int powerUpDMG = 0, powerUpDMGP2 = 0;  // NUMERO DI POWERUP AL DANNO AQUISTATI
  int bananas = 0, bananasP2 = 0, roundPayed = 0;
  int bonusTime = 0, upgradeTime = 0, bonusType = 0, upgradeType = 0;

  // Liste delle varie entità in gioco
  pEnemyList normalEnemyList = NULL, specialEnemyList = new EnemyList,
             bossEnemyList = new EnemyList;
  generateFictionalEnemy(specialEnemyList, bossEnemyList);
  pPosition mountainList = new Position, bonusList = new Position;
  pRoom roomList = new Room;

  clear();

  while (!pause) {
    roomList = drawWindow.changeRoom(
        character, character2, normalEnemyCount, specialEnemyCount,
        bossEnemyCount, normalEnemyList, specialEnemyList, bossEnemyList,
        mountainList, bonusList, roomList, maxRoom, multiplayer);
    normalEnemyList =
        generateEnemy(&normalEnemyCount, 0, normalEnemyList, drawWindow);
    specialEnemyList =
        generateEnemy(&specialEnemyCount, 1, specialEnemyList, drawWindow);
    bossEnemyList =
        generateEnemy(&bossEnemyCount, 2, bossEnemyList, drawWindow);

    getInput(direction);

    moveCharacter(drawWindow, character, direction, commands_P1, roomList, normalEnemyList,
                  pointsOnScreen, bananas, powerUpDMG, bonusPicked, bonusType,
                  bonusTime, upgradeBuyed, upgradeType, upgradeTime,
                  immortalityCheck, immortalityTime, toTheRight, upgradeCost,
                  roomList->mountainList);
    if (multiplayer)
      moveCharacter(drawWindow, character2, direction, commands_P2, roomList, normalEnemyList,
                  pointsOnScreen, bananasP2, powerUpDMGP2, bonusPicked, bonusType,
                  bonusTime, upgradeBuyed, upgradeType, upgradeTime, immortalityCheck,
                  immortalityTime, toTheRightP2, upgradeCost, roomList->mountainList);
    clear();

    noEnemy = checkNoEnemy(drawWindow, normalEnemyList, specialEnemyList,
                           bossEnemyList);

    drawWindow.printCharacter(character.getX(), character.getY(),
                              character.getSkin());
    if (multiplayer)
      drawWindow.printCharacter(character2.getX(), character2.getY(),
                                character2.getSkin());

    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->rightWidth,
                        this->bottomHeigth, noEnemy, maxRoom, false, roomList);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->rightWidth,
                         this->bottomHeigth, pointsOnScreen, character, noEnemy,
                         powerUpDMG, bananas, bananasP2, maxRoom, roomList,
                         true);
    drawWindow.printCharacterStats(character, true);
    if (multiplayer) {
      drawWindow.drawStats(this->frameGameX, this->frameGameY, this->rightWidth,
                           this->bottomHeigth, pointsOnScreen, character2,
                           noEnemy, powerUpDMGP2, bananas, bananasP2, maxRoom,
                           roomList, false);
      drawWindow.printCharacterStats(character2, false);
    } else {
      drawWindow.printEnemyLeftList(normalEnemyList, specialEnemyList,
                                    bossEnemyList);
    }
    drawWindow.drawLeaderboardOnScreen();

    if (drawWindow.lengthListRoom(roomList) > 1) {
      drawWindow.printMountain(roomList->next->mountainList);
      drawWindow.printBonus(roomList->next->bonusList);
      checkMountainDamage(this->playerBullets, roomList->next->mountainList);
      if (multiplayer)
        checkMountainDamage(this->playerBullets2, roomList->next->mountainList);
      checkMountainDamage(this->normalEnemyBullets,
                          roomList->next->mountainList);
      checkMountainDamage(this->specialEnemyBullets,
                          roomList->next->mountainList);
      checkMountainDamage(this->bossEnemyBullets, roomList->next->mountainList);
    }

    increaseCount(points);

    drawWindow.printEnemy(normalEnemyList, drawWindow);
    drawWindow.printEnemy(specialEnemyList, drawWindow);
    drawWindow.printEnemy(bossEnemyList, drawWindow);

    drawWindow.moveEnemySinglePlayer(normalEnemyList, character, drawWindow,
                                     points);
    drawWindow.moveEnemySinglePlayer(specialEnemyList, character, drawWindow,
                                     points);
    drawWindow.moveEnemySinglePlayer(bossEnemyList, character, drawWindow,
                                     points);

    if (multiplayer) {
      drawWindow.moveEnemyMultiplayer(normalEnemyList, character, character2,
                                      drawWindow, points);
      drawWindow.moveEnemyMultiplayer(specialEnemyList, character, character2,
                                      drawWindow, points);
      drawWindow.moveEnemyMultiplayer(bossEnemyList, character, character2,
                                      drawWindow, points);
    }

    generateEnemyBullets(normalEnemyList, this->normalEnemyBullets, character);
    generateEnemyBullets(specialEnemyList, this->specialEnemyBullets,
                         character);
    generateEnemyBullets(bossEnemyList, this->bossEnemyBullets, character);
    if (multiplayer) {
      generateEnemyBullets(normalEnemyList, this->normalEnemyBullets,
                           character2);
      generateEnemyBullets(specialEnemyList, this->specialEnemyBullets,
                           character2);
      generateEnemyBullets(bossEnemyList, this->bossEnemyBullets, character2);
    }

    moveBullets(this->playerBullets);
    if (multiplayer) moveBullets(this->playerBullets2);
    moveBullets(this->normalEnemyBullets);
    moveBullets(this->specialEnemyBullets);
    moveBullets(this->bossEnemyBullets);

    checkEnemyCollision(character, normalEnemyList);
    checkEnemyCollision(character, specialEnemyList);
    checkEnemyCollision(character, bossEnemyList);
    if (multiplayer) {
      checkEnemyCollision(character2, normalEnemyList);
      checkEnemyCollision(character2, specialEnemyList);
      checkEnemyCollision(character2, bossEnemyList);
    }

    gorillaPunch(direction, character, normalEnemyList, pointsOnScreen,
                 toTheRight, true);
    gorillaPunch(direction, character, specialEnemyList, pointsOnScreen,
                 toTheRight, true);
    gorillaPunch(direction, character, bossEnemyList, pointsOnScreen,
                 toTheRight, true);
    if (multiplayer) {
      gorillaPunch(direction, character2, normalEnemyList, pointsOnScreen,
                   toTheRightP2, false);
      gorillaPunch(direction, character2, specialEnemyList, pointsOnScreen,
                   toTheRightP2, false);
      gorillaPunch(direction, character2, bossEnemyList, pointsOnScreen,
                   toTheRightP2, false);
    }

    money(bananas, noEnemy, maxRoom, roundPayed, character, upgradeCost,
          multiplayer, true);
    if (multiplayer) {
      money(bananasP2, noEnemy, maxRoom, roundPayed, character2, upgradeCost,
            multiplayer, false);
    }

    // Si constrolla se i colpi dei players hanno colpito i nemici
    checkBulletCollision(this->playerBullets, character, normalEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->playerBullets, character, specialEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->playerBullets, character, bossEnemyList,
                         pointsOnScreen, immortalityCheck);
    if (multiplayer) {
      checkBulletCollision(this->playerBullets2, character2, normalEnemyList,
                           pointsOnScreen, immortalityCheck);
      checkBulletCollision(this->playerBullets2, character2, specialEnemyList,
                           pointsOnScreen, immortalityCheck);
      checkBulletCollision(this->playerBullets2, character2, bossEnemyList,
                           pointsOnScreen, immortalityCheck);
    }

    // Si constrolla se i colpi dei nemici hanno colpito i players
    checkBulletCollision(this->normalEnemyBullets, character, normalEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->specialEnemyBullets, character, specialEnemyList,
                         pointsOnScreen, immortalityCheck);
    checkBulletCollision(this->bossEnemyBullets, character, bossEnemyList,
                         pointsOnScreen, immortalityCheck);
    if (multiplayer) {
      checkBulletCollision(this->normalEnemyBullets, character2,
                           normalEnemyList, pointsOnScreen, immortalityCheck);
      checkBulletCollision(this->specialEnemyBullets, character2,
                           specialEnemyList, pointsOnScreen, immortalityCheck);
      checkBulletCollision(this->bossEnemyBullets, character2, bossEnemyList,
                           pointsOnScreen, immortalityCheck);
    }

    refresh();

    if (multiplayer) {
      destroyBullet(this->playerBullets, character.getX(), character2.getX());
      destroyBullet(this->playerBullets2, character.getX(), character2.getX());
      destroyBullet(this->normalEnemyBullets, character.getX(),
                    character2.getX());
      destroyBullet(this->specialEnemyBullets, character.getX(),
                    character2.getX());
      destroyBullet(this->bossEnemyBullets, character.getX(),
                    character2.getX());
    } else {
      destroyBullet(this->playerBullets, character.getX(), 0);
      destroyBullet(this->normalEnemyBullets, character.getX(), 0);
      destroyBullet(this->specialEnemyBullets, character.getX(), 0);
      destroyBullet(this->bossEnemyBullets, character.getX(), 0);
    }

    drawWindow.showBonusOnScreen(
        upgradeBuyed, upgradeType, upgradeTime, bonusPicked, bonusType,
        bonusTime, immortalityCheck, immortalityTime, multiplayer);

    checkDeath(pause, character);
    if (multiplayer) checkDeath(pause, character2);

    timeout(50);
    isPause(direction, pause);
    finalScore = pointsOnScreen;
  }
}
