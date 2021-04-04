#include "character.hpp"
class Player : public Character {
 protected:
  int x;
  int y;

 public:
  Player(int x, int y);
};