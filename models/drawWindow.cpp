#include "drawWindow.hpp"

#include <ncurses.h>
#include <unistd.h>

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#define FRAMEGAMEX 7
#define FRAMEGAMEY 22
#define GAMEWIDTH 71   // 49
#define GAMEHEIGTH 20  // 13

#define NORMAL_ENEMY_LIMIT 7
#define MOUNTAIN_LIFE 10

DrawWindow::DrawWindow() {}

/*
  I COLORI SONO IMPARENTATI DA UN ID (IL PRIMO VALORE DI INIT_PAIR)
  I COLORI HANNO ID:
  - ROSSO = 1
  - VERDE = 2
  - GIALLO = 3
  - BIANCO = 4
  - PROIETTILI GIALLI DEL PLAYER = 10
  - GIALLO BORDO = 11
  - MENU = 12
  - DANNO ROSSO = 13
  - MONTAGNE = 15
  - LOSE SCREEN rosso = 16
  - LOSE SCREEN verde = 17
  - UpGrade DISPONIBILE = 20
  - DISCLAIMER RICARICA = 25

  (colori riservati alle munizioni)
  - BIANCO = 21
  - GIALLO = 22
  - ROSSO = 23


  (questi sono riservati solo per la barra della salute):
  - ROSSO = 5
  - GIALLO = 6
  - VERDE = 7
  - BLACK = 8;
  - VIOLA IMMORTALE = 24
*/

void DrawWindow::drawMenu() {
  init_pair(1, COLOR_RED, 232);  // 1 INDICA UN ID, POI METTI IL COLORE CHE VUOI
  attron(COLOR_PAIR(1));         // APRTURA COLORE ROSSO
  mvprintw(LINES/2-10, COLS/2-54,
           "                                                                                                            ");
  mvprintw(LINES/2-9, COLS/2-54,
           "    b    d  P*Y  8b 8 8  d 88888 Yb  dP        A   8**Y  P*Y   "
           "P**b8   b    8     Yb  dP 8**Y .P*Y8 88888   ");
  mvprintw(LINES/2-8, COLS/2-54,
           "    8b  d8 P   Y 8Yb8 8od  8__    YbdP        PY   8__P P   Y P   "
           "`*   PY   8      YbdP  8__P `Yo.* 8__     ");
  mvprintw(LINES/2-7, COLS/2-54,
           "    8Yb P8 b   d 8 Y8 8*Y  8**     8P        P__Y  8**  b   P Y    "
           "   P__Y  8  .o   8P   8**  o.`Y8 8**     ");
  mvprintw(LINES/2-6, COLS/2-54,
           "    8 Y  8  Ybo  8  Y 8  Y 88888  dP        P****Y 8     P*Y   "
           "YoodP P****Y 8ood8  dP    8     8oP* 88888   ");
  mvprintw(LINES/2-5, COLS/2-54,
           "                                                                   "
           "                                         ");
  mvprintw(LINES/2-4, COLS/2-54,
           "     THE REVENGE OF THE MONKEYS HAS JUST BEGUN!                    "
           "                                         ");
  mvprintw(LINES/2-3, COLS/2-54,
           "                                                                   "
           "                                         ");
  attroff(COLOR_PAIR(1));  // CHIUSURA DEL COLORE ROSSO E NERO
}

void DrawWindow::printCommand(int *cnt) {

  init_pair(12, COLOR_BLACK, COLOR_RED);

  if (*cnt == 0) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES/2+1, COLS/2-17, "                                    ");
    mvprintw(LINES/2+2, COLS/2-17, "          START THE FIGHT!          ");
    mvprintw(LINES/2+3, COLS/2-17, "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES/2+1, COLS/2-17, "                                    ");
    mvprintw(LINES/2+2, COLS/2-17, "          START THE FIGHT!          ");
    mvprintw(LINES/2+3, COLS/2-17, "                                    ");
  }
  if (*cnt == 1) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES/2+4, COLS/2-17, "                                    ");
    mvprintw(LINES/2+5, COLS/2-17, "            HOW TO PLAY             ");
    mvprintw(LINES/2+6, COLS/2-17, "                                    ");

    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES/2+4, COLS/2-17, "                                    ");
    mvprintw(LINES/2+5, COLS/2-17, "            HOW TO PLAY             ");
    mvprintw(LINES/2+6, COLS/2-17, "                                    ");
  }
  if (*cnt == 2) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES/2+7, COLS/2-17, "                                    ");
    mvprintw(LINES/2+8, COLS/2-17, "            LEADERBOARD             ");
    mvprintw(LINES/2+9, COLS/2-17, "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES/2+7, COLS/2-17, "                                    ");
    mvprintw(LINES/2+8, COLS/2-17, "            LEADERBOARD             ");
    mvprintw(LINES/2+9, COLS/2-17, "                                    ");
  }
  if (*cnt == 3) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES/2+10, COLS/2-17, "                                    ");
    mvprintw(LINES/2+11, COLS/2-17, "              CREDITS               ");
    mvprintw(LINES/2+12, COLS/2-17, "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES/2+10, COLS/2-17, "                                    ");
    mvprintw(LINES/2+11, COLS/2-17, "              CREDITS               ");
    mvprintw(LINES/2+12, COLS/2-17, "                                    ");
  }
  if (*cnt == 4) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES/2+13, COLS/2-17, "                                    ");
    mvprintw(LINES/2+14, COLS/2-17, "               QUIT!                ");
    mvprintw(LINES/2+15, COLS/2-17, "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES/2+13, COLS/2-17, "                                    ");
    mvprintw(LINES/2+14, COLS/2-17, "               QUIT!                ");
    mvprintw(LINES/2+15, COLS/2-17, "                                    ");
  }

  mvprintw(LINES/2+17, COLS/2-24, "Press [SPACE] to continue or use the arrow to move.");
}

void DrawWindow::printCredits() {
  init_pair(3, COLOR_YELLOW, 232);  // FUNZIONI PER USARE IL COLORE GIALLO
  attron(COLOR_PAIR(3));
  mvprintw(LINES/2-10, COLS/2-51,
           "                                ___ ___ ___ ___ ___ _____   _____ ___                                 ");
  mvprintw(LINES/2-9, COLS/2-51,
           "                               / __| _ \\ __|   \\_ _|_   _| |_   _/ _ \\                                ");
  mvprintw(LINES/2-8, COLS/2-51,
           "                              | (__|   / _|| |) | |  | |     | || (_) |                               ");
  mvprintw(LINES/2-7, COLS/2-51,
           "                               \\___|_|_\\___|___/___| |_|     |_| \\___/                                ");
  attroff(COLOR_PAIR(3));

  init_pair(2, COLOR_GREEN, 232);  // FUNZIONI PER USARE I COLORI VEDI MENU.CPP
  attron(COLOR_PAIR(2));
  mvprintw(LINES/2-6, COLS/2-51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES/2-5, COLS/2-51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES/2-4, COLS/2-51,"          ____ ____ _ _  _                 ____ _  _ ____             ___  ____ ___  ___  ____        ");
  mvprintw(LINES/2-3, COLS/2-51,"          |___ |__/ | |_/                  |___ |\\/| |__|             |__] |___ |__] |__] |___        ");
  mvprintw(LINES/2-2, COLS/2-51,"          |___ |  \\ | | \\_                 |___ |  | |  |             |__] |___ |    |    |___        ");
  mvprintw(LINES/2-1, COLS/2-51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES/2, COLS/2-51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES/2+1, COLS/2-51,
           "                                              menu [ESC]           "
           "                                   ");
  mvprintw(LINES/2+2, COLS/2-51,
           "                                                                   "
           "                                   ");
  attroff(COLOR_PAIR(2));
}
void DrawWindow::credits(int direction) {
  while (direction != 27) {
    printCredits();       // STAMPA GLI AUTORI DEL GIOCO
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

void DrawWindow::printLeaderboardScreen() {
  int prog = LINES/2 - 15;
  for(int y = 0; y < 36; y++ ){
    init_pair(8, COLOR_BLACK, 232);
    attron(COLOR_PAIR(8));
    mvprintw(prog, COLS/2 - 53, "                                                                                                          ");
    prog++;
    attroff(COLOR_PAIR(8));
  }

  init_pair(3, COLOR_YELLOW, 232);
  attron(COLOR_PAIR(3));
  mvprintw(LINES/2 - 13, COLS/2 - 33, " __    _____ _____ ____  _____ _____ _____ _____ _____ _____ ____  ");
  mvprintw(LINES/2 - 12, COLS/2 - 33, "|  |  |   __|  _  |    \\|   __| __  | __  |     |  _  | __  |    \\ ");
  mvprintw(LINES/2 - 11, COLS/2 - 33, "|  |__|   __|     |  |  |   __|    -| __ -|  |  |     |    -|  |  |");
  mvprintw(LINES/2 - 10, COLS/2 - 33, "|_____|_____|__|__|____/|_____|__|__|_____|_____|__|__|__|__|____/ ");

  mvprintw(LINES/2 - 8, COLS/2 - 46, "--------------------------------------------------------------------------------------------");
  mvprintw(LINES/2 + 17, COLS/2 - 40, "col. 1");
  mvprintw(LINES/2 + 17, COLS/2 - 15, "col. 2");
  mvprintw(LINES/2 + 17, COLS/2 + 10, "col. 3");
  mvprintw(LINES/2 + 17, COLS/2 + 35, "col. 4");
  mvprintw(LINES/2 + 19, COLS/2 - 5, "menu [ESC]");
  attroff(COLOR_PAIR(3));
  
  
  std::string line;
  std::ifstream leaderboard("leaderBoard.txt");
  if (leaderboard.is_open()) {
    int i = LINES/2 - 6;
    int maxNameShowed = 0;
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(4));
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS/2 - 46, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    i = LINES/2 - 6;
    maxNameShowed = 0;
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS/2 - 21, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    i = LINES/2 - 6;
    maxNameShowed = 0;
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS/2 + 4, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    i = LINES/2 - 6;
    maxNameShowed = 0;
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS/2 + 29, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    attroff(COLOR_PAIR(4));
    leaderboard.close();
  }
  
}
void DrawWindow::leaderboardScreen(int direction) {
  while (direction != 27) {
    printLeaderboardScreen();
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

void DrawWindow::printHowToPlay() {  // GESTISCE LA SCHERMATA DEL HOW TO PLAY

  init_pair(3, COLOR_YELLOW, 232);   // FUNZIONI PER USARE IL COLORE GIALLO
  attron(COLOR_PAIR(3));
  mvprintw(LINES/2-12, COLS/2-50,
           "                     _____ _____ _ _ _    _____ _____    _____ __  "
           "  _____ __ __                     ");
  mvprintw(LINES/2-11, COLS/2-50,
           "                    |  |  |     | | | |  |_   _|     |  |  _  |  | "
           " |  _  |  |  |                    ");
  mvprintw(LINES/2-10, COLS/2-50,
           "                    |     |  |  | | | |    | | |  |  |  |   __|  "
           "|__|     |_   _|                    ");
  mvprintw(LINES/2-9, COLS/2-50,
           "                    |__|__|_____|_____|    |_| |_____|  |__|  "
           "|_____|__|__| |_|                      ");
  mvprintw(LINES/2-8, COLS/2-50,
           "                                                                   "
           "                                  ");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE GIALLO

  init_pair(2, COLOR_GREEN, 232);  // FUNZIONI PER USARE IL VERDE
  attron(COLOR_PAIR(2));
  mvprintw(LINES/2-7, COLS/2-50,
           "       PLAY THIS ADVENTURE FROM THE POINT OF VIEW OF THE MONKEY "
           "THAT STARTED THE REVOLUTION!         ");
  mvprintw(LINES/2-6, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2-5, COLS/2-50,
           "       ELIMINATE THE ENEMIES, CLEAN THE ROOM, MOVE TO THE NEXT ONE "
           "AND COLLECT BANANAS!              ");
  mvprintw(LINES/2-4, COLS/2-50,
           "       USE THE [ARROWS] TO MOVE AND [W]/[E] TO USE THE "
           "BANANACANNON, WATCH OUT FOR AMMO!             ");
  mvprintw(LINES/2-3, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2-2, COLS/2-50,
           "       IF YOU RUN OUT FOR AMMO, DONT FORGET YOU CAN USE [SPACE] "
           "FOR YOUR TREMENDOUS PUNCHES!         ");
  mvprintw(LINES/2-1, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2, COLS/2-50,
           "       WITH YOUR BANANAS YOU WILL BE ABLE TO BUY UPGRADES FOR THE "
           "BANANACANNON                       ");
  mvprintw(LINES/2+1, COLS/2-50,
           "       OR BUY BACK LIVES YOU HAVE LOST                             "
           "                                  ");
  mvprintw(LINES/2+2, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2+3, COLS/2-50,
           "       WHEN YOU HAVE %d BANANAS PRESS [S] TO UPGRADE THE BANANA "
           "CANNON                               ",
           10);
  mvprintw(LINES/2+4, COLS/2-50,
           "       OR [A] TO RECOVER A LOST LIFE                               "
           "                                  ");
  mvprintw(LINES/2+5, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2+6, COLS/2-50,
           "       COLLECT AS MUCH BONUSES AS POSSIBLE, BUT BEWARE! THEY CAN "
           "HIDE TRAPS!                         ");
  mvprintw(LINES/2+7, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2+8, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2+9, COLS/2-50,
           "          [E][W] = SHOOT   [ARROWS] = MOVE    [A] = BUY EXTRA LIFE "
           "  [S] = DAMAGE UPGRADE            ");
  mvprintw(LINES/2+10, COLS/2-50,
           "                            [R] = RELOAD AMMO    [SPACE] = PUNCH   "
           "                                  ");
  mvprintw(LINES/2+11, COLS/2-50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES/2+12, COLS/2-50,
           "                                              menu [ESC]           "
           "                                  ");
  mvprintw(LINES/2+13, COLS/2-50,
           "                                                                   "
           "                                  ");
  attroff(COLOR_PAIR(2));  // CHIUSURA DEL COLORE VERDE
}
void DrawWindow::HowToPlay(int direction) {
  while (direction != 27) {
    printHowToPlay();     // STAMPA LE HOW TO PLAY
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

void DrawWindow::printCharacter(int x, int y, char c) {
  move(y, x);
  printw("%c", c);
}

void DrawWindow::drawRect(
    int startX, int startY, int width, int heigth, pEnemyList enemyList,
    int round, bool isScreenBound) {  // isScreenBound SI UNA PER FLAGGARE CHE È
                                      // IL RETTANGOLO CHE DELIMITA LO SCHERMO,
                                      // QUINDI NON DEVE APRIRSI
  for (int i = startY; i < width; ++i) {
    mvprintw(startX, i, "-");
    mvprintw(heigth, i, "-");
  }
  if (enemyList->next != NULL || isScreenBound) {
    for (int i = startX; i < heigth; ++i) {
      mvprintw(i, startY, "|");
      mvprintw(i, width, "|");
    }
  }
  if (round == 1) {
    for (int i = startX; i < heigth; ++i) {
      mvprintw(i, startY, "|");
    }
  }
  mvprintw(startX, width, "o");
  mvprintw(startX, startY, "o");
  mvprintw(heigth, startY, "o");
  mvprintw(heigth, width, "o");
}

void DrawWindow::drawLeaderboardOnScreen(){
  std::string localScore[44] = {"NULL"};
  std::string line;
  std::ifstream leaderboard("leaderBoard.txt");

  init_pair(3, COLOR_YELLOW, -1);
  attron(COLOR_PAIR(3));
  mvprintw(5, 94, "LEADERBOARD");
  attroff(COLOR_PAIR(3));
  mvprintw(7, 88, "-----------------------");


  if (leaderboard.is_open()) {
    int i = 9;
    int linesName = 0;
    int maxNameOnScreen = 0;
    while (getline(leaderboard, line) && (linesName < 44)) {
      localScore[linesName] = line.c_str();
      linesName++;
    }
    leaderboard.close();
    linesName--;

    while (linesName >= 0 && maxNameOnScreen < 11) {
      mvprintw(i, 90, "%s", localScore[linesName].c_str());
      i = i + 2;
      linesName--;
      maxNameOnScreen++;
    }
  }
}

void DrawWindow::drawStats(int startX, int startY, int width, int heigth,
                           int pointsOnScreen, Character character,
                           pEnemyList enemyList, int powerUp, int bananas,
                           int maxRound, pRoom roomList) {
  int powerUp_y = 52;
  int powerUp_x = 23;
  int statusAmmoColor = 0;

  mvprintw(startX - 2, startY + 5, "SCORE:");
  mvprintw(startX - 2, startX + 47, "LIFE:");
  mvprintw(powerUp_x, powerUp_y, "POWER-UP");

  mvprintw(26, 52, "MAGAZINE");
  mvprintw(26, 76, "%d", character.getGun().getMagazineAmmo());
  mvprintw(27, 52, "BANANA PEELS");

  if (character.getGun().getTotalAmmo() > 30) {
    statusAmmoColor = 21;
    init_pair(statusAmmoColor, COLOR_WHITE, -1);
    attron(COLOR_PAIR(statusAmmoColor));
  } else if (character.getGun().getTotalAmmo() > 20 &&
             character.getGun().getTotalAmmo() <= 30) {
    statusAmmoColor = 22;
    init_pair(statusAmmoColor, COLOR_YELLOW, -1);
    attron(COLOR_PAIR(statusAmmoColor));
  } else if (character.getGun().getTotalAmmo() <= 20) {
    statusAmmoColor = 23;
    init_pair(statusAmmoColor, COLOR_RED, -1);
    attron(COLOR_PAIR(statusAmmoColor));
  }
  mvprintw(27, 76, "%d", character.getGun().getTotalAmmo());
  attroff(COLOR_PAIR(statusAmmoColor));

  mvprintw(28, 52, "BANANAS");
  mvprintw(28, 76, "%d", bananas);
  mvprintw(29, 52, "ROOM");
  mvprintw(29, 76, "%d/%d", lenghtRoom(roomList), maxRound);
  mvprintw(30, 52, "ROUND MAX");
  mvprintw(30, 76, "%d", maxRound);

  init_pair(11, COLOR_WHITE, 232);
  attron(COLOR_PAIR(11));
  drawRect(startX - 4, startY - 11, width + 12, heigth + 12, enemyList, 0,
           true);
  drawRect(startX - 4, startY + 65, width + 40, heigth + 12, enemyList, 0,
           true);
  attroff(COLOR_PAIR(11));

  init_pair(3, COLOR_YELLOW, -1);  // FUNZIONI PER USARE I COLORI
  attron(COLOR_PAIR(3));
  mvprintw(startX - 2, startY + 12, "%d", pointsOnScreen);
  if (character.getNumberLife() == 3)
    mvprintw(startX - 2, startY + 38, "[C] [C] [C]");
  if (character.getNumberLife() == 2)
    mvprintw(startX - 2, startY + 38, "[C] [C] [ ]");
  if (character.getNumberLife() == 1)
    mvprintw(startX - 2, startY + 38, "[C] [ ] [ ]");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE

  init_pair(3, COLOR_YELLOW, -1);  // FUNZIONI PER USARE I COLORI
  attron(COLOR_PAIR(3));
  if (powerUp == 4) mvprintw(powerUp_x, powerUp_y + 10, "[X] [X] [X] [X]");
  if (powerUp == 3) mvprintw(powerUp_x, powerUp_y + 10, "[X] [X] [X] [ ]");
  if (powerUp == 2) mvprintw(powerUp_x, powerUp_y + 10, "[X] [X] [ ] [ ]");
  if (powerUp == 1) mvprintw(powerUp_x, powerUp_y + 10, "[X] [ ] [ ] [ ]");
  if (powerUp == 0) mvprintw(powerUp_x, powerUp_y + 10, "[ ] [ ] [ ] [ ]");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE
}

Position DrawWindow::randomPosition(int startRange, int endRange) {
  Position pos;
  pos.x = startRange + (std::rand() % (endRange - startRange + 1));
  pos.y = startRange + (std::rand() % (endRange - startRange + 1));
  while (!(mvinch(pos.y, pos.x) == ' ')) {
    pos.x = startRange + (std::rand() % (endRange - startRange) + 1);
    pos.y = startRange + (std::rand() % (endRange - startRange) + 1);
  }
  return pos;
}

pPosition DrawWindow::generateMountain(pPosition list, int &mountainCount) {
  while (mountainCount > 0) {
    int x = randomPosition(40, 70).x;
    int y = randomPosition(8, 19).y;
    pPosition head = new Position;
    head->x = x;
    head->y = y;
    head->skin = '^';
    head->life = MOUNTAIN_LIFE;
    head->next = list;
    list = head;
    mountainCount -= 1;
  }
  return list;
}

pPosition DrawWindow::generateBonus(pPosition bonusList, int &bonusCount) {
  /**
   * Genera la lista dei bonus (coordinate e skin), l'effetto di tali bonus è
   * decretato altrove.
   */
  srand(time(0));
  while (bonusCount > 0) {
    pPosition tmpHead = new Position;
    tmpHead->x = randomPosition(25, 33).x;
    tmpHead->y = randomPosition(8, 19).y;
    tmpHead->skin = '?';
    tmpHead->next = bonusList;
    bonusList = tmpHead;
    bonusCount -= 1;
  }
  return bonusList;
}

void DrawWindow::printMountain(pPosition list) {
  pPosition mountainList = list;
  while (mountainList != NULL) {
    init_pair(15, COLOR_YELLOW, -1);
    attron(COLOR_PAIR(15));
    printCharacter(mountainList->x, mountainList->y, mountainList->skin);
    attroff(COLOR_PAIR(15));
    mountainList = mountainList->next;
  }
}

void DrawWindow::printBonus(pPosition bonusList) {
  bool first = true;
  while (bonusList != NULL) {
    if (first)
      first = false;
    else
      printCharacter(bonusList->x, bonusList->y, bonusList->skin);
    bonusList = bonusList->next;
  }
}

void DrawWindow::showBonusOnScreen(bool &upgradeBuyed, int &upgradeType,
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

int DrawWindow::lenghtList(pEnemyList list) {
  int i;
  if(list == NULL) { i = 0; } else { i = -1; }  // serve a far indicare 0 quando è vuota, invece di -1 che è utile quando si conta.
  while (list != NULL) {
    i++;
    list = list->next;
  }
  return i;
}

int DrawWindow::lenghtRoom(pRoom list) {
  int i = 0;
  while (list != NULL) {
    i++;
    list = list->next;
  }
  return i;
}

void DrawWindow::printCharacterStats(pEnemyList list, pEnemyList specialEnemyList, pEnemyList bossEnemyList, Character character) {
  int enemyLeftOnScreen = lenghtList(list) + lenghtList(specialEnemyList) + lenghtList(bossEnemyList);
  int i = 22;
  int reachBound = 0;       // VEDI RIGA 363
  int X_ElencoNemici = 19;  // gestisce la x da dove inizia la lista dei nemici
  int BarStart = 56;        // gestisce dove partono gli oggetti della barra
  int AddBar = BarStart;    // cicla per aggiungere un cordinata
  int healtColorPair = 0;

  if (enemyLeftOnScreen > 0) {
    mvprintw(i, X_ElencoNemici, "Enemy left: %d", enemyLeftOnScreen);
  } else {
    mvprintw(i, X_ElencoNemici, "[ALL ENEMY DEFEATED!]");
  }

  if (character.getGun().getTotalAmmo() == 0 &&
      character.getGun().getMagazineAmmo() == 0) {
    init_pair(25, COLOR_RED, -1);
    attron(COLOR_PAIR(25));
    mvprintw(26, 76, "%d", character.getGun().getMagazineAmmo());
    mvprintw(25, 52, "OUT OF AMMO!");
    attroff(COLOR_PAIR(25));
  } else if (character.getGun().getMagazineAmmo() == 0) {
    init_pair(25, COLOR_RED, -1);
    attron(COLOR_PAIR(25));
    mvprintw(26, 76, "%d", character.getGun().getMagazineAmmo());
    mvprintw(25, 52, "PRESS [R] TO RELOAD!");
    attroff(COLOR_PAIR(25));
  }

  // CODICE CHE GESTISCE LA BARRA DELLA VITA
  // ------------------------------------------------------------------------------

  mvprintw(i, BarStart - 4, "HP");  // MOSTRA LA SCRITTA HP PRIMA DELLA BARRA

  if (character.getLife() >
      60) {  // GESTISCE IL COLORE DELLA BARRA TRA 100 E 61
    healtColorPair = 6;
    init_pair(healtColorPair, COLOR_GREEN, COLOR_GREEN);
    attron(COLOR_PAIR(healtColorPair));
  }
  if (character.getLife() >= 25 &&
      character.getLife() <=
          60) {  // GESTISCE IL COLORE DELLA BARRA TRA 50 E 25
    healtColorPair = 5;
    init_pair(healtColorPair, COLOR_YELLOW, COLOR_YELLOW);
    attron(COLOR_PAIR(healtColorPair));
  }
  if (character.getLife() < 25) {  // GESTISCE IL COLORE DELLA BARRA TRA 24 E 0
    healtColorPair = 4;
    init_pair(healtColorPair, COLOR_RED, COLOR_RED);
    attron(COLOR_PAIR(healtColorPair));
  }

  init_pair(8, 233, 233);
  attron(COLOR_PAIR(8));
  mvprintw(i, BarStart, "                    ");  // SFONDO NERO BARRA
  attroff(COLOR_PAIR(8));

  attron(COLOR_PAIR(healtColorPair));
  for (int volt = 0; volt <= (character.getLife() - 1) / 5;
       volt++) {  // GENERA IL SIMBOLO " " OGNI DIECI UNITÀ DI VITA
    mvprintw(i, AddBar, " ");
    AddBar++;
  }
  attroff(COLOR_PAIR(healtColorPair));
  mvprintw(i, BarStart - 1,
           "[");  // GERERA I CARATTERI PER IL CONTENITORE DELLA VITA
  mvprintw(i, BarStart + 20, "]");

  // FINE CODICE BARRA DELLA VITA
  // ------------------------------------------------------------------------------------------

  while (list != NULL &&
         reachBound < 8) {  // REACHBOUND SERVE A DETERMINARE IL LIMITE DI
                            // NEMICI VISUALIZZABILI NELLA LISTA DELL'HUD
    if (list->enemy.getX() != 0) {
          i++;
      mvprintw(i, X_ElencoNemici, "- Base Hunter: %d HP",
               list->enemy.getLife());
    }
    reachBound++;
    list = list->next;
  }
  while (specialEnemyList != NULL &&
         reachBound < 8) {  // REACHBOUND SERVE A DETERMINARE IL LIMITE DI
                            // NEMICI VISUALIZZABILI NELLA LISTA DELL'HUD
    if (specialEnemyList->enemy.getX() != 0) {
          i++;
      mvprintw(i, X_ElencoNemici, "- Special Hunter: %d HP",
                specialEnemyList->enemy.getLife());
    }
    reachBound++;
    specialEnemyList = specialEnemyList->next;
  }
  while (bossEnemyList != NULL &&
         reachBound < 8) {  // REACHBOUND SERVE A DETERMINARE IL LIMITE DI
                            // NEMICI VISUALIZZABILI NELLA LISTA DELL'HUD
    if (bossEnemyList->enemy.getX() != 0) {
      i++;
      mvprintw(i, X_ElencoNemici, "- BOSS: %d HP",
               bossEnemyList->enemy.getLife());
    }
    reachBound++;
    bossEnemyList = bossEnemyList->next;
  }
}

void DrawWindow::printEnemy(pEnemyList list, DrawWindow drawWindow) {
  while (list != NULL) {
    drawWindow.printCharacter(list->enemy.getX(), list->enemy.getY(),
                              list->enemy.getSkin());
    list = list->next;
  }
}

void DrawWindow::moveEnemy(pEnemyList list, Character character,
                           DrawWindow drawWindow, long points) {
  int yP = character.getY(), xE, yE;
  int movementSpeedFactor = 1;
  
  while (list != NULL) {

    if(list->enemy.getSkin() == 'e') movementSpeedFactor = 25;
    if(list->enemy.getSkin() == 'E') movementSpeedFactor = 40;
    if(list->enemy.getSkin() == 'B') movementSpeedFactor = 60;

    if (points % movementSpeedFactor == 0) {
      xE = list->enemy.getX(), yE = list->enemy.getY();
      if (yP > yE && (mvinch(yE + 1, xE) == ' ' || mvinch(yE + 1, xE) == '?')) {
        list->enemy.setY(yE + 1);
        drawWindow.printCharacter(xE, yE, list->enemy.getSkin());
      } else if (yP < yE && (mvinch(yE - 1, xE) == ' ' || mvinch(yE - 1, xE) == '?')) {
        list->enemy.setY(yE - 1);
        drawWindow.printCharacter(xE, yE, list->enemy.getSkin());
      }
    }
    list = list->next;
  }
}

pRoom DrawWindow::saveRoom(pPosition mountainList, pPosition bonusList,
                           pRoom roomList) {
  pRoom head = new Room;
  head->mountainList = mountainList;
  head->bonusList = bonusList;
  head->spawnSpecialEnemy = true;
  head->spawnBossEnemy = true;
  head->next = roomList;
  roomList->prev = head;
  roomList = head;
  return roomList;
}

pRoom DrawWindow::changeRoom(Character &character, int &normalEnemyCount,
                             int &round, pEnemyList &normalEnemyList,
                             pPosition &mountainList, pPosition &bonusList,
                             pRoom roomList, int &maxRound) {
  if (character.getX() == GAMEWIDTH) {
    if (maxRound > lenghtRoom(roomList)) {
      roomList = roomList->prev;
      round += 1;
      character.setX(23);
    } else if (maxRound == lenghtRoom(roomList)) {
      character.setX(23);
      int mountainCount = rand() % 8 + 1, bonusCounter = 1;

      if (maxRound < 2)
        bonusCounter = 0;
      else {
        srand(time(0));
        bonusCounter = rand() % 3 + 1;
      }

      roomList->mountainList = generateMountain(mountainList, mountainCount);
      roomList->bonusList = generateBonus(bonusList, bonusCounter);
      roomList = saveRoom(mountainList, bonusList, roomList);
      if (round <= NORMAL_ENEMY_LIMIT)
        normalEnemyCount = round;
      else 
        normalEnemyCount = NORMAL_ENEMY_LIMIT;

      normalEnemyList = normalEnemyList->next;
      maxRound += 1;
    }
  } else if (character.getX() == 22) {
    character.setX(GAMEWIDTH - 1);
    roomList = roomList->next;
    round -= 1;
  }
  return roomList;
}

void DrawWindow::printLoseScreen(float finalScore) {
  init_pair(16, COLOR_RED, 232);
  attron(COLOR_PAIR(16));
  mvprintw(3, 3,
           "                                                                   "
           "                              ");
  mvprintw(4, 3,
           "                          __ _  __ _ _ __ ___   ___    _____   "
           "_____ _ __                        ");
  mvprintw(5, 3,
           "                         / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ "
           "/ / _ \\ '__|                       ");
  mvprintw(6, 3,
           "                        | (_| | (_| | | | | | |  __/ | (_) \\ V /  "
           "__/ |                          ");
  mvprintw(7, 3,
           "                         \\__, |\\__,_|_| |_| |_|\\___|  \\___/ "
           "\\_/ \\___|_|                          ");
  mvprintw(8, 3,
           "                         |___/                                     "
           "                              ");
  mvprintw(9, 3,
           "                                                                   "
           "                              ");
  mvprintw(10, 3,
           "                                                                   "
           "                              ");
  attroff(COLOR_PAIR(16));

  init_pair(17, COLOR_GREEN, 232);
  attron(COLOR_PAIR(17));
  mvprintw(11, 3,
           "               HUNTERS HAVE TRACKED YOU, SURROUNDED AND FINALLY "
           "THEY KILLED YOU...               ");
  mvprintw(12, 3,
           "                                                                   "
           "                              ");
  mvprintw(13, 3,
           "                             YOUR LIFE GOES AWAY WITH YOUR "
           "REVENGE.                              ");
  mvprintw(14, 3,
           "                                                                   "
           "                              ");
  mvprintw(15, 3,
           "            BUT DON'T GET MAD, THERE ARE THOUSANDS OF MONKEYS "
           "READY TO REBELL AGAIN...           ");
  mvprintw(16, 3,
           "                                      ...SOONER OR THEN...         "
           "                              ");
  mvprintw(17, 3,
           "                                                                   "
           "                              ");
  mvprintw(18, 3,
           "                                                                   "
           "                              ");
  mvprintw(19, 3,
           "     FINAL SCORE:                                                  "
           "                              ");
  mvprintw(19, 21, "%.0f", finalScore);
  mvprintw(20, 3,
           "                                                                    set score & exit [ENTER]     ");
  mvprintw(21, 3,
           "                                                                 (no name will not save score)   ");
  mvprintw(22, 3,
           "                                                                   "
           "                              ");
  attroff(COLOR_PAIR(17));
}

void DrawWindow::saveRecord(float finalScore, char name[]) {
  int nameLen = strlen(name);
  int nameMax = 12;
  std::fstream board;
  board.open("leaderBoard.txt", std::ios::app);
  if (board && finalScore > 0 && name[0] != '\0') {  // lo score è salvato solo se maggiore di 0 e il nome non è vuoto
    board << name << ":";
    while(nameLen < nameMax){
      board << " ";
      nameLen++;
    }
    board << finalScore << "\n";
  }
  board.close();
}

void DrawWindow::loseScreen(int direction, float finalScore) {
  char name[10] = {'\0'};
  char name2[10] = {'\0'};
  while (direction != 0) {
    printLoseScreen(finalScore);
    strcat(name, name2);

    init_pair(17, COLOR_GREEN, 232);
    attron(COLOR_PAIR(17));
    mvprintw(21, 21, "__________");
    mvprintw(21, 8, "INSERT NAME: %s", name);
    attroff(COLOR_PAIR(17));
    refresh();
    direction = getstr(name2);
  }
  saveRecord(finalScore, name);
}
