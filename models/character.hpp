#define CHARACTER

#include "gun.hpp"

struct Bullet {
  int x;
  int y;
  char skin;
  float speed;
  bool isPlayerBullet;  // true: colpo del player - false: colpo nemico
  bool moveFoward;  // Attenzione che i colpisparati "in avanti" sono relativi a
                    // chi li spara true sse colpo sparato in avanti, false
                    // altrimenti (una volta assegnata non va più modificata)
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
  Character(int x, int y, char skin, int life, int numberLife);
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

  void setGunDamage(int damage);
  void increaseDamageGun(int damage);
  Gun getGun();
  void setGun(Gun in_gun);
  void setTotalAmmo(int lessAmmo);

  void increaseTotalAmmo(int plusAmmo);
  void decreaseTotalAmmo(int lessAmmo);
  void increaseMagazineAmmo(int plusAmmo);
  void decreaseMagazineAmmo(int lessAmmo);
  void reload();
};
