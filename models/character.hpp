#define CHARACTER

#include "gun.hpp"

struct Bullet {
  int x;
  int y;
  char skin;
  float speed;
  bool moveFoward;  // UNa volta assegnata, non va più modificata
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
  Character();

  void setX(int x);
  int getX();
  void setY(int y);
  int getY();

  void directionUp();
  void directionDown();
  void directionRight();
  void directionLeft();

  char getSkin();
  void setSkin(char skin);

  void increaseLife(int life);
  void decreaseLife(int life);
  int getLife();
  void setLife(int life);
  int getNumberLife();
  void setNumberLife(int numberLife);

  //int getBullet();
  //void bulletUp();
  void increaseDamageGun(int damage);
  Gun getGun();
  void setGun(Gun in_gun);
  int getTotalAmmo();
  void setTotalAmmo(int lessAmmo);
  void decreaseAmmo(int lessAmmo);
  void increaseAmmo(int plusAmmo);
};
