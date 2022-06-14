//
// Created by Lesio on 07.06.2022.
//
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDomDocument>
#include "src/memio.h"

#ifndef NPC_GENERATOR_DATAMANAGER_H
#define NPC_GENERATOR_DATAMANAGER_H


class DataManager : public QObject {
    Q_OBJECT
private:
    QString databaseVersion;
    QSqlDatabase database;
    QSqlDatabase originDatabase;

public:
    DataManager();
    ~DataManager();

    void closeConnection();

    bool updateGenerator();
    bool updateNames();
    bool updateOrigins();
    bool updateOccupations();
    bool updateEdges();
    bool updateHindrances();

    void loadNames();
    void loadOrigins();
    void loadOccupations();

    void fetchDataFromDatabase();

public slots:
    void updateGeneratorSignal();
    bool openConnection();

signals:
    void updateConnectionStatus(QString);
    void tempStatusBar(QString message);
};


#endif //NPC_GENERATOR_DATAMANAGER_H
