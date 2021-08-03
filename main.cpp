#include "models/drawWindow.hpp"
#include "models/player.hpp"
#include "models/engineGame.hpp"
#define FRAMEGAMEX 7
#define FRAMEGAMEY 22
#define GAMEWIDTH 71   // 49
#define GAMEHEIGTH 20  // 13
int main() {
  Gun basicPlayerGun ('~', 25, 100);
  EngineGame game(FRAMEGAMEX, FRAMEGAMEY, GAMEHEIGTH, GAMEWIDTH);
  Player character(FRAMEGAMEY + 5, FRAMEGAMEX + 5,'C', 100, 3, basicPlayerGun);
  DrawWindow drawWindow;
  game.engine(character, drawWindow);
  return 0;
}