#include "attribute.h"

Attribute::Attribute(ATTRIBUTES inputName){
    name = inputName;
}

Attribute::Attribute(ATTRIBUTES inputName, Abilities inputAbilities){
    name = inputName;
    abilities = inputAbilities;
}

Attribute::Attribute(ATTRIBUTES inputName, Dice inputDice, Abilities inputAbilities){
    name = inputName;
    dice = inputDice;
    abilities = inputAbilities;
}

