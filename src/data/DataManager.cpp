//
// Created by Lesio on 07.06.2022.
//

#include "DataManager.h"

DataManager::DataManager(){
    //Set connection info
    QSqlDatabase::addDatabase("QSQLITE", "localDatabase");
    QSqlDatabase::addDatabase("QMYSQL", "originDatabase");
    database = QSqlDatabase::database("localDatabase");
    database.close();
    originDatabase = QSqlDatabase::database("originDatabase");
    originDatabase.close();
    databaseVersion = "1.0";

    originDatabase.setHostName("local-serwer");
    originDatabase.setDatabaseName("deadlands");
    originDatabase.setUserName("lesio");
    originDatabase.setPassword("lesio");
}

DataManager::~DataManager(){
    if(database.isOpen()){
        database.close();
    }
}

void DataManager::updateGeneratorSignal() {
    updateGenerator();
}

bool DataManager::openConnection() {
    if(database.isOpen())
        return true;
    //Check if correct local database file exists
    if(!QFile::exists(MemIO::generatorSavingFolder + "localDB-" + databaseVersion + ".db")){
        QMessageBox::warning(nullptr, "Database error.", "You have old version of local database or no database at all.");
        emit updateConnectionStatus("lack of proper database file.");
        return false;
    }
    database.setDatabaseName(MemIO::generatorSavingFolder + "localDB-" + databaseVersion + ".db");
    if(database.open()){
        emit updateConnectionStatus("connected to local database.");
        return true;
    }
    emit updateConnectionStatus("cannot connect to local database.");
    return false;
}

void DataManager::closeConnection() {
    if(database.isOpen())
        database.close();
    emit updateConnectionStatus("connection closed.");
}

bool DataManager::updateGenerator() {
    if(!originDatabase.open()){
        QMessageBox::warning(nullptr, "No connection.", "Connection to master database could not be established.");
        return false;
    }
    if(!database.isOpen()){
        QMessageBox::warning(nullptr, "No connection.", "Not connected to local database.");
        return false;
    }

    QMessageBox box;
    box.setText("Local database update.");
    box.setInformativeText("Are you sure you want to update local database? We cannot revert those changes.");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    int ret = box.exec();
    if(ret != 0x00004000)
        return false;

    QMessageBox::information(nullptr, "Local database update.", "We will now update your local database, application might freeze.");

    if(!updateNames() || !updateOrigins() || !updateOccupations() || !updateEdges() || !updateHindrances()) {
        QMessageBox::warning(nullptr, "Update failed.", "We have failed to update at least some of the data. Pretty normal thing for us to be honest.");
        return false;
    }
    QMessageBox::information(nullptr, "Update successful", "We have successfully updated your local data!");
    return true;
}

bool DataManager::updateNames() {
    QSqlQuery query(originDatabase);
    query.exec("SELECT id, first_name, origin_id, gender FROM first_names;");
    if(query.numRowsAffected() == -1){
        QMessageBox::warning(nullptr, "Error updating.", "Fetching data on names has failed.");
        return false;
    }

    QSqlQuery localQuery(database);
    localQuery.exec("DELETE FROM first_names;");
    localQuery.prepare("INSERT INTO first_names (id, first_name, origin_id, gender) VALUES (:id, :name, :origin, :gender)");
    while(query.next()){
        qint16 id = static_cast<qint16>(query.value(0).toInt());
        QString first_name = query.value(1).toString();
        qint16 origin_id = static_cast<qint16>(query.value(2).toInt());
        qint16 gender = static_cast<qint16>(query.value(3).toInt());
        localQuery.bindValue(":id", id);
        localQuery.bindValue(":name", first_name);
        localQuery.bindValue(":origin", origin_id);
        localQuery.bindValue(":gender", gender);
        localQuery.exec();
    }

    query.exec("SELECT id, last_name, origin_id FROM last_names;");
    if(query.numRowsAffected() == -1){
        QMessageBox::warning(nullptr, "Error updating.", "Fetching data on names has failed.");
        return false;
    }
    localQuery.exec("DELETE FROM last_names;");
    localQuery.prepare("INSERT INTO last_names (id, last_name, origin_id) VALUES (:id, :name, :origin)");
    while(query.next()){
        qint16 id = static_cast<qint16>(query.value(0).toInt());
        QString last_name = query.value(1).toString();
        qint16 origin_id = static_cast<qint16>(query.value(2).toInt());
        localQuery.bindValue(":id", id);
        localQuery.bindValue(":name", last_name);
        localQuery.bindValue(":origin", origin_id);
        localQuery.exec();
    }
    tempStatusBar("Names have been successfully updated");
    return true;
}

bool DataManager::updateOrigins() {
    QSqlQuery query(originDatabase);
    query.exec("SELECT id, origin FROM origins;");
    if(query.numRowsAffected() == -1){
        QMessageBox::warning(nullptr, "Error updating.", "Fetching data on origins has failed.");
        return false;
    }
    QSqlQuery localQuery(database);
    localQuery.exec("DELETE FROM origins;");
    localQuery.prepare("INSERT INTO origins (id, origin) VALUES (:id, :origin)");
    while(query.next()){
        qint16 id = static_cast<qint16>(query.value(0).toInt());
        QString origin = query.value(1).toString();
        localQuery.bindValue(":id", id);
        localQuery.bindValue(":origin", origin);
        localQuery.exec();
    }
    tempStatusBar("Origins have been successfully updated");
    return true;
}

bool DataManager::updateOccupations() {
    QSqlQuery query(originDatabase);
    query.exec("SELECT id, occupation FROM occupations;");
    if(query.numRowsAffected() == -1){
        QMessageBox::warning(nullptr, "Error updating.", "Fetching data on occupations has failed.");
        return false;
    }
    QSqlQuery localQuery(database);
    localQuery.exec("DELETE FROM occupations;");
    localQuery.prepare("INSERT INTO occupations (id, occupation) VALUES (:id, :occupation)");
    while(query.next()){
        qint16 id = static_cast<qint16>(query.value(0).toInt());
        QString occupation = query.value(1).toString();
        localQuery.bindValue(":id", id);
        localQuery.bindValue(":occupation", occupation);
        localQuery.exec();
    }
    tempStatusBar("Occupations have been successfully updated");
    return true;
}

bool DataManager::updateEdges() {
    QSqlQuery query(originDatabase);
    query.exec("SELECT id, edge, points, description FROM edges;");
    if(query.numRowsAffected() == -1){
        QMessageBox::warning(nullptr, "Error updating.", "Fetching data on edges has failed.");
        return false;
    }
    QSqlQuery localQuery(database);
    localQuery.exec("DELETE FROM edges;");
    localQuery.prepare("INSERT INTO edges (id, edge, points, description) VALUES (:id, :edge, :points, :description)");
    while(query.next()){
        qint16 id = static_cast<qint16>(query.value(0).toInt());
        QString edge = query.value(1).toString();
        qint16 points = static_cast<qint16>(query.value(2).toInt());
        QString description = query.value(3).toString();
        localQuery.bindValue(":id", id);
        localQuery.bindValue(":edge", edge);
        localQuery.bindValue(":points", points);
        localQuery.bindValue(":description", description);
        localQuery.exec();
    }
    tempStatusBar("Edges have been successfully updated");
    return true;
}

bool DataManager::updateHindrances() {
    QSqlQuery query(originDatabase);
    query.exec("SELECT id, hindrance, points, description FROM hindrances;");
    if(query.numRowsAffected() == -1){
        QMessageBox::warning(nullptr, "Error updating.", "Fetching data on hindrances has failed.");
        return false;
    }
    QSqlQuery localQuery(database);
    localQuery.exec("DELETE FROM hindrances;");
    localQuery.prepare("INSERT INTO hindrances (id, hindrance, points, description) VALUES (:id, :hindrance, :points, :description)");
    while(query.next()){
        qint16 id = static_cast<qint16>(query.value(0).toInt());
        QString hindrance = query.value(1).toString();
        qint16 points = static_cast<qint16>(query.value(2).toInt());
        QString description = query.value(3).toString();
        localQuery.bindValue(":id", id);
        localQuery.bindValue(":hindrance", hindrance);
        localQuery.bindValue(":points", points);
        localQuery.bindValue(":description", description);
        localQuery.exec();
    }
    tempStatusBar("Hindrances have been successfully updated");
    return true;
}
