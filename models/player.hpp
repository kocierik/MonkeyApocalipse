#ifndef CHARACTER
#define CHARACTER
#include "character.hpp"
#endif
class Player : public Character {
 public:
  Player(int x, int y, char skin, int life, int numberLife, Gun gun);
  Player(int x, int y, char skin, int life, int numberLife);
};
