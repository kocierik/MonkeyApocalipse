#include "models/drawWindow.hpp"
#include "models/player.hpp"
#include "models/engineGame.hpp"
#define FRAMEGAMEX 3
#define FRAMEGAMEY 3
#define GAMEWIDTH 50
#define GAMEHEIGTH 14
int main(){
    EngineGame game(FRAMEGAMEX, FRAMEGAMEY, GAMEHEIGTH, GAMEWIDTH);
    Player character(10,10);
    DrawWindow drawWindow;
    game.engine(character, drawWindow);
    return 0;
}