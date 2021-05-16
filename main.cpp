#include "models/drawWindow.hpp"
#include "models/player.hpp"
#include "models/engineGame.hpp"
#define FRAMEGAMEX 7
#define FRAMEGAMEY 22
#define GAMEWIDTH 71   // 49
#define GAMEHEIGTH 20  // 13
int main() {
  EngineGame game(FRAMEGAMEX, FRAMEGAMEY, GAMEHEIGTH, GAMEWIDTH);
  Player character(FRAMEGAMEY + 5, FRAMEGAMEX + 5);
  DrawWindow drawWindow;
  game.engine(character, drawWindow);
  return 0;
}
