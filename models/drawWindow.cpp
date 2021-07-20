#include "drawWindow.hpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <ncurses.h>

#define FRAMEGAMEX 7
#define FRAMEGAMEY 22
#define GAMEWIDTH 71   // 49
#define GAMEHEIGTH 20  // 13

DrawWindow::DrawWindow() {}

/*
  I COLORI HANNO ID:
  - ROSSO = 1
  - VERDE = 2
  - GIALLO = 3
*/

void DrawWindow::drawMenu() {
  init_pair(1, COLOR_RED, 232);  // 1 INDICA UN ID, POI METTI IL COLORE CHE VUOI
  attron(COLOR_PAIR(1));         // APRTURA COLORE ROSSO
  mvprintw(1, 0,
           "                                                                   "
           "                                         ");
  mvprintw(2, 0,
           "    b    d  P*Y  8b 8 8  d 88888 Yb  dP        A   8**Y  P*Y   "
           "P**b8   b    8     Yb  dP 8**Y .P*Y8 88888   ");
  mvprintw(3, 0,
           "    8b  d8 P   Y 8Yb8 8od  8__    YbdP        PY   8__P P   Y P   "
           "`*   PY   8      YbdP  8__P `Yo.* 8__     ");
  mvprintw(4, 0,
           "    8Yb P8 b   d 8 Y8 8*Y  8**     8P        P__Y  8**  b   P Y    "
           "   P__Y  8  .o   8P   8**  o.`Y8 8**     ");
  mvprintw(5, 0,
           "    8 Y  8  Ybo  8  Y 8  Y 88888  dP        P****Y 8     P*Y   "
           "YoodP P****Y 8ood8  dP    8     8oP* 88888   ");
  mvprintw(6, 0,
           "                                                                   "
           "                                         ");
  mvprintw(7, 0,
           "     THE REVENGE OF THE MONKEYS HAS JUST BEGUN!                    "
           "                                         ");
  mvprintw(8, 0,
           "                                                                   "
           "                                         ");
  attroff(COLOR_PAIR(1));  // CHIUSURA DEL COLORE ROSSO E NERO
}

void DrawWindow::printCommand(int *cnt) {
  if (*cnt == 0)
    mvprintw(12, 5, "==>  (X) START THE FIGHT!");
  else
    mvprintw(12, 5, "     START THE FIGHT!    ");
  if (*cnt == 1)
    mvprintw(14, 5, "==>  (X) HOW TO PLAY");
  else
    mvprintw(14, 5, "     HOW TO PLAY    ");
  if (*cnt == 2)
    mvprintw(16, 5, "==>  (X) CREDITS");
  else
    mvprintw(16, 5, "     CREDITS      ");  // MUOVO CON LE FRECCE
  if (*cnt == 3)
    mvprintw(18, 5, "==>  (X) QUIT");
  else
    mvprintw(18, 5, "     QUIT     ");
  mvprintw(20, 5, "Press space to continue or use the arrow to move.");
}

void DrawWindow::printCredits() {
  init_pair(3, COLOR_YELLOW, 232);  // FUNZIONI PER USARE IL COLORE GIALLO
  attron(COLOR_PAIR(3));
  mvprintw(10, 3,
           "                              ___ ___ ___ ___ ___ _____   _____ "
           "___                                   ");
  mvprintw(11, 3,
           "                             / __| _ \\ __|   \\_ _|_   _| |_   _/ "
           "_ \\                                  ");
  mvprintw(12, 3,
           "                            | (__|   / _|| |) | |  | |     | || "
           "(_) |                                 ");
  mvprintw(13, 3,
           "                             \\___|_|_\\___|___/___| |_|     |_| "
           "\\___/                                  ");
  attroff(COLOR_PAIR(3));

  init_pair(2, COLOR_GREEN, 232);  // FUNZIONI PER USARE I COLORI VEDI MENU.CPP
  attron(COLOR_PAIR(2));
  mvprintw(14, 3,
           "                                                                   "
           "                                   ");
  mvprintw(15, 3,
           "                                                                   "
           "                                   ");
  mvprintw(16, 3,
           "        ____ ____ _ _  _              ____ _  _ ____               "
           "  ___  ____ ___  ___  ____         ");
  mvprintw(17, 3,
           "        |___ |__/ | |_/               |___ |\\/| |__|              "
           "   |__] |___ |__] |__] |___         ");
  mvprintw(18, 3,
           "        |___ |  \\ | | \\_              |___ |  | |  |             "
           "    |__] |___ |    |    |___         ");
  mvprintw(19, 3,
           "                                                                   "
           "                                   ");
  mvprintw(20, 3,
           "                                                                   "
           "                                   ");
  attroff(COLOR_PAIR(2));  // CHIUSURA DEL COLORE ROSSO E BLU
}
void DrawWindow::credits(int direction) {
  while (direction != 27) {
    drawMenu();           // STAMPA IL TITOLO FINO A CHE NON SI SPINGE ESC
    printCredits();       // STAMPA GLI AUTORI DEL GIOCO
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

void DrawWindow::printHowToPlay() {  // GESTISCE LA SCHERMATA DEL HOW TO PLAY
  init_pair(3, COLOR_YELLOW, 232);   // FUNZIONI PER USARE IL COLORE GIALLO
  attron(COLOR_PAIR(3));
  mvprintw(10, 3,
           "                     _____ _____ _ _ _    _____ _____    _____ __  "
           "  _____ __ __                     ");
  mvprintw(11, 3,
           "                    |  |  |     | | | |  |_   _|     |  |  _  |  | "
           " |  _  |  |  |                    ");
  mvprintw(12, 3,
           "                    |     |  |  | | | |    | | |  |  |  |   __|  "
           "|__|     |_   _|                    ");
  mvprintw(13, 3,
           "                    |__|__|_____|_____|    |_| |_____|  |__|  "
           "|_____|__|__| |_|                      ");
  mvprintw(14, 3,
           "                                                                   "
           "                                  ");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE GIALLO

  init_pair(2, COLOR_GREEN, 232);  // FUNZIONI PER USARE IL VERDE
  attron(COLOR_PAIR(2));
  mvprintw(15, 3,
           "        PLAY THIS ADVENTURE FROM THE POINT OF VIEW OF THE MONKEY "
           "THAT STARTED THE REVOLUTION!        ");
  mvprintw(16, 3,
           "                                                                   "
           "                                  ");
  mvprintw(17, 3,
           "                       USE THE ARROWS TO MOVE AND 'E' TO USE THE "
           "BANANACANNON.                       ");
  mvprintw(18, 3,
           "          ELIMINATE THE ENEMIES, CLEAN THE ROOM, MOVE TO THE NEXT "
           "ONE AND COLLECT BANANAS!           ");
  mvprintw(19, 3,
           "                                                                   "
           "                                  ");
  mvprintw(20, 3,
           "                                  solo dio sa cosa metteremo "
           "dopo...                                 ");
  attroff(COLOR_PAIR(2));  // CHIUSURA DEL COLORE VERDE
}
void DrawWindow::HowToPlay(int direction) {
  while (direction != 27) {
    drawMenu();           // STAMPA IL TITOLO FINO A CHE NON SI SPINGE ESC
    printHowToPlay();     // STAMPA LE HOW TO PLAY
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

void DrawWindow::printCharacter(int x, int y, char c) {
  move(y, x);
  printw("%c", c);
}

void DrawWindow::drawRect(int startX, int startY, int width, int heigth,
                          pEnemyList enemyList) {
  for (int i = startY; i < width; ++i) {
    mvprintw(startX, i, "-");
    mvprintw(heigth, i, "-");
  }
  if (enemyList->next != NULL) {
    for (int i = startX; i < heigth; ++i) {
      mvprintw(i, startY, "|");
      mvprintw(i, width, "|");
    }
  }
  mvprintw(startX, width, "o");
  mvprintw(startX, startY, "o");
  mvprintw(heigth, startY, "o");
  mvprintw(heigth, width, "o");
}

void DrawWindow::drawStats(int startX, int startY, int width, int heigth,
                           long *points, Character character,
                           pEnemyList enemyList) {
  init_pair(3, COLOR_YELLOW, 232);  // FUNZIONI PER USARE I COLORI
  attron(COLOR_PAIR(3));
  drawRect(startX - 4, startY - 11, width + 13, heigth + 4, enemyList);
  mvprintw(startX - 2, startY + 5, "SCORE: %lu", *points);
  if (character.getNumberLife() == 3)
    mvprintw(startX - 2, startX + 50, "LIFE: c-c-c");
  if (character.getNumberLife() == 2)
    mvprintw(startX - 2, startX + 50, "LIFE: c-c");
  if (character.getNumberLife() == 1)
    mvprintw(startX - 2, startX + 50, "LIFE: c");
  attroff(COLOR_PAIR(3));  // CHIUSURA DEL COLORE
}


Position DrawWindow::randomPosition(int startRange, int endRange) {
  Position pos;
  pos.x = startRange + (std::rand() % (endRange - startRange + 1));
  pos.y = startRange + (std::rand() % (endRange - startRange + 1));
  while (!(mvinch(pos.y, pos.x) == ' ')) {
    pos.x = startRange + (std::rand() % (endRange - startRange + 1));
    pos.y = startRange + (std::rand() % (endRange - startRange + 1));
  }
  return pos;
}

void DrawWindow::drawMountain(){
  
}


int DrawWindow::lenghtList(pEnemyList list) {
  int i = -1;
  while (list != NULL) {
    i++;
    list = list->next;
  }
  return i;
}

void DrawWindow::printCharacterStats(pEnemyList list, Character character) {
  int i = 22;
  int X_ElencoNemici = 24;  // gestisce la x da dove inizia la lista dei nemici
  int volt = 0;
  int cont = 0;
  int BarStart = 58;      // gestisce dove partono gli oggetti della barra
  int AddBar = BarStart;  // cicla per aggiungere un cordinata
  int healtColorPair;

  if (lenghtList(list) > 0) {
    mvprintw(i, X_ElencoNemici, "Enemy left: %d", lenghtList(list));
  } else {
    mvprintw(i, X_ElencoNemici, "[ALL ENEMY DEFEATED!]");
  }
  

  // CODICE CHE GESTISCE LA BARRA DELLA VITA ------------------------------------------------------------------------------

  mvprintw(i, BarStart - 4, "HP");                                 // MOSTRA LA SCRITTA HP PRIMA DELLA BARRA

  if(character.getLife() > 60) {                                   // GESTISCE IL COLORE DELLA BARRA TRA 100 E 61
    healtColorPair = 2;
    init_pair(healtColorPair, COLOR_GREEN, 232);
    attron(COLOR_PAIR(healtColorPair));
  }
  if (character.getLife() >= 25 && character.getLife() <= 60) {    // GESTISCE IL COLORE DELLA BARRA TRA 50 E 25
    healtColorPair = 3;
    init_pair(healtColorPair, COLOR_YELLOW, 232);
    attron(COLOR_PAIR(healtColorPair));
  }
  if (character.getLife() < 25) {                                  // GESTISCE IL COLORE DELLA BARRA TRA 24 E 0
    healtColorPair = 1;
    init_pair(healtColorPair, COLOR_RED, 232);
    attron(COLOR_PAIR(healtColorPair));
  }

  mvprintw(i, BarStart, "          ");                             // SFONDO NERO BARRA
  for (cont = 0; volt <= (character.getLife() - 1) / 10; volt++) { // GENERA IL SIMBOLO "=" OGNI DIECI UNITÀ DI VITA 
    mvprintw(i, AddBar, "=");
    AddBar++;
  }
  attroff(COLOR_PAIR(healtColorPair));                             
  mvprintw(i, BarStart - 1, "[");                                  // GERERA I CARATTERI PER IL CONTENITORE DELLA VITA 
  mvprintw(i, BarStart + 10, "]");

  // FINE CODICE BARRA DELLA VITA ------------------------------------------------------------------------------------------

  while (list != NULL) {
    if (list->enemy.getX() != 0) {
      mvprintw(i, X_ElencoNemici, "- Base Enemy: %d HP", list->enemy.getLife());
    }
    i++;
    list = list->next;
  }
}

void DrawWindow::printEnemy(pEnemyList list, DrawWindow drawWindow) {
  while (list != NULL) {
    drawWindow.printCharacter(list->enemy.getX(), list->enemy.getY(),
                              list->enemy.getCharacter());
    list = list->next;
  }
}

void DrawWindow::moveEnemy(pEnemyList list, Character character,
                           DrawWindow drawWindow, long points) {
  while (list != NULL) {
    if (points % 40 == 0) {
      if (character.getY() > list->enemy.getY() && mvinch(list->enemy.getY() + 1, list->enemy.getX()) == ' ') {
        list->enemy.setY(list->enemy.getY() + 1);
        drawWindow.printCharacter(list->enemy.getX(), list->enemy.getY(),
                                  list->enemy.getCharacter());
      } else if (character.getY() < list->enemy.getY() && mvinch(list->enemy.getY() - 1, list->enemy.getX()) == ' ') {
        list->enemy.setY(list->enemy.getY() - 1);
        drawWindow.printCharacter(list->enemy.getX(), list->enemy.getY(),
                                  list->enemy.getCharacter());
      }
    }
    list = list->next;
  }
}

void DrawWindow::changeRoom(Character &character, int &monsterCount, int &round,
                            pEnemyList &list) {
  if (character.getX() == 71) {
    character.setX(23);
    monsterCount = round;
    list = list->next;
  }
}