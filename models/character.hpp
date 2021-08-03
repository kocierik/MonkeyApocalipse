#define CHARACTER

#include "gun.hpp"

struct Bullet {
  int x;
  int y;
  char skin;
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
  char skin;
  int life;
  int numberLife;
  int Nbullet;
  Gun gun;
  Pbullet bullet;

 public:
  Character(int x, int y, char skin, int life, int numberLife, Gun gun);
  // Character(int x, int y, char skin, int life, int numberLife);
  Character();
  void setX(int x);
  int getX();
  void setY(int y);
  int getY();
  int getBullet();
  int getNumberLife();
  void setNumberLife(int numberLife);
  char getSkin();
  void setSkin(char skin);
  void setDamage(int damage);
  int getDamage();
  void increaseLife(int life);
  void decreaseLife(int life);
  int getLife();
  void setLife(int life);
  void bulletUp();

  void directionUp();
  void directionDown();
  void directionRight();
  void directionLeft();

  Gun getGun();
  void setGun(Gun in_gun);
  void setAmmo(int lessAmmo);
  int getAmmo();
  void decreaseAmmo(int lessAmmo);
  void increaseAmmo(int plusAmmo);
};
