//
// Created by Lesio on 07.06.2022.
//
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>

#ifndef NPC_GENERATOR_DATAMANAGER_H
#define NPC_GENERATOR_DATAMANAGER_H


class DataManager : public QObject {
    Q_OBJECT
private:
    QSqlDatabase database;
    bool isConnectionPossible;

    QVector<QString> first_names;
    QVector<QString> last_names;
    QVector<QString> origins;
    QVector<QString> occupations;

public:
    DataManager();
    ~DataManager();

    void initialConnection();

    void loadNames();
    void loadOrigins();
    void loadOccupations();

    void fetchDataFromDatabase();

signals:
    void updateConnectionStatus(QString);
};


#endif //NPC_GENERATOR_DATAMANAGER_H
