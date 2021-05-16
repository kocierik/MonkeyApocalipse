struct Bullet {
  int x;
  int y;
  float speed;
  Bullet* next;
};
typedef Bullet* Pbullet;

class Character {
 protected:
  int direction;  // Input da tastiera per il movimento del characte;r
  int x;
  int y;
  bool isEnemy;
  char character;
  int life;
  int Nbullet;
  Pbullet bullet;

 public:
  Character(int x, int y, char character);
  int getX();
  int getY();
  int getBullet();
  char getCharacter();
  void bulletUp();
  void directionUp();
  void directionDown();
  void directionRight();
  void directionLeft();
};
