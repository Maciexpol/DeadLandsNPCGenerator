#include "mainwindow.h"
#include "src/sessions/sessionmanager.h"
#include "src/generator/character.h"
#include "src/data/DataManager.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SessionManager sessionManager;

    //============ tests
    Character newCharacter = Character();

    // Std Character overview
    for(int i = 0; i < 3; i++){
        newCharacter.stdPrint();
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
        newCharacter.rollCharacter();
    }
    //=========== end test

    Character character;
    DataManager dataManager;
    w.createConnections(sessionManager, character, dataManager);
    dataManager.initialConnection();
    sessionManager.updateSessionInfo(sessionManager);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
