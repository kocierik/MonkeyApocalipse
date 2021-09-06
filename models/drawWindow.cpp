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
#define SPECIAL_ENEMY_FREQUENCY 5  // Spawn ogni 5 round
#define BOSS_ENEMY_FREQUENCY 10    // Spawn ogni 10 round
#define MOUNTAIN_LIFE 10
const int MAXNAMECHARACTER = 10;

DrawWindow::DrawWindow() {}

/*
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

// FUNZIONE CHE STAMPA LA GRAFICA DEL LOGO NEL MENU
void DrawWindow::drawMenu() {
  init_pair(1, COLOR_RED, 232);
  attron(COLOR_PAIR(1));
  mvprintw(LINES / 2 - 10, COLS / 2 - 54,
           "                                                                   "
           "                                         ");
  mvprintw(LINES / 2 - 9, COLS / 2 - 54,
           "    b    d  P*Y  8b 8 8  d 88888 Yb  dP        A   8**Y  P*Y   "
           "P**b8   b    8     Yb  dP 8**Y .P*Y8 88888   ");
  mvprintw(LINES / 2 - 8, COLS / 2 - 54,
           "    8b  d8 P   Y 8Yb8 8od  8__    YbdP        PY   8__P P   Y P   "
           "`*   PY   8      YbdP  8__P `Yo.* 8__     ");
  mvprintw(LINES / 2 - 7, COLS / 2 - 54,
           "    8Yb P8 b   d 8 Y8 8*Y  8**     8P        P__Y  8**  b   P Y    "
           "   P__Y  8  .o   8P   8**  o.`Y8 8**     ");
  mvprintw(LINES / 2 - 6, COLS / 2 - 54,
           "    8 Y  8  Ybo  8  Y 8  Y 88888  dP        P****Y 8     P*Y   "
           "YoodP P****Y 8ood8  dP    8     8oP* 88888   ");
  mvprintw(LINES / 2 - 5, COLS / 2 - 54,
           "                                                                   "
           "                                         ");
  mvprintw(LINES / 2 - 4, COLS / 2 - 54,
           "     THE REVENGE OF THE MONKEYS HAS JUST BEGUN!                    "
           "                                         ");
  mvprintw(LINES / 2 - 3, COLS / 2 - 54,
           "                                                                   "
           "                                         ");
  attroff(COLOR_PAIR(1));
}

// FUNZIONE CHE STAMPA E GESTISCE LE VOCI DEL MENU
void DrawWindow::printCommand(int *cnt) {
  init_pair(12, COLOR_BLACK, COLOR_RED);

  if (*cnt == 0) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES / 2 + 1, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 2, COLS / 2 - 17,
             "         FIGHT FOR FREEDOM!         ");
    mvprintw(LINES / 2 + 3, COLS / 2 - 17,
             "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES / 2 + 1, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 2, COLS / 2 - 17,
             "         FIGHT FOR FREEDOM!         ");
    mvprintw(LINES / 2 + 3, COLS / 2 - 17,
             "                                    ");
  }
  if (*cnt == 1) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES / 2 + 4, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 5, COLS / 2 - 17,
             "        APES STRONG TOGETHER        ");
    mvprintw(LINES / 2 + 6, COLS / 2 - 17,
             "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES / 2 + 4, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 5, COLS / 2 - 17,
             "        APES STRONG TOGETHER        ");
    mvprintw(LINES / 2 + 6, COLS / 2 - 17,
             "                                    ");
  }
  if (*cnt == 2) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES / 2 + 7, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 8, COLS / 2 - 17,
             "            HOW TO PLAY             ");
    mvprintw(LINES / 2 + 9, COLS / 2 - 17,
             "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES / 2 + 7, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 8, COLS / 2 - 17,
             "            HOW TO PLAY             ");
    mvprintw(LINES / 2 + 9, COLS / 2 - 17,
             "                                    ");
  }
  if (*cnt == 3) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES / 2 + 10, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 11, COLS / 2 - 17,
             "            LEADERBOARD             ");
    mvprintw(LINES / 2 + 12, COLS / 2 - 17,
             "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES / 2 + 10, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 11, COLS / 2 - 17,
             "            LEADERBOARD             ");
    mvprintw(LINES / 2 + 12, COLS / 2 - 17,
             "                                    ");
  }
  if (*cnt == 4) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES / 2 + 13, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 14, COLS / 2 - 17,
             "              CREDITS               ");
    mvprintw(LINES / 2 + 15, COLS / 2 - 17,
             "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES / 2 + 13, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 14, COLS / 2 - 17,
             "              CREDITS               ");
    mvprintw(LINES / 2 + 15, COLS / 2 - 17,
             "                                    ");
  }
  if (*cnt == 5) {
    attron(COLOR_PAIR(12));
    mvprintw(LINES / 2 + 16, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 17, COLS / 2 - 17,
             "               QUIT!                ");
    mvprintw(LINES / 2 + 18, COLS / 2 - 17,
             "                                    ");
    attroff(COLOR_PAIR(12));
  } else {
    mvprintw(LINES / 2 + 16, COLS / 2 - 17,
             "                                    ");
    mvprintw(LINES / 2 + 17, COLS / 2 - 17,
             "               QUIT!                ");
    mvprintw(LINES / 2 + 18, COLS / 2 - 17,
             "                                    ");
  }

  mvprintw(LINES / 2 + 20, COLS / 2 - 24,
           "Press [SPACE] to continue or use the arrow to move.");
}

// FUNZIONE CHE STAMPA LA GRAFICA DELLA SCHERMATA DEI CREDITS
void DrawWindow::printCredits() {
  init_pair(3, COLOR_YELLOW, 232); 
  attron(COLOR_PAIR(3));
  mvprintw(LINES / 2 - 10, COLS / 2 - 51,
           "                                ___ ___ ___ ___ ___ _____   _____ "
           "___                                 ");
  mvprintw(LINES / 2 - 9, COLS / 2 - 51,
           "                               / __| _ \\ __|   \\_ _|_   _| |_   "
           "_/ _ \\                                ");
  mvprintw(LINES / 2 - 8, COLS / 2 - 51,
           "                              | (__|   / _|| |) | |  | |     | || "
           "(_) |                               ");
  mvprintw(LINES / 2 - 7, COLS / 2 - 51,
           "                               \\___|_|_\\___|___/___| |_|     |_| "
           "\\___/                                ");
  attroff(COLOR_PAIR(3));

  init_pair(2, COLOR_GREEN, 232);  
  attron(COLOR_PAIR(2));
  mvprintw(LINES / 2 - 6, COLS / 2 - 51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES / 2 - 5, COLS / 2 - 51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES / 2 - 4, COLS / 2 - 51,
           "          ____ ____ _ _  _                 ____ _  _ ____          "
           "   ___  ____ ___  ___  ____        ");
  mvprintw(LINES / 2 - 3, COLS / 2 - 51,
           "          |___ |__/ | |_/                  |___ |\\/| |__|         "
           "    |__] |___ |__] |__] |___        ");
  mvprintw(LINES / 2 - 2, COLS / 2 - 51,
           "          |___ |  \\ | | \\_                 |___ |  | |  |        "
           "     |__] |___ |    |    |___        ");
  mvprintw(LINES / 2 - 1, COLS / 2 - 51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES / 2, COLS / 2 - 51,
           "                                                                   "
           "                                   ");
  mvprintw(LINES / 2 + 1, COLS / 2 - 51,
           "                                              menu [ESC]           "
           "                                   ");
  mvprintw(LINES / 2 + 2, COLS / 2 - 51,
           "                                                                   "
           "                                   ");
  attroff(COLOR_PAIR(2));
}

// FUNZIONE CHE GESTISCE LA LOGICA DELLA SCHERMATA DEI CREDITS
void DrawWindow::credits(int direction) {
  direction = 0;
  while (direction != 27) {
    printCredits();
    direction = getch();
  }
}

// FUNZIONE CHE STAMPA LA SCHERMATA DELLA LEADERBOARD
void DrawWindow::printLeaderboardScreen() {
  int prog = LINES / 2 - 15;
  for (int y = 0; y < 36; y++) {
    init_pair(8, COLOR_BLACK, 232);
    attron(COLOR_PAIR(8));
    mvprintw(prog, COLS / 2 - 53,
             "                                                                 "
             "                                         ");
    prog++;
    attroff(COLOR_PAIR(8));
  }

  init_pair(3, COLOR_YELLOW, 232);
  attron(COLOR_PAIR(3));
  mvprintw(
      LINES / 2 - 13, COLS / 2 - 33,
      " __    _____ _____ ____  _____ _____ _____ _____ _____ _____ ____  ");
  mvprintw(
      LINES / 2 - 12, COLS / 2 - 33,
      "|  |  |   __|  _  |    \\|   __| __  | __  |     |  _  | __  |    \\ ");
  mvprintw(
      LINES / 2 - 11, COLS / 2 - 33,
      "|  |__|   __|     |  |  |   __|    -| __ -|  |  |     |    -|  |  |");
  mvprintw(
      LINES / 2 - 10, COLS / 2 - 33,
      "|_____|_____|__|__|____/|_____|__|__|_____|_____|__|__|__|__|____/ ");

  mvprintw(LINES / 2 - 8, COLS / 2 - 46,
           "-------------------------------------------------------------------"
           "-------------------------");
  mvprintw(LINES / 2 + 17, COLS / 2 - 40, "col. 1");
  mvprintw(LINES / 2 + 17, COLS / 2 - 15, "col. 2");
  mvprintw(LINES / 2 + 17, COLS / 2 + 10, "col. 3");
  mvprintw(LINES / 2 + 17, COLS / 2 + 35, "col. 4");
  mvprintw(LINES / 2 + 19, COLS / 2 - 5, "menu [ESC]");
  attroff(COLOR_PAIR(3));

  std::string line;
  std::ifstream leaderboard("leaderBoard.txt");
  if (leaderboard.is_open()) {
    int i = LINES / 2 - 6;
    int maxNameShowed = 0;
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(4));
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS / 2 - 46, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    i = LINES / 2 - 6;
    maxNameShowed = 0;
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS / 2 - 21, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    i = LINES / 2 - 6;
    maxNameShowed = 0;
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS / 2 + 4, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    i = LINES / 2 - 6;
    maxNameShowed = 0;
    while ((maxNameShowed < 11) && (getline(leaderboard, line))) {
      mvprintw(i, COLS / 2 + 29, " %s ", line.c_str());
      i += 2;
      maxNameShowed++;
    }
    attroff(COLOR_PAIR(4));
    leaderboard.close();
  }
}

// FUNZIONE CHE GESTISCE LA LOGICA DELLA SCHERMATA DELLA LEADERBOARDS DEL MENU
void DrawWindow::leaderboardScreen(int direction) {
  while (direction != 27) {
    printLeaderboardScreen();
    direction = getch();
  }
}

// FUNZIONE CHE STAMPA LA SCHERMATA DELL'HOW TO PLAY
void DrawWindow::printHowToPlay() {

  init_pair(3, COLOR_YELLOW, 232);
  attron(COLOR_PAIR(3));
  mvprintw(LINES / 2 - 12, COLS / 2 - 50,
           "                     _____ _____ _ _ _    _____ _____    _____ __  "
           "  _____ __ __                     ");
  mvprintw(LINES / 2 - 11, COLS / 2 - 50,
           "                    |  |  |     | | | |  |_   _|     |  |  _  |  | "
           " |  _  |  |  |                    ");
  mvprintw(LINES / 2 - 10, COLS / 2 - 50,
           "                    |     |  |  | | | |    | | |  |  |  |   __|  "
           "|__|     |_   _|                    ");
  mvprintw(LINES / 2 - 9, COLS / 2 - 50,
           "                    |__|__|_____|_____|    |_| |_____|  |__|  "
           "|_____|__|__| |_|                      ");
  mvprintw(LINES / 2 - 8, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE GIALLO

  init_pair(2, COLOR_GREEN, 232);  // FUNZIONI PER USARE IL VERDE
  attron(COLOR_PAIR(2));
  mvprintw(LINES / 2 - 7, COLS / 2 - 50,
           "       PLAY THIS ADVENTURE FROM THE POINT OF VIEW OF THE MONKEY "
           "THAT STARTED THE REVOLUTION!         ");
  mvprintw(LINES / 2 - 6, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 - 5, COLS / 2 - 50,
           "       ELIMINATE THE ENEMIES, CLEAN THE ROOM, MOVE TO THE NEXT ONE "
           "AND COLLECT BANANAS!              ");
  mvprintw(LINES / 2 - 4, COLS / 2 - 50,
           "       USE THE [ARROWS] TO MOVE AND [,]/[.] TO USE THE "
           "BANANACANNON, WATCH OUT FOR AMMO!             ");
  mvprintw(LINES / 2 - 3, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 - 2, COLS / 2 - 50,
           "       IF YOU RUN OUT FOR AMMO, DONT FORGET YOU CAN USE [K] "
           "FOR YOUR TREMENDOUS PUNCHES!             ");
  mvprintw(LINES / 2 - 1, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2, COLS / 2 - 50,
           "       WITH YOUR BANANAS YOU WILL BE ABLE TO BUY UPGRADES FOR THE "
           "BANANACANNON                       ");
  mvprintw(LINES / 2 + 1, COLS / 2 - 50,
           "       OR BUY BACK LIVES YOU HAVE LOST                             "
           "                                  ");
  mvprintw(LINES / 2 + 2, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 3, COLS / 2 - 50,
           "       WHEN YOU HAVE %d BANANAS PRESS [0] TO UPGRADE THE BANANA "
           "CANNON                               ",
           10);
  mvprintw(LINES / 2 + 4, COLS / 2 - 50,
           "       OR [9] TO RECOVER A LOST LIFE                               "
           "                                  ");
  mvprintw(LINES / 2 + 5, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 6, COLS / 2 - 50,
           "       COLLECT AS MUCH BONUSES AS POSSIBLE, BUT BEWARE! THEY CAN "
           "HIDE TRAPS!                         ");
  mvprintw(LINES / 2 + 7, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 8, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 9, COLS / 2 - 50,
           "          [,][.] = SHOOT    [ARROW] = MOVE    [9] = BUY EXTRA LIFE "
           "  [0] = DAMAGE UPGRADE            ");
  mvprintw(LINES / 2 + 10, COLS / 2 - 50,
           "                                [L] = RELOAD AMMO    [K] = PUNCH   "
           "                                  ");
  mvprintw(LINES / 2 + 11, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 12, COLS / 2 - 50,
           "                                              <Player 2>           "
           "                                  ");
  mvprintw(LINES / 2 + 13, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 14, COLS / 2 - 50,
           "          [V][B] = SHOOT    [WASD] = MOVE     [1] = BUY EXTRA LIFE "
           "  [2] = DAMAGE UPGRADE            ");
  mvprintw(LINES / 2 + 15, COLS / 2 - 50,
           "                                [R] = RELOAD AMMO    [Q] = PUNCH   "
           "                                  ");
  mvprintw(LINES / 2 + 16, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  mvprintw(LINES / 2 + 17, COLS / 2 - 50,
           "                                              menu [ESC]           "
           "                                  ");
  mvprintw(LINES / 2 + 18, COLS / 2 - 50,
           "                                                                   "
           "                                  ");
  attroff(COLOR_PAIR(2));  // CHIUSURA DEL COLORE VERDE
}

// FUNZIONE CHE GESTISCE LA LOGICA DELLA SCHERMATA DELL'HOW TO PLAY
void DrawWindow::HowToPlay(int direction) {
  direction = 0;
  while (direction != 27) {
    printHowToPlay();     // STAMPA LE HOW TO PLAY
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

// FUNZIONE CHE STAMPA A SCHERMO IL CARATTERE DEL PLAYER
void DrawWindow::printCharacter(int x, int y, char c) {
  move(y, x);
  printw("%c", c);
}

// FUNZIONE CHE STAMPA I RETTANGOLI DI DIMENSIONI DATE E GESTISCE QUANDO E SE SI DEVONO APRIRE
void DrawWindow::drawRect(
    int startX, int startY, int rightWidth, int bottomHeight, bool noEnemy,
    int maxRoom, bool isScreenBound,
    pRoom roomList) {  // isScreenBound SI UNA PER FLAGGARE CHE È
                       // IL RETTANGOLO CHE DELIMITA LO SCHERMO,
                       // QUINDI NON DEVE APRIRSI
  for (int i = startY; i < rightWidth; ++i) {
    mvprintw(startX, i, "-");
    mvprintw(bottomHeight, i, "-");
  }
  if (!noEnemy || isScreenBound) {
    for (int i = startX; i < bottomHeight; ++i) {
      mvprintw(i, startY, "|");
      mvprintw(i, rightWidth, "|");
    }
  }
  if (lengthListRoom(roomList) == 1) {
    for (int i = startX; i < bottomHeight; ++i) {
      mvprintw(i, startY, "|");
    }
  }
  mvprintw(startX, rightWidth, "o");
  mvprintw(startX, startY, "o");
  mvprintw(bottomHeight, startY, "o");
  mvprintw(bottomHeight, rightWidth, "o");
}

// FUNZIONE CHE STAMPA E GESTISCE LE STATS A SCHERMO DURANTE LA PARTITA
void DrawWindow::drawStats(int startX, int startY, int rightWidth,
                           int bottomHeight, int pointsOnScreen,
                           Character character, bool noEnemy, int powerUp,
                           int bananas, int bananasP2, int maxRoom,
                           pRoom roomList, bool isPlayer1) {
  int powerUp_y = 52;
  int powerUp_x = 23;
  int P2Offsetx = 0;
  if (!isPlayer1) {
    powerUp_y = 18;
    P2Offsetx = 34;
  }
  int statusAmmoColor = 0;

  mvprintw(startX - 2, startY + 5, "SCORE:");
  mvprintw(powerUp_x, powerUp_y, "POWER-UP");

  mvprintw(26, 52 - P2Offsetx, "MAGAZINE");
  mvprintw(26, 76 - P2Offsetx, "%d", character.getGun().getMagazineAmmo());
  mvprintw(27, 52 - P2Offsetx, "BANANA PEELS");

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
  mvprintw(27, 76 - P2Offsetx, "%d", character.getGun().getTotalAmmo());
  attroff(COLOR_PAIR(statusAmmoColor));

  mvprintw(28, 52 - P2Offsetx, "BANANAS");
  if (isPlayer1) {
    mvprintw(28, 76 - P2Offsetx, "%d", bananas);
  } else {
    mvprintw(28, 76 - P2Offsetx, "%d", bananasP2);
  }
  mvprintw(29, 52, "ROOM");
  mvprintw(29, 76, "%d/%d", lengthListRoom(roomList) - 1, maxRoom - 1);
  mvprintw(30, 52, "MAX ROOM");
  mvprintw(30, 76, "%d", maxRoom - 1);

  init_pair(11, COLOR_WHITE, 232);
  attron(COLOR_PAIR(11));
  drawRect(startX - 4, startY - 11, rightWidth + 12, bottomHeight + 12, noEnemy,
           0, true, roomList);
  drawRect(startX - 4, startY + 65, rightWidth + 40, bottomHeight + 12, noEnemy,
           0, true, roomList);
  attroff(COLOR_PAIR(11));

  if (isPlayer1) {
    mvprintw(startX - 2, startX + 47, "LIFE:");
    init_pair(3, COLOR_YELLOW, -1);  // FUNZIONI PER USARE I COLORI
    attron(COLOR_PAIR(3));
    mvprintw(startX - 2, startY + 12, "%d", pointsOnScreen);
    if (character.getNumberLife() == 3)
      mvprintw(startX - 2, startY + 38, "[C] [C] [C]");
    else if (character.getNumberLife() == 2)
      mvprintw(startX - 2, startY + 38, "[C] [C] [ ]");
    else if (character.getNumberLife() == 1)
      mvprintw(startX - 2, startY + 38, "[C] [ ] [ ]");
    attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE
  } else {
    mvprintw(30, 18, "LIFE:");
    init_pair(3, COLOR_YELLOW, -1);  // FUNZIONI PER USARE I COLORI
    attron(COLOR_PAIR(3));
    if (character.getNumberLife() == 3)
      mvprintw(30, 24, "[C] [C] [C]");
    else if (character.getNumberLife() == 2)
      mvprintw(30, 24, "[C] [C] [ ]");
    else if (character.getNumberLife() == 1)
      mvprintw(30, 24, "[C] [ ] [ ]");
    attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE
  }

  init_pair(3, COLOR_YELLOW, -1);  // FUNZIONI PER USARE I COLORI
  attron(COLOR_PAIR(3));
  if (powerUp == 4)
    mvprintw(powerUp_x, powerUp_y + 10, "[X] [X] [X] [X]");
  else if (powerUp == 3)
    mvprintw(powerUp_x, powerUp_y + 10, "[X] [X] [X] [ ]");
  else if (powerUp == 2)
    mvprintw(powerUp_x, powerUp_y + 10, "[X] [X] [ ] [ ]");
  else if (powerUp == 1)
    mvprintw(powerUp_x, powerUp_y + 10, "[X] [ ] [ ] [ ]");
  else if (powerUp == 0)
    mvprintw(powerUp_x, powerUp_y + 10, "[ ] [ ] [ ] [ ]");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE
}

// FUNZIONE CHE STAMPA (MENTRE SI GIOCA) LA CLASSIFICA RECENTE DELLE ULTIME 11 PARTITE
void DrawWindow::drawLeaderboardOnScreen() {
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

// FUNZIONE CHE STAMPA LA SCHERMATA DI GAME OVER
void DrawWindow::printLoseScreen(float finalScore) {
  int prog = LINES / 2 - 15;
  for (int y = 0; y < 20; y++) {
    init_pair(8, COLOR_BLACK, 232);
    attron(COLOR_PAIR(8));
    mvprintw(prog, COLS / 2 - 53,
             "                                                                 "
             "                                         ");
    prog++;
    attroff(COLOR_PAIR(8));
  }

  init_pair(16, COLOR_RED, 232);
  attron(COLOR_PAIR(16));
  mvprintw(LINES / 2 - 13, COLS / 2 - 26,
           "  __ _  __ _ _ __ ___   ___    _____   _____ _ __      ");
  mvprintw(LINES / 2 - 12, COLS / 2 - 26,
           " / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|");
  mvprintw(LINES / 2 - 11, COLS / 2 - 26,
           "| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |       ");
  mvprintw(LINES / 2 - 10, COLS / 2 - 26,
           " \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   ");
  mvprintw(LINES / 2 - 9, COLS / 2 - 26,
           " |___/                                                  ");
  attroff(COLOR_PAIR(16));

  init_pair(17, COLOR_GREEN, 232);
  attron(COLOR_PAIR(17));
  mvprintw(LINES / 2 - 7, COLS / 2 - 35,
           "HUNTERS HAVE TRACKED YOU, SURROUNDED AND FINALLY "
           "THEY KILLED YOU...");
  mvprintw(LINES / 2 - 5, COLS / 2 - 20,
           "YOUR LIFE GOES AWAY WITH YOUR "
           "REVENGE.");
  mvprintw(LINES / 2 - 3, COLS / 2 - 38,
           "BUT DON'T GET MAD, THERE ARE THOUSANDS OF MONKEYS "
           "READY TO REBELL AGAIN...");
  mvprintw(LINES / 2 - 2, COLS / 2 - 10, "...SOONER OR THEN...");
  mvprintw(LINES / 2 + 2, COLS / 2 - 48, "FINAL SCORE: %.0f", finalScore);
  mvprintw(LINES / 2 + 2, COLS / 2 + 24, "set score & exit [ENTER]");
  mvprintw(LINES / 2 + 3, COLS / 2 + 21, "(no name will not save score)");
  attroff(COLOR_PAIR(17));
}

// FUNZIONE CHE GESTISCE LA LOGICA DELLA SCHERMATA DI GAME OVER E L'INSERIMENTO DEL NOME PER LO SCORE
void DrawWindow::loseScreen(int direction, float finalScore) {
  direction = 32;
  char name[MAXNAMECHARACTER] = {'\0'};
  char name2[MAXNAMECHARACTER] = {'\0'};
  while (direction != 0) {
    printLoseScreen(finalScore);
    strcat(name, name2);

    init_pair(17, COLOR_GREEN, 232);
    attron(COLOR_PAIR(17));
    mvprintw(LINES / 2 + 3, COLS / 2 - 35, "__________");
    mvprintw(LINES / 2 + 3, COLS / 2 - 48, "INSERT NAME: %s", name);
    attroff(COLOR_PAIR(17));
    refresh();
    direction = getstr(name2);
  }
  saveRecord(finalScore, name);
}

// FUNZIONE CHE GENERA DELLE COORDINATE CASUALI IN UN DETERMINATO RANGE
Position DrawWindow::generateRandomPosition(int startRange, int endRange) {
  Position pos;
  pos.x = startRange + (std::rand() % (endRange - startRange + 1));
  pos.y = startRange + (std::rand() % (endRange - startRange + 1));
  while (!(mvinch(pos.y, pos.x) == ' ')) {
    pos.x = startRange + (std::rand() % (endRange - startRange) + 1);
    pos.y = startRange + (std::rand() % (endRange - startRange) + 1);
  }
  return pos;
}

// FUNZIONE CHE GESTISCE LA GENERAZIONE DELLE MONTAGNE
pPosition DrawWindow::generateMountain(pPosition mountainList,
                                       int &mountainCount) {
  int x, y;
  pPosition head = NULL;
  
  while (mountainCount > 0) {
    x = generateRandomPosition(40, 70).x;
    y = generateRandomPosition(8, 19).y;
    head = new Position;
    head->x = x;
    head->y = y;
    head->skin = '^';
    head->life = MOUNTAIN_LIFE;
    head->next = mountainList;
    mountainList = head;
    mountainCount -= 1;
  }
  return mountainList;
}

// FUNZIONE CHE GESTISCE LA GENERAZIONE DEI BONUS/MALUS
pPosition DrawWindow::generateBonus(pPosition bonusList, int &bonusCount) {
  /**
   * Genera la lista dei bonus (coordinate e skin), l'effetto di tali bonus è
   * decretato altrove.
   */
  pPosition tmpHead = NULL;
  srand(time(0));
  while (bonusCount > 0) {
    tmpHead = new Position;
    tmpHead->x = generateRandomPosition(26, 30).x;
    tmpHead->y = generateRandomPosition(11, 18).y;
    tmpHead->skin = '?';
    tmpHead->next = bonusList;
    bonusList = tmpHead;
    bonusCount -= 1;
  }
  return bonusList;
}

// FUNZIONE CHE STAMPA A SCHERMO LE MONTAGNE
void DrawWindow::printMountain(pPosition mountainList) {
  while (mountainList != NULL) {
    init_pair(15, COLOR_YELLOW, -1);
    attron(COLOR_PAIR(15));
    printCharacter(mountainList->x, mountainList->y, mountainList->skin);
    attroff(COLOR_PAIR(15));
    mountainList = mountainList->next;
  }
}

// FUNZIONE CHE STAMAPA A SCHERMO I BONUS/MALUS
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

// FUNZIONE CHE GESTISCE L'APPARIZIONE TEMPORANEA DEL BANNER CHE TI MOSTRA CHE POWER-UP HAI RACCOLTO
void DrawWindow::showBonusOnScreen(bool &upgradeBuyed, int &upgradeType,
                                   int &upgradeTime, bool &bonusPicked,
                                   int bonustype, int &bonusTime,
                                   bool &immortalityCheck, int &immortalityTime,
                                   bool multiplayer) {
  int x = 25;
  int y = 6;
  int disclaimerTimeLimit = 40;
  int immortalityTimeLimit = 120;

  if (bonusPicked == true && bonustype == 0) {
    mvprintw(y, x, "BUNCH OF BANANAS [+50]    ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 1) {
    mvprintw(y, x, "CRATE OF BANANAS [+300]   ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 2) {
    mvprintw(y, x, "SUPPLY OF BANANAS [+1000] ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 3) {
    mvprintw(y, x, "ROTTEN BANANAS [-100]     ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 4) {
    mvprintw(y, x, "BANANAS SPIDER [-10 HP]   ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 5) {
    mvprintw(y, x, "MONKEY TRAP [-30 HP]      ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 6) {
    mvprintw(y, x, "EAT 1 BANANA [+10 HP]     ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 7) {
    mvprintw(y, x, "EAT 2 BANANA [+20 HP]     ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 8) {
    mvprintw(y, x, "BANANA SMOOTHIE [+40 HP]  ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 9) {
    mvprintw(y, x, "PEEL LOADER [+20 PEELS]   ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 10) {
    mvprintw(y, x, "PEEL LOADER [+40 PEELS]   ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 11) {
    mvprintw(y, x, "PEACE MISSION [+100 PEELS]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 12) {
    mvprintw(y, x, "PISSED OF ENEMY MONKEYS   ");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 13) {
    mvprintw(y, x, "PEELS ON FIRE! [+5 DAMAGE]");
    bonusTime++;
  } else if (bonusPicked == true && bonustype == 14) {
    mvprintw(y, x, "MONKEY GOD! [IMMORTALITY] ");
    bonusTime++;
  }
  if (immortalityCheck == true) {
    init_pair(24, -1, COLOR_MAGENTA);
    attron(COLOR_PAIR(24));
    mvprintw(22, 56, "                    ");
    if (multiplayer) {
      mvprintw(22, 22, "                    ");
    }
    attroff(COLOR_PAIR(24));
    immortalityTime++;
  }

  if (bonusTime >
      disclaimerTimeLimit) {  // LASCIA IL BONUS VISIBILE PER "X" CICLI
    bonusPicked = false;
    bonusTime = 0;  // RESETTA IL TIMER PER IL PROSSIMO BONUS UNA VOLTA SCADUTO
  }

  if (upgradeBuyed == true && upgradeType == 0) {
    mvprintw(y, x + 29, "MORE LIFE!     ");
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

// FUNZIONE CHE CONTA QUANTI NEMICI SONO PRESENTI NELLA LORO LISTA
int DrawWindow::lengthEnemyList(pEnemyList enemyList) {
  int i;
  if (enemyList == NULL) {
    i = 0;
  } else {
    i = -1;
  }
  while (enemyList != NULL) {
    i++;
    enemyList = enemyList->next;
  }
  return i;
}

// FUNZIONE CHE CONTA A CHE STANZA È IL PLAYER
int DrawWindow::lengthListRoom(pRoom roomList) {
  int i = 0;
  while (roomList != NULL) {
    i++;
    roomList = roomList->next;
  }
  return i;
}

// FUNZIONE CHE STAMPA A SCHERMO IL NUMERO E LA LISTA DEI NEMICI RIMASTI NELLA MAPPA
void DrawWindow::printEnemyLeftList(pEnemyList enemyList,
                                    pEnemyList specialEnemyList,
                                    pEnemyList bossEnemyList) {
  int enemyLeftOnScreen = lengthEnemyList(enemyList) +
                          lengthEnemyList(specialEnemyList) +
                          lengthEnemyList(bossEnemyList);

  int i = 22;
  int reachBound = 0;
  int X_ElencoNemici = 19;

  if (enemyLeftOnScreen > 0) {
    mvprintw(i, X_ElencoNemici, "Enemy left: %d", enemyLeftOnScreen);
  } else {
    mvprintw(i, X_ElencoNemici, "[ALL ENEMY DEFEATED!]");
  }

  // PARTE RISERVATA AI NEMICI NORMALI
  while (enemyList != NULL && reachBound < 8) {
    if (enemyList->enemy.getX() != 0) {
      i++;
      mvprintw(i, X_ElencoNemici, "- UN soldier: %d HP",
               enemyList->enemy.getLife());
    }
    reachBound++;
    enemyList = enemyList->next;
  }

  // PARTE RISERVATA AI NEMICI SPECIALI
  while (specialEnemyList != NULL && reachBound < 8) {
    if (specialEnemyList->enemy.getX() != 0) {
      i++;
      mvprintw(i, X_ElencoNemici, "- Elite soldier: %d HP",
               specialEnemyList->enemy.getLife());
    }
    reachBound++;
    specialEnemyList = specialEnemyList->next;
  }

  // PARTE RISERVATA AI BOSS
  while (bossEnemyList != NULL && reachBound < 8) {
    if (bossEnemyList->enemy.getX() != 0) {
      i++;
      mvprintw(i, X_ElencoNemici, "- BOSS: %d HP",
               bossEnemyList->enemy.getLife());
    }
    reachBound++;
    bossEnemyList = bossEnemyList->next;
  }
}

// FUNZIONE CHE STAMPA E GESTISCE LE STATS A SCHERMO DURANTE LA PARTITA
void DrawWindow::printCharacterStats(Character character, bool isPlayer1) {
  int i = 22;
  int BarStart;
  if (isPlayer1) {
    BarStart = 56;
  } else {
    BarStart = 22;
  }     
  int AddBar = BarStart;
  int healtColorPair = 0;

  // GESTISCE L'APPARIZIONE DEI BANNER RIGUARDANTI LE MUNIZIONI
  if (character.getGun().getTotalAmmo() == 0 &&
      character.getGun().getMagazineAmmo() == 0) {
    init_pair(25, COLOR_RED, -1);
    attron(COLOR_PAIR(25));
    mvprintw(25, BarStart - 4, "OUT OF AMMO!");
    attroff(COLOR_PAIR(25));
  } else if (character.getGun().getMagazineAmmo() == 0) {
    init_pair(25, COLOR_RED, -1);
    attron(COLOR_PAIR(25));
    if (isPlayer1) {
      mvprintw(25, BarStart - 4, "PRESS [L] TO RELOAD!");
    } else {
      mvprintw(25, BarStart - 4, "PRESS [R] TO RELOAD!");
    }
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

  // ------------------------------------------------------------------------------------------
  // FINE CODICE BARRA DELLA VITA
}

// FUNZIONE CHE STAMPA A SCHERMO I NEMICI PRESENTI NELLA LISTA DATA
void DrawWindow::printEnemy(pEnemyList enemyList, DrawWindow drawWindow) {
  while (enemyList != NULL) {
    drawWindow.printCharacter(enemyList->enemy.getX(), enemyList->enemy.getY(),
                              enemyList->enemy.getSkin());
    enemyList = enemyList->next;
  }
}

// FUNZIONE CHE GESTISCE I MOVIMENTI DEI NEMICI NELLA MODALITÀ MULTIPLAYER
void DrawWindow::moveEnemyMultiplayer(pEnemyList enemyList, Character character,
                                      Character character2,
                                      DrawWindow drawWindow, long points) {
  int yP = character.getY(), xE, yE;
  int yP2 = character2.getY();
  srand(time(0));
  int movementSpeedFactor = 1;

  while (enemyList != NULL) {
    if (enemyList->enemy.getSkin() == 'e')
      movementSpeedFactor = rand() % 10 + 15;
    else if (enemyList->enemy.getSkin() == 'E')
      movementSpeedFactor = rand() % 10 + 20;
    else if (enemyList->enemy.getSkin() == 'B')
      movementSpeedFactor = rand() % 10 + 30;

    if (points % movementSpeedFactor == 0) {
      xE = enemyList->enemy.getX(), yE = enemyList->enemy.getY();
      if ((yP > yE || yP2 > yE) &&
          (mvinch(yE + 1, xE) == ' ' || mvinch(yE + 1, xE) == '?')) {
        enemyList->enemy.setY(yE + 1);
        drawWindow.printCharacter(xE, yE, enemyList->enemy.getSkin());
      } else if ((yP < yE || yP2 < yE) &&
                 (mvinch(yE - 1, xE) == ' ' || mvinch(yE - 1, xE) == '?')) {
        enemyList->enemy.setY(yE - 1);
        drawWindow.printCharacter(xE, yE, enemyList->enemy.getSkin());
      }
    }
    enemyList = enemyList->next;
  }
}

// FUNZIONE CHE GESTISCE I MOVIMENTI DEI NEMICI NELLA MODALITÀ SINGLEPLAYER
void DrawWindow::moveEnemySinglePlayer(pEnemyList enemyList,
                                       Character character,
                                       DrawWindow drawWindow, long points) {
  int yP = character.getY(), xE, yE;
  srand(time(0));
  int movementSpeedFactor = 1;

  while (enemyList != NULL) {
    // Più è alto il valore aggiunto e più lento sarà il nemico
    if (enemyList->enemy.getSkin() == 'e')
      movementSpeedFactor = rand() % 10 + 15;
    else if (enemyList->enemy.getSkin() == 'E')
      movementSpeedFactor = rand() % 10 + 20;
    else if (enemyList->enemy.getSkin() == 'B')
      movementSpeedFactor = rand() % 10 + 30;

    if (points % movementSpeedFactor == 0) {
      xE = enemyList->enemy.getX(), yE = enemyList->enemy.getY();
      if ((yP > yE) &&
          (mvinch(yE + 1, xE) == ' ' || mvinch(yE + 1, xE) == '?')) {
        enemyList->enemy.setY(yE + 1);
        drawWindow.printCharacter(xE, yE, enemyList->enemy.getSkin());
      } else if ((yP < yE) &&
                 (mvinch(yE - 1, xE) == ' ' || mvinch(yE - 1, xE) == '?')) {
        enemyList->enemy.setY(yE - 1);
        drawWindow.printCharacter(xE, yE, enemyList->enemy.getSkin());
      }
    }
    enemyList = enemyList->next;
  }
}

// FUNZIONE CHE SALVA LO STATO DI UNA STANZA
pRoom DrawWindow::saveRoom(pPosition mountainList, pPosition bonusList,
                           pRoom roomList) {
  pRoom head = new Room;
  head->mountainList = mountainList;
  head->bonusList = bonusList;
  head->next = roomList;
  roomList->prev = head;
  roomList = head;
  return roomList;
}

// FUNZIONE CHE GESTISCE LO SPOSTAMENTO E LA GENERAZIONE DEGLI ELEMENTI NELLA NUOVA STANZA
pRoom DrawWindow::changeRoom(Character &character, Character &character2,
                             int &normalEnemyCount, int &specialEnemyCount,
                             int &bossEnemyCount, pEnemyList &normalEnemyList,
                             pEnemyList &specialEnemyList,
                             pEnemyList &bossEnemyList, pPosition &mountainList,
                             pPosition &bonusList, pRoom roomList, int &maxRoom,
                             bool multiplayer) {
  if (character.getX() >= GAMEWIDTH || character2.getX() >= GAMEWIDTH) {
    // Questo if si "attiva" quando torni nella stanza precedente e poi ritorni
    // nella successiva
    if (maxRoom > lengthListRoom(roomList)) {
      roomList = roomList->prev;
      character.setX(23);
      character2.setX(24);
    } else if (maxRoom == lengthListRoom(roomList)) {
      character.setX(23);
      character2.setX(24);
      int mountainCount = rand() % 8 + 1, bonusCounter = 1;
      if (maxRoom < 2)
        bonusCounter = 0;
      else {
        srand(time(0));
        bonusCounter = rand() % 3 + 1;
      }
      roomList->mountainList = generateMountain(mountainList, mountainCount);
      roomList->bonusList = generateBonus(bonusList, bonusCounter);
      roomList = saveRoom(mountainList, bonusList, roomList);

      // Si assegna i valori alle variaibli che rappresentano i nemici da
      // generare
      howMuchEnemies(maxRoom, multiplayer, normalEnemyCount, specialEnemyCount,
                     bossEnemyCount);
      normalEnemyList = normalEnemyList->next;
      if (maxRoom % SPECIAL_ENEMY_FREQUENCY == 0)
        specialEnemyList = specialEnemyList->next;
      if (maxRoom % BOSS_ENEMY_FREQUENCY == 0)
        bossEnemyList = bossEnemyList->next;
      maxRoom += 1;
    }
  } else if (character.getX() == 22 || character2.getX() == 22) {
    character.setX(GAMEWIDTH - 1);
    character2.setX(GAMEWIDTH - 1);
    roomList = roomList->next;
  }
  return roomList;
}

// FUNZIONE CHE GESTISCE SE E QUANTI NEMICI GENERARE
void DrawWindow::howMuchEnemies(int maxRoom, bool multiplayer,
                                int &normalEnemyCount, int &specialEnemyCount,
                                int &bossEnemyCount) {
  if (maxRoom <= NORMAL_ENEMY_LIMIT) {
    normalEnemyCount = maxRoom + 1;
    if (multiplayer) normalEnemyCount += 2;
  } else {
    normalEnemyCount = NORMAL_ENEMY_LIMIT;

    if (multiplayer) normalEnemyCount += 4;
  }

  if (maxRoom % SPECIAL_ENEMY_FREQUENCY == 0) {
    if (maxRoom < 10)
      specialEnemyCount = 2;
    else if (maxRoom >= 10 && maxRoom < 15)
      specialEnemyCount = 3;
    else if (maxRoom >= 15)
      specialEnemyCount = 4;
    else
      specialEnemyCount = 0;

    if (multiplayer && specialEnemyCount != 0) specialEnemyCount += 1;
  }

  if (maxRoom % BOSS_ENEMY_FREQUENCY == 0) {
    if (maxRoom <= 10)
      bossEnemyCount = 1;
    else if (maxRoom > 10)
      bossEnemyCount = 2;
    else
      bossEnemyCount = 0;

    if (multiplayer && bossEnemyCount != 0) bossEnemyCount += 1;
  }
}

// FUNZIONE CHE STAMPA LA SPLASHSCREEN APPENA SI AVVIA LA PARTITA
void DrawWindow::printSplashScreen() {
  int prog = LINES / 2 - 15;
  for (int y = 0; y < 20; y++) {
    init_pair(8, COLOR_BLACK, 232);
    attron(COLOR_PAIR(8));
    mvprintw(prog, COLS / 2 - 53,
             "                                                                 "
             "                                         ");
    prog++;
    attroff(COLOR_PAIR(8));
  }

  init_pair(3, COLOR_YELLOW, 232);
  attron(COLOR_PAIR(3));
  mvprintw(
      LINES / 2 - 13, COLS / 2 - 34,
      "THE FORCES OF THE UNITED NATIONS MADE THEIR WAY TO THE HEADQUARTERS.");
  mvprintw(LINES / 2 - 12, COLS / 2 - 30,
           "TO PROTECT THE OTHER MONKEYS AND NOT STOP THE MONKEY ADVANCE,");
  mvprintw(LINES / 2 - 11, COLS / 2 - 16, "THERE IS ONLY ONE THING TO DO...");
  mvprintw(LINES / 2 + 1, COLS / 2 - 11, "Press [SPACE] to start!");
  attroff(COLOR_PAIR(3));

  init_pair(1, COLOR_RED, 232);
  attron(COLOR_PAIR(1));
  mvprintw(LINES / 2 - 9, COLS / 2 - 26,
           " _______  __    _______  __    __  .___________. __  ");
  mvprintw(LINES / 2 - 8, COLS / 2 - 26,
           "|   ____||  |  /  _____||  |  |  | |           ||  | ");
  mvprintw(LINES / 2 - 7, COLS / 2 - 26,
           "|  |__   |  | |  |  __  |  |__|  | `---|  |----`|  | ");
  mvprintw(LINES / 2 - 6, COLS / 2 - 26,
           "|   __|  |  | |  | |_ | |   __   |     |  |     |  | ");
  mvprintw(LINES / 2 - 5, COLS / 2 - 26,
           "|  |     |  | |  |__| | |  |  |  |     |  |     |__| ");
  mvprintw(LINES / 2 - 4, COLS / 2 - 26,
           "|__|     |__|  \\______| |__|  |__|     |__|     (__) ");
  attroff(COLOR_PAIR(1));

  init_pair(4, COLOR_WHITE, 232);
  attron(COLOR_PAIR(4));
  mvprintw(LINES / 2 + 1, COLS / 2 - 11, "Press [SPACE] to start!");
  attroff(COLOR_PAIR(4));
}

// FUNZIONE CHE GESTISCE LA LOGICA DELLA SPLASHSCREEN
void DrawWindow::splashScreen(int direction) {
  direction = 0;
  while (direction != 32) {
    printSplashScreen();
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

// FUNZIONE CHE SI ACCERTA CHE IL NOME RISPETTI GLI STANDARD DI VALIDITÀ
bool DrawWindow::ghostNameRecognizer(char name[]) {
  bool GhostName = true;
  int i = 0;
  for (i = 0; i < MAXNAMECHARACTER; i++) {
    GhostName = GhostName && ((name[i] == ' ') || (name[i] == '\0'));
  }
  return GhostName;
}

// FUNZIONE CHE GESTISCE IL SALVATAGGIO DELLO SCORE SUL FILE TXT
void DrawWindow::saveRecord(float finalScore, char name[]) {
  bool ghostName = ghostNameRecognizer(name);
  int nameLen = strlen(name);
  int nameMax = 12;
  std::fstream board;
  board.open("leaderBoard.txt", std::ios::app);
  if ((board) && (finalScore > 0) &&
      (!ghostName)) {  // lo score è salvato solo se maggiore di 0 e il nome non
                       // è vuoto o solo spazi
    board << name << ":";
    while (nameLen < nameMax) {
      board << " ";
      nameLen++;
    }
    board << finalScore << "\n";
  }
  board.close();
}


