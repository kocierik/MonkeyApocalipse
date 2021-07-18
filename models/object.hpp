#include <stdio.h>
#include <string.h>

#define OBJECT
#define NAMESIZE 30

class Object {
    protected:
        char name[NAMESIZE];
        int mapTime;            // Qunatità di tempo in cui sta sulla mappa prima di scomparire, qualora non venisse raccolto.
        int duration;           // Durata dell'effetto dell'oggetto raccolto. Se < 0 allora è permanente.
        bool isMalus;
    public:
        Object (char in_name[], int in_mapTime, int in_duration, bool in_isMalus) {
            strcpy (this -> name, in_name);
            this -> mapTime  = in_mapTime;
            this -> duration = in_duration;
            this -> isMalus = in_isMalus;
        }

        void decrementMapTime  ();
        void decrementDuration ();
        void incrementDuration ();

};