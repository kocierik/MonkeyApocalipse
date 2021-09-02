#include "models/drawWindow.hpp"
#include "models/engineGame.hpp"

#define FRAMEGAMEX 7
#define FRAMEGAMEY 22

#define LIMIT_TOP 7       // Limite superiore della mappa
#define LIMIT_BOTTOM 20   // Limite inferiore della mappa
#define LIMIT_RIGHT 71    // Limite dx della mappa
#define LIMIT_LEFT 22     // Limite sx della mappa

int main() {
  EngineGame game(FRAMEGAMEX, FRAMEGAMEY, LIMIT_TOP, LIMIT_BOTTOM, LIMIT_LEFT, LIMIT_RIGHT);
  DrawWindow drawWindow;
  game.engine(drawWindow);
  return 0;
}