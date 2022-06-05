#include "dices.h"

Dices::Dices()
{
    Dices::rollDices();
}

void Dices::rollDices(){
    dices = RollDices::generateDices();
    Dices::sortDices();
}

void Dices::sortDices() {
    RollDices::sortDices(dices);
}

void Dices::stdPrint(){
    for(auto & d : dices){
        std::cout << "  " << d;
    }
    std::cout << std::endl;
}

QDomElement Dices::XmlSerialize() const {
    QDomElement element;
    element.setTagName("dices");
    for(auto &dice : dices){
        element.appendChild(dice.XmlSerialize());
    }
    return element;
}

void Dices::XmlDeserialize(const QDomElement &element) {
}
