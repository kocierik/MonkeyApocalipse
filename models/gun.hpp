#include <string.h>

#define OBJECT
#define NAMESIZE 30

class Gun {
 protected:
  //char name[NAMESIZE];
  char bulletSkin;
  int damage;
  int ammo;
 public:
  Gun ();
  Gun (char in_bulletSkin, int in_damage, int in_ammo);
  //Gun(char in_name[], int in_bulletSkin, int in_damage);

  //void getname();
  //void setname();
  char getBulletSkin  ();
  int  getDamage      ();
  void increaseDamage (int plusDMG);
  void decreaseDamage (int lessDMG);
  void setDamage      (int in_damage);
  int  getAmmo        ();
  void setAmmo        (int in_ammo);
  void increaseAmmo   (int plusAmmo);
  void decreaseAmmo   (int lessAmmo);
};

struct GunList {
  Gun gun;
  GunList* next;
};
typedef GunList* pGunList;