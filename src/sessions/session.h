#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QDate>

#include "../serializable.h"

class Session : Serializable
{
private:
    QString name;
    QString description;
    QDate creationDate;
    qint16 npcCount;

public:
    Session();
    Session(const QString name, const QString description, const QDate date, const qint16 npcCount);

    QString getName() const{return this->name;};
    QString getDescription() const{return this->description;};
    QDate getCreationDate() const{return this->creationDate;};
    qint16 getNpcCount() const{return this->npcCount;};

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement element) const override;
};

#endif // SESSION_H
