#include "mainwindow.h"
#include "src/sessions/sessionmanager.h"
#include "src/generator/character.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SessionManager sessionManager;
    w.createConnections(sessionManager);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
