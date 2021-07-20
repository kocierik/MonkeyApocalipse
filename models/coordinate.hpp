struct Position {
  int x;
  int y;
  char skin;
  Position* next;
};
typedef Position* pPosition;

class Coordinate {
 protected:
  Position point;

 public:
  Coordinate();
  Coordinate(Position point);
  void setPosition(Position point);
  char getCharacter();
  Position getPosition();
};