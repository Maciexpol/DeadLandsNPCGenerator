#include "card.h"
#include <math.h>

Card::Card(int number)
{
    setFace(number);
    setSuit(number);
}
