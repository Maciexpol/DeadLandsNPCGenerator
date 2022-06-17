#ifndef UNIQUEID_H
#define UNIQUEID_H

#include <QString>
#include <QByteArray>
#include <QSysInfo>
#include <QMessageBox>
#include <QUuid>

class UniqueID
{
private:
    UniqueID();
    static QByteArray getMachineID();
public:
    static QString createUniqueID();

};

#endif // UNIQUEID_H
