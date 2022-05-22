#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sessionManager(SessionManager())
{
    ui->setupUi(this);

    //Create folder structure
    LSaver::createFolderStructure();

    //Connection between SessionManager and MainWindow to handle updating UI
    QObject::connect(&sessionManager, &SessionManager::updateSessionInfo, this, &MainWindow::updateSessionInfo);

    //Connection between SessionManager and MainWindow to handle creating new sessions
    QObject::connect(this, &MainWindow::createNewSession, &sessionManager, &SessionManager::createNewSession);

    //Connection between SessionManager and MainWindow to handle saving sessions
    QObject::connect(this, &MainWindow::saveCurrentSession, &sessionManager, &SessionManager::saveCurrentSession);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSessionInfo(Session session){
    this->ui->sessionName->setText(session.getName());
    this->ui->sessionDescription->setText(session.getDescription());
}

void MainWindow::on_actionSessionNew_triggered()
{
    emit createNewSession();
}

void MainWindow::on_sessionNew_clicked()
{
    emit createNewSession();
}

void MainWindow::on_sessionSave_clicked()
{
    emit saveCurrentSession();
}


void MainWindow::on_actionSessionSave_triggered()
{
    emit saveCurrentSession();
}

