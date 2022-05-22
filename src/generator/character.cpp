#include "character.h"

Character::Character()
{
    Character::rollDices();
}

void Character::rollDices(){
    dices.rollDices();
}

