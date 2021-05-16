#include "drawWindow.hpp"

#include <ncurses.h>

DrawWindow::DrawWindow() {}

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

void DrawWindow::printCommand(int* cnt) {
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
  init_pair(2, COLOR_BLUE, 232);  // FUNZIONI PER USARE I COLORI VEDI MENU.CPP
  attron(COLOR_PAIR(2));
  mvprintw(10, 3,
           "                                                                   "
           "                                    ");
  mvprintw(11, 3,
           "        ____ ____ _ _  _              ____ _  _ ____               "
           "  ___  ____ ___  ___  ____          ");
  mvprintw(12, 3,
           "        |___ |__/ | |_/               |___ |\\/| |__|              "
           "   |__] |___ |__] |__] |___          ");
  mvprintw(13, 3,
           "        |___ |  \\ | | \\_              |___ |  | |  |             "
           "    |__] |___ |    |    |___          ");
  mvprintw(14, 3,
           "                                                                   "
           "                                    ");
  mvprintw(15, 3,
           "                                                                   "
           "                                    ");
  attroff(COLOR_PAIR(2));  // CHIUSURA DEL COLORE ROSSO E BLU
}
void DrawWindow::credits(int direction) {
  while (direction != 27) {
    drawMenu();           // STAMPA IL TITOLO FINO A CHE NON SI SPINGE ESC
    printCredits();       // STAMPA GLI AUTORI DEL GIOCO
    direction = getch();  // ASPETTA UN TASTO IN INPUT
  }
}

void DrawWindow::printCharacter(int x, int y, char c) {
  move(y, x);
  printw("%c", c);
}

void DrawWindow::drawRect(int startX, int startY, int width, int heigth) {
  for (int i = startY; i < width; ++i) {
    mvprintw(startX, i, "-");
    mvprintw(heigth, i, "-");
  }
  for (int i = startX; i < heigth; ++i) {
    mvprintw(i, startY, "|");
    mvprintw(i, width, "|");
  }
  mvprintw(startX, width, "o");
  mvprintw(startX, startY, "o");
  mvprintw(heigth, startX + 15, "o");
  mvprintw(heigth, width, "o");
}

void DrawWindow::drawStats(int startX, int startY, int width, int heigth, long *points) {
  init_pair(2, COLOR_BLUE, 232);  // FUNZIONI PER USARE I COLORI
  attron(COLOR_PAIR(2));
  drawRect(startX - 4, startY - 10, width + 13, heigth + 4);
  mvprintw(startX - 2, startY + 5, "SCORE: %lu",*points);

  mvprintw(heigth + 2, startX + 18, "LIFE: c-c-c");
  attroff(COLOR_PAIR(2));  // CHIUSURA DEL COLORE ROSSO E BLU
}
