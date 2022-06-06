#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Create folder structure
    MemIO::createFolderStructure();

    // For now, invoke closeCurrentSession in orded to show placeholder session.
    emit closeCurrentSession();

    // Generate attributes boxes
    generateAttributesWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateAttributesWidgets(){
    QVector<QVector<QString>> names = MemIO::loadAbilities();

    for(qint16 i = 0; i < names.length(); i++){
        AttributeWidget * newWidget = new AttributeWidget(ATTRIBUTES(i), names[i]);
        switch(i%3){
        case 0:
            this->ui->firstColumn->addWidget(newWidget);
            break;
        case 1:
            this->ui->secondColumn->addWidget(newWidget);
            break;
        case 2:
            this->ui->thirdColumn->addWidget(newWidget);
            break;
        }
    }
}


void MainWindow::createConnections(const SessionManager &sessionManager, const Character &character) const{
    // ============================= SessionManager - MainWindow ==================================

    //Connection between SessionManager and MainWindow to handle updating UI
    QObject::connect(&sessionManager, &SessionManager::updateSessionInfo, this, &MainWindow::updateSessionInfo);

    //Connection between SessionManager and MainWindow to link character list
    QObject::connect(&sessionManager, &SessionManager::linkCharacterList, this, &MainWindow::linkCharacterList);

    //Connection between SessionManager and MainWindow to handle temporary status bar messages
    QObject::connect(&sessionManager, &SessionManager::tempStatusBar, this, &MainWindow::tempStatusBar);

    //Connection between SessionManager and MainWindow to handle creating new sessions
    QObject::connect(this, &MainWindow::createNewSession, &sessionManager, &SessionManager::createNewSession);

    //Connection between SessionManager and MainWindow to handle saving sessions
    QObject::connect(this, &MainWindow::saveCurrentSession, &sessionManager, &SessionManager::saveCurrentSession);

    //Connection between SessionManager and MainWindow to handle closing sessions
    QObject::connect(this, &MainWindow::closeCurrentSession, &sessionManager, &SessionManager::closeCurrentSession);

    //Connection between SessionManager and MainWindow to handle opening sessions
    QObject::connect(this, &MainWindow::openNewSession, &sessionManager, &SessionManager::openNewSession);

    //Connection from QAbstractItemView to handle doubleClick events on QListView
    QObject::connect(this->ui->npcView, &QListView::doubleClicked, &sessionManager, &SessionManager::listDoubleClicked);

    //Connect to SessionManager in order to remove character from session
    QObject::connect(this, &MainWindow::deleteCharacterFromSession, &sessionManager, &SessionManager::deleteCharacterFromSession);

    // ================================ Character - MainWindow ====================================

    //Connection between MainWindow and Character to handle updating character data
    QObject::connect(&character, &Character::updateCharacterInfo, this, &MainWindow::updateCharacterInfo);

    //Connection between MainWindow and Character to handle generating character
    QObject::connect(this, &MainWindow::reRollCharacter, &character, &Character::generateCharacter);

    //Connection between MainWindow and Character to handle adding character to active session
    QObject::connect(this, &MainWindow::addCharacterToSession, &character, &Character::addCharacterToSession);

    // ============================== Character - SessionManager ===================================

    //Connection to handle adding character to session
    QObject::connect(&character, &Character::addCharacter, &sessionManager, &SessionManager::addCharacter);

    //Connection to handle loading character from session list
    QObject::connect(&sessionManager, &SessionManager::loadCharacter, &character, &Character::loadCharacter);
}

void MainWindow::linkCharacterList(QStringListModel *list) {
    this->ui->npcView->setModel(list);
}

void MainWindow::updateSessionInfo(const SessionManager& session){
    this->ui->sessionName->setText(session.getName());
    this->ui->sessionDescription->setText(session.getDescription());
    this->ui->npcView->setModel(session.getCharacterModel());
}

void MainWindow::updateCharacterInfo(const Character &character) {
    this->ui->NameInput->setText(character.getOverview().getFirstName() + character.getOverview().getLastName());
}

void MainWindow::tempStatusBar(QString message) {
    this->ui->statusbar->showMessage(message, 3000);
}

void MainWindow::on_actionSessionNew_triggered()
{
    emit createNewSession();
}

void MainWindow::on_actionSessionSave_triggered()
{
    emit saveCurrentSession();
}

void MainWindow::on_actionSessionClose_triggered()
{
    emit closeCurrentSession();
}

void MainWindow::on_actionSessionOpen_triggered()
{
    emit openNewSession();
}

void MainWindow::on_rerollCharacter_clicked()
{
    emit reRollCharacter();
}

void MainWindow::on_actionGenerate_triggered()
{
    emit reRollCharacter();
}

void MainWindow::on_addToSession_clicked()
{
    emit addCharacterToSession();
}

void MainWindow::on_actionAdd_to_session_triggered()
{
    emit addCharacterToSession();
}

void MainWindow::on_deleteFromSession_clicked()
{
    emit deleteCharacterFromSession(this->ui->npcView->currentIndex());
}
