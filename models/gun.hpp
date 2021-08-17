#include <string.h>

#define OBJECT
#define NAMESIZE 30

class Gun {
 protected:
  char bulletSkin;
  int damage;
  int totalAmmo;         // Munizioni totali
  int magazineAmmo;      // Colpi nel caricatore
  int magazineCapacity;  // Capacità del caricatore

 public:
  Gun();
  Gun(char in_bulletSkin, int in_damage, int in_totalAmmo,
      int in_magazineCapacity);

  char getBulletSkin();
  void setBulletSkin(char newSkin);

  int getDamage();
  void setDamage(int in_damage);
  void increaseDamage(int plusDMG);
  void decreaseDamage(int lessDMG);

  int getMagazineAmmo();
  void setMagazineAmmo(int ammo);
  void increaseMagazineAmmo(int plusAmmo);
  void decreaseMagazineAmmo(int lessAmmo);

  void reloadMagazine();

  int getMagazineCapacity();
  void setMagazineCapacity(int ammo);

  int getTotalAmmo();
  void setTotalAmmo(int in_ammo);
  void increaseTotalAmmo(int plusAmmo);
  void decreaseTotalAmmo(int lessAmmo);
};

struct GunList {
  Gun gun;
  GunList* next;
};
typedef GunList* pGunList;