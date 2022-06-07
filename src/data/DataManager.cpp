//
// Created by Lesio on 07.06.2022.
//

#include "DataManager.h"

DataManager::DataManager(){
    //Set connection info
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setHostName("local-serwer");
    database.setDatabaseName("deadlands");
    database.setUserName("lesio");
    database.setPassword("lesio");

    //Check for data folder and create if such does not exist
    if(!QDir("./data/generationData").exists())
        QDir().mkpath("./data/generator");
}

DataManager::~DataManager(){
    if(database.isOpen()){
        database.close();
    }
}

void DataManager::initialConnection() {
    QMessageBox messageBox = QMessageBox();
    if(database.open()){
        isConnectionPossible = true;
        messageBox.setText("Database connection has been established");
        emit updateConnectionStatus("Connected.");
    }else{
        isConnectionPossible = false;
        QSqlError error = database.lastError();
        messageBox.setText(error.text());
        emit updateConnectionStatus("Not connected");
    }
    messageBox.exec();
}

