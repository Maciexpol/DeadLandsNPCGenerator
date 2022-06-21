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

    ui->attributesPriorityQueueWidget->addItem("Cognition");
    ui->attributesPriorityQueueWidget->addItem("Deftness");
    ui->attributesPriorityQueueWidget->addItem("Smarts");
    ui->attributesPriorityQueueWidget->addItem("Mien");
    ui->attributesPriorityQueueWidget->addItem("Spirit");
    ui->attributesPriorityQueueWidget->addItem("Vigor");
    ui->attributesPriorityQueueWidget->addItem("Quickness");
    ui->attributesPriorityQueueWidget->addItem("Nimbleness");
    ui->attributesPriorityQueueWidget->addItem("Strength");
    ui->attributesPriorityQueueWidget->addItem("Knowledge");
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


void MainWindow::createConnections(const SessionManager &sessionManager,const Character &character, const DataManager &dataManager) const{
    qDebug("Connections start");
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

    //Connection between MainWindow and Character to reroll Traits
    QObject::connect(this->ui->rerollTraits, &QPushButton::clicked, &character, &Character::rollTraits);

    //Connection between MainWindow and Character to reroll Dices of Character
    QObject::connect(this->ui->buttonRollDices, &QPushButton::clicked, &character, &Character::rollFromDices);

    //Connection between every attribute's button and Character to reroll specific attribute
    for(auto & el : attributesWidgetsVecotr){
        if(el->hasAbilities())
            el->connectButton(character);
    }

    //Connection between Attributes rolling function and MainWindow AttributeQueuePriority to get priority
    QObject::connect(&character, &Character::getViewListAttributesPriority, this, &MainWindow::getViewListAttributesPriority);

    //Connection between Attributes rolling function and MainWindow to acutalise actual dices and priority queue
    QObject::connect(&character, &Character::updateOutputQueueAndDices, this, &MainWindow::updateOutputQueueAndDices);

    // ============================== Character - SessionManager ===================================

    //Connection to handle adding character to session
    qDebug("AFTER LOOP");
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

    //Connection between custom widgets and character
    qDebug("Connections end");
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

    // ---- Traits
    // Kill all children
    while(QVBoxLayout* w = this->ui->traitsLayout->findChild<QVBoxLayout*>())
        delete w;

    if(character.getEdgesAndHindrances().getTraitsCount()){
        // Add new edges
        for(auto &trait : character.getEdgesAndHindrances().getEdges()){
            this->ui->traitsLayout->addLayout(new TraitWidget(trait.getName(), trait.getPoints(), trait.getDescription(), TraitType::EDGE));
        }

        // Add new hindrances
        for(auto &trait : character.getEdgesAndHindrances().getHindrances()){
            this->ui->traitsLayout->addLayout(new TraitWidget(trait.getName(), trait.getPoints(), trait.getDescription(), TraitType::HINDRANCE));
        }
        //Check if any traits has been rolled
    }else{
        QVBoxLayout* layout = new QVBoxLayout();
        QLabel* label = new QLabel("");
        layout->addWidget(label);
        this->ui->traitsLayout->addLayout(layout);
    }

}

QVector<QString> MainWindow::getViewListAttributesPriority(){
    QVector<QString> output;
    QAbstractItemModel* model = this->ui->attributesPriorityQueueWidget->model();
    for(qint16 i = 0; i < 10; i ++){
        output.push_back((QString) model->index(i, 0).data(Qt::DisplayRole).toString());
    }
    return output;
}

void MainWindow::updateOutputDices(const QVector<Dice> & inputDices){
    this->ui->Dice0->setText(inputDices[0].toQstring());
    this->ui->Dice1->setText(inputDices[1].toQstring());
    this->ui->Dice2->setText(inputDices[2].toQstring());
    this->ui->Dice3->setText(inputDices[3].toQstring());
    this->ui->Dice4->setText(inputDices[4].toQstring());
    this->ui->Dice5->setText(inputDices[5].toQstring());
    this->ui->Dice6->setText(inputDices[6].toQstring());
    this->ui->Dice7->setText(inputDices[7].toQstring());
    this->ui->Dice8->setText(inputDices[8].toQstring());
    this->ui->Dice9->setText(inputDices[9].toQstring());
}

void MainWindow::updateOutputQueue(const QVector<ATTRIBUTES> & inputAttributes){
    this->ui->At0->setText(translateATTRIBUTES(inputAttributes[0]));
    this->ui->At1->setText(translateATTRIBUTES(inputAttributes[1]));
    this->ui->At2->setText(translateATTRIBUTES(inputAttributes[2]));
    this->ui->At3->setText(translateATTRIBUTES(inputAttributes[3]));
    this->ui->At4->setText(translateATTRIBUTES(inputAttributes[4]));
    this->ui->At5->setText(translateATTRIBUTES(inputAttributes[5]));
    this->ui->At6->setText(translateATTRIBUTES(inputAttributes[6]));
    this->ui->At7->setText(translateATTRIBUTES(inputAttributes[7]));
    this->ui->At8->setText(translateATTRIBUTES(inputAttributes[8]));
    this->ui->At9->setText(translateATTRIBUTES(inputAttributes[9]));
}

void MainWindow::updateOutputQueueAndDices(const QVector<ATTRIBUTES> & inputAttributes, const QVector<Dice> & inputDices){
    if(inputAttributes.length() != 0){
        updateOutputDices(inputDices);
        updateOutputQueue(inputAttributes);
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

