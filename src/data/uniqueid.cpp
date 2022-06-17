#include "uniqueid.h"

QString UniqueID::createUniqueID() {
    QUuid uuid = QUuid::createUuid();
    return uuid.toString();
}
