#include <QMessageBox>
#include "sessionmanager.h"

SessionManager::SessionManager() : _isActive(false)
{
    this->placeholderSession = Session("-",
                                       "Open or create a new session...",
                                       QDate::currentDate(),
                                       69);
    activeSession = placeholderSession;
    updateSessionInfo(activeSession);
}

void SessionManager::setActiveSession(const Session &session){
    this->activeSession = session;
    this->_isActive = true;
    emit updateSessionInfo(getActiveSession());
}

void SessionManager::saveCurrentSession(){
    // Break if there is no active session
    if(!_isActive) return;
    MemIO::saveSession(activeSession.XmlSerialize());
}

void SessionManager::createNewSession(){

    this->saveCurrentSession();

    bool clickedOk = true;
    QString name{};
    QString description{};

    name = QInputDialog::getText(nullptr, tr("New session"),
                                         tr("Session Name:"), QLineEdit::Normal, "", &clickedOk);
    if(!clickedOk || name.isEmpty()) return;

    description = QInputDialog::getText(nullptr, tr("New session"),
                                         tr("Description:"), QLineEdit::Normal, "", &clickedOk);

    if(!clickedOk || description.isEmpty()) return;


    Session newSession = Session(name, description, QDate::currentDate(), 0);
    this->setActiveSession(newSession);
}

void SessionManager::closeCurrentSession() {
    this->saveCurrentSession();
    activeSession = placeholderSession;
    _isActive = false;
    updateSessionInfo(activeSession);
}

void SessionManager::openNewSession() {
    this->saveCurrentSession();
    Session newSession = Session();
    // Get session name
    QString sessionName = QFileDialog::getOpenFileName(nullptr,
                                                       "Choose session.",
                                                       MemIO::sessionsSavingFolder,
                                                       "XML files (*.xml)");
    QDomElement sessionElement = MemIO::loadSession(sessionName);
    if(!sessionElement.isNull()){
        newSession.XmlDeserialize(sessionElement);
        setActiveSession(newSession);
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Could not load session.");
        msgBox.exec();
    }
}

void SessionManager::addCharacterToSession(const qint32 &id, const QString &name) {
    activeSession.addCharacter(id, name);
}
