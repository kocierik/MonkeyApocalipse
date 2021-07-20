struct Position {
  int x;
  int y;
  char character;
  Position* next;
};
typedef Position* pPosition;

class Coordinate {
 protected:
  Position point;

 public:
  Coordinate(Position point);
  void setPosition(Position point);
  char getCharacter();
  Position getPosition();
};