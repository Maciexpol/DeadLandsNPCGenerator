#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QDate>

#include "src/serializable.h"
#include "../generator/character.h"
#include "sessioncharacter.h"

/*!
 * \brief Sessions group and manage generated characters
 *
 * Sessions are an easy way to manage characters. They provide tools to store, add
 * and delete all of the generated NPCs.
 */
class Session : Serializable
{
private:
    // Remember to serialize newly added objects in XmlSerialize
    QString name;
    QString description;
    QDate creationDate;
    qint16 npcCount;
    QVector<SessionCharacter> characters;

public:
    Session();
    Session(const QString &name, const QString &description, const QDate &date, const qint16 &npcCount);

    QString getName() const{return this->name;};
    QString getDescription() const{return this->description;};
    QDate getCreationDate() const{return this->creationDate;};
    qint16 getNpcCount() const{return this->npcCount;};
    QVector<SessionCharacter> getCharacters() const{return this->characters;};

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
    bool XmlValidate() const override;

public slots:
    void addCharacter(const qint32 &id, const QString &name);
    //void removeCharacter(const qint32 &id);
};

#endif // SESSION_H
