#include <QMessageBox>
#include "sessionmanager.h"

SessionManager::SessionManager()
{
    //Create and link QStringListModel for characters
    characterModel = new QStringListModel();
    emit linkCharacterList(characterModel);

    defaultSessionName = "---";

    //Initialize empty session
    isActive = false;
    name = defaultSessionName;
    description = "Create or open a new session...";
    npcCount = 0;
    creationDate = QDate();
    characters.clear();

    updateInfo();

    //TODO: Check for last opened session
}

SessionManager::~SessionManager(){
    delete characterModel;
}

void SessionManager::updateInfo(){
    emit updateSessionInfo(*this);
}

void SessionManager::setSessionData(QString newName, QString newDescription, QDate newDate, qint16 newCount) {
    name = std::move(newName);
    description = std::move(newDescription);
    creationDate = newDate;
    npcCount = newCount;
}

void SessionManager::createCharacterModel() {
    QStringList strings;
    for(auto &character : characters){
        strings << character.toStr();
    }
    characterModel->setStringList(strings);
}

void SessionManager::saveCurrentSession(){
    // Break if there is no active session
    if(!isActive){
        emit tempStatusBar("Current session can't be saved.");
        return;
    }
    MemIO::saveSession(XmlSerialize());
    emit tempStatusBar("Session has been saved.");
}

void SessionManager::createNewSession(){
    saveCurrentSession();

    //Read user input for session name and description
    bool clickedOk = true;
    QString newName{};
    QString newDescription{};
    newName = QInputDialog::getText(nullptr, tr("New session"),
                                         tr("Session Name:"), QLineEdit::Normal, "", &clickedOk);
    if(!clickedOk || name.isEmpty()) {
        emit tempStatusBar("Failed to create a new session.");
        return;
    }
    newDescription = QInputDialog::getText(nullptr, tr("New session"),
                                         tr("Description:"), QLineEdit::Normal, "", &clickedOk);

    if(!clickedOk || description.isEmpty()) {
        emit tempStatusBar("Failed to create a new session.");
        return;
    }
    setSessionData(newName, newDescription, QDate::currentDate(), 0);
    //Clear character list
    characters.clear();
    characterModel->setStringList(QStringList());
    isActive = true;
    updateInfo();
    emit tempStatusBar("New session has been created.");
}

void SessionManager::closeCurrentSession() {
    saveCurrentSession();
    isActive = false;
    setSessionData(defaultSessionName, "Open or create a new session...", QDate(), 0);
    characters.clear();
    characterModel->setStringList(QStringList());
    updateInfo();
    emit tempStatusBar("Session has been closed.");
}

void SessionManager::openNewSession() {
    this->saveCurrentSession();

    QString sessionName = QFileDialog::getOpenFileName(nullptr,
                                                       "Choose session.",
                                                       MemIO::sessionsSavingFolder,
                                                       "XML files (*.xml)");
    QDomElement sessionElement = MemIO::loadSession(sessionName);
    if(!sessionElement.isNull()){
        XmlDeserialize(sessionElement);
        createCharacterModel();
        updateInfo();
        isActive = true;
        emit tempStatusBar("Session has been loaded.");
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Could not load session.");
        msgBox.exec();
    }
}

void SessionManager::addCharacter(const SessionCharacter &character) {
    for (auto &npc: characters) {
        if (npc.getUniqueID() == character.getUniqueID()) {
            emit tempStatusBar("This character is already in this session.");
            return;
        }
    }
    characters.append(character);
    emit tempStatusBar("Character has been added to session.");
    createCharacterModel();
    updateInfo();
}

void SessionManager::deleteCharacterFromSession(QModelIndex index) {
    if(index.row() == -1){
        emit tempStatusBar("No character has been selected.");
        return;
    }

    SessionCharacter npc = characters.at(index.row());
    QMessageBox box;
    box.setText("Are you sure you want to delete this character?");
    box.setInformativeText(npc.toStr());
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);
    int ret = box.exec();

    if (ret == 0x00004000){
        characters.removeAt(index.row());
        createCharacterModel();
        updateInfo();
        emit tempStatusBar("Character has been removed from session.");
    }else{
        emit tempStatusBar("Character has not been removed.");
    }
}

void SessionManager::listDoubleClicked(const QModelIndex &index) {
    emit loadCharacter(characters[index.row()]);
}

QDomElement SessionManager::XmlSerialize() const{
    // Create session element and add basic attributes
    QDomElement element = QDomDocument().createElement("session");
    element.setAttribute("name", this->name);
    element.setAttribute("description", this->description);
    element.setAttribute("creationDate", this->creationDate.toString());
    element.setAttribute("npcCount", this->npcCount);

    // Serialize all characters in this session
    QDomElement npcs = QDomDocument().createElement("characters");
    for(auto &npc : this->characters){
        npcs.appendChild(npc.XmlSerialize());
    }
    // Add serialized characters
    element.appendChild(npcs);

    element.setNodeValue(this->name);
    return element;
}

void SessionManager::XmlDeserialize(const QDomElement &element) {
    name = element.attribute("name", "-");
    description = element.attribute("description", "-");
    creationDate = QDate::fromString(element.attribute("creationDate", ""));
    npcCount = static_cast<qint16>(element.attribute("npcCount", "0").toInt());

    QDomElement character = element.firstChildElement().firstChildElement();
    characters.clear();
    while(!character.isNull()){
        SessionCharacter npc;
        npc.XmlDeserialize(character);
        characters.append(npc);
        character = character.nextSiblingElement();
    }
}
