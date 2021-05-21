#define CHARACTER

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
  void setX(int x);
  int getX();
  void setY(int y);
  int getY();
  int getBullet();
  char getCharacter();
  void setCharacter(char character);
  void setDamage(int damage);
  int getDamage();
  void setLife(int life);
  int getLife();
  void bulletUp();
  void directionUp();
  void directionDown();
  void directionRight();
  void directionLeft();
};
