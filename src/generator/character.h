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
    qint32 uniqueID;
    Attributes attributes;
    Dices dices;
    EdgesAndHindrances edgesAndHindrances;
    Overview overview;

public:
    Character();
    
    qint32 getUniqueID() const {return this->uniqueID;};
    Attributes getAttributes() const{return this->attributes;}
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

    void rollCharacter();
    void rollDices();

public slots:
    void addCharacterToSession();
    void generateCharacter();
    void saveCharacter();
    void loadCharacter(const SessionCharacter&);

signals:
    //Signals to MainWindow
    void updateCharacterInfo(const Character&);

    //Signals to SessionManager
    void addCharacter(SessionCharacter&);

    //Probably should be removed, idk
    //void removeCharacter(const qint32);

};

#endif // CHARACTER_H
