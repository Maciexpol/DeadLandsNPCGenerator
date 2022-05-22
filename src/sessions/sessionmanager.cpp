#include "sessionmanager.h"

SessionManager::SessionManager() : _isActive(false)
{

}

void SessionManager::setActiveSession(const Session &session){
    this->activeSession = session;
    this->_isActive = true;
}

void SessionManager::saveCurrentSession(){
    // Break if there is no active session
    if(!_isActive) return;
    LSaver::save(activeSession);
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
    emit updateSessionInfo(this->activeSession);
}
