/*
    Un oggetto del gioco sarà la classe padre di sottoclassi quali:
        . Arma  (possibile modifica all'attuale sparo del player, ovvero si può aggiungere un attributo arma al personaggio)
        . Mina (volendo una mina può essere vista anche come un oggetto enemy)
        . Oggetti raccoglibili:
            . Bonus / Malus: Possibili implementazioni:
                - Modificatori di punteggio
                - Modificatori temporanei / permanenti di armi
                - Modificatori temporanei / permanenti del personaggio
                - Modificatori temporanei / permanenti dei nemici
*/

#include "object.hpp"

Object::Object (char in_name[], int in_mapTime, int in_duration, bool in_isMalus) {
    strcpy (this -> name, in_name);
    this -> mapTime  = in_mapTime;
    this -> duration = in_duration;
    this -> isMalus = in_isMalus;
}

void Object::decrementMapTime  () { this -> mapTime  -= 1; }
void Object::decrementDuration () { this -> duration -= 1; }
void Object::incrementDuration () { this -> duration += 1; }

