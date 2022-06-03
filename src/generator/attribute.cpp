#include "attribute.h"

void Attribute::rollAbilitiesLvl(){
    abilities.rollAbilitesLvl(abilitiesLvlSum);
}

void Attribute::rollAbilitiesLvl(qint16 newAbilitiesLvlSum){
    setAbilitiesLvlSum(newAbilitiesLvlSum);
    rollAbilitiesLvl();
}

