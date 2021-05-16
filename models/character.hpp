struct Bullet {
  int x;
  int y;
  float speed;
  Bullet* next;
};
typedef Bullet* Pbullet;

class Character {
 protected:
  int direction;  // Input da tastiera per il movimento del character
  int x;
  int y;
  bool isEnemy;
  char character;
  int life;
  int Nbullet;
  int damage;
  Pbullet bullet;

 public:
  Character(int x, int y, char character, int damage, int life);
  int getX();
  int getY();
  int getBullet();
  char getCharacter();
  int getDamage();
  int getLife();
  void bulletUp();
  void directionUp();
  void directionDown();
  void directionRight();
  void directionLeft();
};
