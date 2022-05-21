#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QDate>

class Session
{
private:
    QString name;
    QString description;
    QDate creationDate;
    qint16 npcCount;

public:
    Session();
};

#endif // SESSION_H
