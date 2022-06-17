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
    // emit closeCurrentSession();

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
        attributesWidgetsVecotr.push_back(newWidget);
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

    connectionStatus = new QLabel(this);
    connectionStatus->setText("No connection.");
    connectionStatus->setObjectName(QString::fromUtf8("connectionStatus"));
    this->ui->statusbar->addPermanentWidget(connectionStatus);
}


void MainWindow::createConnections(const SessionManager &sessionManager, const Character &character, const DataManager &dataManager) const{
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

    //Connection between MainWindow and Character to reroll lvlSum Distribution
    QObject::connect(this->ui->buttonRollLvlSums, &QPushButton::clicked, &character, &Character::rollFromLvlPoints);

    //Connection between MainWindow and Character to reroll Overview
    QObject::connect(this->ui->buttonRollOverview, &QPushButton::clicked, &character, &Character::rollFromOverview);

    //Connection between MainWindow and Character to reroll Name
    QObject::connect(this->ui->buttonRollName, &QPushButton::clicked, &character, &Character::rollFromName);

    //Connection between MainWindow and Character to reroll Age
    QObject::connect(this->ui->buttonRollAge, &QPushButton::clicked, &character, &Character::rollAge);

    //Connection between MainWindow and Character to reroll Occupation
    QObject::connect(this->ui->buttonRollOccupation, &QPushButton::clicked, &character, &Character::rollOccupation);

    //Connection between MainWindow and Character to reroll Origin
    QObject::connect(this->ui->buttonRollOrigin, &QPushButton::clicked, &character, &Character::rollFromOrigin);

    //Connection between every attribute's button and Character to reroll specific attribute
    for(auto & el : attributesWidgetsVecotr){
        el->connectButton(character);
    }

    // ============================== Character - SessionManager ===================================

    //Connection to handle adding character to session
    QObject::connect(&character, &Character::addCharacter, &sessionManager, &SessionManager::addCharacter);

    //Connection to handle loading character from session list
    QObject::connect(&sessionManager, &SessionManager::loadCharacter, &character, &Character::loadCharacter);

    // ============================== MainWindow - DataManager ===================================

    //Connection to handle updating connection status
    QObject::connect(&dataManager, &DataManager::updateConnectionStatus, this, &MainWindow::updateConnectionStatus);

    //Connection to handle updating data
    QObject::connect(this, &MainWindow::updateGeneratorData, &dataManager, &DataManager::updateGeneratorSignal);

    //Connection to handle status bar update
    QObject::connect(&dataManager, &DataManager::tempStatusBar, this, &MainWindow::tempStatusBar);

    //Connection to open database connection
    QObject::connect(this, &MainWindow::openConnection, &dataManager, &DataManager::openConnection);

<<<<<<< HEAD
=======
    //Connection between custom widgets and character
    for(auto & el : attributesWidgetsVecotr){
        el->connectButton(character);
    }
>>>>>>> 3c92d8c60617a59c14856ad983aff0d4ae1c5d97
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
    // ---- Overview
    this->ui->NameInput->setText( character.getOverview().getFirstName() + " " + character.getOverview().getLastName());
    this->ui->AgeInput->setText( QString::number(character.getOverview().getAge()) );
    this->ui->OriginInput->setText( character.getOverview().getOrigin());
    this->ui->OccuppationInput->setText( character.getOverview().getOccupation());

    // ---- Edges and Hindrances

    // ---- Attributes
    QVector<Attribute> charAttributes= character.getAttributes().getAttributesVector();
    for(qint16 i = 0; i < 10; i++){
        std::cout << charAttributes.length();
        // set dice
        QString dc = QString::number(charAttributes[i].getDice().getNumber()) + "d" + QString::number(charAttributes[i].getDice().getSides());
        attributesWidgetsVecotr[i]->setDiceText(dc);

        if(charAttributes[i].hasAbilities()){ // if there is no abilities - skip
            // set LvlSum
            attributesWidgetsVecotr[i]->setLvlSumText(QString::number(charAttributes[i].getabilitiesLvlSum()));
            // set abilities lvl
            QVector<QString> lvls; // vector with lvl strings
            for(auto i : charAttributes[i].getAbilities().getAbilites()){
                lvls.push_back(QString::number(i.getLvl()));
            }
            attributesWidgetsVecotr[i]->setAbilitiesLvlsText(lvls);
        }
    }
}

void MainWindow::updateConnectionStatus(QString message) {
    connectionStatus->setText("DB status: " + message);
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

void MainWindow::on_actionGeneratorUpdate_triggered()
{
    emit updateGeneratorData();
}

void MainWindow::on_actionGeneratorConnect_triggered()
{
    emit openConnection();
}

