#include "attributes.h"

Attributes::Attributes()
{
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i)));
    }
}
