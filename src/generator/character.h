#ifndef CHARACTER_H
#define CHARACTER_H

#include <QModelIndex>

#include "src/serializable.h"
#include "src/sessions/sessioncharacter.h"
#include "attributes.h"
#include "dices.h"
#include "edgesandhindrances.h"
#include "overview.h"
#include "rolldices.h"
#include "src/data/uniqueid.h"

/*!
 * \brief Character data
 *
 * Holds character data and manages its' generation.
 */
class Character : public QObject, Serializable
{
    Q_OBJECT

private:
    // Remember to serialize newly added objects in XmlSerialize
    QString uniqueID;
    Attributes attributes;
    Dices dices;
    EdgesAndHindrances edgesAndHindrances;
    Overview overview;

public:
    Character();
    
    QString getUniqueID() const {return this->uniqueID;};
    Attributes* getAttributes() {return &this->attributes;}
    Attributes getAttributes() const {return this->attributes;}
    Dices getDices() const{return this->dices;};
    EdgesAndHindrances getEdgesAndHindrances() const{return this->edgesAndHindrances;};
    Overview getOverview() const{return this->overview;};

    void stdPrint();
    void updateInfo();

    //Reimplement this function also in SessionCharacter
    QString toStr() const;
    SessionCharacter toSessionCharacter() const;

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
    bool XmlValidate() const override;

    void rollDices();
    void rollEdgesAndHindrances();

public slots:
    void addCharacterToSession();
    void generateCharacter();
    void saveCharacter();
    void loadCharacter(const SessionCharacter&);

    void rollCharacter();
    void rollFromDices();
    void rollFromLvlPoints();
    void rollSpecificAbility(const ATTRIBUTES & name);
//    void rollFromEdgesAndHindrances();
    void rollFromOverview();
    void rollFromName();
    void rollAge();
    void rollOccupation();
    void rollFromOrigin();

signals:
    //Signals to MainWindow
    void updateCharacterInfo(const Character&);

    void updateOutputQueueAndDices(const QVector<ATTRIBUTES> &, const QVector<Dice> &);

    //Signals to SessionManager
    void addCharacter(SessionCharacter&);

    //Probably should be removed, idk
    //void removeCharacter(const qint32);
    QVector<QString> getViewListAttributesPriority();

};

#endif // CHARACTER_H
