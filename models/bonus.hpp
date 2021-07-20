#include <string.h>

#ifndef COORDINATE
#define COORDINATE
#include "coordinate.hpp"
#endif

#define OBJECT
#define NAMESIZE 30

class Bonus : public Coordinate {
    protected:
        char name[NAMESIZE];
        int mapTime;            // Quantità di tempo in cui sta sulla mappa prima di scomparire, qualora non venisse raccolto.
        int duration;           // Durata dell'effetto dell'oggetto raccolto. Se < 0 allora è permanente.
    public:
        Bonus ();
        Bonus (Position point, char in_name[], int in_mapTime, int in_duration);
        
        void decrementMapTime  ();
        void decrementDuration ();
        void incrementDuration ();

};

struct BonusList {
    Bonus bonus;
    BonusList* next;
};
typedef BonusList* pBonusList;