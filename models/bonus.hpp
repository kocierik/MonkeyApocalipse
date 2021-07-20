#include <string.h>

#define OBJECT
#define NAMESIZE 30

class Bonus {
    protected:
        char name[NAMESIZE];
        char skin;
        int mapTime;            // Quantità di tempo in cui sta sulla mappa prima di scomparire, qualora non venisse raccolto.
        int duration;           // Durata dell'effetto dell'oggetto raccolto. Se < 0 allora è permanente.
    public:
        Bonus (char in_name[], int in_mapTime, int in_duration) {
            strcpy (this -> name, in_name);
            this -> skin     = '?';
            this -> mapTime  = in_mapTime;
            this -> duration = in_duration;
        }

        void decrementMapTime  ();
        void decrementDuration ();
        void incrementDuration ();

};

struct BonusList {
    Bonus bonus;
    BonusList* next;
};
typedef BonusList* pBonusList;