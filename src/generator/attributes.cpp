#include "attributes.h"

Attributes::Attributes(const qint16 & characterLvlPoints, const Dices & dices){

//    return;
//    QVector<QVector<QString>> abilities{};

    QVector<QVector<QString>> abilities = MemIO::loadAbilities();
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i), abilities[i], dices.getDice(i)));
    }
    rollAttributesLvlPoints(characterLvlPoints);
}

Attributes::Attributes(const Attributes & at){
    attributes = {};
    for(qint16 i = 0; i < at.getAttributesVector().length(); i++){
        attributes.push_back(at.getAttributesVector()[i]);
    }
    actualPriority = {};
    for(qint16 i = 0; i < at.getActualPriority().length(); i++){
        actualPriority.push_back(at.getActualPriority()[i]);
    }
}

Attributes::Attributes(const Dices & dices, QVector<QString> queue){
    QVector<QVector<QString>> abilities = MemIO::loadAbilities();
    actualPriority.clear();

    Tiles tiles = Tiles(queue);
    tiles.shuffleTiles({70, 60, 50, 40, 30, 25, 20, 15, 10, 5});
//    tiles.shuffleTiles({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    for(qint16 i = 0; i < 10; i++){
        actualPriority.push_back(tiles.getTiles()[i]);
    }
    std::cout<< actualPriority.length() << " Length of Actual priority during rolling";

    for(qint16 i = 0; i < 10; i++){
        qint16 index = 0;
        while(actualPriority[index] != ATTRIBUTES(i)){
            index++;
            if(index >= 10)
                std::cout << "attributes constructor index error" << std::endl;
        }

        attributes.push_back(Attribute(ATTRIBUTES(i), abilities[i], dices.getDice(index)));
    }
}

Attributes & Attributes::operator=(const Attributes & at){
    attributes = {};
    for(qint16 i = 0; i < at.getAttributesVector().length(); i++){
        attributes.push_back(at.getAttributesVector()[i]);
    }
    actualPriority = {};
    for(qint16 i = 0; i < at.getActualPriority().length(); i++){
        actualPriority.push_back(at.getActualPriority()[i]);
    }
    return *this;
}

Attribute* Attributes::getAttribute(const ATTRIBUTES & sName){
//  1 option
//    return attributes[(qint16) sName];
//    option may be bad, because it needs attributes to be in specific order
//  2 option
    for(qint16 i = 0; i < attributes.length(); i++){
        if(attributes[i].getName() == sName)
            return &attributes[i];
    }
    return {};
}

qint16 Attributes::generateLvlPoints(){
    qint16 sum = 0;
    sum += getAttribute(ATTRIBUTES::Cognition)->getDice().getSides();
    sum += getAttribute(ATTRIBUTES::Knowledge)->getDice().getSides();
    sum += getAttribute(ATTRIBUTES::Smarts)->getDice().getSides();
    return sum;
}

void Attributes::clearAttributesLvlPoints(){
    for(auto & at : attributes){
        if(at.hasAbilities())
            at.clearAbilitiesLvl();
    }
}

void Attributes::clearAttributesLvlSum(){
    for(auto & at : attributes){
        if(at.hasAbilities())
            at.clearAbilitiesLvlSum();
    }
    clearAttributesLvlPoints();
}

void Attributes::rollAttributesLvlPoints(const qint16 & characterLvlPoints){
    // reseting lvl of all abilities in all attributes
    clearAttributesLvlPoints();
    // random generator init

    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> num(0, attributes.length()-1); // distribute results between 1 and 6 inclusive.

    // randomly increasing abillities lvl by one
    for(qint16 i = 0; i < characterLvlPoints; i++){
        qint16 index = num(gen);

        // rolling as long as we find attribute with abilities
        while(attributes[index].hasAbilities() == 0 or attributes[index].getAbilitiesCount() * maxAbilityLvl <= attributes[index].getabilitiesLvlSum()){
            index = num(gen);
        }

        attributes[index].increaseAbilitiesLvlSum();
    }

    // rolling abilities inside of abilities
    for(auto & at : attributes){
        if(at.hasAbilities())
            at.rollAbilitiesLvl();
    }
}

void Attributes::stdPrint(){
    for(auto & at : attributes){
        at.stdPrint();
    }
}

QDomElement Attributes::XmlSerialize() const {
    //XD
    QDomElement element = QDomDocument().createElement("attributes");

    for(auto &attribute : attributes){
        element.appendChild(attribute.XmlSerialize());
    }
    return element;
}

void Attributes::XmlDeserialize(const QDomElement &element) {
    attributes.clear();
    QDomElement node = element.firstChildElement();
    while(!node.isNull()){
        Attribute attribute;
        attribute.XmlDeserialize(node);
        attributes.append(attribute);
        node = node.nextSiblingElement();
    }
}
