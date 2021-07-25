#include <string.h>

#ifndef COORDINATE
#define COORDINATE
#include "coordinate.hpp"
#endif

#define OBJECT
#define NAMESIZE 30

class Item : public Coordinate {
 protected:
  char name[NAMESIZE];
  int mapTime;  // Quantità di tempo in cui sta sulla mappa prima di scomparire,
                // qualora non venisse raccolto.
  int duration;  // Durata dell'effetto dell'oggetto raccolto. Se < 0 allora è
                 // permanente.
 public:
  Item();
  Item(char in_name[], int in_mapTime, int in_duration);

  void decrementMapTime();
  void decrementDuration();
  void incrementDuration();
};

struct ItemList {
  Item bonus;
  ItemList* next;
};
typedef ItemList* pItemList;